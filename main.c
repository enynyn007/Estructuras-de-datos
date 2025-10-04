/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definición del nodo
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Definición de la lista circular
typedef struct {
    Nodo* cabeza;
    Nodo* cola;
    int tamano;
} ListaCircular;

// Prototipos de funciones
ListaCircular* crearLista();
void agregarAlFrente(ListaCircular* lista, int valor);
void agregarAlFinal(ListaCircular* lista, int valor);
void agregarEnPosicion(ListaCircular* lista, int valor, int posicion);

void eliminarDelFrente(ListaCircular* lista);
void eliminarDelFinal(ListaCircular* lista);
void eliminarEnPosicion(ListaCircular* lista, int posicion);

bool buscar(ListaCircular* lista, int valor);
void recorrer(ListaCircular* lista);
int obtenerTamano(ListaCircular* lista);
bool estaVacia(ListaCircular* lista);
void limpiar(ListaCircular* lista);
void mostrar(ListaCircular* lista);
int obtenerCabeza(ListaCircular* lista);
int obtenerCola(ListaCircular* lista);

// Función para crear una lista vacía
ListaCircular* crearLista() {
    ListaCircular* lista = (ListaCircular*)malloc(sizeof(ListaCircular));
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->tamano = 0;
    return lista;
}

// Agregar al frente
void agregarAlFrente(ListaCircular* lista, int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    if (estaVacia(lista)) {
        nuevo->siguiente = nuevo;
        lista->cabeza = nuevo;
        lista->cola = nuevo;
    } else {
        nuevo->siguiente = lista->cabeza;
        lista->cola->siguiente = nuevo;
        lista->cabeza = nuevo;
    }
    lista->tamano++;
}

// Agregar al final
void agregarAlFinal(ListaCircular* lista, int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    if (estaVacia(lista)) {
        nuevo->siguiente = nuevo;
        lista->cabeza = nuevo;
        lista->cola = nuevo;
    } else {
        nuevo->siguiente = lista->cabeza;
        lista->cola->siguiente = nuevo;
        lista->cola = nuevo;
    }
    lista->tamano++;
}

// Agregar en posición
void agregarEnPosicion(ListaCircular* lista, int valor, int posicion) {
    if (posicion < 0 || posicion > lista->tamano) {
        printf("Posición inválida.\n");
        return;
    }

    if (posicion == 0) {
        agregarAlFrente(lista, valor);
    } else if (posicion == lista->tamano) {
        agregarAlFinal(lista, valor);
    } else {
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->dato = valor;
        Nodo* actual = lista->cabeza;
        for (int i = 0; i < posicion - 1; i++) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
        lista->tamano++;
    }
}

// Eliminar del frente
void eliminarDelFrente(ListaCircular* lista) {
    if (estaVacia(lista)) {
        printf("La lista está vacía.\n");
        return;
    }

    Nodo* temp = lista->cabeza;
    if (lista->cabeza == lista->cola) {
        lista->cabeza = NULL;
        lista->cola = NULL;
    } else {
        lista->cabeza = temp->siguiente;
        lista->cola->siguiente = lista->cabeza;
    }

    free(temp);
    lista->tamano--;
}

// Eliminar del final
void eliminarDelFinal(ListaCircular* lista) {
    if (estaVacia(lista)) {
        printf("La lista está vacía.\n");
        return;
    }

    Nodo* actual = lista->cabeza;
    if (lista->cabeza == lista->cola) {
        free(actual);
        lista->cabeza = NULL;
        lista->cola = NULL;
    } else {
        while (actual->siguiente != lista->cola) {
            actual = actual->siguiente;
        }
        free(lista->cola);
        lista->cola = actual;
        lista->cola->siguiente = lista->cabeza;
    }
    lista->tamano--;
}

// Eliminar en posición
void eliminarEnPosicion(ListaCircular* lista, int posicion) {
    if (posicion < 0 || posicion >= lista->tamano) {
        printf("Posición inválida.\n");
        return;
    }

    if (posicion == 0) {
        eliminarDelFrente(lista);
    } else if (posicion == lista->tamano - 1) {
        eliminarDelFinal(lista);
    } else {
        Nodo* actual = lista->cabeza;
        for (int i = 0; i < posicion - 1; i++) {
            actual = actual->siguiente;
        }
        Nodo* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        free(temp);
        lista->tamano--;
    }
}

// Buscar valor
bool buscar(ListaCircular* lista, int valor) {
    if (estaVacia(lista)) return false;
    Nodo* actual = lista->cabeza;
    do {
        if (actual->dato == valor) return true;
        actual = actual->siguiente;
    } while (actual != lista->cabeza);
    return false;
}

// Recorrer la lista
void recorrer(ListaCircular* lista) {
    mostrar(lista);
}

// Tamaño
int obtenerTamano(ListaCircular* lista) {
    return lista->tamano;
}

// ¿Está vacía?
bool estaVacia(ListaCircular* lista) {
    return lista->tamano == 0;
}

// Limpiar la lista
void limpiar(ListaCircular* lista) {
    while (!estaVacia(lista)) {
        eliminarDelFrente(lista);
    }
}

// Mostrar elementos
void mostrar(ListaCircular* lista) {
    if (estaVacia(lista)) {
        printf("La lista está vacía.\n");
        return;
    }

    Nodo* actual = lista->cabeza;
    printf("Elementos de la lista: ");
    do {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    } while (actual != lista->cabeza);
    printf("\n");
}

// Obtener cabeza
int obtenerCabeza(ListaCircular* lista) {
    if (estaVacia(lista)) {
        printf("La lista está vacía.\n");
        return -1;
    }
    return lista->cabeza->dato;
}

// Obtener cola
int obtenerCola(ListaCircular* lista) {
    if (estaVacia(lista)) {
        printf("La lista está vacía.\n");
        return -1;
    }
    return lista->cola->dato;
}

// Menú de prueba
void menu() {
    ListaCircular* lista = crearLista();
    int opcion, valor, posicion;

    do {
        printf("\n--- MENÚ LISTA CIRCULAR ENLAZADA ---\n");
        printf("1. Agregar al frente\n");
        printf("2. Agregar al final\n");
        printf("3. Agregar en posición\n");
        printf("4. Eliminar del frente\n");
        printf("5. Eliminar del final\n");
        printf("6. Eliminar en posición\n");
        printf("7. Buscar valor\n");
        printf("8. Mostrar lista\n");
        printf("9. Obtener tamaño\n");
        printf("10. ¿Está vacía?\n");
        printf("11. Obtener cabeza\n");
        printf("12. Obtener cola\n");
        printf("13. Limpiar lista\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese valor: ");
                scanf("%d", &valor);
                agregarAlFrente(lista, valor);
                break;
            case 2:
                printf("Ingrese valor: ");
                scanf("%d", &valor);
                agregarAlFinal(lista, valor);
                break;
            case 3:
                printf("Ingrese valor: ");
                scanf("%d", &valor);
                printf("Ingrese posición: ");
                scanf("%d", &posicion);
                agregarEnPosicion(lista, valor, posicion);
                break;
            case 4:
                eliminarDelFrente(lista);
                break;
            case 5:
                eliminarDelFinal(lista);
                break;
            case 6:
                printf
