#include "Attaque2Present24.h"

void remplirListe(msgCle_t* liste, u32 tailleListe, u32 message, u8 flag) {
  for(u32 cleMaitre = 0; cleMaitre < tailleListe; ++cleMaitre) {
    u32 sousCLe[11];
    cadencementDeCle(sousCLe, cleMaitre);
    if(flag) {
      liste[cleMaitre].message = fctDeChiffrement(message, sousCLe);
    }
    else {
      liste[cleMaitre].message = fctDeDeChiffrement(message, sousCLe);
    }
    liste[cleMaitre].cle = cleMaitre;
  }
}

void trouverClesCandidates(u32 cle, u32 cle2, u32 mClair2, u32 mChiffre2) {
  u32 sousCle[11], sousCle2[11];
  cadencementDeCle(sousCle, cle);
  cadencementDeCle(sousCle2, cle2);
  u32 tmp = fctDeChiffrement(mClair2, sousCle);
  if(mChiffre2 == fctDeChiffrement(tmp, sousCle2)) {
    printf("Cle : %06x, cle2 : %06x\n", cle, cle2);
  }
}

void trouverCollisions(msgCle_t* listeClair, msgCle_t* listeChiffre,
                      u32 tailleListe, u32 mClair2, u32 mChiffre2)
{
  for(u32 i = 0; i < tailleListe; ++i) {
    rechercheDichotomique(listeClair, listeChiffre[i], 0, tailleListe, mClair2, mChiffre2);
  }
}