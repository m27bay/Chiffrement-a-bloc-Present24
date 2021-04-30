#ifndef Chiffrement_h
#define Chiffrement_h

#include "MyInclude.h"

void cadencementDeCle(u32 sousCle[nbrSousCle], const u32 cleMaitre);
u32 fctDeChiffrement(u32 mClaire, u32 sousCle[nbrSousCle]);

#endif