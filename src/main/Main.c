#include "../lib/Chiffrement.h"

/**
 * mClair = 0x000000
 * cleMaitre = 0x000000
 * mChiffre = 0xbb57e6
 * */
u8 test1() {
  u32 mClair = 0x000000;
  u32 cleMaitre = 0x000000;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0xbb57e6);
}

/**
 * mClair = 0xffffff
 * cleMaitre = 0x000000
 * mChiffre = 0x739293
 * */
u8 test2() {
  u32 mClair = 0xffffff;
  u32 cleMaitre = 0x000000;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0x739293);
}

/**
 * mClair = 0x000000
 * cleMaitre = 0xffffff
 * mChiffre = 0x1b56ce
 * */
u8 test3() {
  u32 mClair = 0x000000;
  u32 cleMaitre = 0xffffff;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0x1b56ce);
}

/**
 * cleMaitre = 0xf955b9
 * mClair = 0xd1bd2d
 * mChiffre = 0x47a929
 * */
u8 test4() {
  u32 mClair = 0xf955b9;
  u32 cleMaitre = 0xd1bd2d;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0x47a929);
}

int main(void) {
  printf("Test : %s", (test1()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test2()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test3()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test4()) ? "Succes\n" : "Echec\n");

  return 0;
}
