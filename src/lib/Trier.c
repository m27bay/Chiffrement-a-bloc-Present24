#include "Trier.h"

/**
 * Description : Echange deux valeurs.
 * Entre : La valeur a.
 *         La valeur b.
 * */
void echange(msgCle_t* a, msgCle_t* b) {
  msgCle_t tmp = *a;
  *a = *b;
  *b = tmp;
}

/**
 * Description : Echange les valeurs de la liste entre le debut et la fin
 *               afin de trie la liste par ordre croissant.
 * Entree : La liste a trie.
 *          Le debut de la liste.
 *          La fin de la liste.
 * */
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

/**
 * Description : Algorithme quick sort qui permet de trier les elements
 *               de la liste entre le debut et la fin par ordre croissant.
 * Entree : La liste a trie.
 *          Le debut de la liste.
 *          La fin de la liste.
 * */
void quickSort(msgCle_t* liste, i32 deb, i32 fin) {
  if(deb < fin) {
    i32 positionPartition = partition(liste, deb, fin);
    quickSort(liste, deb, positionPartition - 1);
    quickSort(liste, positionPartition + 1, fin);
  }
}

/**
 * Description : Applique l'algorithme de quick sort pour
 *               trier la liste dans l ordre croissant.
 * Entree : La liste a trie.
 *          La taille de la liste.
 * */
void trieCroissant(msgCle_t* liste, u32 tailleListe) {
  quickSort(liste, 0, tailleListe - 1);
}

/**
 * Description : Applique l'algorithme de recherche dichotomique et teste
 *               les cles trouvees.
 * Entree : La liste trie par ordre croissant a parcourir.
 *          Le message et sa cle a trouver.
 *          Le debut de la liste.
 *          La fin de la liste.
 *          Un nouveau message clair.
 *          Un nouveau message chiffre.
 * */
void rechercheDichotomique(msgCle_t* liste, msgCle_t msgCle, i32 deb, i32 fin,
                          u32 mClair2, u32 mChiffre2) {
  i32 milieu = 0;
  i32 milieu2 = 0;

  // Element non present dans la liste.
  if(fin < deb) { return; }
  
  else {
    // Calcule du milieu.
    milieu = ( (deb + fin) / 2 );

    // Element trouve.
    if(msgCle.message == liste[milieu].message) {

      // D'autre cle plus basse dans la liste ?
      milieu2 = milieu;
      while(msgCle.message == liste[milieu2].message) {
        // Test de cles trouve.
        trouverClesCandidates(liste[milieu2].cle, msgCle.cle, mClair2, mChiffre2);
        milieu2--;
      }

      // D'autre cle plus haute dans la liste ?
      milieu2 = milieu+1;
      while(msgCle.message == liste[milieu2].message) {
        // Test de cles trouve.
        trouverClesCandidates(liste[milieu2].cle, msgCle.cle, mClair2, mChiffre2);
        milieu2++;
      }
    }

    // Element non trouve.
    else {
      // Liste trie par ordre croissant
      // Element plus petit, donc dans la moitie basse de la liste. 
      if(msgCle.message < liste[milieu].message) {
        return rechercheDichotomique(liste, msgCle, deb, milieu - 1, mClair2, mChiffre2);
      }
      // Element plus grand, donc dans la moitie haute de la liste. 
      return rechercheDichotomique(liste, msgCle, milieu + 1, fin, mClair2, mChiffre2);
    }
  }
}
