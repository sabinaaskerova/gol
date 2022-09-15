.PHONY :clean
CFLAGS = -Wall -g
CPPFLAGS = -I/usr/include/cairo
LDFLAGS = -lcairo -lm -lX11
IFLAGS = -Iinclude
OPATH = obj/
CPATH = src/
BPATH = bin/
MODE =

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

ifeq ($(MODE), TEXTE)	
main : main.o io.o jeu.o grille.o ranlib
	mkdir -p $(BPATH)
	gcc $(CFLAGS) $(CPPFLAGS) -o main -L 'lib' -ljeu
	mv -f $@ $(BPATH)

main.o : main.c io.o jeu.o grille.o
jeu.o : jeu.c jeu.h
io.o : io.c io.h
grille.o : grille.c grille.h

%.o: %.c
	mkdir -p $(OPATH)
	gcc $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c $<
	mv $@ $(OPATH)

ranlib : 
	mkdir -p lib
	ar -crv libjeu.a $(OPATH)main.o $(OPATH)io.o $(OPATH)jeu.o $(OPATH)grille.o
	mv libjeu.a lib

else 
ifeq ($(MODE),)

main: main_cairo.o io_cairo.o jeu.o grille.o ranlib
	mkdir -p $(BPATH)
	gcc $(CFLAGS) $(LDFLAGS) -o main -L 'lib' -ljeu
	mv -f $@ $(BPATH)

main_cairo.o : main_cairo.c jeu.o io_cairo.o grille.o
jeu.o : jeu.c jeu.h grille.o
io_cairo.o : io_cairo.c io_cairo.h grille.o
grille.o : grille.c grille.h

%.o: %.c
	mkdir -p $(OPATH)
	gcc $(CFLAGS) -c $< $(CPPFLAGS) $(IFLAGS)
	mv $@ $(OPATH)

ranlib : 
	mkdir -p lib
	ar -crv libjeu.a $(OPATH)main_cairo.o $(OPATH)io_cairo.o $(OPATH)jeu.o $(OPATH)grille.o
	mv libjeu.a lib

endif
endif 

clean : 
	rm $(OPATH)* $(BPATH)*
	rmdir $(OPATH) $(BPATH)

docs : 
	doxygen Doxyfile

dist : 
	tar -lcvf AskerovaSabina-GoL-0.5.tar.xz src include makefile doc