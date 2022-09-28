#include "arbre_prefix2.h"

//Fonction qui alloue et retourne un arbre
noeud* creer_arbre(){
    noeud* arbre=malloc(sizeof(*arbre));
     if(arbre==NULL){
        printf("ERREUR D'ALLOCATION DE L'ARBRE\n");
        exit(EXIT_FAILURE);
    }
    arbre->fin_mot=false;
    int i;
    for(i=0; i<N; i++){
        arbre->fils[i]=NULL;
    }
    return arbre;
}

//Fonction qui permet d'insérer le mot signed_mot dans l'arbre *racine
void inserer_arbre(noeud** racine,char * signed_mot){
    //On caste le char en unsigned char pour ne pas avoir d'indice négatif
    unsigned char *mot=(unsigned char *)(signed_mot);
    if(*racine==NULL){
         *racine=creer_arbre();
    }
    noeud* p=*racine;
    int longeur=strlen(signed_mot);
    //On traite les lettres une par une pour ajouter le mot à l'arbre
    for (int i = 0; i < longeur; i++) {
        //Si la lettre n'est pas présente dans l'arbre, on l'ajoute
        if(p->fils[tolower(mot[i])]==NULL){
            p->fils[tolower(mot[i])]=creer_arbre(); 
        }
        //On desecend dans l'arbre avant d'ajouter la lettre suivante
        p=p->fils[tolower(mot[i])];
    }
    if(p->fin_mot){
        printf("Le mot %s est déjà dans l'arbre\n",mot);
        return;
    }
    //On indique que la dernière lettre correspond à la fin d'un mot grace au booléen
    else {
        p->fin_mot=true;
        return;
    }
}

//Fonction qui permet d'afficher tous les mots de l'arbre 
void afficher_arbre(noeud* arbre){
    if(arbre==NULL){
        printf("L'arbre est vide\n");
    }
    affichage(arbre,NULL,0);
}

void affichage(noeud* arbre,char * signed_prefix,int longueur){
    //On caste le char en unsigned char pour ne pas avoir d'indice négatif
    unsigned char *prefix=(unsigned char *)signed_prefix;
    char newprefix[longueur+2];
    memcpy(newprefix,prefix,longueur);
    newprefix[longueur+1]=0;
    //Si la lettre ajouté correspond à la fin d'un mot on affiche le mot 
    if(arbre->fin_mot){
        printf("%s\n",prefix);
    }
/*  On continue de descendre dans l'arbre même si on a affiché un mot puisque le mot affiché peut 
    être contenu dans un mot plus long (exemple: "abaissa" est contenu dans "abaissable") */ 
    int i;
    //On traite chaque fils  
    for (i=0; i< N; i++){
        if(arbre->fils[i]!=NULL){
            //On ajoute la lettre du noeud suivant à newprefix
            newprefix[longueur]=i;
            //On appel la fonction affichage pour l'arbre fils
            affichage(arbre->fils[i],newprefix,longueur+1);
        }
    }
}

//Fonction qui renvoie true si le mot recherché est dans l'arbre et false s'il ne l'est pas
bool rechercher_mot(noeud* arbre, char* signed_mot){
    if(arbre==NULL){
        return false;
    }
    //On caste le char en unsigned char pour ne pas avoir d'indice négatif
    unsigned char *mot=(unsigned char *)signed_mot;
    int longueur=strlen(signed_mot);
    noeud* p=arbre;
    int i;
    //On verifie que chaque lettre apparait dans le bon ordre dans l'arbre
    for(i=0; i<longueur ;i++){
        if(p->fils[tolower(mot[i])]==NULL){
            return false;
        }
        p=p->fils[tolower(mot[i])];
    }
/* On retourne directement le booleen fin de mot : si le mot est dans l'arbre alors le booléen 
    vaut vrai, si le mot correspond seulement au début d'un mot plus long le booléen vaut faux 
    (exemple 'abai' est contenu dans 'abaissa') donc 'abai' apparait dans l'arbre contenant 'abaissa'
    mais ce n'est pas un mot de l'arbre */
    return p->fin_mot;
}


void libere_arbre(noeud* a){
    int i=0;
    int j=0;
    for(i=0;i<N;i++){
        if(a->fils[i]!=NULL){
            libere_arbre(a->fils[i]);
            j++;
        }
    }
    free(a);
}

noeud* lecture_dico(char * dico){
    FILE * f;
    noeud* arbre=NULL;
    char mot[27];
    f=fopen(dico, "r");
    if(f==NULL){
        printf("Impossible d'ouvrir le fichier\n"); 
        exit(EXIT_FAILURE);
    }
    else printf("Ouverture du fichier %s reussie\n",dico);
    while(fgets(mot,27,f)!=NULL){
        inserer_arbre(&arbre,strtok(mot,"\n")); 
    } 
    fclose(f);
    return arbre;
}

void verificateur_ortho(char* texte,noeud* dictionnaire){
    FILE * f;
    int compteur=0;
    char ligne[10000];
    f=fopen(texte, "r");
    if(f==NULL){printf("Impossible d'ouvrir le fichier\n"); exit(EXIT_FAILURE);}
    else printf("Ouverture du fichier %s reussie\n",texte);
     // La définitions de séparateurs connus.
    const char * separators = " \"?(),‘`'.-!:;\n";
    printf("Les mots suivants n'appartiennent pas au dictionnaire :\n");
    noeud* mots_non_presents=NULL;
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
                inserer_arbre(&mots_non_presents,mot);
                }
            // On récupère le mot suivant.
            mot = strtok (NULL,separators);
        }
    }  
    printf("\n"); 
    libere_arbre(mots_non_presents);
    libere_arbre(dictionnaire);
    fclose(f);
    printf("Les %d mots ci-dessus n'appartiennent pas au dictionnaire.\n",compteur);
}