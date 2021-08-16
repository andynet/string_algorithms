#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 4

typedef struct node node_t;
struct node {
    uint start;
    uint length;
    uint n_children;
    node_t **children;
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
node_t *node_create(uint start, uint length, uint alphabet_size);
void    node_destroy(node_t **node);
void    node_print(node_t *node);

node_t *node_create(uint start, uint length, uint alphabet_size) {
    node_t *node = malloc(sizeof *node);
    node->start = start;
    node->length = length;
    node->n_children = alphabet_size;
    node->children = malloc(sizeof *(node->children) * alphabet_size);
    for (uint i = 0; i < alphabet_size; i++) node->children[i] = NULL;
    return node;
}

void node_destroy(node_t **node) {
    free((*node)->children);
    free((*node));
    (*node) = NULL;
}

void node_print(node_t *node) {
    printf("%p %2d %2d\t", node, node->start, node->length);
    for (uint i = 0; i < node->n_children; i++) printf("%p\t", node->children[i]);
    printf("\n");
}

void subtree_print(node_t *node, uint depth) {
    for (uint i = 0; i < depth; i++) printf("\t");
    node_print(node);
    for (uint i = 0; i < node->n_children; i++) {
        if (node->children[i] != NULL) subtree_print(node->children[i], depth + 1);
    }
}

void suffix_tree_insert(suffix_tree_t *st, char const *text);

suffix_tree_t *suffix_tree_create(char const *text) {
    suffix_tree_t *st = malloc(sizeof *st);
    st->text = malloc(strlen(text) + 1);
    strcpy(st->text, text);

    node_t *node = node_create(0, 0, 4);
    st->root = node;

    char *suffix = malloc(strlen(text));
    for (uint i = 0; i < strlen(text); i++) {
        strcpy(suffix, text+i);
        // printf("%s\n", suffix);
        suffix_tree_insert(st, suffix);
    }
    return st;
}

uint ctoidx(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return 4;
    }
}

void suffix_tree_insert(suffix_tree_t *st, char const *text) {
    if (st->root->children == NULL) {
        st->root->children = malloc((sizeof *(st->root->children)) * ALPHABET_SIZE);
        for (uint i = 0; i < ALPHABET_SIZE; i++) st->root->children = NULL;
    }
    node_t *current;
    uint pos = 0;
    current = st->root;
    if (&current->children[ctoidx(text[pos])] == NULL) {

    }

    for (uint i = 0; i < strlen(text); i++) {

    }
}

