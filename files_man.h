#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include "lista.h"

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
                if (strcmp(de->d_name,"test.c") == 0 || strcmp(de->d_name,"test") == 0 || strcmp(de->d_name,"files_man.h") == 0 || strcmp(de->d_name,"lista.h") == 0) {
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
                if (strcmp(de->d_name,"test.c") == 0 || strcmp(de->d_name,"test") == 0 || strcmp(de->d_name,"files_man.h") == 0 || strcmp(de->d_name,"lista.h") == 0) {
                        continue;
                } else {
                        if (de->d_type == 8) {
                                strcpy(pel->peliculas[i],de->d_name);
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
                file = fopen(pel->peliculas[i],"r");
                if (file == NULL) {
                        return -1;
                }
                fgets(genero,250,file);
                genero[strlen(genero)-1]=0;
                fgets(anio,250,file);
                anio[strlen(anio)-1]=0;
                fclose(file);
                mov_arch(genero,anio,pel->peliculas[i]);
        }
        return 1;
}

void navegador(char *raiz){
        int Flag_Raiz = 1;
        int Flag_Anio = 0;
        int Flag_Archivo = 0;
        int Flag_Salida = 0;
        int opcion;
        int i;
        char *path = (char *)malloc(100*sizeof(char));
        char *pel_year = (char *)malloc(100*sizeof(char));
        char *pel_genre = (char *)malloc(100*sizeof(char));
        char *pel_name = (char *)malloc(100*sizeof(char));
        Tlist *lista = crear_lista();
        struct dirent *de;
        DIR *dir;
        while (Flag_Salida != 1) {
                if (Flag_Raiz == 1) {
                        dir = opendir(raiz);
                        while ((de = readdir(dir)) != NULL) {
                                if (de->d_type == 4) {
                                        if (strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0 || strcmp(de->d_name,".git") == 0) {
                                                continue;
                                        } else {
                                                insertar(de->d_name,lista);
                                        }
                                }
                        }
                        toHome(lista);
                        printf("====>  Generos\n");
                        for (i = 0; i < getlarge(lista); i++) {
                                printf("[%d] ----> %s\n",i+1,getval(lista));
                                next(lista);
                        }
                        printf("[0] ----> Salir\n");
                        printf("\n");
                        printf("Seleccione un genero mediante opcion numerica: ");
                        scanf("%d",&opcion);
                        printf("\n");
                        while (opcion < 0 || opcion > getlarge(lista)) {
                                printf("Seleccione una opcion valida: "); // Modificar codigo para colocar la eñe
                                scanf("%d",&opcion);
                                printf("\n");
                        }
                        if (opcion == 0) {
                                closedir(dir);
                                erase_lista(lista);
                                free((void *)pel_name);
                                free((void *)pel_genre);
                                free((void *)pel_year);
                                free((void *)path);
                                free((void *)lista);
                                return;
                        } else if (opcion > 0 && opcion <= getlarge(lista)) {
                                toHome(lista);
                                for (i = 0; i < (opcion-1); i++) {
                                        next(lista);
                                }
                                strcpy(path,getval(lista));
                                strcpy(pel_genre,getval(lista));
                                erase_lista(lista);
                                free((void *)lista);
                                lista = crear_lista();
                                Flag_Raiz = 0;
                                Flag_Anio = 1;
                                closedir(dir);
                        }
                } else if (Flag_Anio == 1) {
                        dir = opendir(path);
                        while ((de = readdir(dir)) != NULL) {
                                if (de->d_type == 4) {
                                        if (strcmp(de->d_name,".") == 0 || strcmp(de->d_name,".git") == 0) {
                                                continue;
                                        } else {
                                                insertar(de->d_name,lista);
                                        }
                                }
                        }
                        toHome(lista);
                        for (i = 0; i < getlarge(lista); i++) {
                                if (strcmp(getval(lista),"..") == 0) {
                                        printf("====>  %s\n",pel_genre);
                                        printf("[%d] ----> Volver a Generos\n",i+1);
                                } else {
                                        printf("[%d] ----> %s\n",i+1,getval(lista));
                                }
                                next(lista);
                        }
                        printf("[0] ----> Salir\n");
                        printf("\n");
                        printf("Seleccione un anio mediante opcion numerica: "); // Modificar codigo para colocar la eñe
                        scanf("%d",&opcion);
                        printf("\n");
                        while (opcion < 0 || opcion > getlarge(lista)) {
                                printf("Seleccione una opcion valida: "); // Modificar codigo para colocar la eñe
                                scanf("%d",&opcion);
                                printf("\n");
                        }
                        if (opcion == 0) {
                                closedir(dir);
                                erase_lista(lista);
                                free((void *)lista);
                                free((void *)pel_name);
                                free((void *)pel_genre);
                                free((void *)pel_year);
                                free((void *)path);
                                return;
                        } else if (opcion > 0 && opcion <= getlarge(lista)) {
                                if (opcion == 1) {
                                        Flag_Raiz = 1;
                                        Flag_Anio = 0;
                                        closedir(dir);
                                        erase_lista(lista);
                                        free((void *)lista);
                                        lista = crear_lista();
                                } else {
                                        toHome(lista);
                                        for (i = 0; i < (opcion-1); i++) {
                                                next(lista);
                                        }
                                        strcpy(pel_year,getval(lista));
                                        strncat(path,"/",1);
                                        strncat(path,pel_year,strlen(pel_year));
                                        strncat(path,"/",1);
                                        erase_lista(lista);
                                        free((void *)lista);
                                        lista = crear_lista();
                                        Flag_Archivo = 1;
                                        Flag_Anio = 0;
                                        closedir(dir);
                                }
                        }
                } else if (Flag_Archivo == 1) {
                        dir = opendir(path);
                        while ((de = readdir(dir)) != NULL) {
                                if (de->d_type == 8 || de->d_type == 4) {
                                        if (strcmp(de->d_name,".") == 0 || strcmp(de->d_name,".git") == 0) {
                                                continue;
                                        } else {
                                                insertar(de->d_name,lista);
                                        }
                                }
                        }
                        toHome(lista);
                        for (i = 0; i < getlarge(lista); i++) {
                                if (strcmp(getval(lista),"..") == 0) {
                                        printf("====>  %s\n",pel_genre);
                                        printf("===>  %s\n",pel_year);
                                        printf("[%d] ----> Volver a la carpeta anterior\n",i+1);
                                } else {
                                        printf("[%d] ----> %s\n",i+1,getval(lista));
                                }
                                next(lista);
                        }
                        printf("[0] ----> Salir\n");
                        printf("\n");
                        printf("Seleccione una pelicula mediante opcion numerica: "); // Modificar codigo para colocar la eñe
                        scanf("%d",&opcion);
                        printf("\n");
                        while (opcion < 0 || opcion > getlarge(lista)) {
                                printf("Seleccione una opcion valida: "); // Modificar codigo para colocar la eñe
                                scanf("%d",&opcion);
                                printf("\n");
                        }
                        return;
                }
        }
}
