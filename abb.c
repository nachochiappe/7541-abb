#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "abb.h"

struct abb_nodo {
	const char* clave;
	void* dato;
	abb_nodo_t* izq;
	abb_nodo_t* der;
};

struct abb {
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t* comparar;
	abb_destruir_dato_t* destruir;
};

// Crea una copia de la clave pasada por parametro
// Pre: Ninguna.
// Post: Devuelve una copia de la clave, NULL si no funcionó malloc().
char* crear_clave(const char* clave){
	char *copia = malloc(sizeof(char) * (strlen(clave) + 1));
	if (!copia) return NULL;
	strcpy(copia, clave);
	return copia;
}

// Crea un nuevo nodo del árbol
// Pre: Ninguna.
// Post: Devuelve un nuevo nodo hoja.
abb_nodo_t* abb_nodo_crear(const char* clave, void* dato) {
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if (!nodo) return NULL;
	nodo->clave = crear_clave(clave);
	nodo->dato = dato;
	nodo->izq = NULL,
	nodo->der = NULL;
	return nodo;
}

// Destruye un nodo del árbol
// Pre: El nodo existe.
// Post: Destruye el nodo y su contenido.
void* abb_nodo_destruir(abb_nodo_t* nodo) {
	if (!nodo) return NULL;
	void* dato = nodo->dato;
	//free((char*)nodo->clave);
	free(nodo);
	return dato;
}

// Crea un nuevo árbol
// Pre: Ninguna.
// Post: Devuelve un nuevo árbol vacío.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
	abb_t* abb = malloc(sizeof(abb_t));
	if (!abb) return NULL;
	abb->raiz = NULL;
	abb->cantidad = 0;
	abb->comparar = &cmp;
	abb->destruir = &destruir_dato;
	return abb;
}

// Función que busca recursivamente la ubicación donde guardar el nodo, y lo guarda.
// Pre: El árbol existe.
// Post: Devuelve TRUE si pudo guardar el nodo, FALSE si no.
bool abb_guardar_r(abb_t *arbol, abb_nodo_t* nodo_actual, const char *clave, void *dato) {
	int r = arbol->comparar(nodo_actual->clave, clave);
	// Si la clave ya pertenece al árbol, destruyo su dato (si hace falta) y lo reemplazo
	if (r == 0) {
		if (arbol->destruir) {
			arbol->destruir(nodo_actual->dato);
		}
		nodo_actual->dato = crear_clave(clave);
	}
	// Si la clave de la raíz es mayor a la que se debe guardar, busco por la izquierda
	else if (r == 1) {
		// Si no hay nada a la izquierda, guardo el nodo
		if (!nodo_actual->izq) {
			abb_nodo_t* nuevo_nodo = abb_nodo_crear(clave, dato);
			nodo_actual->izq = nuevo_nodo;
			arbol->cantidad++;
			return true;
		}
		return abb_guardar_r(arbol, nodo_actual->izq, clave, dato);
	}
	// Si es menor, por la derecha
	else if (r == -1) {
		// Si no hay nada a la derecha, guardo el nodo
		if (!nodo_actual->der) {
			abb_nodo_t* nuevo_nodo = abb_nodo_crear(clave, dato);
			nodo_actual->der = nuevo_nodo;
			arbol->cantidad++;
			return true;
		}
		return abb_guardar_r(arbol, nodo_actual->der, clave, dato);
	}
	return false;
}

// Guarda una clave en el árbol
// Pre: El árbol existe.
// Post: Devuelve TRUE si pudo guardar la clave, FALSE si no.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
	if (!arbol) return false;
	// Si el árbol está vacío, lo guardo en la raíz
	if (abb_cantidad(arbol) == 0) {
		abb_nodo_t* nuevo_nodo = abb_nodo_crear(clave, dato);
		if (!nuevo_nodo) return false;
		arbol->raiz = nuevo_nodo;
		arbol->cantidad++;
		return true;
	}
	return abb_guardar_r(arbol, arbol->raiz, clave, dato);
}

// Borra un nodo del árbol.
// Pre: El árbol existe.
// Post: Devuelve el dato asociado a la clave borrada (si existe), NULL si no existe.
void *abb_borrar(abb_t *arbol, const char *clave) {
	if (!arbol) return NULL;
	if (!abb_pertenece(arbol, clave)) return NULL;
	//else return abb_borrar_r(arbol->raiz, NULL, 0, clave, arbol);
}

// Busca una clave en un árbol recursivamente.
// Pre: Ninguna.
// Post: Devuelve el nodo buscado (si existe), NULL si no existe.
abb_nodo_t *abb_buscar_r(const abb_t *arbol, abb_nodo_t* nodo, const char *clave) {
	int r = arbol->comparar(nodo->clave, clave);
	// Si el nodo es NULL, llegué al final del árbol y no lo encontré
	if (!nodo) return NULL;
	// Si las claves son iguales, devuelvo el dato asociado al nodo
	if (r == 0) return nodo;
	// Si la clave del nodo es menor a la del parámetro, busco por la derecha
	else if (r == -1) return abb_buscar_r(arbol, nodo->der, clave);
	// Si es mayor, por la izquierda
	return abb_buscar_r(arbol, nodo->izq, clave);
}

// Obtiene el dato asociado a una clave del árbol.
// Pre: El árbol existe.
// Post: Devuelve el dato asociado a la clave (si existe), NULL si no existe.
void *abb_obtener(const abb_t *arbol, const char *clave) {
	if (!arbol) return NULL;
	abb_nodo_t* nodo = abb_buscar_r(arbol, arbol->raiz, clave);
	if (!nodo) return NULL;
	return nodo->dato;
}

// Verifica si una clave pertenece a un árbol.
// Pre: El árbol existe.
// Post: Devuelve TRUE si la clave pertenece al árbol, FALSE si no.
bool abb_pertenece(const abb_t *arbol, const char *clave) {
	if (!arbol) return false;
	abb_nodo_t* nodo = abb_buscar_r(arbol, arbol->raiz, clave);
	if (!nodo) return false;
	return true;
}

// Devuelve la cantidad de nodos de un árbol.
// Pre: El árbol existe.
// Post: Devuelve la cantidad de nodos del árbol.
size_t abb_cantidad(abb_t *arbol) {
	if (!arbol) return 0;
	return arbol->cantidad;
}

// Destruye un árbol.
// Pre: El árbol existe.
// Post: Se destruyó el árbol y todo lo que contiene.
void abb_destruir(abb_t *arbol) {
	
}

// Primitivas iterador interno

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
	
}

// Primitivas iterador externo

struct abb_iter {
	
};

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
	
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
	
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
	
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
	
}

void abb_iter_in_destruir(abb_iter_t* iter) {
	
}