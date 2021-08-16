#include "../src/ctoi.h"
#include <stdio.h>

int main(void) {
    ctoi_t *ctoi = ctoi_create("AACGCGCGT");
    printf("%d\n", ctoi_get_alphabet_size(ctoi));
    printf("A = %d\n", ctoi_map(ctoi, 'A'));
    printf("C = %d\n", ctoi_map(ctoi, 'C'));
    printf("G = %d\n", ctoi_map(ctoi, 'G'));
    printf("T = %d\n", ctoi_map(ctoi, 'T'));
    printf("N = %d\n", ctoi_map(ctoi, 'N'));
    ctoi_destroy(ctoi);
    ctoi = NULL;
}
