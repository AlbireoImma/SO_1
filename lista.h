#include <stdlib.h>
#include <stdio.h>

/******** Struct: tnodo ********************
   Descripcion: Nodo base de una lista
   Composicion:
   info: puntero hacia el String
   sig: Puntero hacia el siguiente nodo de la lista
 ************************************************/

typedef struct nodo
{
        char *info;
        struct nodo *sig;
} tnodo;

/******** Struct: Tlist ********************
   Descripcion: Estuctura la cual representa una lista
   Composicion:
   head: Puntero que contiene la direccion de memoria del primer elemento de la lista
   curr: Puntero que contiene la direccion de memoria del elemento actual de la lista
   curr: puntero que contiene la direccion de memoria del elemento final de la lista
   largo: Entero que contiene el largo de la lista
   pos: Entero que contiene la posicion actual del curr dentro de la lista
 ************************************************/

typedef struct list
{
        tnodo *head;
        tnodo *tail;
        tnodo *curr;
        int largo;
        int pos;
} Tlist;

/******** Funcion: crear_lista ********************
   Descripcion: Crea una estructura del tipo lista en memoria dinamica
   Parametros: Ninguno
   Retorno: Un puntero del tipo Tlist
 ************************************************/

Tlist *crear_lista(){
        Tlist *A;
        A = (Tlist *)calloc(1,sizeof(Tlist));
        return A;
}

/******** Funcion: printlista ********************
   Descripcion: Imprime los valores de una lista ademas de su tamaño y el espacio que ocupa en el heap
   Parametros:
   L: Puntero hacia la lista a imprimir
   Retorno: Ninguno
 ************************************************/

void printlista(Tlist *L)
{
        if (L->largo == 0)
        {
                printf("#\t\t\tLista vacia\t\t\t#\n");
                return;
        }
        tnodo *aux = L->head;
        printf(">> [ ");
        for (int i = 0; i < L->largo; i++)
        {
                printf("%s ",aux->sig->info);
                aux = aux->sig;
        }
        printf("]\n");
        printf(">>> Largo lista: %d\n",L->largo);
        printf(">>> Memoria utilizada: %ld bytes\n",sizeof(tnodo)*(L->largo+1));
        return;
}

/******** Funcion: eliminar_lista ********************
   Descripcion: borra el nodo en el cual se situa el curr dentro de la lista
   Parametros:
   L: Puntero hacia la lista
   Retorno: Ninguno
 ************************************************/

void eliminar_lista(Tlist *L)
{
        if (L->largo == 0) return;
        tnodo *aux;
        if (L->curr == L->tail)
        {
                free((void *)L->tail);
                L->tail = L->curr;
                L->largo--;
                return;
        }
        aux = L->curr->sig->sig;
        free((void *)L->curr->sig);
        L->curr->sig = aux;
        L->largo--;
        return;
}

/******** Funcion: getval ********************
   Descripcion: Retorna el valor del nodo donde se encuentra curr
   Parametros:
   L: Puntero hacia la lista
   Retorno: Valor de la lista en la poscion actual
 ************************************************/

char *getval(Tlist *L)
{
        if (L->curr == L->tail)
        {
                return L->curr->info;
        }
        return L->curr->sig->info;
}

/******** Funcion: next  ********************
   Descripcion: Mueve el puntero de curr al siguiente nodo en caso de no haber terminado la lista
   Parametros:
   L: Puntero hacia la lista
   Retorno: Ninguno
 ************************************************/

void next(Tlist *L)
{
        if (L->curr == L->tail) {
                return;
        }
        L->curr = L->curr->sig;
        L->pos++;
        return;
}

/******** Funcion: prev  ********************
   Descripcion: Mueve el puntero de curr al nodo anterior en caso de no estar en el principio de la lista
   Parametros:
   L: Puntero hacia la lista
   Retorno: Ninguno
 ************************************************/

void prev(Tlist *L)
{
        if (L->curr == L->head) return;
        L->curr = L->head;
        int i;
        for (i = 0; i < L->pos-1; i++) L->curr = L->curr->sig;
        L->pos = L->pos-1;
}

/******** Funcion: buscar  ********************
   Descripcion: Busca un entero en particular dentro de la lista
   Parametros:
   item: entero a buscar dentro de la lista
   L: Puntero hacia la lista
   Retorno: Un 1 en caso de estar el elemento o un 0 en caso contrario
 ************************************************/

int buscar(char *item, Tlist *L)
{
        if (L->largo == 0) return 0;
        tnodo *aux = L->head;
        int i;
        for (i = 0; i < L->largo; i++)
        {
                aux = aux->sig;
                if (strcmp(aux->info,item) == 0){
                  return 1;
                }
        }
        return 0;
}

/******** Funcion: toHome  ********************
   Descripcion: Mueve el puntero de curr al nodo en el cual comienza la lista
   Parametros:
   L: Puntero hacia la lista
   Retorno: Ninguno
 ************************************************/

void toHome(Tlist *L)
{
        L->curr = L->head;
        return;
}

/******** Funcion: getlarge  ********************
   Descripcion: Obtiene el valor correspondiente al largo de la lista
   Parametros:
   L: Puntero hacia la lista
   Retorno: Entero el cual representa el largo de nodos de la lista
************************************************/

int getlarge(Tlist *L)
{
        return L->largo;
}

/******** Funcion: insertar  ********************
   Descripcion: Inserta un elemento en la posicion actual del curr
   Parametros:
   item: entero a insertar dentro de la lista
   L: Puntero hacia la lista
   Retorno: Ninguno
************************************************/

void insertar(char *item, Tlist* L)
{
        tnodo *aux;
        if (L->head == NULL)
        {
                L->head = (tnodo *)calloc(1,sizeof(tnodo));
                L->curr = L->head;
                L->tail = L->head;
        }
        if (L->largo == 0)
        {
                L->curr->sig = (tnodo *)calloc(1,sizeof(tnodo));
                L->curr->sig->info = item;
                L->tail = L->curr->sig;
                L->largo++;
                return;
        }
        aux = (tnodo *)calloc(1,sizeof(tnodo));
        aux->info = (char *)malloc(strlen(item)*sizeof(char));
        strcpy(aux->info,item);
        aux->sig = L->curr->sig;
        L->curr->sig = aux;
        if (L->curr == L->tail)
        {
                L->tail = L->curr->sig;
        }
        L->largo++;
}

/******** Funcion: erase_lista  ********************
   Descripcion: Elimina la lista completa de la memoria
   Parametros:
   L: Puntero hacia la lista
   Retorno: Ninguno
 ************************************************/

void erase_lista(Tlist *L){
        if (L->largo == 0)
        {
                free((void *)L->head);
                return;
        }
        int i;
        tnodo *aux = L->head;
        for (i = 0; i < L->largo; i++)
        {
                aux = aux->sig;
                if (i < L->largo-1) {
                  free((void *)aux->info);
                }
        }
        while(L->largo > 0)
        {
                tnodo *aux = L->head;
                for (i = 0; i < L->largo; i++)
                {
                        aux = aux->sig;
                }
                free((void *)aux);
                L->largo--;
        }
        free((void *)L->head);
        return;
}
