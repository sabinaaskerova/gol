/**
 * @file io_cairo.h
 * @author Sabina Askerova
 * @brief l'en-tête pour io_cairo.c
 */
#ifndef __IO_H_CAIRO
#define __IO_H_CAIRO

#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"

extern int vieillissement;
extern int t; //temps d'évolution de la colonie
extern int (*compte_voisins_vivants) (int, int, grille); //pointeur de fonction pour calcul des voisins vivants
extern int (*age_cellule) (int, int, grille*);

//affichage d'une fenetre, d'une grille, des informations en mode graphique
void affiche_grille_cairo(grille g, cairo_surface_t *surface);

//déroulement du jeu en mode graphique
void debut_jeu_cairo(grille *g, grille *gc);

#endif