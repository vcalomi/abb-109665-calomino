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
