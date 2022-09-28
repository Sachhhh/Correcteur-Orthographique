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
hashtable creer_hash_table(int n);
void inserer_hash_tete(char* mot, maillon** pl);
void inserer_hash_table(hashtable tab,char* mot);
void liberer_hash_liste(maillon** pl);
void liberer_hash_table(hashtable tab);
unsigned long hash(char* mot,int n);
bool rechercher_hash_mot(hashtable tab,char* mot);
void afficher_hash_table(hashtable tab);
