Comp 1 : 

int foo(int a) {
    a += 3;
    return a;
}
void bar(int *a) {
    *a += 3;
}
void baz(int *a) {
    a[0] += 3;
}
int main() {
    int a = 5;
    a=foo(a);
    bar(&a);
    baz(&a);
}


Comp 2 : 

#include <stdio.h>
#include <stdlib.h>
char *foo(int a) {
    char *tab=malloc(sizeof(char)*a);
    for (int i = 0; i < a; ++i) {
        tab[i] = 'a';
    }
    return tab;
}
char *bar(int a) {
    char *tab = malloc(sizeof(char)*a);
    for (int i = 0; i < a; ++i) {
        tab[i] = 'a';
    }
    return tab;
}
void baz(char *tab, int b) {
    tab = malloc(sizeof(char)*b);
    for (int i = 0; i < b; ++i) {
        tab[i] = 'a';
    }
}
int main() {
    char *a = foo(4);
    char *b = bar(4);
    char *c;
    baz(c, 4);
    free(a);
    free(b);
    free(c);
}