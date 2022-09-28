#include "arbre_radix.h"

int main(int argc, char const *argv[]){
  if(argc!=3){
    printf("Veuillez saisir le fichier à tester et le ficgier contenant le dictionnaire");
    exit(EXIT_FAILURE);
  }
  verificateur_ortho((char*)argv[1],lecture_dico((char*)argv[2]));
}
