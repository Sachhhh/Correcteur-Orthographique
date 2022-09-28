#include "hashtable.h"

hashtable creer_hashtable(int n) { 
  hashtable tab;  
  tab.size = n ;
  tab.data = calloc (n,sizeof(maillon*)) ; 
    if(tab.data==NULL){
        printf("ERREUR D'ALLOCATION DE LA TABLE\n");
        exit(EXIT_FAILURE);
    }
  int i ;
  for (i=0 ; i<n ; i++) {
    tab.data[i] = NULL;
  }
  return tab;
}

void inserer_tete(char* mot,maillon** pl){
    maillon* liste=calloc(1,sizeof(*liste));
    liste->mot=strdup(mot);
    liste->suivant=*pl;
    *pl=liste;
}

void inserer_table(hashtable tab,char* mot){
    int h=hash(mot,T);
    maillon* p=tab.data[h];
        while(p!=NULL){
            if(strcasecmp(mot,p->mot)==0){
                printf("Le mot %s est deja dans l'arbre.\n",mot);
                return;
            }
            p=p->suivant;
        }
    inserer_tete(mot,&tab.data[h]);
}

unsigned long hash(char* mot,int n){
    unsigned long somme=0;
    int i;
    for(i=0; mot[i]!='\0';i++){
        somme=somme*31+tolower(mot[i]);
    }
    return somme%n;
}

bool rechercher_mot(hashtable tab,char* mot){
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

void liberer_liste(maillon** pl){
  maillon* l;
  while(*pl!=NULL){
    l=*pl;
    *pl=(*pl)->suivant;
    free(l->mot);
    free(l);
  }
}

void liberer_table(hashtable tab){
    int i=0;
    for (i=0;i<tab.size;i++){
        liberer_liste(&(tab.data[i]));
    }
    free(tab.data);
}

void afficher_table(hashtable tab){
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

hashtable lecture_dico(char* dictionnaire){
    FILE * f;
    hashtable tab=creer_hashtable(T);
    char mot[27];
    f=fopen(dictionnaire, "r");
    if(f==NULL){
        printf("Impossible d'ouvrir le fichier\n"); 
        exit(EXIT_FAILURE);
    }
    else {
    printf("Ouverture du fichier %s reussie\n",dictionnaire);
    }
    while(fgets(mot,27,f)!=NULL){
        inserer_table(tab,strtok(mot,"\r\n")); 
    } 
    fclose(f);
    return tab;
}

void verificateur_ortho(char* texte,hashtable dictionnaire){
    FILE * f;
    int compteur=0;
    char ligne[10000];
    f=fopen(texte, "r");
    if(f==NULL){printf("Impossible d'ouvrir le fichier\n"); exit(EXIT_FAILURE);}
    else printf("Ouverture du fichier %s reussie\n",texte);
     // La définitions de séparateurs connus.
    const char * separators = " \"?(),‘`'.-!:;\n";
    printf("Les mots suivants n'appartiennent pas au dictionnaire :\n");
    hashtable mots_non_presents=creer_hashtable(T);
    int i=0;
    while(fgets(ligne,10000,f)!=NULL){
        // On cherche à récupérer, un à un, tous les mots de la ligne
        // et on commence par le premier.
        char * mot = strtok (ligne,separators);
        while ( mot != NULL ) {
            if(i==10){
                printf("\n");
                i=0;
            }
            if (!rechercher_mot(dictionnaire,mot) && !rechercher_mot(mots_non_presents,mot)){
                i++;
                printf("%s ",mot);
                compteur++;
                inserer_table(mots_non_presents,mot);
                }
            // On récupère le mot suivant.
            mot = strtok (NULL,separators);
        }
    }  
    printf("\n"); 
    fclose(f);
    liberer_table(mots_non_presents);
    liberer_table(dictionnaire);
    printf("Les %d mots ci-dessus n'appartiennent pas au dictionnaire.\n",compteur);
}

int nombre_collisions(hashtable tab){
    int nb=0;
    int n=0;
    int i;
    for (i=0; i<tab.size; i++){
        maillon* p=tab.data[i];
        n=0;
        while(p!=NULL){
            p=p->suivant;
            n++;
        if(nb<n){
            nb=n;
            }
        }
    }   
    return nb;
}

