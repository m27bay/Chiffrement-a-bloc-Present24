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
 * Description : Applique l'attaque sur plusieurs couples clair-chiffre.
 * */
void testAttaque() {
  // Mickael Le Denmat : OK
  // (m1,c1) = (0x91c472,0x60ab71) (m2,c2) = (0xf18a50,0x68b9d2)
  // (k1,k2) = (0x24d0c2,0x7c05bc)
  attaque2Present24(0x91c472, 0x60ab71, 0xf18a50, 0x68b9d2);

  // Gabriel Dos Santos : OK
  // (m1,c1) = (0xb404cc,0x23714f) (m2,c2) = (0x576dcf,0x45051b)
  // (k1,k2) = (0x009dbe,0x6c198b)
  // (k1,k2) = (0x57f0b5,0x28baf5)
  // (k1,k2) = (0x37048e,0x4af525)
  attaque2Present24(0xb404cc, 0x23714f, 0x576dcf, 0x45051b);

  // Theophile Molinatti : OK
  // (m1,c1) = (0xce157a,0x0ed3f0) (m2,c2) = (0x4181c8,0x650e1e)
  // (k1,k2) = (0x6deda7,0xe7141f)
  attaque2Present24(0xce157a, 0x0ed3f0, 0x4181c8, 0x650e1e);

  // Quentin Gruchet : Ok
  // (m1,c1) = (0x10dc72,0xd1d556) (m2,c2) = (0x8f60f1,0x8d3b0b)
  // (k1,k2) = (0x20507a,0x3d4773)
  // (k1,k2) = (0x61dd5a,0xdf6dc6)
  // (k1,k2) = (0x104fff,0x6ee8ea)
  attaque2Present24(0x10dc72, 0xd1d556, 0x8f60f1, 0x8d3b0b);
}