#include "Chiffrement.h"

void cadencementDeCle(u32* ki, u32 cleMaitre) {
  // Copie cle maitre dans le 24 bits de poids fort
  u80_t k;
  initU80(&k);
  copieU32DansU80(&k, cleMaitre);

  ki[0] = obtenirSousCle(k);
  pivot61(&k);

  ki = NULL;
}

u32 fctDeChiffrement(u32 m, u32* ki) {

  return 0;
}