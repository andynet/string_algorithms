#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

typedef struct suffix_tree suffix_tree_t;
typedef struct node node_t;

// externals
suffix_tree_t  *suffix_tree_create(char const *text);
void            suffix_tree_destroy(suffix_tree_t *st);
void            suffix_tree_print(suffix_tree_t *st);

// internals
void suffix_tree_insert(suffix_tree_t *st, char const *text);

node_t *node_create(uint start, uint length, uint alphabet_size);
void    node_destroy(node_t *node);
void    node_print(node_t *node);


#endif //SUFFIX_TREE_H
