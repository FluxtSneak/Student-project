#include <stdbool.h>

typedef struct _entry_t entry_t;
typedef struct _hm_t hm_t;

int hash(const char* str, int length);
// création d'un pointeur vers une hm
hm_t *hm_create(unsigned int length);
// destruction de la hm et libération de la mémoire
void hm_destroy(hm_t **hm);

entry_t * entry_create(const char *const key, const char *const value);
// insère la paire key-value dans la hm. si key est déjà présente
// écraser value dans la hm.
hm_t *hm_set(hm_t *hm, const char *const key, const char *const value);
// retourne la valeur associé à la clé, key
char *hm_get(const hm_t *const hm, const char *const key);
// retire une clé de la hm et la retourne
char *hm_rm(hm_t *hm, const char *const key); 

// convertit la hm en chaîne de caractères
char *hm_to_str(const hm_t *const hm);
// affiche le contenu de la hm
void hm_print(const hm_t *const hm);
