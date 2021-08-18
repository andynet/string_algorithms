#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define ALPHABET_SIZE 4
#define ASCII_SIZE 128
#define EMPTY (-1)
#define K 2

typedef struct fasta_record {
    char *id;
    char *seq;
} fa_record;

void fa_record_print(fa_record *rec) {
    printf("%s\n", rec->id);
    printf("%s\n", rec->seq);
}

fa_record *fa_record_init(const char *id, const char *seq) {
    fa_record *rec = malloc(sizeof *rec);

    uint n = strlen(id);
    rec->id = malloc(sizeof (rec->id) * (n+1));
    strcpy(rec->id, id);

    uint m = strlen(seq);
    rec->seq = malloc(sizeof (rec->seq) * (m+1));
    strcpy(rec->seq, seq);

    return rec;
}

void fa_record_free(fa_record *rec) {
    free(rec->seq);
    free(rec->id);
    free(rec);
}

char *get_id(char *line) {
    for (uint i=0; i<strlen(line); i++) {
        if (line[i] == ' ') {
            line[i] = '\0';
        }
    }

    uint n = strlen(line);
    char *ret = malloc(sizeof (*ret) * (n+1));
    strcpy(ret, line);

    return ret;
}

fa_record *read_record(char **lineptr, size_t *n, FILE *fp) {
    char *id = get_id(*lineptr);
    ssize_t read = getline(lineptr, n, fp);
    if (read == -1) {
        printf("Error: cannot read line.");
        exit(EXIT_FAILURE);
    }
    uint seq_size = 1;
    char *seq = malloc(sizeof *seq * seq_size);
    memset(seq, 0, seq_size);
    uint i = 0;
    char *line = *lineptr;
    uint m;
    while ((m = strlen(line)) > 0 && !feof(fp) && line[0] != '>') {
        line[m-1] = '\0';
        m--;
        while (i + m >= seq_size) {
            seq_size *= 2;
            seq = realloc(seq, seq_size);
        }
        strcat(seq, line);
        i += m;
        read = getline(lineptr, n, fp);
    }
    if (ferror(fp)) {
        printf("Error while reading file.");
    }
    fa_record *rec = fa_record_init(id, seq);
    free(id);
    free(seq);
    return rec;
}

char *convert_toidx(char *str) {
    uint n = strlen(str);
    char *new = malloc(sizeof *new * (n+1)); 
    char *ctoidx = malloc(sizeof *ctoidx * ASCII_SIZE);
    for (uint i=0; i<ASCII_SIZE; i++) { ctoidx[i] = EMPTY; }
    ctoidx['A'] = 1;
    ctoidx['C'] = 2;
    ctoidx['G'] = 3;
    ctoidx['T'] = 4;
    for (uint i=0; i < n; i++) {
        new[i] = ctoidx[(uint)str[i]];
    }
    free(ctoidx);
    return new;
}

uint kmertopos(char *kmer) {
    uint res = 0;
    for (uint i=0; i < strlen(kmer); i++) {
        res *= ALPHABET_SIZE;
        res += kmer[i];
    }
    return res;
}

uint kmertoposnext(char *kmer, const char *prev_kmer, uint prev_value) {
    return prev_value - (prev_kmer[0] * (uint)pow(4, K-1)) + kmer[strlen(kmer)-1];
}

void print_num(char *num) {
    printf("num: ");
    for (uint i=0; i< strlen(num); i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
}

uint get_lowest(uint k) {
    uint res = 0;
    for (uint i=0; i < k; i++) {
        res *= ALPHABET_SIZE;
        res += 1;
    }
    return res;
}

void bitvector_print(bool *bitvector, uint size) {
    for (uint i=0; i<size; i++) printf("%d ", bitvector[i]);
    printf("\n");
}

bool **bitvectors_create(uint number) {
    bool **bitvectors = malloc(sizeof *bitvectors * number);
    return bitvectors;
}

float **table_create(uint n) {
    float **table = malloc(sizeof *table * n);
    for (uint i=0; i<n; i++) {
        table[i] = malloc(sizeof *table[i] * n);
        //for (uint j=0; j<n; j++) {
        //    table[i][j] = -1;
        //}
        memset(table[i], -1, sizeof *table[i] * n);
    }
    return table;
}

void table_print(float **table, uint n) {
    for (uint i=0; i<n; i++) {
        for (uint j=0; j<n; j++) {
            printf("%.4f\t", table[i][j]);  // float are precise to log10(2^24) ~ 7 decimal places
        }
        printf("\n");
    }
}

uint get_intersection(const bool *bitvector1, const bool *bitvector2, uint size) {
    uint res = 0;
    for (uint i=0; i<size; i++) {
        if (bitvector1[i] == true && bitvector2[i] == true)
            res++;
    }
    return res;
}

uint get_union(const bool *bitvector1, const bool *bitvector2, uint size) {
    uint res = 0;
    for (uint i=0; i<size; i++) {
        if (bitvector1[i] == true || bitvector2[i] == true)
            res++;
    }
    return res;
}

bool is_dna(char *s) {
    for (uint i=0; i<strlen(s); i++) {
        if (!(s[i] == 1 || s[i] == 2 || s[i] == 3 || s[i] == 4))
            return false;
    }
    return true;
}

float jaccard_dist(const bool *bitvector1, const bool *bitvector2, uint size) {
    uint inter_n = get_intersection(bitvector1, bitvector2, size);
    uint union_n = get_union(bitvector1, bitvector2, size);
    return (float)inter_n / (float)union_n;
}

bool *get_bitvector(char *seq, uint lowest_val, uint size) {
    bool *bitvector = malloc(sizeof *bitvector * size); // bitvector[i] points to the 0th element, which is bool
    memset(bitvector, false, size);
    char kmer[K+1];
    memset(kmer, 0, K+1);

    char *num = convert_toidx(seq);
    for (uint i=K; i <= strlen(seq); i++) {
        strncpy(kmer, &num[i-K], K);
        // printf("kmer: %x %x %x\n", kmer[0], kmer[1], kmer[2]);
        if (!is_dna(kmer)) { continue; }
        uint value = kmertopos(kmer) - lowest_val;   // TODO: change this to rolling hash
        bitvector[value] = true;
    }
    free(num);

    return bitvector;
}

FILE *fa_open(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File %s does not exist.", filename);
        exit(EXIT_FAILURE);
    }
    return fp;
}

uint get_number_of_records(FILE *fna) {
    char *lineptr = NULL;
    size_t n = 0;
    getline(&lineptr, &n, fna);
    uint record_num = 0;
    while (!feof(fna)) {
        if (lineptr[0] == '>') record_num++;
        getline(&lineptr, &n, fna);
    }
    free(lineptr);
    lineptr = NULL;
    fseek(fna, 0, SEEK_SET);
    return record_num;
}

bool **get_bitvectors(FILE *fp, uint numofrecords) {
    fa_record *rec;

    char *lineptr = NULL;
    size_t n = 0;
    ssize_t m = getline(&lineptr, &n, fp);  // https://code.woboq.org/userspace/glibc/stdio-common/getline.c.html
    if (m == -1) printf("Failed to read a line.");

    bool **bitvectors = bitvectors_create(numofrecords);

    uint lowest_val = get_lowest(K);
    uint bvsize = (uint)pow(4, K);

    uint rec_num = 0;
    while (!feof(fp)) {
        rec = read_record(&lineptr, &n, fp);
        bitvectors[rec_num] = get_bitvector(rec->seq, lowest_val, bvsize);
        rec_num++;
        fa_record_free(rec);
    }
    free(lineptr);
    lineptr = NULL;
    return bitvectors;
}

float **get_jaccard_distance_matrix(uint numofrecords, bool **bitvectors) {
    float **result = table_create(numofrecords);
    uint bvsize = (uint)pow(4, K);
    for (uint i=0; i<numofrecords; i++) {
        for (uint j=i; j<numofrecords; j++) {
            result[j][i] = result[i][j] = jaccard_dist(bitvectors[i], bitvectors[j], bvsize);
        }
    }
    return result;
}
