#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define nbrSousCle 11      //< Le cadencement de cle donne 11 sous cles.
#define tailleCle 16777216 //< = 2^24

typedef unsigned char u8; //< Code sur 8 bits.
typedef unsigned int u32; //< Code sur 32 bits.
typedef int i32;					//< Code sur 32 bits.

// Structure representant une variable sur 80 bits.
typedef struct u80_s {
  u8 tab[10];
} u80_t;

void initU80(u80_t* n);
void copieU32DansU80(u80_t* registreK, u32 cleMaitre);
void copieU80DansU80(u80_t* copie, const u80_t original);
// ################################################

// Structure associant un message et sa cle.
typedef struct {
	u32 message;
	i32 cle;
} msgCle_t;

// Structure assciant deux cles entre elles.
typedef struct {
	i32 cle;
	i32 cle2;
} pairCle_t;

// Tableau définie dans MyInclude.c, utilise dans d'autre fichiers.
u8 tabSubstitution[16];
u8 tabPermutation[24];

u8 invTabSubstitution[16];
u8 invTabPermutation[24];
// ################################################################

// Fonction d'affiche en binaire.
void afficheBinU8v2(const u8 n);
void afficheBinU32v2(const u32 n);
void afficheBinU80v2(const u80_t n);

void afficheBinU8(const u8 n);
void afficheBinU32(const u32 n);
void afficheBinU80(const u80_t n);
// ##############################

//
void afficherSousCLe(const u32 sousCle[nbrSousCle]);
