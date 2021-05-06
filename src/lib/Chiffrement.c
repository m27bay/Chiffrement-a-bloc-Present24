#include "Chiffrement.h"

/**
 * Description : Applique le tableau de substitution sur une variable
 *               de 32 bits.
 * Entree : Une variable de 32 bits.
 * Sortie : Une variable de 32 bits.
 * */
u32 chiffrementSubstitution(u32 etat) {
  u32 nouvEtat = 0;
  u8 sousEtat;

  for(size_t i = 0; i < 6; ++i) {
    sousEtat = (etat & 0xf);
    nouvEtat |= (tabSubstitution[sousEtat] << (4 * i));
    etat >>= 4;
  }

  return nouvEtat;
}

/**
 * Description : Applique le tableau de permutation sur une variable
 *               de 32 bits.
 * Entree : Une variable de 32 bits.
 * Sortie : Une variable de 32 bits.
 * */
u32 chiffrementPermutation(const u32 etat) {
  u32 nouvEtat = 0;
  u32 bitEtat, bitNouvEtat;
  u32 masque = 1;

  for(u8 i = 0; i < 24; ++i) {
    bitEtat = (etat >> i) & masque;
    bitNouvEtat = (bitEtat << tabPermutation[i]); 
    nouvEtat |= bitNouvEtat;
  }

  return nouvEtat;
}

/**
 * Description : Chiffre le message clair à l'aide des sous cles.
 * Entree : Le message clair.
 *          Le tableau de sous cles.
 * Sortie : Le message chiffre.
 * */
u32 fctDeChiffrement(const u32 mClair, const u32 sousCle[nbrSousCle]) {
  u32 etat = mClair, mChiffre;
  u8 i;

  for(i = 1; i < 11; ++i) {
    etat ^= sousCle[i-1];
    etat = chiffrementSubstitution(etat);
    etat = chiffrementPermutation(etat);
  }

  etat ^= sousCle[nbrSousCle-1];
  mChiffre = etat;
  return mChiffre;
}