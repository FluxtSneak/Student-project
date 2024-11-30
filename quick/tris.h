#include <stdlib.h>
#include <stdbool.h>


typedef struct _stack{
    int *data;
    int capacity;
    int sommet;
} stack;



void stack_init(stack *stk, int capacity);
void stack_destroy(stack *stk);
void stack_empile(stack *stk, int value);
int stack_depile(stack *stk);
int stack_count(stack *stk);
bool stack_isEmpty(stack *stk);
bool isSorted(int size, int tab[size], bool (*comp)(int, int));
bool stack_isFull(stack *stk);
void stack_transfert(stack *stk, stack *stk2);
bool greater(int32_t a, int32_t b);
bool smaller(int32_t a, int32_t b);
void swap_value(int32_t *ind1, int32_t *ind2);
void arraycopy(int32_t *sorted, const int32_t *const orig,int32_t nitems);
void sort(int32_t *sorted, const int32_t *const orig, int32_t nitems, bool (*comp)(int32_t, int32_t));
void quicksort(int size, int array[size], int first, int last,bool (*comp)(int, int));
int partition(int size, int array[size], int first, int last,bool (comp)(int, int));
void print_array(int32_t *arr, int32_t size);