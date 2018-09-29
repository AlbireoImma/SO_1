all: peliculas

# Regla para el programa principal
peliculas: peliculas.o
	gcc -o peliculas peliculas.o

peliculas.o: peliculas.c files_man.h lista.h
	gcc -c peliculas.c

run:
	./peliculas

clean:
	rm -f peliculas *.o
