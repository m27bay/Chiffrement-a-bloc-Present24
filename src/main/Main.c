#include "../lib/Chiffrement.h"

// #define DEBUG 1
#define DEBUG 0

int main(void) {
  if(DEBUG) {
    u8 a = 185; // 1011 1001
    a &= 0x7f;
    printf("a : "); afficheBinU8(a); printf("\n");
  }
  else {
    // Note le bit sur le poids fort
    u32 cleMaitre = 0x000000;

    //
    u32 ki[11];
    cadencementDeCle(ki, cleMaitre);
    afficherSousCLe(ki);
    printf("testSousCle : %s\n", ( testSousCle(ki) ? "Succes." : "Erreur." ) );

    //
    u32 messageClaire = 0x000000;
    printf("messageChiffre : %x\n", fctDeChiffrement(messageClaire, ki));
  }

  return 0;
}
