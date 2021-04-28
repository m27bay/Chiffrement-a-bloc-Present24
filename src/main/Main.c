#include "../lib/Chiffrement.h"

// #define DEBUG 1
#define DEBUG 0

int main(void) {
  if(DEBUG) {
    
  }
  else {
    // Note le bit sur le poids fort
    u32 cleMaitre = 0x000000;

    //
    u32 ki[11];
    cadencementDeCle(ki, cleMaitre);
    afficherSousCLe(ki);
    printf("testSousCle : %d\n", testSousCle(ki));

    //
    u32 messageClaire = 0x000000;
    printf("messageChiffre : %x\n", fctDeChiffrement(messageClaire, ki));
  }

  return 0;
}
