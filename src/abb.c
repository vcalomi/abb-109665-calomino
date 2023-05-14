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
		if (arbol->comparador(actual->elemento, elemento) >= 0) {
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

nodo_abb_t *extraer_elemento_mas_derecho(nodo_abb_t *raiz,
					 void **elemento_extraido)
{
	if (!raiz->derecha) {
		*elemento_extraido = raiz->elemento;
		nodo_abb_t *izq = raiz->izquierda;
		free(raiz);
		return izq;
	}
	raiz->derecha =
		extraer_elemento_mas_derecho(raiz->derecha, elemento_extraido);
	return raiz;
}

void *abb_quitar_recursivo(nodo_abb_t *raiz, void *elemento,
			   int (*comparador)(void *, void *), void **extraido,
			   bool *encontrado)
{
	if (!raiz)
		return NULL;
	int comparacion = comparador(elemento, raiz->elemento);
	if (comparacion == 0) {
		*encontrado = true;
		nodo_abb_t *izq = raiz->izquierda;
		nodo_abb_t *der = raiz->derecha;
		*extraido = raiz->elemento;
		if (izq != NULL && der != NULL) {
			void *elemento_derecho = NULL;
			raiz->izquierda = extraer_elemento_mas_derecho(
				raiz->izquierda, &elemento_derecho);
			raiz->elemento = elemento_derecho;
			return raiz;
		} else {
			free(raiz);
			if (!izq)
				return der;
			return izq;
		}
	} else if (comparacion < 0) {
		raiz->izquierda = abb_quitar_recursivo(raiz->izquierda,
						       elemento, comparador,
						       extraido, encontrado);
	} else {
		raiz->derecha = abb_quitar_recursivo(raiz->derecha, elemento,
						     comparador, extraido,
						     encontrado);
	}
	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	void *extraido = NULL;
	bool encontre_elemento = false;
	arbol->nodo_raiz = abb_quitar_recursivo(arbol->nodo_raiz, elemento,
						arbol->comparador, &extraido,
						&encontre_elemento);
	if (encontre_elemento)
		arbol->tamanio--;
	return extraido;
}

void *abb_buscar_recursivo(nodo_abb_t *raiz, void *elemento,
			   int (*comparador)(void *, void *))
{
	if (!raiz)
		return NULL;
	int comparacion = comparador(raiz->elemento, elemento);
	if (comparacion < 0) {
		return (abb_buscar_recursivo(raiz->derecha, elemento,
					     comparador));
	} else if (comparacion > 0) {
		return (abb_buscar_recursivo(raiz->izquierda, elemento,
					     comparador));
	} else {
		return raiz->elemento;
	}
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	return abb_buscar_recursivo(arbol->nodo_raiz, elemento,
				    arbol->comparador);
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

void liberar_nodos(nodo_abb_t *raiz)
{
	if (raiz != NULL) {
		liberar_nodos(raiz->izquierda);
		liberar_nodos(raiz->derecha);
		free(raiz);
	}
}

void abb_destruir(abb_t *arbol)
{
	if (!arbol)
		return;
	liberar_nodos(arbol->nodo_raiz);
	free(arbol);
}

void liberar_elemento(nodo_abb_t *raiz, void (*destructor)(void *))
{
	if (raiz) {
		liberar_elemento(raiz->izquierda, destructor);
		liberar_elemento(raiz->derecha, destructor);
		destructor(raiz->elemento);
	}
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;
	if (destructor) {
		liberar_elemento(arbol->nodo_raiz, destructor);
	}
	abb_destruir(arbol);
}

bool abb_cada_elemento_inorden(nodo_abb_t *raiz,
			       bool (*funcion)(void *, void *), void *aux,
			       size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar = abb_cada_elemento_inorden(raiz->izquierda, funcion,
						   aux, contador);
	if (!continuar)
		return false;

	(*contador)++;
	if (funcion(raiz->elemento, aux) == false) {
		return false;
	}

	continuar = abb_cada_elemento_inorden(raiz->derecha, funcion, aux,
					      contador);
	if (!continuar)
		return false;
	return true;
}

bool abb_cada_elemento_preorden(nodo_abb_t *raiz,
				bool (*funcion)(void *, void *), void *aux,
				size_t *contador)
{
	if (!raiz)
		return true;

	(*contador)++;
	if (funcion(raiz->elemento, aux) == false) {
		return false;
	}

	bool continuar = abb_cada_elemento_preorden(raiz->izquierda, funcion,
						    aux, contador);
	if (!continuar)
		return false;

	continuar = abb_cada_elemento_preorden(raiz->derecha, funcion, aux,
					       contador);
	if (!continuar)
		return false;
	return true;
}

bool abb_cada_elemento_postorden(nodo_abb_t *raiz,
				 bool (*funcion)(void *, void *), void *aux,
				 size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar = abb_cada_elemento_postorden(raiz->izquierda, funcion,
						     aux, contador);
	if (!continuar)
		return false;

	continuar = abb_cada_elemento_postorden(raiz->derecha, funcion, aux,
						contador);
	if (!continuar)
		return false;

	(*contador)++;
	if (funcion(raiz->elemento, aux) == false) {
		return false;
	}
	return true;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion)
		return 0;

	size_t contador = 0;

	switch (recorrido) {
	case INORDEN:
		abb_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux,
					  &contador);
		break;
	case PREORDEN:
		abb_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux,
					   &contador);
		break;
	case POSTORDEN:
		abb_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux,
					    &contador);
		break;
	default:
		break;
	}
	return contador;
}

bool array_inorden(nodo_abb_t *raiz, void **array, size_t *cantidad,
		   size_t tamanio_array)
{
	if (!raiz)
		return true;

	bool continuar = true;
	continuar = array_inorden(raiz->izquierda, array, cantidad,
				  tamanio_array) &&
		    continuar;

	if (*cantidad < tamanio_array && continuar) {
		array[*cantidad] = raiz->elemento;
		(*cantidad)++;
	} else {
		continuar = false;
	}

	continuar =
		array_inorden(raiz->derecha, array, cantidad, tamanio_array) &&
		continuar;

	return continuar;
}

bool array_preorden(nodo_abb_t *raiz, void **array, size_t *cantidad,
		    size_t tamanio_array)
{
	if (!raiz)
		return true;

	bool continuar = true;
	if (*cantidad < tamanio_array && continuar) {
		array[*cantidad] = raiz->elemento;
		(*cantidad)++;
	} else {
		continuar = false;
	}

	continuar = array_preorden(raiz->izquierda, array, cantidad,
				   tamanio_array) &&
		    continuar;

	continuar =
		array_preorden(raiz->derecha, array, cantidad, tamanio_array) &&
		continuar;

	return continuar;
}

bool array_postorden(nodo_abb_t *raiz, void **array, size_t *cantidad,
		     size_t tamanio_array)
{
	if (!raiz)
		return true;

	bool continuar = true;
	continuar = array_postorden(raiz->izquierda, array, cantidad,
				    tamanio_array) &&
		    continuar;

	continuar = array_postorden(raiz->derecha, array, cantidad,
				    tamanio_array) &&
		    continuar;

	if (*cantidad < tamanio_array && continuar) {
		array[*cantidad] = raiz->elemento;
		(*cantidad)++;
	} else {
		continuar = false;
	}
	return continuar;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || tamanio_array == 0 || array == NULL) {
		return 0;
	}

	size_t cantidad_elementos = 0;
	switch (recorrido) {
	case INORDEN:
		array_inorden(arbol->nodo_raiz, array, &cantidad_elementos,
			      tamanio_array);
		return cantidad_elementos;
	case PREORDEN:
		array_preorden(arbol->nodo_raiz, array, &cantidad_elementos,
			       tamanio_array);
		return cantidad_elementos;
	case POSTORDEN:
		array_postorden(arbol->nodo_raiz, array, &cantidad_elementos,
				tamanio_array);
		return cantidad_elementos;
	default:
		return 0;
	}
	return cantidad_elementos;
}
