#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "arbre_prefix1.h"

int main(int argc, char* argv[]){
  if(argc!=3){
    printf("Veuillez saisir le fichier à tester et le ficgier contenant le dictionnaire\n");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));

  int repeat;

  printf("Combien de répétitions souhaitez vous faire ?\n>> ");
  scanf("%d", &repeat);

  long double sum1=0;
  long double moyenne1=0;

    for (int i=0; i<repeat; i++){
      long double cl = clock();
      lecture_dico((char *)argv[2]);
      cl = (clock()-cl)/(long double)CLOCKS_PER_SEC;
      sum1 += cl;
    }
  moyenne1 = (double)sum1/repeat;

  long double sum2=0;
  long double moyenne2=0;
 

    for (int i=0; i<repeat; i++){
      noeud* dico=lecture_dico(argv[2]);
      long double cl = clock();
      verificateur_ortho((char *)argv[1],dico);
      cl = (clock()-cl)/(long double)CLOCKS_PER_SEC;
      sum2 += cl;
    }
  moyenne2 = (double)sum2/repeat;
  printf("Temps moyen d'éxecution pour créer le dico sur %d répétitions avec l'arbre prefix : %.3Lf s\n",repeat,moyenne1);
  printf("Temps moyen d'éxecution pour verifier le texte sur %d répétitions avec l'arbre prefix : %.3Lf s\n",repeat,moyenne2);
  return EXIT_SUCCESS;
}

