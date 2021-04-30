#ifndef Chiffrement_h
#define Chiffrement_h

#include "MyInclude.h"

void cadencementDeCle(u32 sousCle[nbrSousCle], const u32 cleMaitre);
u32 fctDeChiffrement(u32 mClaire, u32 sousCle[nbrSousCle]);

void testChiffrementSubstitution(u32 etat);
void testChiffrementPermutation(const u32 etat);

#endif