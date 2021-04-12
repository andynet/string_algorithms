#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "suffix_array.h"

char  *read_file(char *filename) {
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
char  *concat(char *str1, char *str2) {
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

