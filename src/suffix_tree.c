#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/ctoi.h"
#include "suffix_tree.h"

#define ALPHABET_SIZE 4

struct node {
    uint start;
    uint length;
    uint n_children;
    node_t **children;
};

struct suffix_tree {
    char *text;
    ctoi_t *ctoi;
    node_t *root;
};

node_t *node_create(uint start, uint length, uint alphabet_size) {
    node_t *node = malloc(sizeof *node);
    node->start = start;
    node->length = length;
    node->n_children = alphabet_size;
    node->children = malloc(sizeof node->children * alphabet_size);
    for (uint i = 0; i < alphabet_size; i++) node->children[i] = NULL;
    return node;
}

void node_destroy(node_t *node) {
    free(node->children);
    free(node);
}

void node_print(node_t *node) {
    printf("%p %2d %2d\t", (void *)node, node->start, node->length);
    for (uint i = 0; i < node->n_children; i++) printf("%p\t", (void *)node->children[i]);
    printf("\n");
}

void subtree_print(node_t *node, uint depth) {
    for (uint i = 0; i < depth; i++) printf("\t");
    node_print(node);
    for (uint i = 0; i < node->n_children; i++) {
        if (node->children[i] != NULL) subtree_print(node->children[i], depth + 1);
    }
}

suffix_tree_t *suffix_tree_create(char const *text) {
    suffix_tree_t *st = malloc(sizeof *st);
    st->text = strdup(text);
    st->ctoi = ctoi_create(text);
    st->root = node_create(0, 0, ctoi_get_alphabet_size(st->ctoi));

    for (uint i = 0; i < strlen(text); i++) {
        suffix_tree_insert(st, text + i);
    }
    return st;
}

void node_insert_child(node_t *node, char const *text, uint pos, ctoi_t *ctoi) {
    node_t *child;
    child = node->children[ctoi_map(ctoi, text[pos]) - 1];
    if (child == NULL) {
        // node_insert_child
        uint start = node->start + node->length;
        uint length = strlen(text + pos);
        node_t *new_node = node_create(start, length, ALPHABET_SIZE);
        child = new_node;
    } else {
        if (strncmp(&text[child->start], &text[pos], child->length) == 0) {
            node = child;
            node_insert_child(node, text, pos + child->length, ctoi);
        } else {
            // find ho many characters match
            uint n_matching = 2; // TODO: slowscan(&text[child->start], &text[pos], child->length)
            // split child
            uint s1 = child->start;
            uint l1 = n_matching;
            uint s2 = s1 + l1;
            uint l2 = child->length - l1;
            node_destroy(child);
            child = node_create(s1, l1, ALPHABET_SIZE);
            child->children[ctoi_map(ctoi, text[s1 + l1]) - 1]
                = node_create(s2, l2, ALPHABET_SIZE);
            // add another node
            child->children[ctoi_map(ctoi, text[pos + l1]) - 1]
                = node_create(pos + l1, strlen(text) - pos - l1, ALPHABET_SIZE);
        }
    }
}

void suffix_tree_insert(suffix_tree_t *st, char const *text) {
    node_insert_child(st->root, text, 0, st->ctoi);
}
