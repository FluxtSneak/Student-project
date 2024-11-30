#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>     /* srand(), rand() */
#include <time.h>       /* time() */
#include <math.h>       /* log() */

void main(){
    srand(time(NULL));

    int max=0;
    printf("Bienvenue dans le nombre secret \nUn nombre sera choisi aléatoirement entre 0 et celui de votre choix \nQuel sera le nombre maximum ? ");
    scanf("%d", &max);
    
    int prop;
    int nb_rand = rand()%(max+1);
    int nb_prop=1;
    printf("Quelle est votre proposition ? ");
    scanf("%d",&prop);
    int optimal=1;
    

    while(prop!=nb_rand){
        
        if(prop>max||prop<0){
            printf("Le nombre entrer doit être compris entre 0 et %d. ",max);
        }
        else if(prop <nb_rand){
            nb_prop++;
            printf("Le nombre secret est plus grand ");
        }
        else if(prop >nb_rand){
            nb_prop++;
            printf("Le nombre secret est plus petit ");
        }
        printf("Essayez encore ");
        scanf("%d",&prop);

    }
    while(max>1){
        max/=2;
        optimal++;
    }
       
    printf("GG %d trouvé en %d propositions \n",nb_rand, nb_prop);
    printf("Le nombre optimal maximal de coups était %d\n", optimal);




}