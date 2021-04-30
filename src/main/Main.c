#include "../lib/Chiffrement.h"

void test1() {
  u32 cleMaitre = 0x000000;

  //
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  // afficherSousCLe(sousCLe);
  // printf("testSousCle : %s\n", ( testSousCle(sousCLe) ? "Succes." : "Erreur." ) );

  //
  u32 mClaire = 0x000000;
  // testChiffrementSubstitution(0xf0a8d4);
  // testChiffrementPermutation(0xf0a8d4);
  fctDeChiffrement(mClaire, sousCLe);
}

void test2() {
  u32 cleMaitre = 0xffffff;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClaire = 0x000000;
  fctDeChiffrement(mClaire, sousCLe);
}

void test3() {
  u32 cleMaitre = 0xd1bd2d;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClaire = 0xf955b9;
  fctDeChiffrement(mClaire, sousCLe);
}

int main(void) {
  test1(); // ok
  printf("\n\n");
  test2(); // pas ok
  printf("\n\n");
  test3(); // ok

  return 0;
}
