#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_args(char **argv, int argc);
char *read_file(char *filename);
char *concat(char *str1, char *str2);
char **create_suffixes(char *str);
static int suffix_cmp(const void *a, const void *b);
size_t *construct_SA(const char *text, char **suffixes);
void print_example(char *text, char **suffixes, size_t *suffix_array);
void save_SA(char *file, size_t *SA, size_t n);

typedef enum {IN=1, OUT} arg;

int main(int argc, char **argv) {
    parse_args(argv, argc);
    char *text = read_file(argv[IN]);
    char *new_text = concat(text, "$");
    char **suffixes = create_suffixes(new_text);
    qsort(suffixes, strlen(new_text), sizeof (char *), suffix_cmp);
    size_t *suffix_array = construct_SA(new_text, suffixes);
    print_example(new_text, suffixes, suffix_array);
    save_SA(argv[OUT], suffix_array, strlen(new_text));
    return 0;
}

char* read_file(char *filename) {
    FILE *in = fopen(filename, "r");
    if (!in) {
        printf("File cannot be opened.");
        exit(0);
    }

    char c;
    char *str = (char *) malloc(100 * sizeof (*str));
    int i = 0;
    while ((c = (char)fgetc(in)) != EOF) {
        str[i] = c;
        i++;
    }
    str[i] = '\0';

    int err = fclose(in);
    if (err) {
        printf("File did not close correctly.");
    }
    return str;
}

char *concat(char *str1, char *str2) {
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char **create_suffixes(char *str) {
    char **result = (char **) malloc(strlen(str) * sizeof (char *));
    for (int i=0; i < strlen(str); i++) {
        result[i] = (char *) malloc((strlen(str) - i) * sizeof (char));
        strcpy(result[i], (str + i));
    }
    return result;
}

static int suffix_cmp(const void *a, const void *b) {
    return strcmp(* (char * const *) a, * (char * const *) b);
}

size_t *construct_SA(const char *text, char **suffixes) {
    size_t *suffix_array = (size_t *) malloc(strlen(text) * sizeof (size_t));
    for (int i=0 ; i < strlen(text); i++ ) {
        suffix_array[i] = strlen(text) - strlen(suffixes[i]);
    }
    return suffix_array;
}

void print_example(char *text, char **suffixes, size_t *suffix_array) {
    printf("%s\n", text);
    for (int i=0; i < strlen(text); i++) {
        printf("%zu %s\n", suffix_array[i], suffixes[i]);
    }
}

void parse_args(char **argv, int argc){
    int opt;
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i': argv[IN] = optarg; break;
            case 'o': argv[OUT] = optarg; break;
            default:
                fprintf(stderr, "Usage: %s -i input.txt -o output.txt\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

void save_SA(char *filename, size_t *SA, size_t n) {
    FILE *out = fopen(filename, "w");
    if (!out) {
        printf("File cannot be opened.");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i < n; i++) {
        fprintf(out, "%zu ", SA[i]);
    }
    int err = fclose(out);
    if (err) {
        printf("File did not close correctly.");
        exit(EXIT_FAILURE);
    }
}


