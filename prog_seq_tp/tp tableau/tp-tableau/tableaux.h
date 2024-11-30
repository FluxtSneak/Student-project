#ifndef _TABLEAUX_H_
#define _TABLEAUX_H_

void fill_with_rand(int size, int tab[size]);
int find_smallest(int size, int tab[size]);
void swap(int size, int tab[size], int ind1, int ind2);
void swap_big_at_end(int size, int tab[size]);
int find(int size, int tab[size],int nb);
double average(int size, int tab[size]);
double variance(int size, int tab[size]);
void sort(int size, int tab[size]);
double find_median(int size, int tab[size]);
void show(int size, int tab[size]);
void init(int size, int tab[size]);
void check_tabs(int size ,int tab[size], int size2, int tab2[size2]);



#endif