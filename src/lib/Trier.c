#include "Trier.h"

void echange(msgCle_t* a, msgCle_t* b) {
  msgCle_t tmp = *a;
  *a = *b;
  *b = tmp;
}

u32 partition(msgCle_t* liste, i32 deb, i32 fin) {
  u32 pivot = liste[fin].message;
  i32 i = (deb - 1);
  for(i32 j = deb; j < fin; ++j) {
    if(liste[j].message < pivot) {
      i++;
      echange(&liste[i], &liste[j]);
    }
  }
  echange(&liste[i + 1], &liste[fin]);

  return (i + 1);
}

void quickSort(msgCle_t* liste, i32 deb, i32 fin) {
  if(deb < fin) {
    i32 positionPartition = partition(liste, deb, fin);
    quickSort(liste, deb, positionPartition - 1);
    quickSort(liste, positionPartition + 1, fin);
  }
}

void trieCroissant(msgCle_t* liste, u32 tailleListe) {
  quickSort(liste, 0, tailleListe - 1);
}

i32 rechercheDichotomique(msgCle_t* liste, u32 message, i32 deb, i32 fin) {
  i32 milieu = 0;
  if(fin < deb) { return -1; }
  else {
    milieu = ( (deb + fin) / 2 );
    if(message == liste[milieu].message) { return liste[milieu].cle; }
    else { 
      if(message < liste[milieu].message) {
        return rechercheDichotomique(liste, message, deb, milieu - 1);
      }
      return rechercheDichotomique(liste, message, milieu + 1, fin);
    }
  }
}
