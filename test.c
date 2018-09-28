#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "files_man.h"
#include <time.h>

int main(void) {
        clock_t begin = clock();
        peliculas *pel = obtener_peliculas(".");
        printf("Cantidad de archivos en Raiz: %d\n", pel->cant_peliculas);
        print_pel(pel);
        int Flag = pel->cant_peliculas;
        while (Flag > 0) {
          organizar(pel);
          free_peliculas(pel);
          if (Flag > 0) {
            pel = obtener_peliculas(".");
            Flag = pel->cant_peliculas;
          }
        }
        free_peliculas(pel);
        clock_t end = clock();
        double time_s = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Archivos organizados en: %lf segundos\n",time_s);
        navegador(".");
        return 0;
}
