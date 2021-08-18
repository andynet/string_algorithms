#include <unistd.h>
#include "functions.c"

enum Arguments {FASTA=0, OUT};
char **arg_parse(int argc, char **argv);

int main(int argc, char **argv) {
    // argc = 5;
    // char *argv_test[] = {
    //     "-f", "../data/mini.fasta",
    //     "-o", "../data/output.tsv"
    // };
    // argv = argv_test;

    char **args = arg_parse(argc, argv);

    FILE *fp;
    char *filename = args[FASTA];
    fp = fa_open(filename);
    uint numofrecords = get_number_of_records(fp);
    bool **bitvectors = get_bitvectors(fp, numofrecords);
    fclose(fp);

    float **dist_matrix = get_jaccard_distance_matrix(numofrecords, bitvectors);

    table_print(dist_matrix, numofrecords);
    exit(EXIT_SUCCESS);
}

void print_usage(char *pname) {
    fprintf(stderr, "Usage: %s -f <FASTA> -o <OUTPUT>\n", pname);
}

char **arg_parse(int argc, char **argv) {
    if (argc != 5) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    char **args = malloc(sizeof (*args) * 2);
    int opt;
    while ((opt = getopt(argc, argv, "f:o:")) != -1) {
        switch (opt) {
            case 'f': args[FASTA] = optarg; break;
            case 'o': args[OUT] = optarg; break;
            default: 
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    return args;
}
