#pragma once

#include "MyInclude.h"
#include "Attaque2Present24.h"

void trieCroissant(msgCle_t* liste, u32 tailleListe);
void rechercheDichotomique(msgCle_t* liste, msgCle_t message, i32 deb, i32 fin,
                          u32 mClair2, u32 mChiffre2);