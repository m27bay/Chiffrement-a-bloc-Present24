#include "Attaque2Present24.h"

// 2 pow 24 = 16777216


void listeChiffrement(u32 listeClair[16777216], u32 mClair) {
  for(u32 cleMaitre = 0; cleMaitre <= 0xffffff; ++cleMaitre) {
    u32 sousCLe[11];
    cadencementDeCle(sousCLe, cleMaitre);
    listeClair[cleMaitre] = fctDeChiffrement(mClair, sousCLe);
  }
}

void listeDechiffrement(u32 listeDechiffrement[16777216], u32 mChiffre) {
  for(u32 cleMaitre = 0; cleMaitre <= 0xffffff; ++cleMaitre) {
      u32 sousCLe[11];
      cadencementDeCle(sousCLe, cleMaitre);
      listeDechiffrement[cleMaitre] = fctDeDeChiffrement(mChiffre, sousCLe);
  }
}

void trouverCollisions(u32 collision[16777216],
                    u32 listeClair[16777216],
                    u32 listeDechiffrement[16777216]) 
{
  u32 j = 0;
  for(u32 i = 0; i <= 0xffffff; ++i) {
    if(listeClair[i] == listeDechiffrement[i]) {
      collision[j] = listeClair[i];
      j++;
    }
  }
}