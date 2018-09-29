#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "files_man.h"

int main(void) {
        peliculas *pel = obtener_peliculas(".");
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
        navegador(".");
        return 0;
}
