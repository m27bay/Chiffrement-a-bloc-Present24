#pragma once

#include "Chiffrement.h"
#include "Dechiffrement.h"
#include "MyInclude.h"
#include "Trier.h"

void remplirListe(msgCle_t* liste, u32 tailleListe, u32 message, u8 flag);
void trouverClesCandidates(u32 cle, u32 cle2, u32 mClair2, u32 mChiffre2);
void trouverCollisions(msgCle_t* listeClair, msgCle_t* listeChiffre,
                      u32 tailleListe, u32 mClair2, u32 mChiffre2);

