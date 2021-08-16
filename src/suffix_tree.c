#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node_t;
struct node {
    uint start;
    uint end;
    node_t *children;
};

typedef struct suffix_tree suffix_tree_t;
struct suffix_tree {
    char *text;
    node_t *root;
};

// externals
suffix_tree_t  *suffix_tree_create(char const *text);
void            suffix_tree_destroy(suffix_tree_t **st);
void            suffix_tree_print(suffix_tree_t *st);

// internals
void suffix_tree_insert(suffix_tree_t *st, char const *text);

suffix_tree_t *suffix_tree_create(char const *text) {
    suffix_tree_t *st = malloc(sizeof *st);
    st->text = malloc(strlen(text) + 1);
    strcpy(st->text, text);

    node_t *node = malloc(sizeof *node);
    node->start = 0;
    node->end = 0;
    node->children = NULL;
    st->root = node;

    char *suffix = malloc(strlen(text));
    for (uint i = 0; i < strlen(text); i++) {
        strcpy(suffix, text+i);
        // printf("%s\n", suffix);
        suffix_tree_insert(st, suffix);
    }
    return st;
}

void suffix_tree_insert(suffix_tree_t *st, char const *text) {

}

