/**
* \file : jeu.c
* code pour le jeu
* \author Sabina Askerova
*/

#include "jeu.h"
#include "grille.h"
#include "io.h"

/** 
 * \fn compte_voisins_vivants_cyclique (int i, int j, grille g)
 * \param i i-eme ligne coord de la cellule
 * \param j j-ieme colonne coord de la cellule
 * \param g la grillle 
 * \return int nombre de voisins vivants en mode cyclique
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}
/**
 * \fn compte_voisins_vivants_non_cyclique (int i, int j, grille g)
 * \param i i-eme ligne coord de la cellule
 * \param j j-ieme colonne coord de la cellule
 * \param g la grille
 * \return int nombre de voisins vivants en mode non-cyclique
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;

	if((i - 1 >= 0) && (j - 1 >= 0)){
		if((i - 1 < l) && (j - 1 < c)){
			v+= est_vivante(i - 1, j - 1, g);
		}
	}
	if((i - 1 >= 0) && (j + 1 >= 0)){
		if((i - 1 < l) && (j + 1 < c)){
			v+= est_vivante(i - 1, j + 1, g);	
		}
	}

	if((i - 1 >= 0) && (j >= 0)){
		if((i - 1 < l) && (j < c)){
			v+= est_vivante(i - 1, j, g);
		}
	}

	if((i + 1 >= 0) && (j - 1 >= 0)){
		if((i + 1 < l) && (j - 1 < c)){
			v+= est_vivante(i + 1, j - 1, g);	
		}
	}
	
	
	if((i + 1 >= 0) && (j + 1 >= 0)){
		if((i + 1 < l) && (j + 1 < c)){
			v+= est_vivante(i + 1, j + 1, g);	
		}
	}
	if((i + 1 >= 0) && (j >= 0)){
		if((i + 1 < l) && (j  < c)){
			v+= est_vivante(i + 1, j, g);	
		}
	}

	if((i  >= 0) && (j + 1 >= 0)){
		if((i  < l) && (j -+ 1 < c)){
			v+= est_vivante(i, j + 1, g);
		}
	}

	if((i  >= 0) && (j - 1 >= 0)){
		if((i  < l) && (j - 1 < c)){
			v+= est_vivante(i, j - 1, g);
		}
	}

	return v;
}
//on assigne la fonction de calcul de voisins en mode cyclique au pointeur
int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

/**
 * \fn age_cellule_v(int i, int j, grille *g)
 * \param i i-eme ligne coord de la cellule
 * \param j j-ieme colonne coord de la cellule
 * \param g la grille
 * \return int age de la cellule en mode vieillissement
 */
int age_cellule_v(int i, int j, grille *g){
		if(g->cellules[i][j] > 0 && g->cellules[i][j] <= 8){
			g->cellules[i][j]++;
		}
		else if(g->cellules[i][j] == -1){
			g->cellules[i][j] = -1;
		} else{
			g->cellules[i][j] = 0;
			
		}
	return g->cellules[i][j];
}
/**
 * \fn age_cellule_non_v(int i, int j, grille *g)
 * \param i i-eme ligne coord de la cellule
 * \param j j-ieme colonne coord de la cellule
 * \param g la grille
 * \return int la valeur actuelle de la cellule
 */
int age_cellule_non_v(int i, int j, grille *g){
	return g->cellules[i][j];
}

int (*age_cellule) (int, int, grille*) = age_cellule_non_v;

/**
 * \fn evolue (grille *g, grille *gc)
 * \param g 
 * \param gc 
 * \brief fait evoluer la grille selon le nombre des voisins vivants et selon le mode de vieillissemetn OFF/ON
 */
void evolue (grille *g, grille *gc){
	copie_grille(*g,*gc); // copie temporaire de la grille, gc est une copie de g
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);
			int age = age_cellule(i, j, g);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ){
					set_morte(i,j,*g);
				} else{
					g->cellules[i][j] = age;
				}
			}
			else 
			{ // evolution d'une cellule morte
			
				if(est_non_viable(i,j,*g)){
					g->cellules[i][j] = -1;
				} else if( v==3 ){
					set_vivante(i,j,*g);
				} 
			}
				
			}
		}
	return;
}



/**
 * \fn Osc oscillante(grille* g)
 * \brief calcule le periode et le délai d'oscillation d'une colonie
 * 
 * \param g grille
 * \return Osc les infos d'oscillation de cette colonie
 */
Osc oscillante(grille* g){
	Osc o = malloc(sizeof(struct info_osc));
	//int result;
	//int temps = 1; // temps local pour le test
	int delai = 0;
	int period =1;

	grille gc; //copie de la grille g
	grille g3; //grille de comparaison
	grille g4; //grille de comparaison
	
	alloue_grille(g->nbl, g->nbc, &g4);
	copie_grille(*g, g4);
	alloue_grille(g->nbl, g->nbc, &g3);
	copie_grille(*g, g3);
	alloue_grille(g->nbl, g->nbc, &gc);
	copie_grille(*g, gc);
	grille g2; //grille intermediare necessaire pour l'évolution
	alloue_grille(g->nbl, g->nbc, &g2);
	evolue(&g3, &g2);

	int i=0;
	while(i < 1000){
        while(!(grilles_egales(g3, gc)) && period < 999){
            evolue(&g3, &g2);
            period++;
        }
        if(period < 999) {
			break;
		}
        if(grille_morte(&gc)){
			period=1; 
			break;}
        delai++;
		i++;
    }

    if(i==999){
		period=0;
	} 
	if(period > 100){ 
		period = 1;
		while(!grilles_egales(g3, gc)){
			evolue(&gc, &g2);
			delai++;
		
		}
		delai = delai % 1000;
		evolue(&gc, &g2);
		copie_grille(gc, g4);
		while(!grilles_egales(g4, gc)){
				evolue(&gc, &g2);
				period++;
		}
	}
	o->period = period;
	o->delai  = delai;
	libere_grille(&gc);
	libere_grille(&g2);
	libere_grille(&g3);
	return o;
}

