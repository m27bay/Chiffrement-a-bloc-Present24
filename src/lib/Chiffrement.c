#include "Chiffrement.h"

/**
 * Tableaux globaux utilisé pour faire des subtitutions
 * et des permutations de bits.
 * 
 * tabSubstitution : Associe une valeur sur 4 bits à une autre valeur
 *                    sur 4 bits.
 * 
 * tabPermutation : Associe la position d'un bit à une autre position.
 * */
u8 tabSubstitution[16] = {12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 15, 8, 4, 7, 1, 2};
u8 tabPermutation[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

/**
 * Description : Recupere 24 bits de registreK[39] à registreK[16]
 *                pour former la sous cle.
 * Entree : Le registre : un tableau de 10 octects..
 * Sortie : La sous cle : sousCle sur 32 bits, avec les 8 premiers bits à 0.
 * */
u32 obtenirSousCle(const u80_t registreK) {
  u32 sousCle;
  sousCle = registreK.tab[5]; // sousCle = registreK[39]...registreK[32]
  sousCle <<= 8;

  sousCle |= registreK.tab[6]; // sousCle = registreK[39]...registreK[24]
  sousCle <<= 8;

  sousCle |= registreK.tab[7]; // sousCle = registreK[39]...registreK[16]
  
  return sousCle;
}

/**
 * Description : Pivote le registre de 61 position vers la gauche.
 * Entree : Le registre : un tableau de 10 octects.
 * */
void cadencementPivot61(u80_t* registreK) {
  u80_t kCopie;
  initU80(&kCopie);
  copieU80DansU80(&kCopie, *registreK); // kCopie = registreK

  // registreK[79]...registreK[0] = registreK[18]...registreK[19]
  for(size_t i = 0; i < 10; i++) {
    u8 a = kCopie.tab[ ((i + 7) % 10) ]; 
    a <<= 5; 
    u8 b = kCopie.tab[ ((i + 8) % 10) ];
    b >>= 3;
    registreK->tab[i] = (a | b);
  }
}

/**
 * Description : Applique la substition au registre[0].
 * Entree : Le registre : un tableau de 10 octects.
 * */
void cadencementSubsitution(u80_t *registreK) {
  u8 indice = (registreK->tab[0] & 0xf0); // indice = k79 k78 k77 k76 0 0 0 0.
  indice >>= 4; // indice = 0 0 0 0 k79 k78 k77 k76.

  u8 resultSubstitution = tabSubstitution[indice];
  resultSubstitution <<= 4;
  resultSubstitution |= (registreK->tab[0] & 0x0f);
  registreK->tab[0] = resultSubstitution; // = S1 S2 S3 S4 k75 k74 k73 k72.
}

/**
 * Description : Applique un xor entre certain bit du registre
 *                et le tour de la boucle.
 * Entree : Le registre : un tableau de 10 octects.
 *          le numero du tour du boucle : i.
 * */
void cadencementXor(u80_t *registreK, const u8 i) {
  // i = i7 i6 i5 i4 i3 i2 i1 i0.
  u8 tabi8 = i << 7; // = i0 0 0 0 0 0 0 0.
  u8 tabi7 = i >> 1; // = 0 i7 i6 i5 i4 i3 i2 i1.

  registreK->tab[7] ^= tabi7;
  registreK->tab[8] ^= tabi8;
}

/**
 * Description : Rempli le tableau de sous cle en fonction de la cle maitre.
 * Entree : La cle maitre : cleMaitre.
 *          Le tableau de sous cles : sousCle.
 * */
void cadencementDeCle(u32 sousCle[nbrSousCle], const u32 cleMaitre) {
  u80_t registreK;
  initU80(&registreK);
  // On copie les 24 bits de la cle maitre dans les 80 bits du registre k.
  copieU32DansU80(&registreK, cleMaitre); 

  for(u8 i = 1; i <= nbrSousCle; ++i) {
    sousCle[i-1] = obtenirSousCle(registreK);
    cadencementPivot61(&registreK);
    cadencementSubsitution(&registreK);
    cadencementXor(&registreK, i);
  }
}

/**
 * Description : Applique le tableau de substitution sur l'etat en parametre.
 * Entree : L'etat : etat.
 * Sortie : Le nouveau etat : nouvEtat.
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
 * Description : Applique le tableau de permutation sur l'etat en parametre.
 * Entree : L'etat : etat.
 * Sortie : Le nouveau etat : nouvEtat.
 * */
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

/**
 * Description : Chiffre le message clair à l'aide des sous cles.
 * Entree : Le message clair : mClair.
 *          Le tableau de sous cles : sousCle.
 * Sortie : Le message chiffre : mChiffre.
 * */
u32 fctDeChiffrement(u32 mClair, u32 sousCle[nbrSousCle]) {
  printf("Message clair : %06x\n", mClair);
  u32 etat = mClair, mChiffre;
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