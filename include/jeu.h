/**
 * \file jeu.h
 * \author Sabina Askerova
 * \brief l'en-tête pour jeu.c
 */
#ifndef __JEU_H
#define __JEU_H

#include <stdio.h>
#include <stdlib.h>
#include "grille.h"

/**
 * \typedef typedef struct info_osc
 * \ structure pour les informations d'oscillation d'une colonie
 */
typedef struct info_osc
{
    int period;
    int delai;
} *Osc;


// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants_cyclique (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords ne sont pas cycliques.
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

int age_cellule_non_v(int i, int j, grille *g);

int age_cellule_v(int i, int j, grille *g);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

void set_vieilli(int i, int j, grille *g);

//calcul du période et du délai d'oscillation de la colonie
Osc oscillante(grille* g);
#endif
