#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ASCII_SIZE 128

typedef struct ctoi {
    u_int8_t alphabet_size;
    char mapping[ASCII_SIZE];
} ctoi_t;

ctoi_t *ctoi_create(char const *text) {
    ctoi_t *ctoi = malloc(sizeof *ctoi);
    memset(ctoi->mapping, 0, ASCII_SIZE);
    uint i, n = 0;
    for (i = 0; i < strlen(text); i++)
        ctoi->mapping[text[i]] = 1;
    for (i = 0; i < ASCII_SIZE; i++) {
        if (ctoi->mapping[i] == 0)
            ctoi->mapping[i] = -1;
        else {
            ctoi->mapping[i] = n;
            n++;
        }
    }
    ctoi->alphabet_size = n;
    return ctoi;
}

void ctoi_destroy(ctoi_t *ctoi) {
    free(ctoi);
}

u_int8_t ctoi_get_alphabet_size(ctoi_t *ctoi) {
    return ctoi->alphabet_size;
}

u_int8_t ctoi_map(ctoi_t *ctoi, char c) {
    if (c < 0) {
        printf("Error: char c = %d", c);
        exit(EXIT_FAILURE);
    }
    return ctoi->mapping[c];
}

