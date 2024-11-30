#include <stdio.h>
#include <stdbool.h>

bool bar(void *elem1, void *elem2){
    return (*(double*)elem1>*(double *)elem2);
}

void *foo(void *tab, int n_items, int s_items, bool (*bar)(void *, void *)) {
    if (n_items <= 0 || s_items <= 0 || NULL == tab) {
        return NULL;
    }

    void *elem = tab;
    for (int i = 1; i < n_items; ++i) {
        // void pointer arithmetics is illegal illegal in C
        void *tmp_elem = (void *)((char *)tab + i*s_items);

        if (bar(elem, tmp_elem)) {
            elem = tmp_elem;
        }
    }
    return elem;
}

int main(){
    double tab[5]={-1,2,3,4,5};

    double *yes =foo(tab, 5,sizeof(double),bar);
    printf("%f \n",*yes);
    

return 0;
}