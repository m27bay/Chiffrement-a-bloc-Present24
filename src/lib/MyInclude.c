#include "MyInclude.h"

/**
 * Tableaux globaux utilisé pour faire des subtitutions
 * et des permutations de bits.
 * 
 * tabSubstitution : Associe une valeur sur 4 bits à une autre valeur
 *                    sur 4 bits.
 * invTabSubstitution : Tableau inverse de tabSubstitution.
 * 
 * tabPermutation : Associe la position d'un bit à une autre position.
 * 
 * invTabPermutation : Tableau inverse de tabPermutation.
 * */
u8 tabSubstitution[16] = {12, 5, 6, 11, 9, 0, 10, 13,
													3, 14, 15, 8, 4, 7, 1, 2};

u8 tabPermutation[24] = {0, 6, 12, 18, 1, 7, 13, 19,
												2, 8, 14, 20, 3, 9, 15, 21, 4,
												10, 16, 22, 5, 11, 17, 23};

u8 invTabSubstitution[16] = {5, 14, 15, 8, 12, 1, 2, 13,
														11, 4, 6, 3, 0, 7, 9, 10};

u8 invTabPermutation[24] = {0, 4, 8, 12, 16, 20, 1, 5,
														9, 13, 17, 21, 2, 6, 10, 14,
														18, 22, 3, 7, 11, 15, 19, 23};

/**
 * Description : Affiche une variable en bit, du poids faible au poids fort.
 * Entree : La variable sur 8 bits.
 * */
void afficheBinU8v2(const u8 n) {
	u8 bit = 0;
	u8 masque = 1;

	for(int i = 0; i < 8; ++i) {
		bit = (n & masque) >> i; // Selection du bit et mise en poids faible.
		if(! (i % 4) ) { printf(" "); }
		printf("%d", bit);
		masque <<= 1;
	}
}

/**
 * Description : Affiche une variable en bit, du poids fort au poids faible.
 * Entree : La variable sur 8 bits.
 * */
void afficheBinU8(const u8 n) {
	u8 bit = 0;
	u8 masque = 128;

	for(int i = 7; i >= 0; --i) {
		bit = (n & masque) >> i;
		if(! ((7-i) % 4) ) { printf(" "); }
		printf("%d", bit);
		masque >>= 1;
	}
}

/**
 * Description : Affiche une variable en bit, du poids faible au poids fort.
 * Entree : La variable sur 32 bits.
 * */
void afficheBinU32v2(const u32 n) {
	u32 bit = 0;
	u32 masque = 1;

	for(int i = 0; i < 32; ++i) {
		bit = (n & masque) >> i;
		if(! (i % 4) ) { printf(" "); }
		printf("%d", bit);
		masque <<= 1;
	}
}

/**
 * Description : Affiche une variable en bit, du poids fort au poids faible.
 * Entree : La variable sur 32 bits.
 * */
void afficheBinU32(const u32 n) {
	u32 bit = 0;
	u32 masque = 0x80000000;

	for(int i = 31; i >= 0; --i) {
		bit = (n & masque) >> i;
		if( !((31 - i) % 4) ) { printf(" "); }
		printf("%d", bit);
		masque >>= 1;
	}
}

/**
 * Description : Affiche une variable en bit, de poids faible au poids fort.
 * Entree : La variable sur 80 bits.
 * */
void afficheBinU80v2(const u80_t n) {
  for(size_t j = 0; j < 10; ++j) {
    afficheBinU8v2(n.tab[j]);
  }
}

/**
 * Description : Affiche une variable en bit, de poids fort au poids faible.
 * Entree : La variable sur 80 bits.
 * */
void afficheBinU80(const u80_t n) {
  for(size_t j = 0; j < 10; ++j) {
    afficheBinU8(n.tab[j]);
  }
}

/**
 * Description : Affiche les sous cles contenues dans le tableau.
 * Entree : Le tableau de sous cles.
 * */
void afficherSousCLe(const u32 sousCle[nbrSousCle]) {
	for(size_t i = 0; i < nbrSousCle; ++i) {
		printf("Sous cle n°%ld :", i+1); afficheBinU32(sousCle[i]); printf(" <=> %06x\n", sousCle[i]);
	}
}

/**
 * Description : Initialise une variable de type u80_t.
 * Entree : Un pointeur sur la variable de 80 bits.
 * */
void initU80(u80_t* n) {
  for(size_t i = 0; i < 10; ++i) {
    n->tab[i] = 0;
  }
}

/**
 * Description : Copie une variable sur 32 bits dans une variable sur 80 bits
 * 							en commencant par le bit de poids fort.
 * Entree : Un pointeur sur la variable de 80 bits, la copie.
 * 					La variable de 32 bits, l'original.
 * */
void copieU32DansU80(u80_t* registreK, u32 cleMaitre) {
  for(size_t i = 2; cleMaitre != 0; --i) {
    registreK->tab[i] = cleMaitre & 0xffffff;
    cleMaitre >>= 8;
  }
}

/**
 * Description : Copie une variable sur 80 bits dans une variable sur 80 bits.
 * Entree : Un pointeur sur la variable de 80 bits, la copie.
 * 					La variable de 80 bits, l'original.
 * */
void copieU80DansU80(u80_t* copie, const u80_t original) {
	for(size_t i = 0; i < 10; ++i) {
		copie->tab[i] = original.tab[i];
	}
}