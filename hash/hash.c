#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include "generic_vector.h"


typedef struct _entry_t {
    char *key;
    char *value;
}entry_t;
typedef struct _hm_t {
    element **elements;
    int length;
}hm_t;


int hash(const char* str, int length){
    int val = 0;
int len=strlen(str);
for (int i = 0; i <len ; ++i) {
    val = 43 * val + str[i];
}
return (val % length);
}
// création d'un pointeur vers une hm
hm_t *hm_create(unsigned int length){
     hm_t * hashmap=malloc(sizeof(hm_t));
    hashmap->elements=malloc(sizeof(element*)*length);
    hashmap->length=length;
    
    for(int i =0;i<(int)length;i++){
        hashmap->elements[i]=lst_vector_init();
    }
    return hashmap;
}
// destruction de la hm et libération de la mémoire
void hm_destroy(hm_t **hm){
    for(int i=0; i<(*hm)->length;i++){
        lst_vector_empty(&(*hm)->elements[i]);
    }
    free((*hm)->elements);
    free(*hm);
}
entry_t * entry_create(const char *const key, const char *const value){
    entry_t* a=malloc(sizeof(entry_t));
    a->key=malloc(sizeof(char)*(strlen(key)+1));
    a->value=malloc(sizeof(char)*(strlen(value)+1));
    strcpy(a->key,key);
    strcpy(a->value,value);
    return a;
}
// insère la paire key-value dans la hm. si key est déjà présente
// écraser value dans la hm.
hm_t *hm_set(hm_t *hm, const char *const key, const char *const value){
    int pos=hash(key,hm->length);
    element* crt=hm->elements[pos];
    if(crt!=NULL){
        while(crt->next!=NULL){
        entry_t *tst=(entry_t*)(crt->data);
        if(!strcmp(tst->key,key)){
            strcpy(tst->value,value);
            return hm;
        }
        crt=crt->next;
        }
    }
    entry_t* ent=entry_create(key, value);
    lst_vector_push(&hm->elements[pos],ent);
    return hm;
    

}
// retourne la valeur associé à la clé, key
char *hm_get(const hm_t *const hm, const char *const key){
    int pos=hash(key,hm->length);
    element* crt=hm->elements[pos];
    while(crt->next!=NULL){
    entry_t *tst=(entry_t*)(crt->data);
    if(!strcmp(tst->key,key)){
        
        return tst->value;
    }
    crt=crt->next;
    }
    return NULL;
}
// retire une clé de la hm et la retourne
char *hm_rm(hm_t *hm, const char *const key){
    int pos=hash(key,hm->length);
    element* crt=hm->elements[pos];
    element* old_crt=crt;
    while(crt->next!=NULL){
    entry_t *tst=(entry_t*)(crt->data);
    if(!strcmp(tst->key,key)){
        char* my_key=malloc(sizeof(char)*80);
        strcpy(my_key,tst->key);
        old_crt->next=crt->next;
        free(crt->data);
        free(crt);
        return my_key;
    }
    old_crt=crt;
    crt=crt->next;
    }
    return NULL;
} 

// convertit la hm en chaîne de caractères
char *hm_to_str(const hm_t *const hm){
    char my_str[10000];
    for(int i =0; i<hm->length;i++){
        element * crt=hm->elements[i];
        while(crt->next!=NULL){
            entry_t* KV=(entry_t*)crt;
            strcat(my_str,KV->key);
            strcat(my_str,KV->value);
            
        }
    }
    char*bigstring=malloc(sizeof(char)*2000);
    strcpy(bigstring,my_str);
    return bigstring;
}
// affiche le contenu de la hm
void hm_print(const hm_t *const hm){
    for(int i =0; i<hm->length;i++){
        element * crt=hm->elements[i];
        while(crt!=NULL){
            entry_t* KV=(entry_t*)crt;
            printf("Key : %s   | ",KV->key);
            printf("Value : %s\n",KV->value);
            crt=crt->next;
        }
    }
}