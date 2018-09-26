#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "files_man.h"

int main(void) {
  printf("Cantidad de archivos en Raiz: %d\n", cant_txt("."));
  return 0;
}
