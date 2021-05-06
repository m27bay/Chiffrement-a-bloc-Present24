#include "Cadencement.h"

/**
 * Description : Recupere les 24 bits de registreK[39] à registreK[16]
 *               pour former la sous cle.
 * Entree : Un tableau de 10 octects.
 * Sortie : La sous cle sur 32 bits, avec les 8 premiers bits à 0.
 * */
u32 obtenirSousCle(const u80_t registreK) {
  u32 sousCle;
  sousCle = registreK.tab[5]; // sousCle = registreK[39]...registreK[32].
  sousCle <<= 8;

  sousCle |= registreK.tab[6]; // sousCle = registreK[39]...registreK[24].
  sousCle <<= 8;

  sousCle |= registreK.tab[7]; // sousCle = registreK[39]...registreK[16].
  
  return sousCle;
}

/**
 * Description : Pivote le registre de 61 position vers la gauche.
 * Entree : Un tableau de 10 octects.
 * */
void cadencementPivot61(u80_t* registreK) {
  u80_t kCopie;
  initU80(&kCopie);
  copieU80DansU80(&kCopie, *registreK); // kCopie = registreK.

  // registreK[79]...registreK[0] = registreK[18]...registreK[19].
  for(size_t i = 0; i < 10; i++) {
    u8 a = kCopie.tab[ ((i + 7) % 10) ]; // Decalage de 7 octects.
    a <<= 5; 
    u8 b = kCopie.tab[ ((i + 8) % 10) ]; // Decalage de 8 octects.
    b >>= 3;
    registreK->tab[i] = (a | b); // Concatenation de a et b.
  }
}

/**
 * Description : Applique la substition au registre[0].
 * Entree : Un tableau de 10 octects.
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
 * Entree : Un tableau de 10 octects.
 *          Le numero du tour du boucle.
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
 * Entree : La cle maitre.
 *          Le tableau de sous cles.
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
