/**
 * \file io_cairo.c
 * \author Sabina Askerova
 * \brief affichage et deroulement du jeu en mode graphique avec bibliothèques cairo et X11
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
#include "io_cairo.h"
#include <X11/keysymdef.h>

#define SIZEX 800
#define SIZEY 800

#define MAX 256 //taille max du nom du fichier grille*.txt

int cyclique = 1;
int vieillissement = 0; 
int t = 0; //variable pour le temps d'évolution
char *temps; //chaîne de caractères pour l'affichage du temps d'évolution
char *age; //chaîne de caractères pour l'affichage de l'age d'une cellule
char *p;//chaîne de caractères pour l'affichage du période d'oscillation
char *d; //chaîne de caractères pour l'affichage du délai d'oscillation

/**
 * \brief affiche une grille en mode graphique
 * \param g la grille à afficher
 * \param surface surface d'affichage
 */
void affiche_grille_cairo(grille g, cairo_surface_t *surface){

	int largeur = g.nbc * 50+40;
	int hauteur = g.nbl *50+130;

	temps = malloc(sizeof(char)*3);
	sprintf (temps, "%d", t);
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
	cairo_paint(cr);

	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	cairo_move_to(cr, 5, 30);
	cairo_set_font_size(cr, 20);
	cairo_select_font_face(cr, "Purisa",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
	cairo_show_text(cr, "Temps d'évolution : ");
	cairo_show_text(cr,temps);
	free(temps);
	cairo_move_to(cr, 5, 50);
	cairo_show_text(cr, "Mode cyclique : ");

	//l'affichage des modes
	if(cyclique){
		cairo_show_text(cr, "activé");
	}else{
		cairo_show_text(cr, "desactivé");
	}
	cairo_move_to(cr, 5, 70);
	cairo_show_text(cr, "Mode vieillissement : ");
	if(vieillissement){
		cairo_show_text(cr, "activé");
	}else{
		cairo_show_text(cr, "desactivé");
	}
	cairo_move_to(cr, 5, 100);
	
	//boucle principale pour l'affichage d'une grille
	for (int i=0, a=130 ;  i<g.nbl ; i++, a+=50){
		for (int j=0, b=40 ; j<g.nbc ; j++, b+=50){
			age = malloc(sizeof(char)*3);
			sprintf (age, "%d", g.cellules[i][j]);
			cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
			cairo_move_to(cr, b-10, a-10);
			cairo_line_to(cr, b-10,a+40);
			cairo_move_to(cr, b-10, a-10);
			cairo_line_to(cr, b+40, a-10);
			cairo_move_to(cr, b+40, a-10);
			cairo_line_to(cr, b+40,a+40);
			cairo_move_to(cr, b+40, a+40);
			cairo_line_to(cr, b-10,a+40);
			cairo_stroke(cr);
			
			cairo_rectangle(cr,b,a,30,30);

			if(g.cellules[i][j] == -1){
				cairo_rectangle(cr,b,a,30,30);
				cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); //cellules non viables sont rouges
				cairo_fill(cr);
			} else{
				if( vieillissement == 0){ //mode 'v' non alume
					if (g.cellules[i][j] == 0 ){ //cellules mortes
						cairo_rectangle(cr,b,a,30,30);
						cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
						cairo_fill(cr);
					} else{ // cellules vivantes 
						cairo_rectangle(cr,b,a,30,30);
						cairo_set_source_rgb(cr, 0.0, 1.0, 1.0); 
						cairo_fill(cr);
					}
				} else{ 
					if (g.cellules[i][j] == 0 ){ //cellules mortes mode 'v'
						cairo_rectangle(cr,b,a,30,30);
						cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); //white
						cairo_fill(cr);
					} else{ //cellules vivantes mode 'v'
						cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
						cairo_text_extents_t extents;
						cairo_set_font_size(cr, 20);
						cairo_select_font_face(cr, "Times",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
						cairo_text_extents(cr, "8", &extents);
						cairo_move_to(cr, largeur/(g.nbc*3)+b-extents.width, hauteur/(g.nbl*3)+a);
						cairo_show_text(cr,age);
						free(age);

					}
				}
			}		
		}
	}

	//affichage des informations supplémentaires pour l'utilisateur
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_set_font_size(cr, 20);
	cairo_select_font_face(cr, "Helvetica",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
	cairo_move_to(cr, 30, 730);
	cairo_show_text(cr, "Click gauche : evolution");
	cairo_move_to(cr, 30, 750);
	cairo_show_text(cr, "Click droit : quitter le jeu");
	cairo_move_to(cr, 400, 730);
	cairo_show_text(cr, "v: vieillessement on/off");
	cairo_move_to(cr, 400, 750);
	cairo_show_text(cr, "c: mode cyclique on/off");
	cairo_move_to(cr, 400, 770);
	cairo_show_text(cr, "n: chemin d'une nouvelle grille à charger");
	cairo_destroy(cr);
}

/**
 * \fn void debut_jeu_cairo(grille *g, grille *gc)
 * \brief boucle principal du jeu en mode graphique
 * \param g du type grille
 * \param gc du type grille(utilisé pour évolution de la colonie)
 */
void debut_jeu_cairo(grille *g, grille *gc){
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	//création d'une fênetre
	scr = DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);
	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie - Sabina Askerova");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	while(1) {
		//tracking des évenements
		XNextEvent(dpy, &e);

		if(e.type ==Expose && e.xexpose.count<1){
			affiche_grille_cairo(*g, cs);
		} else if(e.type ==ButtonPress){
			if(e.xbutton.button ==3){ //click droit ferme le jeu
				break;
			} else if(e.xbutton.button == 1){ //click gauche fait évoluer la colonie des cellules
				evolue(g, gc);
				t++;
				affiche_grille_cairo(*g, cs);
			}
		}

		if(e.type == KeyPress){ 
			switch (XLookupKeysym(&e.xkey, 0)) {

				case 'v':{ //activation du mode de vieillessement
					if(vieillissement){
						vieillissement = 0;
						age_cellule = age_cellule_non_v;
					} 
					else{
						vieillissement = 1;
						age_cellule = age_cellule_v;
					}
					affiche_grille_cairo(*g, cs);
					break;
				}
                case 'c':{
					if(cyclique){
						cyclique = 0;
						compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
					} else{
						cyclique = 1;
						compte_voisins_vivants = compte_voisins_vivants_cyclique;
					}
					affiche_grille_cairo(*g, cs);
					break;
				}                
				case 'n':{
					t = 0; //temps d'evolution réinitialisé pour la nouvelle grille
					libere_grille(g);
					libere_grille(gc);
					char nom[MAX];
					printf("Entrez le nom de la grille\n");
					scanf("%s", nom);
					init_grille_from_file(nom, g);
					alloue_grille(g->nbl, g->nbc, gc); //on charge la nouvelle grille donnée
					affiche_grille_cairo(*g, cs);
					break;
				}

				case 'o':{
				//si vieillessement activé ce n'est considere comme oscillante 
				//que a partir de l'etape quand ca devient vide
				//car l'age des cellules change ce n'est pas la meme configuratioin donc pas oscillante a cet etape
				Osc o = oscillante(g);
				int period = o->period;
				int delai = o->delai;
				p = malloc(sizeof(char)*3);
				sprintf (p, "%d", period);
				d = malloc(sizeof(char)*3);
				sprintf (d, "%d", delai);
				cairo_t *cr;
				cr=cairo_create(cs);
				cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
				cairo_set_font_size(cr, 20);
				cairo_select_font_face(cr, "Helvetica",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
				cairo_move_to(cr, 30, 690);
				
				if(period > 99){
					cairo_show_text(cr, "Le delai de l'oscillation est egal a ");
					cairo_show_text(cr, d);
					cairo_move_to(cr, 30, 710);
					cairo_show_text(cr, "La colonie est oscillante. Le période est égal à :");
					cairo_show_text(cr,p);
				} else{
					cairo_show_text(cr, "Le delai de l'oscillation est egal a ");
					cairo_show_text(cr, d);
					cairo_move_to(cr, 30, 710);
					cairo_show_text(cr, "La colonie est oscillante. Le période est égal à :");
					cairo_show_text(cr,p);
					
					
				}	
				free(p);
				free(d);			
				break;
			}
				}
		}
}
			cairo_surface_destroy(cs); // destroy cairo surface
			XCloseDisplay(dpy);

}
