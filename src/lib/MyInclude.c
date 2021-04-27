#include "MyInclude.h"

void afficheBinU8v2(const u8 n) {
	u8 bit = 0;
	u8 masque = 1;
	for(int i=0; i<8; ++i) {
		bit = (n & masque) >> i;
		if(!(i%4)) printf(" ");
		printf("%d", bit);
		masque <<= 1;
	}
}

void afficheBinU8(const u8 n) {
	u8 bit = 0;
	u8 masque = 128;
	for(int i=7; i>=0; --i) {
		bit = (n & masque) >> i;
		if(!((7-i)%4)) printf(" ");
		printf("%d", bit);
		masque >>= 1;
	}
}

void afficheBinU32v2(const u32 n) {
	u32 bit = 0;
	u32 masque = 1;
	for(int i=0; i<32; ++i) {
		bit = (n & masque) >> i;
		if(!(i%4)) printf(" ");
		printf("%d", bit);
		masque <<= 1;
	}
}

void afficheBinU32(const u32 n) {
	u32 bit = 0;
	u32 masque = 0x80000000;
	for(int i=31; i>=0; --i) {
		bit = (n & masque) >> i;
		if(!((31-i)%4)) printf(" ");
		printf("%d", bit);
		masque >>= 1;
	}
}

void afficheBinU80v2(const u80_t n) {
  for(size_t j=0; j<10; ++j) {
    afficheBinU8v2(n.tab[j]);
  }
}

void afficheBinU80(const u80_t n) {
  for(size_t j=0; j<10; ++j) {
    afficheBinU8(n.tab[j]);
  }
}

void initU80(u80_t* n) {
  for(size_t i=0; i<10; ++i) {
    n->tab[i] = 0;
  }
}

void copieU32DansU80(u80_t* k, u32 cleMaitre) {
  for(size_t i=2; cleMaitre!=0; --i) {
    k->tab[i] = cleMaitre & 0xffffff;
    cleMaitre >>= 8;
  }
  printf("k :"); afficheBinU80(*k); printf("\n");
}

void copieU80DansU80(u80_t* copie, const u80_t original) {
	if(!copie) {
		printf("ERREUR : pointeur nul.");
		return;
	}
	for(size_t i=0; i<9; ++i) {
		copie->tab[i] = original.tab[i];
	}
}

u32 obtenirSousCle(const u80_t k) {
  u32 a, b, c;
  a = k.tab[5];
  b = k.tab[6];
  b <<= 8;
  c = k.tab[7];
  c <<= 16;
  u32 tmp = a | b | c;
  printf("tmp :"); afficheBinU32(tmp); printf("\n");

  return tmp;
}

void pivot61(u80_t* k) {
	u80_t copie;
	initU80(&copie);
	copieU80DansU80(&copie, *k);
	printf("k: "); afficheBinU80(*k); printf("\n");
	printf("copie: "); afficheBinU80(copie); printf("\n");

	//
	for(size_t i=7; i; --i) {
		k->tab[i+2] = k->tab[i];
		k->tab[i+2] >>= 3;
	}

	k->tab[0] = 0;
	k->tab[1] = 0;	
	printf("k: "); afficheBinU80(*k); printf("\n");

}

