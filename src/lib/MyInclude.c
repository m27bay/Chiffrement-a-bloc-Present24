#include "MyInclude.h"

/**
 * Tableaux globaux utilisé pour faire des subtitutions
 * et des permutations de bits.
 * 
 * tabSubstitution : Associe une valeur sur 4 bits à une autre valeur
 *                    sur 4 bits.
 * 
 * tabPermutation : Associe la position d'un bit à une autre position.
 * */
u8 tabSubstitution[16] = {12, 5, 6, 11, 9, 0, 10, 13,
													3, 14, 15, 8, 4, 7, 1, 2};

u8 tabPermutation[24] = {0, 6, 12, 18, 1, 7, 13, 19,
												2, 8, 14, 20, 3, 9, 15, 21, 4,
												10, 16, 22, 5, 11, 17, 23};

/**
 * Description : Affiche la variable n en bit du poids
 * 								faible au poids fort.
 * Entree : La variable sur 8 bits : n.
 * */
void afficheBinU8v2(const u8 n) {
	u8 bit = 0;
	u8 masque = 1;

	for(int i = 0; i < 8; ++i) {
		bit = (n & masque) >> i;
		if(! (i % 4) ) { printf(" "); }
		printf("%d", bit);
		masque <<= 1;
	}
}

/**
 * Description : Affiche la variable n en bit du poids
* 								fort au poids faible.
 * Entree : La variable sur 8 bits : n.
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
 * Description : Affiche la variable n en bit du poids
 * 								faible au poids fort.
 * Entree : La variable sur 32 bits : n.
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
 * Description : Affiche la variable n en bit du poids
 * 								fort au poids faible.
 * Entree : La variable sur 32 bits : n.
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
 * Description : Affiche la variable n en bit de poids
 * 								faible au poids fort.
 * Entree : La variable sur 80 bits : n.
 * */
void afficheBinU80v2(const u80_t n) {
  for(size_t j = 0; j < 10; ++j) {
    afficheBinU8v2(n.tab[j]);
  }
}

/**
 * Description : Affiche la variable n en bit de poids
 * 								fort au poids faible.
 * Entree : La variable sur 80 bits : n.
 * */
void afficheBinU80(const u80_t n) {
  for(size_t j = 0; j < 10; ++j) {
    afficheBinU8(n.tab[j]);
  }
}

/**
 * Description : Affiche les sous cles contenues dans le tableau.
 * Entree : La variable sur 80 bits : n.
 * */
void afficherSousCLe(const u32 sousCle[nbrSousCle]) {
	for(size_t i = 0; i < nbrSousCle; ++i) {
		printf("Sous cle n°%ld :", i+1); afficheBinU32(sousCle[i]); printf(" <=> %06x\n", sousCle[i]);
	}
}

/**
 * Description : Initialise la variable n à 0.
 * Entree : Un pointeur sur la variable de 80 bits : n.
 * */
void initU80(u80_t* n) {
  for(size_t i = 0; i < 10; ++i) {
    n->tab[i] = 0;
  }
}

/**
 * Description : Copie la variable cleMaitre dans la variable
 * 								registreK en commencant par le poids fort.
 * Entree : Un pointeur sur la variable : registreK pour le remplir.
 * 					La cle maitre : cleMaitre : que l'on doit copier
 * 						dans registreK.
 * */
void copieU32DansU80(u80_t* registreK, u32 cleMaitre) {
  for(size_t i = 2; cleMaitre != 0; --i) {
    registreK->tab[i] = cleMaitre & 0xffffff;
    cleMaitre >>= 8;
  }
}

/**
 * Description : Copie les champs de d'une varaible à l'autre.
 * Entree : Un pointeur sur la variable copie, pour le remplir.
 * 					La variable original, que l'on va copier.
 * */
void copieU80DansU80(u80_t* copie, const u80_t original) {
	for(size_t i = 0; i < 10; ++i) {
		copie->tab[i] = original.tab[i];
	}
}

/**
 * Description : 
 * Entree : .
 * */
u8 testSousCle(const u32 ki[nbrSousCle]) {
	u32 reponse[nbrSousCle] = {
		0x000000, 0x000000, 0x000001, 0x000001, 
		0x400062, 0x80002a,	0xc00033, 0x40005b,
		0x00064c, 0x800284, 0x400355
	};

	for(size_t i = 0; i < nbrSousCle; ++i) {
		if( reponse[i] != ki[i] ) { 
			// printf("ECHEC SOUS CLE N°%ld : attendue %x,
			// obtenue %x\n", i+1, reponse[i], ki[1]);
			return 0;
		}
	}

	return 1;
}