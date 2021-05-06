#include "../lib/Chiffrement.h"
#include "../lib/Dechiffrement.h"
#include "../lib/Attaque2Present24.h"
#include "../lib/Trier.h"

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

void testChiffrementDechiffrement() {
  printf("Test chiffrement : %s", (test1a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test dechiffrement : %s", (test1b()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test chiffrement : %s", (test2a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test dechiffrement : %s", (test2b()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test chiffrement : %s", (test3a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test dechiffrement : %s", (test3b()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test chiffrement : %s", (test4a()) ? "Succes\n" : "Echec\n");
  printf("\n");
  printf("Test dechiffrement : %s", (test4b()) ? "Succes\n" : "Echec\n");
}

void afficherListe(u32* liste, u32 tailleListe) {
  for(size_t i = 0; i < tailleListe; ++i) {
    printf("%06x\n", liste[i]);
  }
}

void afficherCollision(pairCle_t* collision, u32 tailleCollision) {
  for(size_t i = 0; i < tailleCollision; ++i) {
    printf("cle : %06x, cle2 : %06x\n", collision[i].cle, collision[i].cle2);
  }
}

void testAttaque(u32 mClair, u32 mChiffre, u32 mClair2, u32 mChiffre2) {
  clock_t t = clock();

  msgCle_t* listeClair = malloc(tailleCle * sizeof(msgCle_t));
  if(!listeClair) { printf("ERREUR : pointeur nul\n"); return; }
  msgCle_t* listeChiffre = malloc(tailleCle * sizeof(msgCle_t));
  if(!listeChiffre) { printf("ERREUR : pointeur nul\n"); return; }
  pairCle_t* collision = malloc(tailleCle * sizeof(pairCle_t));
	if(!collision) { printf("ERREUR : pointeur nul\n"); return; }
  initListePairCle(collision, tailleCle);

  remplirListe(listeClair, tailleCle, mClair, 1);
  trieCroissant(listeClair, tailleCle);
  remplirListe(listeChiffre, tailleCle, mChiffre, 0);
  u32 msg = listeChiffre[0x28baf5].message;
  printf("message : %06x\n", msg);
  trieCroissant(listeChiffre, tailleCle);

  printf("%d\n", rechercheDichotomique(listeClair, msg, 0, tailleCle));

  trouverCollisions(collision, listeClair, listeChiffre, tailleCle);
  trouverClesCandidates(collision, tailleCle, mClair2, mChiffre2);
 
  free(listeClair);
  free(listeChiffre);
  free(collision);

  t = clock() - t;
  printf("temps d'execution : %f sec\n", ((float)t)/CLOCKS_PER_SEC);
}

int main(void) {
  // testChiffrementDechiffrement();

  // Moi : OK
  // (m1,c1) = (0x91c472,0x60ab71) (m2,c2) = (0xf18a50,0x68b9d2)
  // (k1,k2) = (0x24d0c2,0x7c05bc)
  // testAttaque(0x91c472, 0x60ab71, 0xf18a50, 0x68b9d2);

  // gab : 
  // (m1,c1) = (0xb404cc,0x23714f) (m2,c2) = (0x576dcf,0x45051b)
  // (k1,k2) = (0x009dbe,0x6c198b)
  // (k1,k2) = (0x57f0b5,0x28baf5)
  // (k1,k2) = (0x37048e,0x4af525)
  testAttaque(0xb404cc, 0x23714f, 0x576dcf, 0x45051b);

  // theo : 
  // (m1,c1) = (0xce157a,0x0ed3f0) (m2,c2) = (0x4181c8,0x650e1e)
  // (k1,k2) = (0x6deda7,0xe7141f)
  // testAttaque(0xce157a, 0x0ed3f0, 0x4181c8, 0x650e1e);

  // quentin : 
  // (m1,c1) = (0x10dc72,0xd1d556) (m2,c2) = (0x8f60f1,0x8d3b0b)
  // (k1,k2) = (0x20507a,0x3d4773)
  // (k1,k2) = (0x61dd5a,0xdf6dc6)
  // (k1,k2) = (0x104fff,0x6ee8ea)
  // testAttaque(0x10dc72, 0xd1d556, 0x8f60f1, 0x8d3b0b);

  return 0;
}
