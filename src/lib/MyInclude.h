#include<stdio.h>
#include<stdlib.h>

#include<string.h>

#define nbrSousCle 11

typedef unsigned char u8;
typedef char i8;
typedef unsigned int u32;

typedef struct u80_s {
  u8 tab[10];
} u80_t;

void afficheBinU8v2(const u8);
void afficheBinU32v2(const u32);
void afficheBinU80v2(const u80_t);

void afficheBinU8(const u8);
void afficheBinU32(const u32);
void afficheBinU80(const u80_t);

void afficherSousCLe(const u32[nbrSousCle]);
u8 testSousCle(const u32[nbrSousCle]);

void initU80(u80_t*);
void copieU32DansU80(u80_t*, u32);
void copieU80DansU80(u80_t*, const u80_t);

void inverserBit(u32*, const u8, const u8);