#include <criterion/criterion.h>
#include <stdlib.h>
#include "../src/bmh.c"

Test(external, empty_test) {}
Test(external, no_match) {
    cr_assert(bmh("A", "BBB") == -1);
}
Test(external, match_at_the_beginning) {
    cr_assert(bmh("AB", "ABBBB") == 0);
}
Test(external, match_at_the_end) {
    cr_assert(bmh("AB", "BBBBAB") == 4);
}
Test(external, match_in_the_middle) {
    cr_assert(bmh("AB", "BBBABBBB") == 3);
}
Test(external, multiple_matches) {
    cr_assert(bmh("AB", "ABBAB") == 0);
    cr_assert(bmh("AB", "ABBAB") == 3);
}
Test(external, multiple_overlapping_matches) {
    cr_assert(bmh("AAA", "AAAA") == 0);
    cr_assert(bmh("AAA", "AAAA") == 1);
}
