#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct noeud;

struct cellule {
    struct noeud* arbre; 
    struct cellule* suivante;
};

typedef struct cellule* liste;

void inserer_tete(struct noeud* nouvel_arbre, liste* pl);
void inserer_queue(struct noeud* nouvel_arbre, liste* pl);
void liberer(liste* pl);