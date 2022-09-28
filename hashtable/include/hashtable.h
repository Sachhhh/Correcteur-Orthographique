#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define T 100000


typedef struct maillon{
    char* mot;
    struct maillon* suivant;
}maillon;

typedef struct hashtable{
  int size;
  maillon** data;
} hashtable;

/* crée et retourne une nouvelle table de m listes vides */
hashtable creer_hashtable(int n);
void inserer_tete(char* mot, maillon** pl);
void inserer_table(hashtable tab,char* mot);
void liberer_liste(maillon** pl);
void liberer_table(hashtable tab);
unsigned long hash(char* mot,int n);
bool rechercher_mot(hashtable tab,char* mot);
void afficher_table(hashtable tab);
hashtable lecture_dico(char* dictionnaire);
void verificateur_ortho(char* texte,hashtable);
int nombre_collisions(hashtable tab);