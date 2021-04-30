#include "../lib/Chiffrement.h"

/**
 * cleMaitre = 0x000000
 * mClaire = 0x000000
 * mChiffre = 0xbb57e6
 * */
u8 test1() {
  u32 cleMaitre = 0x000000;

  //
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  // afficherSousCLe(sousCLe);
  // printf("testSousCle : %s\n", ( testSousCle(sousCLe) ? "Succes." : "Echec." ) );

  //
  u32 mClaire = 0x000000;
  // testChiffrementSubstitution(0xf0a8d4);
  // testChiffrementPermutation(0xf0a8d4);
  u32 mChiffre = fctDeChiffrement(mClaire, sousCLe);
  return (mChiffre == 0xbb57e6);
}

/**
 * cleMaitre = 0x000000
 * mClaire = 0xffffff
 * mChiffre = 0x739293
 * */
u8 test2() {
  u32 cleMaitre = 0xffffff;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClaire = 0x000000;
  u32 mChiffre = fctDeChiffrement(mClaire, sousCLe);
  return (mChiffre == 0x739293);
}

/**
 * cleMaitre = 0xf955b9
 * mClaire = 0xd1bd2d
 * mChiffre = 0x47a929
 * */
u8 test3() {
  u32 cleMaitre = 0xd1bd2d;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClaire = 0xf955b9;
  u32 mChiffre = fctDeChiffrement(mClaire, sousCLe);
  return (mChiffre == 0x47a929);
}

int main(void) {
  printf("Test : %s", (test1()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test2()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test3()) ? "Succes\n" : "Echec\n");

  return 0;
}
