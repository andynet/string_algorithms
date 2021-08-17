#include <criterion/criterion.h>
#include <stdio.h>
#include "../src/ctoi.h"

Test(core, empty_test) {}

Test(core, ctoi_creates_correct_map) {
    ctoi_t *ctoi = ctoi_create("ACGTGCA");
    cr_assert(ctoi_get_alphabet_size(ctoi) == 4);
    cr_assert(ctoi_map(ctoi, 'A') == 1);
    cr_assert(ctoi_map(ctoi, 'C') == 2);
    cr_assert(ctoi_map(ctoi, 'G') == 3);
    cr_assert(ctoi_map(ctoi, 'T') == 4);
    cr_assert(ctoi_map(ctoi, 'X') == 255);

    ctoi_destroy(ctoi);
    ctoi = NULL;
}

Test(core, ctoi_encoded_can_be_decoded) {
    char *str = "ACGTGCA";
    ctoi_t *ctoi = ctoi_create(str);

    u_int8_t *encoded = ctoi_encode(ctoi, str);
    char *decoded = ctoi_decode(ctoi, encoded);
    cr_assert(strcmp(str, decoded) == 0);

    free(encoded);
    free(decoded);
    ctoi_destroy(ctoi);
    ctoi = NULL;
}

Test(core, unknown_letters_are_decoded_into_space) {
    ctoi_t *ctoi = ctoi_create("ACGT");

    u_int8_t *encoded = ctoi_encode(ctoi, "ACGTNTGCA");
    char *decoded = ctoi_decode(ctoi, encoded);
    char *expected = "ACGT TGCA";
    cr_assert(strcmp(decoded, expected) == 0);

    free(encoded);
    free(decoded);
    ctoi_destroy(ctoi);
    ctoi = NULL;
}
