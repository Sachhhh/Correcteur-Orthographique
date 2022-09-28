#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define N 256

typedef struct noeud {
    struct noeud* fils[N];
    bool fin_mot;
}noeud;

noeud* creer_arbre();
void inserer_arbre(noeud** racine, char * mot);
void affichage(noeud* arbre,char * prefix,int longueur);
void afficher_arbre(noeud* arbre);
bool rechercher_mot(noeud* arbre, char* mot);
noeud* lecture_dico(char * dico);
void verificateur_ortho(char* texte, noeud* dictionnaire);
void libere_arbre(noeud* a);



