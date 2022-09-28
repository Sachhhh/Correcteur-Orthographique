#include "liste.h"

typedef struct noeud {
    char * radix;
    liste fils;
    bool fin_mot;
}noeud;

typedef noeud * arbre_radix;

noeud* creer_arbre_radix(char * radix);

void inserer_arbre(noeud** racine,char * mot);
char * supp_n_mot(char* mot, int n);

noeud* lecture_dico(char * dico);

bool rechercher_mot( arbre_radix arbre,char * mot);

void compresse(arbre_radix arb_r);
void affichage(noeud* arbre,char * prefix);
void afficher_arbre(noeud* arbre);
void libere_arbre(noeud* a);

void verificateur_ortho(char* texte,noeud* dictionnaire);

