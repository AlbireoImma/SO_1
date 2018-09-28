#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>

typedef struct
{
        char **peliculas;
        int cant_peliculas;
} peliculas;

void free_peliculas(peliculas *pel){
        int i;
        for (i = 0; i < pel->cant_peliculas; i++) {
                //   printf("Eliminando Array...\n");
                //   printf("Array %s %p\n",pel->peliculas[i],&pel->peliculas[i]);
                free((void *)pel->peliculas[i]);
                //   printf("Array eliminado!!\n");
        }
        free(pel->peliculas);
        free(pel);
}

peliculas *obtener_peliculas(char *nombre_dir){
        int archivos = 0;
        struct dirent *de;
        DIR *dir = opendir(nombre_dir);

        if (dir == NULL) {
                // Error al abrir el directorio
                peliculas *pel = (peliculas *)calloc(1,sizeof(peliculas));
                pel->cant_peliculas = -1;
                return pel;
        }

        while ((de = readdir(dir)) != NULL) {
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
        peliculas *pel = (peliculas *)calloc(1,sizeof(peliculas));
        pel->peliculas = (char **)calloc(archivos,sizeof(char*));
        pel->cant_peliculas = archivos;
        int i;
        for (i = 0; i < archivos; i++) {
                pel->peliculas[i] = (char *)calloc(50,sizeof(char));
        }
        dir = opendir(nombre_dir);

        if (dir == NULL) { // Error al abrir el directorio
                peliculas *pel = (peliculas *)calloc(1,sizeof(peliculas));
                pel->cant_peliculas = -1;
                return pel;
        }
        i = 0;
        while ((de = readdir(dir)) != NULL) {
                // Que no sea ninguno de los archivos usados por el programa
                if (strcmp(de->d_name,"test.c") == 0 || strcmp(de->d_name,"test") == 0 || strcmp(de->d_name,"files_man.h") == 0) {
                        continue;
                } else {
                        if (de->d_type == 8) {
                                pel->peliculas[i]=de->d_name;
                                i++;
                        }
                }
        }
        closedir(dir);
        return pel;
}

void print_pel(peliculas *pel){
        int i;
        for (i = 0; i < pel->cant_peliculas; i++) {
                printf("%d) %s\n",i+1,pel->peliculas[i]);
        }
        return;
}

void mov_arch(char *genero,char *anio,char *nombre_archivo){
        char path[700] = "";
  #ifdef __linux__
        strncat(path,genero,strlen(genero));
        mkdir(path, 0755);
        strncat(path,"/",1);
        strncat(path,anio,strlen(anio));
        mkdir(path, 0755);
        strncat(path,"/",1);
        strncat(path,nombre_archivo,strlen(nombre_archivo));
        rename(nombre_archivo,path);
  #else
        _mkdir(path);
        strncat(path,nombre_archivo,strlen(nombre_archivo));
        _rename(nombre_archivo,path);
  #endif
}

int organizar(peliculas *pel){
        int i;
        FILE *file;
        char genero[250];
        char anio[250];
        for (i = 0; i < pel->cant_peliculas; i++) {
                //printf("Abriendo: %s\n",pel->peliculas[i]);
                file = fopen(pel->peliculas[i],"r");
                if (file == NULL) {
                        return -1;
                }
                //printf("Archivo abierto\n");
                fscanf(file, "%s",genero);
                //printf("genero --> %s\n",genero );
                fscanf(file, "%s",anio);
                //printf("anio --> %s\n",anio );
                fclose(file);
                mov_arch(genero,anio,pel->peliculas[i]);
        }
        return 1;
}

void ver_arbol(char *nombre_dir){

}

void listdir(const char *name, int indentar)
{
        DIR *dir;
        struct dirent *entry;

        if (!(dir = opendir(name)))
                return;

        while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, "test.c") == 0 || strcmp(entry->d_name, "test") == 0 || strcmp(entry->d_name, "files_man.h") == 0) {
                        continue;
                } else if (entry->d_type == DT_DIR) {
                        char path[257];
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".git") == 0){
                                continue;
                              }
                        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                        printf("%*s[%s]\n", indentar, "", entry->d_name);
                        listdir(path, indentar + 2);
                } else {
                        printf("%*s- %s\n", indentar, "", entry->d_name);
                }
        }
        closedir(dir);
}
