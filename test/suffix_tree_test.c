#include <criterion/criterion.h>
#include "../src/suffix_tree.c"

Test(core, empty_test) {}

Test(core, constructed_suffix_tree) {
    char *text = "abaab$";
    suffix_tree_t *st = suffix_tree_create(text);

    suffix_tree_destroy(&st);
}
