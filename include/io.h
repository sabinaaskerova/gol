/**
 * \file io.h
 * \brief l'en-tête pour io.c
 * \author Sabina Askerova
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"



extern int vieillissement;
extern int t;
extern int (*compte_voisins_vivants) (int, int, grille);
extern int (*age_cellule) (int, int, grille*);
// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
