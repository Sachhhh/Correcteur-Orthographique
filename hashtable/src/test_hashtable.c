#include "hashtable.h"

int main(int argc, char const *argv[]){

  if(argc!=2){
    printf("Veuillez saisir le fichier contenant le dictionnaire\n");
    exit(EXIT_FAILURE);
  }

  hashtable tab=creer_hashtable(T);
  afficher_table(tab);

  //Test d'insertions
  inserer_table(tab,"ARBRE");
  inserer_table(tab,"liste");
  inserer_table(tab,"radix");
  inserer_table(tab,"arborescense");
  inserer_table(tab,"prefix");
  inserer_table(tab,"arborer");
  inserer_table(tab,"liste");
  inserer_table(tab,"arbre");
  

  //Test de recherche
  printf("%d\n",rechercher_mot(tab, "arbre"));
  printf("%d\n",rechercher_mot(tab, "liste"));
  printf("%d\n",rechercher_mot(tab, "radix"));
  printf("%d\n",rechercher_mot(tab, "arbre"));
  printf("%d\n\n",rechercher_mot(tab,"arborescense"));
  printf("%d\n",rechercher_mot(tab, "zaertrh"));
  printf("%d\n",rechercher_mot(tab, "ra"));
  printf("%d\n",rechercher_mot(tab, "radi"));
  printf("%d\n",rechercher_mot(tab, "arbores"));
  printf("%d\n",rechercher_mot(tab, "scense"));
  printf("%d\n",rechercher_mot(tab, "a"));
  printf("%d\n",rechercher_mot(tab, "aRBre"));
  printf("%d\n",rechercher_mot(tab, "LISTE"));
  printf("%d\n",rechercher_mot(tab, "Radix"));
  printf("%d\n\n",rechercher_mot(tab,"arborescEnsE"));

  afficher_table(tab);

  //Affichage du dictionnaire
  hashtable dico=lecture_dico((char*)argv[1]);

  //Affichage du nombre de collisions maximal
  printf("%d\n",nombre_collisions(dico));

  liberer_table(dico);
  return 0;
}


