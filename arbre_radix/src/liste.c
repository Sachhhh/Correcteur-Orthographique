#include"liste.h"

void inserer_tete(struct noeud* nouvel_arbre, liste* pl){
    struct cellule *liste=calloc(1,sizeof(*liste));
    liste->arbre=nouvel_arbre;
    liste->suivante=*pl;
    *pl=liste;
}

void inserer_queue(struct noeud* nouvel_arbre, liste* pl){
  if(*pl==NULL){
    inserer_tete(nouvel_arbre,pl);
    return;
  }
  else {
    liste p=*pl;
    while(p->suivante!=NULL){
      p=p->suivante;
    }
    liste l=malloc(sizeof(struct cellule));
    l->arbre=nouvel_arbre;
    l->suivante=NULL;
    p->suivante=l;
  }
}

void liberer(liste* pl){
  liste l;
  while(*pl!=NULL){
    l=*pl;
    *pl=(*pl)->suivante;
    free(l); 
  }
}