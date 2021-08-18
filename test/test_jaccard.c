#include <criterion/criterion.h>
#include "../src/functions.c"

Test(tmp, test1) {}

Test(tmp, test_get_bitvector) {
    char *seq = "AAAA";
    uint lowest_val = get_lowest(2);
    uint size = (uint)pow(4, 2);

    bool bitvector1[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool *bitvector2 = get_bitvector(seq, lowest_val, size);
    for (int i=0; i < size; i++) {
        cr_assert(bitvector1[i] == bitvector2[i]);
    }
}

Test(suite, test_get_bitvector2) {
    char *seq = "TTTTTTTT";
    uint lowest_val = get_lowest(2);
    uint size = (uint)pow(4, 2);

    bool bitvector1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    bool *bitvector2 = get_bitvector(seq, lowest_val, size);
    for (int i=0; i < size; i++) {
        cr_assert(bitvector1[i] == bitvector2[i]);
    }
}

Test(suite, test_get_number_of_records) {
    FILE *fa;
    fa = fa_open("../data/mini.fasta");
    uint record_num = get_number_of_records(fa);
    cr_assert(record_num == 5);
    fa = fa_open("../data/ex1.fna");
    record_num = get_number_of_records(fa);
    cr_assert(record_num == 1);
}

