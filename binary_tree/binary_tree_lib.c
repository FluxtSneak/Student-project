#include "binary_tree_lib.h"
#include <stdlib.h>


// Fonctions de création, destruction et affichage
// création d'un arbre vide (retourne NULL)
node_t *bst_create(){
    node_t* bst =NULL;
    return bst;
} 
node_t *bst_create_node(int val){
    node_t *new_node=malloc(sizeof(node_t));
    new_node->val=val;
    new_node->left=NULL;
    new_node->right=NULL;
    return new_node;
}
// détruit l'arbre et vide la mémoire
void bst_destroy(node_t *tree){
    if(tree==NULL){
        return;
    }    
    if(tree->left!=NULL){
        bst_destroy(tree->left);
    }
    if(tree->right!=NULL){
        bst_destroy(tree->right);
    }
    free(tree);
}

// affiche l'arbre (voir plus bas)
void bst_print(node_t *tree,int prof){
    if (tree == NULL) {
    return;
  }
  bst_print(tree->left, prof + 1);
  for (int i = 0; i < prof; i++) {
    printf("-------");
  }
  printf(" %d \n\n", tree->val);
  bst_print(tree->right, prof + 1);

}

// insertion de val dans l'arbre et retourne l'arbre (ou NULL si problème)
node_t *bst_insert(node_t *tree, int val){
    if(tree==NULL){
        tree=bst_create_node(val);
    }
    else if(val>tree->val){
        if(tree->right==NULL){
            tree->right=bst_create_node(val);            
        }
        else{
            bst_insert(tree->right, val);
        }
    }
    else if(val<=tree->val){
        if(tree->left==NULL){
            tree->left=bst_create_node(val);                  
        }
        else{
            bst_insert(tree->left, val);
        }
    }
    else{
        return NULL;
    }
       
    return tree;
    
}

bool bst_is_empty(node_t *tree){
    return NULL==tree;
}

// efface le premier élément contenant la valeur val dans l'arbre
// et retourne l'arbre (ne fait rien si val est absente)
node_t *bst_delete(node_t *tree, int val){
    if(!bst_is_empty(tree)){
        if(val>tree->val){
            tree->right=bst_delete(tree->right, val);
        }
        else if(val<tree->val){
            tree->left =bst_delete(tree->left, val);
        }
        else if(tree->left!=NULL&&tree->right!=NULL){
            node_t * next= bst_find_max_node(tree->right);
            tree->val=next->val;
            tree->right=bst_delete(next, next->val);
        }
        else{
            node_t* tmp=tree;
            if(tmp->left!=NULL){
                tree=tree->left;
            }
            else if(tmp->right!=NULL){
                tree=tree->right;
            }
            else{
                tree=NULL;
            }
            free(tmp);
        }        
    }
    return tree;
}

// la valeur val est-elle présente dans l'arbre?
bool bst_is_present(node_t *tree, int val){
    if(val<tree->val){
        bst_is_present(tree->left, val);
    }
    else if(val>tree->val){
        bst_is_present(tree->right, val);
    }
    if(val==tree->val){  
        return true;
    }
    return false;
}

// retourne le noeud où la valeur val se trouve (NULL si absent)
node_t *bst_search(node_t *tree, int val){
    if(val<tree->val){
        bst_search(tree->left,val);
    }
    if(val<tree->val){
        bst_search(tree->right,val);
    }
    if(val==tree->val){
        return tree;
    }
    return NULL;
}

// l'arbre est-il un arbre binaire de recherche?
bool bst_is_bst(node_t *tree){
    if(!(tree->val>tree->left->val)&&tree->left!=NULL){
        return false;
    }
    else if(!(tree->val<tree->right->val)&&tree->right!=NULL){
        return false;
    }
    else if(tree->left!=NULL){
        bst_is_bst(tree->left);
    }
    else if(tree->right!=NULL){
        bst_is_bst(tree->right);
    }
    return true;

}

// retourne le noeud avec la valeur minimale de l'arbre (NULL s'il y a pas)
node_t *bst_find_min_node(node_t *tree){
    if(tree==NULL){
        return NULL;
    }
    else if(tree->left!=NULL){
        return bst_find_min_node(tree->left);    
    }
    else{
        return tree;
    }
}

// retourne la valeur la plus petite stockée dans l'arbre (ou MIN_INT)
int bst_find_min(node_t *tree){
    return bst_find_min_node(tree)->val;
}

// retourne le noeud avec la valeur maximale de l'arbre (NULL s'il y a pas)
node_t *bst_find_max_node(node_t *tree){
    node_t* tree_out=tree;
    if(tree->right!=NULL){   
        tree_out=bst_find_max_node(tree->right);
        
    }
    return tree_out;
}

// retourne la valeur la plus grande stockée dans l'arbre (ou MAX_INT)
int bst_find_max(node_t *tree){
    return bst_find_max_node(tree)->val;
}