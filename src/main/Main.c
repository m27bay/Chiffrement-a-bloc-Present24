#include "../lib/Test.h"

void parseChoix(int argc, char *argv[]) {
  if(argc == 4) {
    if(strcmp(argv[1], "-c") == 0) {
      u32 mClair = strtol(argv[2], NULL, 16);
      u32 cleMaitre = strtol(argv[3], NULL, 16);

      u32 sousCLe[11];
      cadencementDeCle(sousCLe, cleMaitre);

      printf("PRESENT24_\033[1;32m%06x\033[0m_(%06x) = %06x.\n", cleMaitre, mClair, fctDeChiffrement(mClair, sousCLe));
    }
    else if(strcmp(argv[1], "-d") == 0) {
      u32 mChiffre = strtol(argv[2], NULL, 16);
      u32 cleMaitre = strtol(argv[3], NULL, 16);

      u32 sousCLe[11];
      cadencementDeCle(sousCLe, cleMaitre);

      printf("%06x = PRESENT24_\033[1;31m%06x\033[0m_(%06x).\n", mChiffre, cleMaitre, fctDeDeChiffrement(mChiffre, sousCLe));
    }
    else {
      printf("Option inconnue.\n");
    }
  }
  else if(argc == 6) {
    if(strcmp(argv[1], "-a") == 0) {
      printf("\t\033[1;34m>> Debut attaque <<\033[0m\n");
      attaque2Present24(strtol(argv[2], NULL, 16), strtol(argv[3], NULL, 16), strtol(argv[4], NULL, 16), strtol(argv[5], NULL, 16));
      printf("\t\033[1;34m>> fin attaque <<\033[0m\n");
    }
    else {
      printf("Option inconnue.\n");
    }
  }
  else {
    printf("Utilisation : \n");
    printf("-c message cleMaitre : Pour chiffer\n");
    printf("-d message cleMaitre : Pour dechiffer\n");
    printf("-a m1 c1 m2 c2 : Pour attaquer\n");
    return;
  }
}

int main(int argc, char *argv[]) {
  printf("\n");
  parseChoix(argc, argv);
  printf("\n");
  
  return 0;
}
