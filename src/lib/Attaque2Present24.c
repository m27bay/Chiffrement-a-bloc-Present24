#include "Attaque2Present24.h"

void remplirListe(msgCle_t* liste, u32 tailleListe, u32 message, u8 flag) {
  for(u32 cleMaitre = 0; cleMaitre < tailleListe; ++cleMaitre) {
    u32 sousCLe[11];
    cadencementDeCle(sousCLe, cleMaitre);
    if(flag) {
      liste[cleMaitre].message = fctDeChiffrement(message, sousCLe);
      liste[cleMaitre].cle = cleMaitre;
    }
    else {
      liste[cleMaitre].message = fctDeDeChiffrement(message, sousCLe);
      liste[cleMaitre].cle = cleMaitre;
    }
  }
}

void trouverCollisions(pairCle_t* collision, msgCle_t* listeClair,
                      msgCle_t* listeChiffre, u32 tailleListe)
{
  u32 nbrCollision = 0;
  i32 cleMsg = -1;

  for(u32 i = 0; i < tailleListe; ++i) {
    cleMsg = rechercheDichotomique(listeClair, listeChiffre[i].message, 0, tailleListe);
    if(cleMsg != -1) {
      collision[nbrCollision].cle = cleMsg;
      collision[nbrCollision].cle2 = listeChiffre[i].cle;
      nbrCollision++;
    }
  }
}

void trouverClesCandidates(pairCle_t* collision, u32 tailleCollision,
                          u32 mClair2, u32 mChiffre2)
{
  for(size_t i = 0; i < tailleCollision; ++i) {
    if(collision[i].cle == -1) { return; }
    u32 sousCle[11], sousCle2[11];
    cadencementDeCle(sousCle, collision[i].cle);
    cadencementDeCle(sousCle2, collision[i].cle2);
    u32 tmp = fctDeChiffrement(mClair2, sousCle);
    if(mChiffre2 == fctDeChiffrement(tmp, sousCle2)) {
      printf("Cle : %06x, cle2 : %06x\n", collision[i].cle, collision[i].cle2);
    }
  }
}