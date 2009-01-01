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
  int i;
  FILE *file;
  char genero[250];
  char anio[250];
  for (i = 0; i < pel->cant_peliculas; i++) {
    printf("Abriendo: %s\n",pel->peliculas[i]);
    file = fopen(pel->peliculas[i],"r");
    if (file =NULL) {
      printf("Mal abierto\n");
    }
    printf("Archivo abierto\n");
    fscanf(file, "%s",genero);
    printf("1\n");
    printf("genero --> %s\n",genero );
    fscanf(file, "%s",&anio);
    printf("anio --> %s\n",anio );
    fclose(file);
    crear_dir(genero,anio,pel->peliculas[i]);
  }
  return 0;
}
