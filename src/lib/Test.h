#pragma once

#include "MyInclude.h"
#include "Chiffrement.h"
#include "Dechiffrement.h"
#include "Attaque2Present24.h"

u8 testSousCle(const u32 sousCle[nbrSousCle]);
void testChiffrementDechiffrement();
void testAttaque(u32 mClair, u32 mChiffre, u32 mClair2, u32 mChiffre2);