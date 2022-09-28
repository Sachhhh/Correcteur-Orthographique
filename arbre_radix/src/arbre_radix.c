#include "../include/arbre_radix.h"
#include "../include/hashtable.h"
#include <ctype.h>


// Creer un arbre avec un seul caractère
noeud* creer_arbre_radix(char * radix){
    struct noeud* arbre=malloc(sizeof(*arbre));
    if(arbre==NULL){
        printf("ERREUR D'ALLOCATION DE L'ARBRE\n");
        exit(EXIT_FAILURE);
    }
    char * new_radix=NULL;
    new_radix=strdup(radix);
    arbre->radix=new_radix;
    arbre->fils=NULL;
    arbre->fin_mot=false;
    return arbre;
}

void inserer_arbre(noeud** arbre,char* mot){
    //printf("%s - ",mot);

    // Verification que l'arbre est non nul :
    if(*arbre==NULL){
        *arbre=creer_arbre_radix(" ");
    }

    // p va parcourir notre arbre :
    noeud* p=*arbre;
    liste q=p->fils;
    // Notre arbre n'a pas de fils, on creer un nv fils avec le mots 
    if(p->fils==NULL){
        inserer_tete(creer_arbre_radix(mot),&p->fils);
        p->fils->arbre->fin_mot=true;
        return;
    }
    

    int i=0;
    int longueur_mot=strlen(mot)-1;
  
    while(p->fils!=NULL){
        int longueur_radix=strlen(p->fils->arbre->radix)-1;

        // On compare lettre par lettre en commençant par le début du mot : 
        while(tolower(mot[i])==tolower(p->fils->arbre->radix[i])){
            // Cas 1 : Si nous avons comparé toutes les lettres du mot à ajouter et du radix trouver
            if(i==longueur_mot){
                  if(i==longueur_radix){
                        // On met a 1 le fin de mot;
                       if(p->fils->arbre->fin_mot){
                            printf("Le mot %s est déjà dans l'arbre.\n",mot);
                            p->fils=q;
                            return;
                        }
                        p->fils->arbre->fin_mot=true;
                        p->fils=q;
                        return;
                    }

                // Cas 2 : Si on a parcouru tout le mot mais pas tout le radix : 
                    // On doit rajouter un noeud avec notre bout de mot et ajouter la suite derriere
                liste fils=p->fils->arbre->fils;
                char * fin_radix=supp_n_mot(p->fils->arbre->radix,i+1);
                p->fils->arbre->radix=mot;
                p->fils->arbre->fils=NULL;
                //On ajoute le fils contenant le reste du radix du noeud découpé au noeud correspondant au prefixe commun
                inserer_tete(creer_arbre_radix(fin_radix),&p->fils->arbre->fils);
                // On transmet au noeud si le mot était finis;
                p->fils->arbre->fils->arbre->fin_mot=p->fils->arbre->fin_mot;
                //On remet la liste de fils du noeud découpé dans le noeud contenant la deuxième partie du radix
                p->fils->arbre->fils->arbre->fils=fils;
                //On indique que le noeud du mot correspond à la fin d'un mot
                p->fils->arbre->fin_mot=true;
                p->fils=q;
                return;
                
            }

            // Cas 3 : Si on a parcouru tout le radix mais pas tout le mot : 
            if(i==longueur_radix){
                mot=supp_n_mot(mot,longueur_radix+1);
                inserer_arbre(&(p->fils->arbre),mot);
                p->fils=q;
                return;
            }


            // On passe a la lettre suivante :
            i++;
        }

        // Cas 4 : Aucune lettre n'est en commun :
        if(i==0){
            // On regarde dans le prochain fils
           
            if(p->fils->suivante==NULL){
                // Si il n'y a pas de prochain fils alors on ajoute un nv fils 
                inserer_tete(creer_arbre_radix(mot),&q);
                q->arbre->fin_mot=true;
                p->fils=q;
                return;
            } 
            p->fils=p->fils->suivante;             
        }


        // Cas 5 : Aucun des deux mots n'est arrivé à la fin : 

        else {
            char * prefix_commun=strndup(mot, i);
            char * fils1=supp_n_mot(mot,i);
            char * fils2=supp_n_mot(p->fils->arbre->radix,i);
           
            //On stocke la liste des fils du noeud qu'on découpe
            liste fils=p->fils->arbre->fils;
            bool sauv_fin_mot=p->fils->arbre->fin_mot;
            //On met à jour la valeur du noeud correspondant au prefixe commun
            char * free_radix=p->fils->arbre->radix;
            p->fils->arbre->radix=prefix_commun;
            p->fils->arbre->fin_mot=false;
            //On vide la liste des fils du noeud correspondant au prefixe commun
            p->fils->arbre->fils=NULL;
            //On ajoute le fils contenant la fin du mot au noeud correspondant au prefixe commun
            inserer_tete(creer_arbre_radix(fils1),&p->fils->arbre->fils);
            //On indique que noeud correspond à la fin d'un mot
            p->fils->arbre->fils->arbre->fin_mot=true;
            //On ajoute le fils contenant le reste du radix du noeud découpé au noeud correspondant au prefixe commun
            inserer_tete(creer_arbre_radix(fils2),&p->fils->arbre->fils);
            //On remet la liste de fils du noeud découpé dans le noeud contenant la deuxième partie du radix
            p->fils->arbre->fils->arbre->fils=fils;
            p->fils->arbre->fils->arbre->fin_mot=sauv_fin_mot;
            p->fils=q;
            free(free_radix);
            return;
        }
    }            
}

char * supp_n_mot(char* mot, int n){
    char * new_mot=mot+n;
    return new_mot;
}



//Fonction qui permet d'afficher tous les mots de l'arbre 
void afficher_arbre(noeud* arbre){
    if(arbre==NULL){
        printf("L'arbre est vide.\n");
        return;
    }
    affichage(arbre," ");
}

void affichage(noeud* arbre,char * prefix){
    // printf("appelle de affichage\n");

    // printf("fin de mot pour %s , %d \n",prefix,arbre->fin_mot);

    //Si la lettre ajouté correspond à la fin d'un mot on affiche le mot 
    if(arbre->fin_mot){
        printf("%s\n",prefix);
    }
/*  On continue de descendre dans l'arbre même si on a affiché un mot puisque le mot affiché peut 
    être contenu dans un mot plus long (exemple: "abaissa" est contenu dans "abaissable") */ 
    //On traite chaque fils  
    while(arbre->fils!=NULL){
            //On ajoute le radix du noeud suivant à newprefix
            int longueur=strlen(prefix)+strlen(arbre->fils->arbre->radix)+1;
            char newprefix[longueur];
            memcpy(newprefix,prefix,strlen(prefix));
            int i;
            int j=0;
            for(i=strlen(prefix);i<longueur;i++){
                newprefix[i]=arbre->fils->arbre->radix[j];
                j++;
            }
            newprefix[longueur]='\0';
            //On appel la fonction affichage pour l'arbre fils
            affichage(arbre->fils->arbre,newprefix);
            arbre->fils=arbre->fils->suivante;
        }
}


bool rechercher_mot(noeud* arbre,char* mot){
    // Verification que l'arbre est non nul :
    if(arbre==NULL){
        return false;
    }
    // p va parcourir notre arbre :
    noeud* p=arbre;
    int i=0;
    int longueur_mot=strlen(mot)-1; 
    liste q=p->fils;
    while(p->fils!=NULL){
        int longueur_radix=strlen(p->fils->arbre->radix)-1;
        // On compare lettre par lettre en commençant par le début du mot : 
        while(tolower(mot[i])==tolower(p->fils->arbre->radix[i])){
            // Cas 1 : Si nous avons comparé toutes les lettres du mot à ajouter et du radix trouver
            if(i==longueur_mot){
                  if(i==longueur_radix){
                        // On met a 1 le fin de mot;
                       if(p->fils->arbre->fin_mot){
                            p->fils=q;
                            return true;
                        }
                        p->fils=q;
                        return false;
                    }
                // Cas 2 : Si on a parcouru tout le mot mais pas tout le radix : 
                    // On doit rajouter un noeud avec notre bout de mot et ajouter la suite derriere
                p->fils=q;
                return false;
            }
            // Cas 3 : Si on a parcouru tout le radix mais pas tout le mot : 
            if(i==longueur_radix){
                mot=supp_n_mot(mot,longueur_radix+1);
                noeud * new_recherche=p->fils->arbre;
                p->fils=q;
                return rechercher_mot(new_recherche,mot);
            }
            // On passe a la lettre suivante :
            i++;
        }
        // Cas 4 : Aucune lettre n'est en commun :
        if(i==0){
            // On regarde dans le prochain fils
            if(p->fils->suivante==NULL) {p->fils=q;return false;}
            p->fils=p->fils->suivante;     
        }
        // Cas 5 : Aucun des deux mots n'est arrivé à la fin : 
        else {p->fils=q;return false;}
    }  
    p->fils=q;
    return false;          
}


void libere_arbre(noeud* a){
    while(a->fils!=NULL) {
        libere_arbre(a->fils->arbre);
        liste sauv=a->fils;
        a->fils=a->fils->suivante;
        free(sauv);
    }

    if(a->fils==NULL){
        free(a->radix);
        free(a);
        return;
    } 
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
    char ligne[10000];
    f=fopen(texte, "r");
    if(f==NULL){printf("Impossible d'ouvrir le fichier\n"); exit(EXIT_FAILURE);}
    else printf("Ouverture du fichier %s reussie\n",texte);
     // La définitions de séparateurs connus.
    const char * separators = " \"?(),‘`'.-!:;\n";
    printf("Les mots suivants n'appartiennent pas au dictionnaire :\n");
    // noeud* mots_non_presents=NULL; /* Solution ou l'on insere les mots_non_presents à un arbre radix */
    hashtable mots_non_presents=creer_hash_table(T);  /* Solution ou l'on insere les mots_non_presents à un arbre radix */
    int i=0;
    int compteur=0;
    while(fgets(ligne,10000,f)!=NULL){
        // On cherche à récupérer, un à un, tous les mots de la ligne
        // et on commence par le premier.
        char * mot = strtok (ligne,separators);
        while ( mot != NULL ) {
            if(i==10){
                printf("\n");
                i=0;
            }
            if (!rechercher_mot(dictionnaire,mot) && !rechercher_hash_mot(mots_non_presents,mot)){
                i++;
                compteur++;
                printf("%s ",mot);
                //inserer_arbre(&mots_non_presents,mot); /* Solution ou l'on insere les mots_non_presents à un arbre radix */
                inserer_hash_table(mots_non_presents,mot); /* Solution ou l'on insere les mots_non_presents à un arbre radix */
                }
            // On récupère le mot suivant.
            mot= strtok (NULL,separators);
        }
    } 
    printf("\n"); 
    //afficher_arbre(mots_non_presents);
    // libere_arbre(mots_non_presents); /* Solution ou l'on insere les mots_non_presents à un arbre radix */
    liberer_hash_table(mots_non_presents); /* Solution ou l'on insere les mots_non_presents à une hashtable */
    libere_arbre(dictionnaire);
    fclose(f);
    printf("Les %d mots ci-dessus n'appartiennent pas au dictionnaire.\n",compteur);
}