#include "Chiffrement.h"

u8 tabSubstitution[16] = {12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 15, 8, 4, 7, 1, 2};
u8 tabPermutation[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

/**
 * Description : Recupere et concatene la sous cle.
 * Entree : Le registre k.
 * Sortie : La sous cle sur 32 bits.
 * */
u32 obtenirSousCle(const u80_t registreK) {
  u32 sousCle;
  sousCle = registreK.tab[5];
  sousCle <<= 8;

  sousCle |= registreK.tab[6];
  sousCle <<= 8;

  sousCle |= registreK.tab[7];
  
  return sousCle;
}

/**
 * Description : Pivote le registre k de 61 position vers la gauche.
 * Entree : Le registre k.
 * */
void cadencementPivot61(u80_t* registreK) {
  u80_t kCopie;
  initU80(&kCopie);
  copieU80DansU80(&kCopie, *registreK);

  for(size_t i = 0; i < 10; i++) {
    u8 a = kCopie.tab[ ((i + 7) % 10) ];
    a <<= 5; 
    u8 b = kCopie.tab[ ((i + 8) % 10) ];
    b >>= 3;
    registreK->tab[i] = (a | b);
  }
}

void cadencementSubsitution(u80_t *registreK) {
  u8 indice = (registreK->tab[0] & 0xf0);
  indice >>= 4;

  u8 resultSubstitution = tabSubstitution[indice];
  resultSubstitution <<= 4;
  resultSubstitution |= (registreK->tab[0] & 0x0f);
  registreK->tab[0] = resultSubstitution;
}

void cadencementXor(u80_t *registreK, const u8 i) {
  // i = i7 i6 i5 i4 i3 i2 i1 i0
  u8 tabi8 = i << 7; // = i0 0 0 0 0 0 0 0
  u8 tabi7 = i >> 1; // = 0 i7 i6 i5 i4 i3 i2 i1

  registreK->tab[7] ^= tabi7;
  registreK->tab[8] ^= tabi8;
}

/**
 * Description : Rempli le tableau de sous cle sousCle en fonction de la cle maitre.
 * Entree : La cle maitre : cleMaitre
 *          Le tableau de sous cles : sousCle.
 * */
void cadencementDeCle(u32 sousCle[nbrSousCle], const u32 cleMaitre) {
  // Copie cle maitre dans le 24 bits de poids fort
  u80_t registreK;
  initU80(&registreK);
  copieU32DansU80(&registreK, cleMaitre);

  for(u8 i = 1; i <= nbrSousCle; ++i) {
    sousCle[i-1] = obtenirSousCle(registreK);
    cadencementPivot61(&registreK);
    cadencementSubsitution(&registreK);
    cadencementXor(&registreK, i);
  }
}

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

void testChiffrementSubstitution(u32 etat) {
  chiffrementSubstitution(etat);
}

u32 chiffrementPermutation(const u32 etat) {
  u32 nouvEtat = 0;
  u32 bitEtat, bitNouvEtat;
  u32 masque = 1;
  for(u8 i = 0; i < 24; ++i) {
    bitEtat = (etat >> i) & masque;
    bitNouvEtat = (bitEtat << (tabPermutation[i])); 
    nouvEtat |= bitNouvEtat;
  }

  return nouvEtat;
}

void testChiffrementPermutation(const u32 etat) {
  chiffrementPermutation(etat);
}

/**
 * Description : 
 * Entree : 
 * Sortie :
 * */
u32 fctDeChiffrement(u32 mClaire, u32 sousCle[nbrSousCle]) {
  printf("Message claire : %06x\n", mClaire);
  u32 etat = mClaire, mChiffre;
  u8 i;
  for(i = 1; i < 11; ++i) {
    printf("Tour %d, Etat : %06x, Sous-clé : %06x\n", i, etat, sousCle[i-1]);
    etat ^= sousCle[i-1];
    etat = chiffrementSubstitution(etat);
    etat = chiffrementPermutation(etat);
  }

  etat ^= sousCle[nbrSousCle-1];
  printf("Tour %d, Etat : %06x, Sous-clé : %06x\n", i, etat, sousCle[i-1]);
  mChiffre = etat;
  printf("Message chiffré : %06x\n", mChiffre);
  return mChiffre;
}