#include "../src/suffix_tree.c"

int main(void) {
    node_t *root = node_create(0, 0, 3);
        node_t *node3 = node_create(5, 1, 3);  // $
        root->children[0] = node3;
        node_t *node1 = node_create(0, 1, 3);  // A
        root->children[1] = node1;
            node_t *node4 = node_create(3, 3, 3);  // AB$
            node1->children[0] = node4;
            node_t *node5 = node_create(1, 1, 3);  // B
            node1->children[1] = node5;
                node_t *node7 = node_create(5, 1, 3);  // $
                node5->children[0] = node7;
                node_t *node6 = node_create(2, 4, 3);  // AAB$
                node5->children[1] = node6;
        node_t *node2 = node_create(1, 1, 3);  // B
        root->children[2] = node2;
            node_t *node9 = node_create(5, 1, 3);  // $
            node2->children[0] = node9;
            node_t *node8 = node_create(2, 4, 3);  // AAB$
            node2->children[1] = node8;

    subtree_print(root, 0);
}
