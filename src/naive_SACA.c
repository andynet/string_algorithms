#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suffix_array.h"   // why this can not include suffix_cmp function?

typedef enum {IN=1, OUT} arg;
void parse_args(char **argv, int argc);
static int suffix_cmp(const void *a, const void *b);

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

static int suffix_cmp(const void *a, const void *b) {
    return strcmp(* (char * const *) a, * (char * const *) b);
}
