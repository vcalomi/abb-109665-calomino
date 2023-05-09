#include "pa2m.h"
#include "src/abb.h"

int comparacion(void *e1, void *e2)
{
	if (!e1)
		return -1;
	if (!e2)
		return 1;
	int elemento1 = *((int *)e1);
	int elemento2 = *((int *)e2);
	if (elemento1 == elemento2)
		return 0;
	else if (elemento1 > elemento2)
		return 1;
	else
		return -1;
}

void pruebas_creacion()
{
	pa2m_afirmar(abb_crear(NULL) == NULL,
		     "Crear un arbol sin funcion comparadora devuelve NULL");
	abb_t *arbol = abb_crear(comparacion);
	pa2m_afirmar(
		arbol != NULL,
		"Crear un arbol con funcion comparadora valida es posible");

	pa2m_afirmar(abb_vacio(arbol), "El arbol esta vacio");
	abb_destruir(arbol);
}

void pruebas_insercion()
{
	abb_t *arbol = abb_crear(comparacion);

	pa2m_afirmar(abb_vacio(arbol), "El arbol esta vacio");

	int *valor_1 = calloc(1, sizeof(int));
	*valor_1 = 20;
	int *valor_2 = calloc(1, sizeof(int));
	*valor_2 = 30;
	int *valor_3 = calloc(1, sizeof(int));
	*valor_3 = 50;
	int *valor_4 = calloc(1, sizeof(int));
	*valor_4 = 20;

	pa2m_afirmar(abb_insertar(NULL, valor_1) == NULL,
		     "Insertar con arbol NULL devuelve NULL");
	pa2m_afirmar(abb_insertar(arbol, NULL) == arbol,
		     "Puedo insertar NULL en el arbol");
	pa2m_afirmar(abb_insertar(arbol, 0) == arbol,
		     "Puedo insertar 0 en el arbol");
	pa2m_afirmar(abb_insertar(arbol, false) == arbol,
		     "Puedo insertar false en el arbol");
	pa2m_afirmar(abb_insertar(arbol, valor_1) == arbol,
		     "Inserto un elemento como raiz");
	pa2m_afirmar(abb_insertar(arbol, valor_1) == arbol,
		     "Inserto un elemento como raiz");
	pa2m_afirmar(abb_insertar(arbol, valor_1) == arbol,
		     "Inserto un elemento como raiz");
	pa2m_afirmar(abb_insertar(arbol, valor_2) == arbol,
		     "Inserto un elemento hoja");
	pa2m_afirmar(abb_insertar(arbol, valor_3) == arbol,
		     "Inserto un elemento como raiz");
	pa2m_afirmar(abb_insertar(arbol, valor_4) == arbol,
		     "Inserto un elemento repetido");

	abb_destruir(arbol);
	free(valor_1);
	free(valor_2);
	free(valor_3);
	free(valor_4);
}

void pruebas_quitar()
{
	pa2m_afirmar(abb_quitar(NULL, NULL) == NULL,
		     "No se puede quitar de un arbol nulo");

	abb_t *arbol = abb_crear(comparacion);
	int *valor_1 = calloc(1, sizeof(int));
	*valor_1 = 20;
	int *valor_2 = calloc(1, sizeof(int));
	*valor_2 = 30;
	int *valor_3 = calloc(1, sizeof(int));
	*valor_3 = 50;
	int *valor_4 = calloc(1, sizeof(int));
	*valor_4 = 20;
	int *valor_5 = calloc(1, sizeof(int));
	*valor_5 = 25;
	int *valor_6 = calloc(1, sizeof(int));
	*valor_6 = 0;

	pa2m_afirmar(abb_quitar(arbol, valor_1) == NULL,
		     "No se puede quitar elementos de un arbol vacio");

	abb_insertar(arbol, valor_1);
	pa2m_afirmar(abb_quitar(arbol, valor_1) == valor_1,
		     "Se puede quitar la raiz del arbol sin hijos");

	abb_insertar(arbol, valor_1);
	abb_insertar(arbol, valor_2);
	abb_insertar(arbol, valor_3);

	pa2m_afirmar(abb_quitar(arbol, valor_1) == valor_1,
		     "Se puede quitar la raiz con hijos");

	abb_destruir(arbol);
	arbol = abb_crear(comparacion);

	abb_insertar(arbol, valor_1);
	abb_insertar(arbol, valor_2);
	abb_insertar(arbol, valor_3);
	abb_insertar(arbol, valor_4);
	abb_insertar(arbol, valor_5);

	pa2m_afirmar(abb_quitar(arbol, valor_2) == valor_2,
		     "Puedo quitar un elemento con hijos");
	pa2m_afirmar(abb_quitar(arbol, valor_3) == valor_3,
		     "Puedo quitar un elemento sin hijos");

	abb_destruir(arbol);
	arbol = abb_crear(comparacion);

	abb_insertar(arbol, valor_1);
	abb_insertar(arbol, valor_2);
	abb_insertar(arbol, valor_3);
	abb_insertar(arbol, valor_4);
	abb_insertar(arbol, valor_5);
	abb_insertar(arbol, valor_6);

	pa2m_afirmar(abb_quitar(arbol, valor_6) == valor_6,
		     "Se puede quitar el 0");

	abb_destruir_todo(arbol, free);
	free(valor_6);
}

void pruebas_buscar()
{
	abb_t *arbol = abb_crear(comparacion);
	int *valor_1 = calloc(1, sizeof(int));
	*valor_1 = 20;
	pa2m_afirmar(abb_buscar(NULL, valor_1) == NULL,
		     "Buscar en un arbol inexistente devuelve NULL");
	pa2m_afirmar(abb_buscar(arbol, valor_1) == NULL,
		     "Buscar en un arbol vacio devuelve NULL");

	int *valor_2 = calloc(1, sizeof(int));
	*valor_2 = 30;
	int *valor_3 = calloc(1, sizeof(int));
	*valor_3 = 50;
	int *valor_4 = calloc(1, sizeof(int));
	*valor_4 = 20;
	int *valor_5 = calloc(1, sizeof(int));
	*valor_5 = 25;
	int *valor_6 = calloc(1, sizeof(int));
	*valor_6 = 0;
	abb_insertar(arbol, valor_1);
	abb_insertar(arbol, valor_2);
	abb_insertar(arbol, valor_3);
	abb_insertar(arbol, valor_4);
	abb_insertar(arbol, valor_5);
	abb_insertar(arbol, valor_6);

	int *valor_7 = calloc(1, sizeof(int));
	*valor_7 = 39;

	pa2m_afirmar(
		abb_buscar(arbol, valor_7) == NULL,
		"No se puede encontrar un elemento que no esta en el arbol");
	pa2m_afirmar(
		abb_buscar(arbol, valor_5) == valor_5,
		"Buscar un elemento que esta en el arbol devuelve el elemento");
	pa2m_afirmar(
		abb_buscar(arbol, valor_6) == valor_6,
		"Buscar un elemento con valor 0 que esta en el arbol devuelve el elemento");

	abb_destruir_todo(arbol, free);
	free(valor_7);
}

void pruebas_tamanio_y_vacio()
{
	pa2m_afirmar(abb_tamanio(NULL) == 0,
		     "Un arbol invalido tiene tamaño 0");
	pa2m_afirmar(abb_vacio(NULL) == true, "Un arbol invalido esta vacio");

	abb_t *arbol = abb_crear(comparacion);

	pa2m_afirmar(abb_vacio(arbol) == true, "El arbol esta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El arbol vacio tiene tamaño cero");

	int *valor_1 = calloc(1, sizeof(int));
	*valor_1 = 12;

	abb_insertar(arbol, valor_1);

	pa2m_afirmar(abb_vacio(arbol) == false,
		     "El arbol ya no esta vacio luego de insertar");
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "El tamaño aumenta luego de insertar");

	int *valor_2 = calloc(1, sizeof(int));
	*valor_2 = 15;

	abb_insertar(arbol, valor_2);

	abb_quitar(arbol, valor_1);
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "Luego de sacar un elemento disminuye el tamaño");

	abb_destruir_todo(arbol, free);
	free(valor_1);
}

bool funcion_recorrido(void *e1, void *e2)
{
	if (!e1)
		return -1;
	if (!e2)
		return 1;
	int elemento1 = *((int *)e1);
	int elemento2 = *((int *)e2);
	return elemento1 < elemento2;
}

void pruebas_recorrido_abb_con_cada_elemento()
{
	int *aux_alto = calloc(1, sizeof(int));
	*aux_alto = 100;
	int *aux_medio = calloc(1, sizeof(int));
	*aux_medio = 35;
	abb_t *arbol = abb_crear(comparacion);
	int *valor_1 = calloc(1, sizeof(int));
	*valor_1 = 10;
	int *valor_2 = calloc(1, sizeof(int));
	*valor_2 = 20;
	int *valor_3 = calloc(1, sizeof(int));
	*valor_3 = 30;
	int *valor_4 = calloc(1, sizeof(int));
	*valor_4 = 40;
	int *valor_5 = calloc(1, sizeof(int));
	*valor_5 = 50;
	abb_insertar(arbol, valor_2);
	abb_insertar(arbol, valor_1);
	abb_insertar(arbol, valor_3);
	abb_insertar(arbol, valor_4);
	abb_insertar(arbol, valor_5);

	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, funcion_recorrido,
					   aux_alto) == 0,
		     "No se puede iterar con arbol nulo");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, aux_alto) == 0,
		     "No se puede iterar con funcion nula");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_recorrido,
					   NULL) != 0,
		     "Se puede iterar con aux nulo");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_recorrido,
					   aux_alto) == 5,
		     "Se itera todo el arbol");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_recorrido,
					   aux_medio) == 4,
		     "Se itera hasta la mitad del arbol");

	abb_destruir_todo(arbol, free);
	free(aux_alto);
	free(aux_medio);
}

void pruebas_recorrido_con_array()
{
	size_t *tamanio_array_mayor = calloc(1, sizeof(size_t));
	*tamanio_array_mayor = 10;
	size_t *tamanio_array_incompleto = calloc(1, sizeof(size_t));
	*tamanio_array_incompleto = 3;
	void *array_completo = calloc(1, sizeof(void *) * *tamanio_array_mayor);
	void *array_incompleto =
		calloc(1, sizeof(void *) * *tamanio_array_incompleto);
	abb_t *arbol = abb_crear(comparacion);
	int *valor_1 = calloc(1, sizeof(int));
	*valor_1 = 10;
	int *valor_2 = calloc(1, sizeof(int));
	*valor_2 = 20;
	int *valor_3 = calloc(1, sizeof(int));
	*valor_3 = 30;
	int *valor_4 = calloc(1, sizeof(int));
	*valor_4 = 40;
	int *valor_5 = calloc(1, sizeof(int));
	*valor_5 = 50;
	abb_insertar(arbol, valor_1);
	abb_insertar(arbol, valor_2);
	abb_insertar(arbol, valor_3);
	abb_insertar(arbol, valor_4);
	abb_insertar(arbol, valor_5);

	pa2m_afirmar(abb_recorrer(NULL, INORDEN, array_completo,
				  *tamanio_array_mayor) == 0,
		     "No se puede recorrer con arbol NULL");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, NULL, *tamanio_array_mayor) ==
			     0,
		     "No se puede iterar con un array NULL");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array_completo, 0) == 0,
		     "No se puede iterar si el tamaño del array es 0");
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, array_incompleto,
			     *tamanio_array_incompleto) == 3,
		"Recorrer el arbol con un array de tamaño menor al arbol devuelve la cantidad de elementos correcta");
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, array_completo,
			     *tamanio_array_mayor) == 5,
		"Recorrer el arbol con un array de tamaño mayor al arbol devuelve la cantidad de elementos correcta");

	abb_destruir_todo(arbol, free);
	free(array_incompleto);
	free(array_completo);
	free(tamanio_array_incompleto);
	free(tamanio_array_mayor);
}

int main()
{
	pa2m_nuevo_grupo("\nPruebas de creacion");
	pruebas_creacion();

	pa2m_nuevo_grupo("\nPruebas de insercion");
	pruebas_insercion();

	pa2m_nuevo_grupo("\nPruebas de quitar");
	pruebas_quitar();

	pa2m_nuevo_grupo("\nPruebas de buscar");
	pruebas_buscar();

	pa2m_nuevo_grupo("\nPruebas de tamaño y vacio");
	pruebas_tamanio_y_vacio();

	pa2m_nuevo_grupo("\nPruebas de recorrido y abb con cada elemento");
	pruebas_recorrido_abb_con_cada_elemento();

	pa2m_nuevo_grupo("\nPruebas de recorrido con array");
	pruebas_recorrido_con_array();

	return pa2m_mostrar_reporte();
}
