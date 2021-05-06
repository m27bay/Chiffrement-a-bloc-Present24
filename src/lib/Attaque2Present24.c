#include "Attaque2Present24.h"

/**
 * Description : Rempli une liste de taille donne en chiffrant (flag = 1),
 *              ou en dechiffrant (flag = 0) le message avec toutes
 *              les cles possible sur 24 bits.
 * Entree : La liste que l'on va remplir.
 *          La taille de la liste.
 *          Le message a chiffrer, ou dechiffrer.
 *          Le flag indiquent si l'on chiffre ou dechiffre.
 * */
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

/**
 * Description : Affiche la/les cles candidates en chiffrant/ dechiffrant
 *               de nouveau messages et verifie le resultat.
 * Entree : La cle pour chiffrer.
 *          La cle pour déchiffrer.
 *          Un nouveau message clair.
 *          Un nouveau message chiffre. 
 * */
void trouverClesCandidates(u32 cle, u32 cle2, u32 mClair2, u32 mChiffre2) {
  u32 sousCle[11], sousCle2[11];
  cadencementDeCle(sousCle, cle);
  cadencementDeCle(sousCle2, cle2);
  u32 tmp = fctDeChiffrement(mClair2, sousCle);
  if(mChiffre2 == fctDeChiffrement(tmp, sousCle2)) {
    printf("Cle : %06x, cle2 : %06x\n", cle, cle2);
  }
}

/**
 * Description : Recherche les collisions entre la liste chiffre et la
 *               liste clair puis affiche les cles candidates.
 * Entree : La liste clair.
 *          La liste chiffre.
 *          La taille des listes.
 *          Un nouveau message clair.
 *          Un nouveau message chiffre. 
 * */
void trouverCollisions(msgCle_t* listeClair, msgCle_t* listeChiffre,
                      u32 tailleListe, u32 mClair2, u32 mChiffre2)
{
  for(u32 i = 0; i < tailleListe; ++i) {
    rechercheDichotomique(listeClair, listeChiffre[i], 0, tailleListe, mClair2, mChiffre2);
  }
}

/**
 * Description : Attaque par le milieu le chiffrement 2PRESENT24.
 * Entree : Deux couples clair-chiffre.
 * */
void attaque2Present24(u32 mClair, u32 mChiffre, u32 mClair2, u32 mChiffre2) {
  msgCle_t* listeClair = malloc(tailleCle * sizeof(msgCle_t));
  if(!listeClair) { printf("ERREUR : pointeur nul\n"); return; }
  msgCle_t* listeChiffre = malloc(tailleCle * sizeof(msgCle_t));
  if(!listeChiffre) { printf("ERREUR : pointeur nul\n"); return; }

  remplirListe(listeClair, tailleCle, mClair, 1);
  trieCroissant(listeClair, tailleCle);
  remplirListe(listeChiffre, tailleCle, mChiffre, 0);
  trieCroissant(listeChiffre, tailleCle);

  trouverCollisions(listeClair, listeChiffre, tailleCle, mClair2, mChiffre2);
 
  free(listeClair);
  free(listeChiffre);
}