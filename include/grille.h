/**
* \file : grille.h
* \brief l'en-tête pour grille.c
* \author Sabina Askerova
*/
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
* \typedef typedef struct grille
* \ Déclaration de la structure de grille
*/
typedef struct {
    int nbl; /**nombre de lignes */
    int nbc; /** nombre de colonnes */
    int** cellules; /** tableau de tableau de cellules */
} grille;
 
//alloue une grille de taille l*c, initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

//libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// teste si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){
    if(g.cellules[i][j] > 0 && g.cellules[i][j] <= 8){
        return 1;
    } else{
        return 0;
    }
}
// rend non viable la cellule (i,j) de la grille g
static inline void non_viable(int i, int j, grille g){
    g.cellules[i][j] = -1;
}
// teste si la cellule (i,j) de la grille g est non viable
static inline int est_non_viable(int i, int j, grille g){
    return g.cellules[i][j] == -1;
}

// recopie gs dans gd (sans allocation)
void copie_grille(grille gs, grille gd);


//teste si les deux grilles sont égales
int grilles_egales(grille g1, grille g2);

//teste si la grille est morte
int grille_morte(grille *g);

#endif
