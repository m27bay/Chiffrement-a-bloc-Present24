#include "../lib/Chiffrement.h"
#include "../lib/Dechiffrement.h"
#include "../lib/Attaque2Present24.h"

/**
 * Chiffrement : 
 * mClair = 0x000000
 * cleMaitre = 0x000000
 * mChiffre = 0xbb57e6
 * */
u8 test1a() {
  u32 mClair = 0x000000;
  u32 cleMaitre = 0x000000;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0xbb57e6);
}

/**
 * Dechiffrement : 
 * mChiffre = 0xbb57e6
 * cleMaitre = 0x000000
 * mClair = 0x000000
 * */
u8 test1b() {
  u32 mChiffre = 0xbb57e6;
  u32 cleMaitre = 0x000000;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClair = fctDeDeChiffrement(mChiffre, sousCLe);
  return (mClair == 0x000000);
}

/**
 * Chiffrement : 
 * mClair = 0xffffff
 * cleMaitre = 0x000000
 * mChiffre = 0x739293
 * */
u8 test2a() {
  u32 mClair = 0xffffff;
  u32 cleMaitre = 0x000000;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0x739293);
}

/**
 * Dechiffrement : 
 * mChiffre = 0x739293
 * cleMaitre = 0x000000
 * mClair = 0xffffff
 * */
u8 test2b() {
  u32 mChiffre = 0x739293;
  u32 cleMaitre = 0x000000;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClair = fctDeDeChiffrement(mChiffre, sousCLe);
  return (mClair == 0xffffff);
}

/**
 * Chiffrement : 
 * mClair = 0x000000
 * cleMaitre = 0xffffff
 * mChiffre = 0x1b56ce
 * */
u8 test3a() {
  u32 mClair = 0x000000;
  u32 cleMaitre = 0xffffff;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0x1b56ce);
}

/**
 * Dechiffrement : 
 * mChiffre = 0x1b56ce
 * cleMaitre = 0xffffff
 * mClair = 0x000000
 * */
u8 test3b() {
  u32 mChiffre = 0x1b56ce;
  u32 cleMaitre = 0xffffff;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClair = fctDeDeChiffrement(mChiffre, sousCLe);
  return (mClair == 0x000000);
}

/**
 * Chiffrement : 
 * mClair = 0xf955b9
 * cleMaitre = 0xd1bd2d
 * mChiffre = 0x47a929
 * */
u8 test4a() {
  u32 mClair = 0xf955b9;
  u32 cleMaitre = 0xd1bd2d;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mChiffre = fctDeChiffrement(mClair, sousCLe);
  return (mChiffre == 0x47a929);
}

/**
 * Dechiffrement : 
 * mChiffre = 0x47a929
 * cleMaitre = 0xd1bd2d
 * mClair = 0xf955b9
 * */
u8 test4b() {
  u32 mChiffre = 0x47a929;
  u32 cleMaitre = 0xd1bd2d;
  u32 sousCLe[11];
  cadencementDeCle(sousCLe, cleMaitre);
  u32 mClair = fctDeDeChiffrement(mChiffre, sousCLe);
  return (mClair == 0xf955b9);
}

void testAttaque(u32 mClair, u32 mChiffre,
                u32 mClair2, u32 mChiffre2)
{
  u32* listeClair = malloc( (tailleCle + 2) * sizeof(u32));
  u32* listeChiffre = malloc( (tailleCle + 2) * sizeof(u32));
  u32* collision = malloc( (tailleCle + 2) * sizeof(u32));

  creerListeChiffrement(listeClair, mClair);
  creerListeDechiffrement(listeChiffre, mChiffre);
  trouverCollisions(collision, listeClair, listeChiffre);

  // u32 listeClair2[tailleCle + 2];
  // u32 listeChiffre2[tailleCle + 2];
  // u32 collision2[tailleCle + 2];

  // creerListeChiffrement(listeClair2, mClair2);
  // creerListeDechiffrement(listeChiffre2, mChiffre2);
  // trouverCollisions(collision2, listeClair2, listeChiffre2);

  // u8 nombreCollision = 0;
  // for(size_t i = 0; i <= tailleCle; ++i) {
  //   if(collision[i] == collision2[i]) {
  //     nombreCollision++;
  //   }
  // }

  // printf("Nombre de collision : %d", nombreCollision);

  free(listeClair);
  free(listeChiffre);
  free(collision);
}

int main(void) {
  printf("Test : %s", (test1a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test1b()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test2a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test2b()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test3a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test3b()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test4a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test : %s", (test4b()) ? "Succes\n" : "Echec\n");

  testAttaque(0x91c472, 0x60ab71, 0xf18a50, 0x68b9d2);

  return 0;
}
