#include "Dechiffrement.h"

/**
 * Description : Applique le tableau de invSubstitution sur une variable
 *               de 32 bits.
 * Entree : Une variable de 32 bits.
 * Sortie : Une variable de 32 bits.
 * */
u32 dechiffrementSubstitution(u32 etat) {
  u32 nouvEtat = 0;
  u8 sousEtat;

  for(size_t i = 0; i < 6; ++i) {
    sousEtat = (etat & 0xf);
    nouvEtat |= (invTabSubstitution[sousEtat] << (4 * i));
    etat >>= 4;
  }

  return nouvEtat;
}

/**
 * Description : Applique le tableau de invPermutation sur une variable
 *               de 32 bits.
 * Entree : Une variable de 32 bits.
 * Sortie : Une variable de 32 bits.
 * */
u32 dechiffrementPermutation(const u32 etat) {
  u32 nouvEtat = 0;
  u32 bitEtat, bitNouvEtat;
  u32 masque = 1;

  for(u8 i = 0; i < 24; ++i) {
    bitEtat = (etat >> i) & masque;
    bitNouvEtat = (bitEtat << invTabPermutation[i]); 
    nouvEtat |= bitNouvEtat;
  }

  return nouvEtat;
}

/**
 * Description : Dechiffre le message chiffre à l'aide des sous cles.
 * Entree : Le message chiffre.
 *          Le tableau de sous cles.
 * Sortie : Le message claire.
 * */
u32 fctDeDeChiffrement(const u32 mChiffre, const u32 sousCle[nbrSousCle]) {
  u32 etat = mChiffre, mClair;
  i32 i = nbrSousCle - 1;
  etat ^= sousCle[i];
  i -= 1;

  for(; i >= 0; --i) {
    etat = dechiffrementPermutation(etat);
    etat = dechiffrementSubstitution(etat);
    etat ^= sousCle[i];
  }

  mClair = etat;
  return mClair;
}