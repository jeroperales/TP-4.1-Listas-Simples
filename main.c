#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct
{
    char nombre[20];
    int edad;
} persona;

typedef struct
{
    persona dato;
    struct nodo* siguiente;
} nodo;

//PROTOTIPADO
persona cargarPersona();
void cargarArchivo(char nombre[]);
void mostrarArchivo(char nombre[]);
nodo* inicLista();
nodo* listarPersona(char nombre[], nodo* lista, int opc);
nodo* agregarPrincipio(nodo* lista, nodo* nuevoNodo);
nodo* crearNodo(persona personita);
void mostrarNodo(nodo* aux);
void muestraLista(nodo* lista);
nodo* ordenaLista(nodo* lista, nodo* nuevoNodo);
int recorreLista(nodo* lista, char nombrePersona[]);
nodo* cargarIntercalado(nodo* lista1, nodo* lista2, nodo* lista3);

int main()
{
    //VARIABLES
    int opc, flag;
    char nombrePersona[20];
    char nombre[] = {"miArchivo.bin"};
    FILE* archi;
    nodo* lista = inicLista(lista);
    nodo* lista2 = inicLista(lista2);
    nodo* lista3 = inicLista(lista3);

    //MENU

    printf("================MENU================\n");
    printf(" -Punto 1             -Punto 2\n");
    printf(" -Punto 3             -Punto 4\n");
    printf(" -Punto 5             -Punto 6\n");
    printf(" -Punto 7             -Salir\n");
    printf("====================================");
    fflush(stdin);
    printf("\nIngrese una opcion: \n");
    scanf("%i", &opc);



    switch(opc)
    {

    case 1: //Hacer un programa que lea de un archivo datos y los inserte en una lista
        cargarArchivo(nombre);
        cargarArchivo("lista2.bin");
        //mostrarArchivo(nombre);

        lista = listarPersona(nombre, lista, 0);
        lista2 = listarPersona("lista2.bin", lista2, 0);


        muestraLista(lista);
        muestraLista(lista2);

        break;

    case 2: //Hacer un programa que lea de un archivo datos y los inserte en una lista en forma ordenada

        lista = listarPersona(nombre, lista, 1);
        muestraLista(lista);

        break;

    case 3: //Hacer una función que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada

        lista = listarPersona(nombre, lista, 1);

        printf("INGRESE EL NOMBRE DE LA PERSONA QUE QUIERE BUSCAR \n");
        fflush(stdin);
        gets(nombrePersona);
        flag = recorreLista(lista, nombrePersona);

        if (flag==1)
        {
            printf("\nLA PERSONA ESTA EN LA LISTA!\n");
        }
        else
        {

            printf("\nNO ESTA EN LA LISTA\n");
        }

        break;

    case 4://Hacer una función que intercale en orden los elementos de dos listas ordenadas generando una nueva lista. Se deben redireccionar los punteros, no se deben crear nuevos nodos con la función crearNodo().

        //cargarArchivo(nombre);
        //cargarArchivo("lista2.bin");


        lista = listarPersona(nombre, lista, 1);
        lista2 = listarPersona("lista2.bin", lista2, 1);

        lista3 = cargarIntercalado(lista, lista2, lista3);
        printf("\n\nLISTA INTERCALADA: ");
        muestraLista(lista3);

        break;

    case 5: //Invertir los elementos de una lista redireccionando solamente los punteros. (No se deben crear nuevos nodos con la función crearNodo())

        break;

    case 6:

        break;

        return 0;
    }
}

persona cargarPersona()
{

    persona aux;
    printf("\nNombre: ");
    fflush(stdin);
    gets(&aux.nombre);
    printf("\nEdad: ");
    fflush(stdin);
    scanf("%d", &aux.edad);

    return aux;
}


void cargarArchivo(char nombre[])
{

    persona aux;
    char opc;
    FILE* archi = fopen(nombre, "a+b");
    if(archi!=NULL)
    {
        do
        {
            aux = cargarPersona();
            fwrite(&aux, sizeof(persona), 1, archi);
            printf("\n Desea continuar? s/n: ");
            fflush(stdin);
            scanf("%c", &opc);
        }
        while(opc == 's');
        fclose(archi);
    }
    else
    {
        printf("\n Error al abrir el archivo!\n");
        exit(1);
    }
}

void mostrarArchivo(char nombre[])
{
    persona aux;
    int i = 1;

    FILE* archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        do
        {
            fread(&aux, sizeof(persona), 1, archi);
            if (!feof(archi))
            {
                printf("\n--------------------------");
                printf("\n-PERSONA %i-", i);
                printf("\nNombre: %s", aux.nombre);
                printf("\nEdad: %d", aux.edad);
                printf("\n--------------------------\n");
                i++;
            }
        }
        while(!feof(archi));
        fclose(archi);
    }
    else
    {
        printf("\n\nError al abrir el archivo!");
        exit(1);
    }
}

nodo* inicLista(nodo* lista)
{
    lista = NULL;
    return lista;
}

nodo* listarPersona(char nombre[], nodo* lista, int opc)
{

    //DEFAULT / OPC = 0: Cargar normal
    //SI OPC = 1 ENTONCES ORDENAR POR NOMBRE
    persona aux;
    nodo* nuevo;
    FILE* archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        while(!feof(archi))
        {
            fread(&aux, sizeof(persona), 1, archi);
            if(!feof(archi))
            {
                nuevo = crearNodo(aux);
                if(opc == 1)
                {
                    lista = ordenaLista(lista, nuevo);
                }
                else
                {
                    lista = agregarPrincipio(lista,nuevo);
                }
            }
        }
        fclose(archi);
    }
    else
    {
        printf("\n\nError al abrir el archivo!\n");
        exit(0);
    }
    return lista;

}

nodo* crearNodo(persona personita)
{

    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->dato = personita;
    aux->siguiente = NULL;

    return aux;
}

nodo* agregarPrincipio(nodo* lista, nodo* nuevoNodo)
{
    if (lista!=NULL)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        lista = nuevoNodo;
    }
    return lista;
}





void mostrarNodo(nodo* aux)
{
    persona personita;
    printf("\n-----NODO-----");
    printf("\nNOMBRE: %s", aux->dato.nombre);
    printf("\nEDAD: %i \n", aux->dato.edad);

}

void muestraLista(nodo* lista)
{

    nodo* aux = lista;

    while (aux != NULL)
    {
        mostrarNodo(aux);
        aux = aux->siguiente;
    }
}

nodo* ordenaLista(nodo* lista, nodo* nuevoNodo)
{
    nodo* ante;
    nodo* seg;
    if (lista!=NULL)
    {
        if (strcmp(nuevoNodo->dato.nombre, lista->dato.nombre)<0)
        {
            lista = agregarPrincipio(lista, nuevoNodo);
        }
        else
        {
            ante = lista;
            seg = lista->siguiente;

            while((seg != NULL)&&(strcmp(nuevoNodo->dato.nombre,seg->dato.nombre)>0))
            {
                ante = seg;
                seg = seg->siguiente;
            }
            nuevoNodo->siguiente = seg;
            ante->siguiente = nuevoNodo;
        }


    }
    else
    {
        lista = nuevoNodo;
    }


    return lista;
}

int recorreLista(nodo* lista, char nombrePersona[])
{
    int flag = 0;
    nodo* aux = lista;
    if (aux == NULL)
    {
        printf("LA LISTA NO ESTA CARGADA!");
    }
    else
    {
        while (aux != NULL && flag != 1)
        {
            if (strcmp(nombrePersona, aux->dato.nombre)==0)
            {
                flag = 1;
            }
            else
            {
                aux = aux->siguiente;
            }
        }
    }
    return flag;
}

nodo* cargarIntercalado(nodo* lista1, nodo* lista2, nodo* lista3)
{

    nodo* aux1 = lista1;
    nodo* aux2 = lista2;
    nodo* aux3 = lista3;
    nodo* nuevo;
    int flag = 0;

    while(aux1 || aux2)
    {
        if(aux1 && aux2)
        {
            nuevo = crearNodo(aux1->dato);
            aux3 = agregarPrincipio(aux3, nuevo);
            aux1 = aux1->siguiente;

            nuevo = crearNodo(aux2->dato);
            aux3 = agregarPrincipio(aux3, nuevo);

            aux2 = aux2->siguiente;
        }
        else if (aux1 && !aux2)
        {
            nuevo = crearNodo(aux1->dato);
            aux3 = agregarPrincipio(aux3, nuevo);

            aux1 = aux1->siguiente;
        }
        else if (!aux1 && aux2)
        {
            nuevo = crearNodo(aux2->dato);
            aux3 = agregarPrincipio(aux3, nuevo);

            aux2 = aux2->siguiente;
        }
    }

    return aux3;
}
