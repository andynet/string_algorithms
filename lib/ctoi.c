#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctoi.h"

#define ASCII_SIZE 128

struct ctoi {
    u_int8_t alphabet_size;
    char mapping[ASCII_SIZE];
};

ctoi_t *ctoi_create(char const *text) {
    ctoi_t *ctoi = malloc(sizeof *ctoi);
    memset(ctoi->mapping, 0, ASCII_SIZE);
    uint i;
    char n = 0;
    for (i = 0; i < strlen(text); i++)
        ctoi->mapping[(uint)text[i]] = 1;
    for (i = 0; i < ASCII_SIZE; i++) {
        if (ctoi->mapping[i] == 0)
            ctoi->mapping[i] = -1;
        else {
            n++;
            ctoi->mapping[i] = n;
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
    return ctoi->mapping[(uint)c];
}

u_int8_t *ctoi_encode(ctoi_t *ctoi, char const *str) {
    uint n = strlen(str);
    u_int8_t *encoded_str = malloc(n + 1);

    for (uint i = 0; i < n; i++) {
        encoded_str[i] = ctoi_map(ctoi, str[i]);
    }

    encoded_str[n] = '\0';
    return encoded_str;
}

char *create_inverse_mapping(char const *mapping) {
    char *inverse = malloc(ASCII_SIZE);
    memset(inverse, 0, ASCII_SIZE);
    for (u_int8_t i = 0; i < ASCII_SIZE; i++) {
        if (mapping[i] < 0)
            continue;
        else
            inverse[(uint)mapping[i]] = (char)i;
    }
    return inverse;
}

char *ctoi_decode(ctoi_t *ctoi, u_int8_t const *encoded_str) {
    uint n = 0;
    while (encoded_str[n] != 0) n++;
    char *decoded_str = malloc(n + 1);

    char *imap = create_inverse_mapping(ctoi->mapping);
    for (uint i = 0; i < n; i++) {
        if (encoded_str[i] >= ASCII_SIZE)
            decoded_str[i] = ' ';
        else
            decoded_str[i] = imap[encoded_str[i]];
    }

    decoded_str[n] = '\0';
    free(imap);
    return decoded_str;
}

