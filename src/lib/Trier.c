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

void rechercheDichotomique(msgCle_t* liste, msgCle_t msgCle, i32 deb, i32 fin,
                          u32 mClair2, u32 mChiffre2) {
  i32 milieu = 0;
  i32 milieu2 = 0;
  if(fin < deb) { return; }
  else {
    milieu = ( (deb + fin) / 2 );
    if(msgCle.message == liste[milieu].message) {
      milieu2 = milieu;
      while(msgCle.message == liste[milieu2].message) {
        trouverClesCandidates(liste[milieu2].cle, msgCle.cle, mClair2, mChiffre2);
        milieu2--;
      }
      milieu2 = milieu+1;
      while(msgCle.message == liste[milieu2].message) {
        trouverClesCandidates(liste[milieu2].cle, msgCle.cle, mClair2, mChiffre2);
        milieu2++;
      }
    }
    else { 
      if(msgCle.message < liste[milieu].message) {
        return rechercheDichotomique(liste, msgCle, deb, milieu - 1, mClair2, mChiffre2);
      }
      return rechercheDichotomique(liste, msgCle, milieu + 1, fin, mClair2, mChiffre2);
    }
  }
}
