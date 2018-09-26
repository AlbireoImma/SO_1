#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/sendfile.h>

int cant_txt(char *nombre_dir){
  int archivos = 0;
  struct dirent *de;
  DIR *dir = opendir(nombre_dir);

  if (dir == NULL){  // Error al abrir el directorio
    return -1;
  }

  while ((de = readdir(dir)) != NULL){
    // Que no sea ninguno de los archivos usados por el programa
    if (strcmp(de->d_name,"test.c") == 0 || strcmp(de->d_name,"test") == 0 || strcmp(de->d_name,"files_man.h") == 0) {
      continue;
    } else {
      if (de->d_type == 8) {
        archivos++;
      }
    }
  }
  closedir(dir);
  return archivos;
}
