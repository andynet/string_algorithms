#include "../src/suffix_tree.c"

int main(void) {
    char *text = "abaab$";
    suffix_tree_t *st = suffix_tree_create(text);
}
