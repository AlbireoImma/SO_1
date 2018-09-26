#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "files_man.h"

int main(void) {
  // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
  // for readdir()
  printf("Cantidad de archivos en Raiz: %d\n", cant_txt("."));
  return 0;
}
