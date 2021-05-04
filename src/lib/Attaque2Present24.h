#pragma once

#include "Chiffrement.h"
#include "Dechiffrement.h"
#include "MyInclude.h"

// Structure contenant les informations nécessaires au thread
typedef struct {
	u32* liste;
	u8 debut;
	u8 fin;
} message_t;

void creerListeChiffrement(u32 listeClair[16777216], u32 mClair);

void creerListeDechiffrement(u32 listeChiffre[16777216],
                        u32 mChiffre);

void trouverCollisions(u32 collision[16777216],
                    u32 listeClair[16777216],
                    u32 listeChiffre[16777216]);
