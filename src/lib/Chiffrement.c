#include "Chiffrement.h"

u8 tabSubstitution[16] = {12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 15, 8, 4, 7, 1, 2};
u8 tabPermutation[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

/**
 * Description : Recupere et concatene la sous cle.
 * Entree : Le registre k.
 * Sortie : La sous cle sur 32 bits.
 * */
u32 obtenirSousCle(const u80_t k) {
  u32 sousCle;
  sousCle = k.tab[5];
  sousCle <<= 8;

  sousCle |= k.tab[6];
  sousCle <<= 8;

  sousCle |= k.tab[7];
  
  return sousCle;
}

/**
 * Description : Pivote le registre k de 61 position vers la gauche.
 * Entree : Le registre k.
 * */
void cadencementPivot61(u80_t* k) {
  u80_t kCopie;
  initU80(&kCopie);
  copieU80DansU80(&kCopie, *k);

  for(size_t i = 0; i < 10; i++) {
    u8 a = kCopie.tab[ ((i + 7) % 10) ];
    a <<= 5; 
    u8 b = kCopie.tab[ ((i + 8) % 10) ];
    b >>= 3;
    k->tab[i] = (a | b);
  }
}

void cadencementSubsitution(u80_t *k) {
  u8 indice = (k->tab[0] & 0xf0);
  indice >>= 4;

  u8 resultSubstitution = tabSubstitution[indice];
  resultSubstitution <<= 4;
  resultSubstitution |= (k->tab[0] & 0x0f);
  k->tab[0] = resultSubstitution;
}

void cadencementXor(u80_t *k, const u8 i) {
  // i = i7 i6 i5 i4 i3 i2 i1 i0
  u8 tabi8 = i << 7; // = i0 0 0 0 0 0 0 0
  u8 tabi7 = i >> 1; // = 0 i7 i6 i5 i4 i3 i2 i1

  k->tab[7] ^= tabi7;
  k->tab[8] ^= tabi8;
}

/**
 * Description : Rempli le tableau de sous cle ki en fonction de la cle maitre.
 * Entree : La cle maitre : cleMaitre
 *          Le tableau de sous cles : ki.
 * */
void cadencementDeCle(u32 ki[nbrSousCle], u32 cleMaitre) {
  // Copie cle maitre dans le 24 bits de poids fort
  u80_t k;
  initU80(&k);
  copieU32DansU80(&k, cleMaitre);

  for(u8 i = 1; i <= nbrSousCle; ++i) {
    ki[i-1] = obtenirSousCle(k);
    cadencementPivot61(&k);
    cadencementSubsitution(&k);
    cadencementXor(&k, i);
  }
}

u32 chiffrementSubstitution(const u32 etat) {
  u32 nouvEtat = 0;
  u8 sousEtat;
  u32 masque = 0xf0000000;
  for(size_t i = 0; i < 6; ++i) {
    sousEtat = (etat & masque);
    // printf("sousEtat : %x\n", sousEtat); afficheBinU8(sousEtat); printf("\n");
    nouvEtat |= sousEtat;
    // printf("nouvEtat : %x\n", nouvEtat); afficheBinU32(nouvEtat); printf("\n");
    nouvEtat <<= 4;
    // printf("nouvEtat : %x\n", nouvEtat); afficheBinU32(nouvEtat); printf("\n");
    masque >>= 4;
  }

  // printf("nouvEtat : %x\n", nouvEtat); afficheBinU32(nouvEtat); printf("\n");
  return nouvEtat;
}

u32 chiffrementPermutation(const u32 etat) {
  // printf("etat : %x,", etat); afficheBinU32(etat); printf("\n");
  u32 nouvEtat = 0;
  u32 bitEtat, bitNouvEtat;
  u32 masque = 1;
  for(u8 i = 0; i < 24; ++i) {
    bitEtat = (etat >> i) & masque;
    // printf("\netape n°%d, bitEtat : %x,", i, bitEtat); afficheBinU32(bitEtat); printf("\n");
    bitNouvEtat = (bitEtat << (tabPermutation[i])); 
    // printf("bitNouvEtat : %x,", bitNouvEtat); afficheBinU32(bitNouvEtat); printf("\n");
    nouvEtat |= bitNouvEtat;
    // printf("nouvEtat : %x,", nouvEtat); afficheBinU32(nouvEtat); printf("\n");
  }

  // printf("nouvEtat : %x,", nouvEtat); afficheBinU32(nouvEtat); printf("\n");
  return nouvEtat;
}

/**
 * Description : 
 * Entree : 
 * Sortie :
 * */
u32 fctDeChiffrement(u32 m, u32 ki[nbrSousCle]) {
  u32 etat = m, chiffre;
  for(u8 i = 1; i < 11; ++i) {
    etat ^= ki[i];
    etat = chiffrementSubstitution(etat);
    etat = chiffrementPermutation(etat);
    printf("etat : %x\n", etat); afficheBinU32(etat); printf("\n");
  }

  etat ^= ki[nbrSousCle-1];
  chiffre = etat;
  return chiffre;
}