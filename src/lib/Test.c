#include "Test.h"

/**
 * Description :
 * Entree :
 * */
u8 testSousCle(const u32 ki[nbrSousCle]) {
	u32 reponse[nbrSousCle] = {
		0x000000, 0x000000, 0x000001, 0x000001, 
		0x400062, 0x80002a,	0xc00033, 0x40005b,
		0x00064c, 0x800284, 0x400355
	};

	for(size_t i = 0; i < nbrSousCle; ++i) {
		if(reponse[i] != ki[i]) {
			return 0;
		}
	}

	return 1;
}

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

/**
 * Description : Appel des fonctions test de chiffrement/dechiffrement.
 * */
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

/**
 * Description : Appel de la fonction attaque2Present24
 *               et calcul du temps d'execution;
 * Entree : Deux couples clair-chiffre.
 * */
void testAttaque(u32 mClair, u32 mChiffre, u32 mClair2, u32 mChiffre2) {
  clock_t t = clock();

  attaque2Present24(mClair, mChiffre, mClair2, mChiffre2);

  t = clock() - t;
  float tempsExeSec = ((float) t) / CLOCKS_PER_SEC;
  printf("temps d'execution : %f sec.\n", tempsExeSec);
}