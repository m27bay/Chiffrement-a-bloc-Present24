#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define nbrSousCle 11
#define tailleCle 16777216

typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;

typedef struct u80_s {
  u8 tab[10];
} u80_t;

u8 tabSubstitution[16];
u8 tabPermutation[24];

void afficheBinU8v2(const u8 n);
void afficheBinU32v2(const u32 n);
void afficheBinU80v2(const u80_t n);

void afficheBinU8(const u8 n);
void afficheBinU32(const u32 n);
void afficheBinU80(const u80_t n);

void afficherSousCLe(const u32 sousCle[nbrSousCle]);
u8 testSousCle(const u32 sousCle[nbrSousCle]);

void initU80(u80_t* n);
void copieU32DansU80(u80_t* registreK, u32 cleMaitre);
void copieU80DansU80(u80_t* copie, const u80_t original);