/**
* \file : io.c
* \author Sabina Askerova
*/
#include "io.h"
#include "jeu.h"

#define MAX 256

int cyclique = 1;
int vieillissement = 0;
int t = 0;

/**
 * \fn affiche_trait (int c)
 * \param c 
 * \return rien
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
/**
 * \fn affiche_ligne (int c, int* ligne)
 * \param c 
 * \param ligne 
 * \return rien
 */
void affiche_ligne (int c, int* ligne){
	int i;

	for (i=0; i<c; ++i) {
		if(ligne[i] == -1){
				printf ("|\033[31;1;1m X \033[0m");
		} else{
			if( vieillissement == 0){
				if (ligne[i] == 0 ){
					printf ("|   ");
				} else {
					printf ("|\033[96;1;1m 0 \033[0m");
				}
		} else{
			if (ligne[i] == 0 ){
				printf ("|   ");
			} else {
				printf ("|\033[96;1;1m %d \033[0m", ligne[i] - 1);
			}

		}
		}
	}

	printf("|\n");
	return;
}

/**
 * \fn affiche_grille (grille g)
 * \param g grille à afficher
 * \return rien
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	//printf("\n");
	system("clear");
	printf("Temps d'évolution:\033[95;1;1m %d\033[0m\n", t);
	if(cyclique == 1){
		printf("Mode cyclique\033[32;1;1m activé \033[0m\n");
	} else {
		printf("Mode cyclique\033[31;1;1m desactivé \033[0m\n");
	}
	if(vieillissement == 1){
		printf("Mode vieillissement\033[32;1;1m activé \033[0m\n");
	} else{
		printf("Mode vieillissement\033[31;1;1m desactivé \033[0m\n");
	}
	
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}
/**
 * \param g grille à effacer
 * \return rien
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * \fn debut_jeu(grille *g, grille *gc)
 * \param g 
 * \param gc 
 * \return rien
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {	
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				t++; //temps d'evolution augmente
				efface_grille(*g);
				affiche_grille(*g);
				
				break;
			}
			case 'n':
			{
				//touche 'n' pour le nom de la grille
				t = 0; //temps d'evolution réinitialisé pour la nouvelle grille
				libere_grille(g);
				libere_grille(gc);
				char nom[MAX]; //chemin du fichier grille
				
				printf("Entrez le nom de la grille\n");
				scanf("%s", nom);
				init_grille_from_file(nom, g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
				break;
			}
			case 'c':
			{
				if(cyclique == 1){
					cyclique = 0;
					compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
					efface_grille(*g);
					affiche_grille(*g);
				} else{
					cyclique = 1;
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
					efface_grille(*g);
					affiche_grille(*g);
				}
				c = getchar();
				break;
			}

			case 'v':
			{
				if(vieillissement == 0){
					vieillissement = 1;
					age_cellule = age_cellule_v;
					efface_grille(*g);
					affiche_grille(*g);
					
					
				} else{
					vieillissement = 0;
					age_cellule = age_cellule_non_v;
					efface_grille(*g);
					affiche_grille(*g);
					
				}
				//ajouter getchar en plus pour faire manger le \n
				c = getchar();
				break;
			}

			case 'o':{

				//si vieillessement activé ce n'est considere comme oscillante 
				//que a partir de l'etape quand ca devient vide
				//car l'age des cellules change ce n'est pas la meme configuratioin donc pas oscillante a cet etape
				//int period = oscillante(g);
				//int delai = calcul_delai(g);
				Osc o = oscillante(g);
				int period = o->period;
				int delai = o->delai;
				//int delai;
				//int period;
				/*
				if(period != 0){
					printf("\n###Test d'oscillation :###\n\n");
        			if(period==-1){
					printf("Pas d'oscillation\n\n");
					printf("Oscillation prévue à partir du temps %d, de période %d\n" , delai, period);
					
					}else{
						printf("Oscillation prévue à partir du temps %d, de période %d\n" , delai, period);
					}
        			 
    
				} */
				printf("Le delai de l'oscillation est egal a %d\n", delai);
					printf(" Le période est égal à : %d\n", period);
				/*
				if(period == 0){
					printf("Le delai de l'oscillation est egal a %d\n", delai);
					printf("La colonie n'est pas oscillante à cet étape\n");
					printf("Le période est égal à : %d\n", period);
					
				} else{
					printf("Le delai de l'oscillation est egal a %d\n", delai);
					printf(" Le période est égal à : %d\n", period);
					
					
				}
				*/
				c = getchar();
				//break;
			}

			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		
		c = getchar(); 
	}
	return;	
}
