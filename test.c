#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "files_man.h"

int main(void) {
  peliculas *pel = obtener_peliculas(".");
  printf("Cantidad de archivos en Raiz: %d\n", pel->cant_peliculas);
  print_pel(pel);
  return 0;
}
