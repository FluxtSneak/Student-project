
#include "quad_tree.h"

int main(int argc, char** argv) {
   //control des arguments et assignation
   if (argc < 2) {
      printf("Veuillez spécifier un nom pour le fichier d'entrée et de sortie'!");
      return EXIT_FAILURE;
   }
   if (argc < 2) {
      printf("Il manque un argument à votre programme !");
      return EXIT_FAILURE;
   }
   char *filenameIn=argv[1];
   char *filenameOut=argv[2];

   //ouverture fichier pgm et création de l'arbre
   node *tree_img = tree_from_file(filenameIn);
   average(tree_img);
   //Transformations :
   //choix de la symétrie
   printf("Choisissez le type de symétrie à faire subire à votre image 0, 1, 2 ou 3 :\n0: Pas de symétrie\n1: Horizontale\n2: Verticale \n3: Centrale\n");
   int ans;
   scanf("%d",&ans);
   while((ans!=0)&&(ans!=1)&&(ans!=2)&&(ans!=3)){ //vérification que l'utilisateur ne soit pas un petit rigolo
      printf("%d\n",ans);
      printf("Veuillez choisir parmis les propositions !\n");
      scanf("%d",&ans);
   }
   symetry(tree_img, ans);

   //choix du taux de compression
   printf("Choisissez le seuil d'erreur pour votre compression \nEntre 0.0 et 3.0\n");
   double seuil;
   scanf("%lf",&seuil);
   while((seuil>3)||(seuil<0)){ //vérification que l'utilisateur ne soit pas un petit rigolo
      printf("Votre seuil n'est pas valide.\nChoisissez en un entre 0 et 3\n");
      scanf("%lf",&seuil);
   }
   int oldSize=nbNodes(tree_img);
   compress(tree_img, seuil);
   int newSize=nbNodes(tree_img);
   printf("Votre image a été compressée à %.2f%%\n", compressRate(oldSize, newSize));
   //écriture du nouveaux fichier et clean de l'arbre
   tree2file(tree_img, filenameOut);
   tree_destroy(tree_img);
   return 0;
}