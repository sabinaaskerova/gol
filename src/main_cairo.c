/**
 * \file main_cairo.c
 * \author Sabina Askerova
 */
#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/X.h>
#include <X11/Xresource.h>
#include <X11/keysymdef.h>
#include "io_cairo.h"
#include "grille.h"
#include "jeu.h"

#define SIZEX 800
#define SIZEY 800

#define MAX 256
/**
 * \brief appel des fonctions pour le déroulement du jeu en mode graphique. Affichage d'une fênetre graphique avec la grille passée en paramètre
 * 
 * \param argc 
 * \param argv fichier de la grille
 * \return int 
 */
int main(int argc, char ** argv){	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	debut_jeu_cairo(&g, &gc);
	libere_grille(&g);
	libere_grille(&gc);
	return 0;

}