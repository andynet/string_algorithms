#ifndef CTOI_H
#define CTOI_H
#include <stdlib.h>

typedef struct ctoi ctoi_t;

ctoi_t     *ctoi_create(char const *text);
void        ctoi_destroy(ctoi_t *ctoi);
u_int8_t    ctoi_get_alphabet_size(ctoi_t *ctoi);
u_int8_t    ctoi_map(ctoi_t *ctoi, char c);

#endif //CTOI_H
