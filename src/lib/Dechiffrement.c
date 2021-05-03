#include "Dechiffrement.h"

u8 inverseSubstitution(const u8 sousEtat) {
  for(u8 i = 0; i < 16; ++i) {
    if(tabSubstitution[i] == sousEtat) {
      return i;
    }
  }
  return 0;
}

u32 dechiffrementSubstitution(u32 etat) {
  // printf("dechiffrementSubstitution, etat : %06x\n", etat);
  u32 nouvEtat = 0;
  u8 sousEtat;

  for(size_t i = 0; i < 6; ++i) {
    sousEtat = (etat & 0xf);
    nouvEtat |= (inverseSubstitution(sousEtat) << (4 * i));
    etat >>= 4;
  }

  // printf("dechiffrementSubstitution, nouvEtat : %06x\n", nouvEtat);
  return nouvEtat;
}

u8 inversePermutation(const u8 i) {
  for(u8 j = 0; j < 24; ++j) {
    if(tabPermutation[j] == i) {
      return j;
    }
  }
  return 0;
}

u32 dechiffrementPermutation(const u32 etat) {
  u32 nouvEtat = 0;
  u32 bitEtat, bitNouvEtat;
  u32 masque = 1;

  for(u8 i = 0; i < 24; ++i) {
    bitEtat = (etat >> i) & masque;
    bitNouvEtat = (bitEtat << inversePermutation(i)); 
    nouvEtat |= bitNouvEtat;
  }

  // printf("dechiffrementPermutation, etat : %06x\n", etat);
  // printf("dechiffrementPermutation, nouvEtat : %06x\n", nouvEtat);
  return nouvEtat;
}

u32 fctDeDeChiffrement(const u32 mChiffre, const u32 sousCle[nbrSousCle]) {
  printf("Message chiffre : %06x\n", mChiffre);
  u32 etat = mChiffre, mClair;
  i32 i = nbrSousCle - 1;
  // printf("Etat : %06x\n", etat);
  etat ^= sousCle[i];
  printf("Tour %d, Etat : %06x, Sous-clé : %06x\n", i, etat, sousCle[i]);
  i -= 1;

  for(; i >= 0; --i) {
    etat = dechiffrementPermutation(etat);
    etat = dechiffrementSubstitution(etat);
    etat ^= sousCle[i];
    printf("Tour %d, Etat : %06x, Sous-clé : %06x\n", i, etat, sousCle[i]);
  }

  mClair = etat;
  printf("Message claire : %06x\n", mClair);
  return mClair;
}