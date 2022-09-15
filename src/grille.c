/**
* \file : grille.c
* code pour les grilles
* \author Sabina Askerova
*/
#include "grille.h"

/**
 * \fn void init_grille_from_file (char * filename, grille* g) 
 * initialise la grille à partir d'un fichier texte
 * \relatesalso grille
 * \param filename le fichier qui sera lu
 * \param g pointeur sur la grille
 * \return rien
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes = 0;
	int non_vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile, "%d", & non_vivantes);
	for (n=0; n< non_vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		non_viable(i,j,*g);
	}

	
	fclose (pfile);
	return;
}

/**
 * \fn copie_grille (grille gs, grille gd)
 * fait une copie de la grille donnée
 * \relatesalso grille
 * \param gs grille initiale
 * \param gd grille dans laquelle on copie la grille initiale
 * \return rien
 */
void copie_grille(grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

 /**
* \relatesalso grille
* \param l le nombre de lignes
* \param c nombre de colonnes
* \param g un pointeur sur une structure de gille
* \ alloue une grille de taille l*c, initialise toutes les cellules à mortes
* \return rien 
*/
void alloue_grille (int l, int c, grille* g){
    //g = (grille*) malloc(sizeof(grille));
    g->nbl = l;
    g->nbc = c;
    g->cellules = (int**) malloc(sizeof(int*)*l);

    for(int i = 0; i < l; i++){
        g->cellules[i] = (int*) malloc(sizeof(int)*c);
		for(int j = 0; j < c; j++){
            set_morte(i, j, *g);
    	}
	}
}

/**
* \fn libere_grille (grille* g)
* \relatesalso grille
* \param g un pointeur sur une structure de gille
* libère une grille
* \return rien 
*/
void libere_grille (grille* g){
    for(int i = 0; i < g->nbl; i++){
        free(g->cellules[i]);
    }
    free(g->cellules);
}

int grilles_egales(grille g1, grille g2){
	int result = 1;
	for(int i = 0; i < g1.nbl; i++){
		for(int j = 0; j < g1.nbc; j++){
			if(g1.cellules[i][j] != g2.cellules[i][j]){
				result = 0;
			}
		}
	}

	return result;
}

int grille_morte(grille *g){
	int res = 1;
    for(int i=0; i < g->nbl; i++){
        for(int j=0; j < g->nbc; j++){
            if(g->cellules[i][j] != 0 && g->cellules[i][j] != -1){
				res = 0;
			} 
        }
    }
    return res;
}