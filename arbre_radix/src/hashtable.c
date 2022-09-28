#include "hashtable.h"

hashtable creer_hash_table(int n) { 
  hashtable tab;  
  tab.size = n ;
  tab.data = calloc (n,sizeof(maillon*)) ; 
  int i ;
  for (i=0 ; i<n ; i++) {
    tab.data[i] = NULL;
  }
  return tab;
}

void inserer_hash_tete(char* mot,maillon** pl){
    maillon* liste=calloc(1,sizeof(*liste));
    liste->mot=strdup(mot);
    liste->suivant=*pl;
    *pl=liste;
}

void inserer_hash_table(hashtable tab,char* mot){
    int h=hash(mot,T);
    maillon* p=tab.data[h];
        while(p!=NULL){
            if(strcasecmp(mot,p->mot)==0){
                printf("Le mot %s est deja dans l'arbre.\n",mot);
                return;
            }
            p=p->suivant;
        }
    inserer_hash_tete(mot,&tab.data[h]);
}

unsigned long hash(char* mot,int n){
    unsigned long somme=0;
    int i;
    for(i=0; mot[i]!='\0';i++){
        somme=somme*31+tolower(mot[i]);
    }
    return somme%n;
}

bool rechercher_hash_mot(hashtable tab,char* mot){
    int h=hash(mot,T);
    maillon* p=tab.data[h];
    while(p!=NULL){
        if(strcasecmp(p->mot,mot)==0){
            return true;
        }
        p=p->suivant;
    }
    return false;
}

void liberer_hash_liste(maillon** pl){
  maillon* l;
  while(*pl!=NULL){
    l=*pl;
    *pl=(*pl)->suivant;
    free(l->mot);
    free(l);
  }
}

void liberer_hash_table(hashtable tab){
    int i=0;
    for (i=0;i<tab.size;i++){
        liberer_hash_liste(&(tab.data[i]));
    }
    free(tab.data);
}

void afficher_hash_table(hashtable tab){
    int i;
    int j=1;
    for(i=0; i<tab.size; i++){
        maillon* p=tab.data[i];
        while(p!=NULL){
            printf("%s\n",p->mot);
            p=p->suivant;
            j=0;
        }
    }
    if(j==1){
        printf("La table est vide.\n");
    }
}
