#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct _node_t {
int val;
struct _node_t *left;
struct _node_t *right;
} node_t;


// Fonctions de création, destruction et affichage
node_t *bst_create();
node_t *bst_create_node(int val);
void bst_destroy(node_t *tree);
bool bst_is_empty(node_t *tree);
void bst_print(node_t *tree, int prof);
node_t *bst_insert(node_t *tree, int val);
node_t *bst_delete(node_t *tree, int val);
bool bst_is_present(node_t *tree, int val);
node_t *bst_search(node_t *tree, int val);
bool bst_is_bst(node_t *tree);
node_t *bst_find_min_node(node_t *tree);
int bst_find_min(node_t *tree);
node_t *bst_find_max_node(node_t *tree);
int bst_find_max(node_t *tree);
