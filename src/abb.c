#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;
	abb_t *arbol = calloc(1, sizeof(abb_t));
	if (!arbol) {
		free(arbol);
		return NULL;
	}
	arbol->comparador = comparador;
	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}

	nodo_abb_t *nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
	if (!nuevo_nodo) {
		free(nuevo_nodo);
		return NULL;
	}
	nuevo_nodo->elemento = elemento;

	if (!arbol->nodo_raiz) {
		arbol->nodo_raiz = nuevo_nodo;
		arbol->tamanio++;
		return arbol;
	}

	nodo_abb_t *actual = arbol->nodo_raiz;
	while (actual) {
		if (arbol->comparador(actual->elemento, elemento) <= 0) {
			if (!actual->izquierda) {
				actual->izquierda = nuevo_nodo;
				arbol->tamanio++;
				actual = NULL;
			} else
				actual = actual->izquierda;
		} else {
			if (!actual->derecha) {
				actual->derecha = nuevo_nodo;
				arbol->tamanio++;
				actual = NULL;
			} else
				actual = actual->derecha;
		}
	}
	return arbol;
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol || !arbol->tamanio)
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol || !arbol->tamanio)
		return 0;
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
