#include "Attaque2Present24.h"

void creerListeChiffrement(u32 listeClair[tailleCle + 2], u32 mClair) {
  for(u32 cleMaitre = 0; cleMaitre <= 0xffffff; ++cleMaitre) {
    u32 sousCLe[11];
    cadencementDeCle(sousCLe, cleMaitre);
    listeClair[cleMaitre] = fctDeChiffrement(mClair, sousCLe);
  }
}

void creerListeDechiffrement(u32 listeChiffre[tailleCle + 2],
                            u32 mChiffre)
{
  for(u32 cleMaitre = 0; cleMaitre <= 0xffffff; ++cleMaitre) {
      u32 sousCLe[11];
      cadencementDeCle(sousCLe, cleMaitre);
      listeChiffre[cleMaitre] = fctDeDeChiffrement(mChiffre, sousCLe);
  }
}

void trouverCollisions(u32 collision[tailleCle + 2],
                    u32 listeClair[tailleCle + 2],
                    u32 listeChiffre[tailleCle + 2]) 
{
  u32 j = 0;
  for(u32 i = 0; i <= 0xffffff; ++i) {
    if(listeClair[i] == listeChiffre[i]) {
      collision[j] = listeClair[i];
      j++;
    }
  }
}