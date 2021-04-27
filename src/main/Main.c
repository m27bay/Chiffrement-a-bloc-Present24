#include "../lib/Chiffrement.h"

int main(void) { 
  // Note le bit sur le poids fort
  u32 cleMaitre = 0xf34ab7;
  printf("cleMaitre :"); afficheBinU32(cleMaitre); printf("\n");

  u32 ki[11];
  cadencementDeCle(ki, cleMaitre);

  return 0;
}
