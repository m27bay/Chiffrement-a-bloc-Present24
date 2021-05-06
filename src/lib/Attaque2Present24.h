#pragma once

#include "Chiffrement.h"
#include "Dechiffrement.h"
#include "MyInclude.h"
#include "Trier.h"

void remplirListe(msgCle_t* liste, u32 tailleListe, u32 message, u8 flag);

void trouverCollisions(pairCle_t* collision, msgCle_t* listeClair,
                      msgCle_t* listeChiffre, u32 tailleListe);

void trouverClesCandidates(pairCle_t* collision, u32 tailleCollision,
                          u32 mClair2, u32 mChiffre2);
