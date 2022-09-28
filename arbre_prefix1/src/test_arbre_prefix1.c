#include "arbre_prefix1.h"

int main(int argc, char* argv[]){
  if(argc!=2){
    printf("Veuillez saisir le contenant le dictionnaire\n");
    exit(EXIT_FAILURE);
  }
    noeud* arbre=NULL;

    //Test d'insertions
    inserer_arbre(&arbre,"arbre");
    inserer_arbre(&arbre,"liste");
    inserer_arbre(&arbre,"radix");
    inserer_arbre(&arbre,"arborescense");
    inserer_arbre(&arbre,"prefix");
    inserer_arbre(&arbre,"arborer");
    inserer_arbre(&arbre,"liste");
    inserer_arbre(&arbre,"arbre");
    inserer_arbre(&arbre,"arbre");

    //Test de recherche
    printf("%d\n",rechercher_mot(arbre, "arbre"));
    printf("%d\n",rechercher_mot(arbre, "liste"));
    printf("%d\n",rechercher_mot(arbre, "radix"));
    printf("%d\n",rechercher_mot(arbre, "arbre"));
    printf("%d\n\n",rechercher_mot(arbre,"arborescense"));
    printf("%d\n",rechercher_mot(arbre, "zaertrh"));
    printf("%d\n",rechercher_mot(arbre, "ra"));
    printf("%d\n",rechercher_mot(arbre, "radi"));
    printf("%d\n",rechercher_mot(arbre, "arbores"));
    printf("%d\n",rechercher_mot(arbre, "scense"));
    printf("%d\n",rechercher_mot(arbre, "a"));
    printf("%d\n",rechercher_mot(arbre, "aRBre"));
    printf("%d\n",rechercher_mot(arbre, "LISTE"));
    printf("%d\n",rechercher_mot(arbre, "Radix"));
    printf("%d\n\n",rechercher_mot(arbre,"arborescEnsE"));

    afficher_arbre(arbre);
    
    //Affichage du dictionnaire
    afficher_arbre(lecture_dico((char*)argv[1]));
    
    noeud* dico=lecture_dico((char*)argv[1]);
    libere_arbre(dico);
}
   