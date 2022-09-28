#include "liste.h"
#include <ctype.h>

typedef struct noeud {
    unsigned char lettre;
    liste fils;
    bool fin_mot;
}noeud;

noeud* creer_arbre(char lettre);
void inserer_arbre(noeud** racine, char * signed_mot);
void affichage(noeud* arbre,char * prefix,int longueur);
void afficher_arbre(noeud* arbre);
bool rechercher_mot(noeud* arbre, char* signed_mot);
noeud* lettre_est_presente(noeud* arbre,char lettre);
noeud* lecture_dico(char * dico);
void verificateur_ortho(char* texte, noeud* dictionnaire);
void libere_arbre(noeud* a);
