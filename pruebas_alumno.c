#include "abb.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int cmp(const char* clave_vieja, const char* clave_nueva) {
	// Si las claves son iguales, devuelve 0
	int vieja = atoi(clave_vieja);
	int nueva = atoi(clave_nueva);
	if (vieja == nueva) return 0;
	// Si clave nueva es mayor a clave vieja, return 1
	else if (nueva > vieja) return 1;
	// Si clave nueva es menor a clave vieja, return -1
	else return (-1);
}
abb_comparar_clave_t cmp_ptr = &cmp;

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_abb() {
	char *val1 = "Uno";
	char *val2 = "Dos";
	char *val3 = "Tres";
	char *val4 = "Cuatro";
	char *val5 = "Cinco";
	char *val6 = "Seis";
	char *val7 = "Siete";
	char *val8 = "Ocho";
	char *val9 = "Nueve";
	char *val10 = "Diez";
	char *val11 = "Once";
	
	abb_t* arbol = abb_crear(*cmp, NULL);
	print_test("Prueba arbol vacio: ", arbol);
	print_test("Cantidad de arbol es 0: ", abb_cantidad(arbol) == 0);
	
	print_test("Guardo 'Clave 52 | Valor <Uno>' en la raiz de arbol: ", abb_guardar(arbol, "52", val1));
	print_test("El 52 pertenece", abb_pertenece(arbol, "52"));
	print_test("Cantidad de arbol es 1: ", abb_cantidad(arbol) == 1);
	
	print_test("Guardo 'Clave 2 | Valor <Dos>' en arbol: ", abb_guardar(arbol, "2", val2));
	print_test("El 2 pertenece", abb_pertenece(arbol, "2"));
	print_test("Cantidad de arbol es 2: ", abb_cantidad(arbol) == 2);
	print_test("Guardo 'Clave 33 | Valor <Tres>' en arbol: ", abb_guardar(arbol, "33", val3));
	print_test("El 33 pertenece", abb_pertenece(arbol, "33"));
	print_test("Cantidad de arbol es 3: ", abb_cantidad(arbol) == 3);
	print_test("Guardo 'Clave 99 | Valor <Cuatro>' en arbol: ", abb_guardar(arbol, "99", val4));
	print_test("El 99 pertenece", abb_pertenece(arbol, "99"));
	print_test("Cantidad de arbol es 4: ", abb_cantidad(arbol) == 4);
	print_test("Reemplazo dato de clave 2 por <Cinco> en arbol: ", abb_guardar(arbol, "2", val5));
	print_test("Cantidad de arbol es 4: ", abb_cantidad(arbol) == 4);
	
	print_test("Busco clave 2 con abb_obtener, devuelve <Cinco>: ", val5 == abb_obtener(arbol, "2"));
	print_test("Busco clave 111 con abb_obtener, devuelve NULL: ", NULL == abb_obtener(arbol, "111"));
	print_test("Busco clave 33 con abb_pertenece, devuelve TRUE: ", abb_pertenece(arbol, "33"));
	print_test("Busco clave 10 con abb_pertenece, devuelve FALSE: ", !abb_pertenece(arbol, "10"));

	print_test("Cantidad de arbol antes de borrar es 4: ", abb_cantidad(arbol) == 4);
	print_test("Borro nodo hoja, clave 33, devuelve el dato <Tres>: ", abb_borrar(arbol, "33") == val3);
	print_test("Busco el nodo borrado con abb_pertenece, devuelve false: ", !abb_pertenece(arbol, "33"));
	print_test("Cantidad de arbol despues de borrar es 3: ", abb_cantidad(arbol) == 3);

	print_test("Guardo 'Clave 30 | Valor <Seis>' en arbol: ", abb_guardar(arbol, "30", val6));
	print_test("Guardo 'Clave -1 | Valor <Siete>' en arbol: ", abb_guardar(arbol, "-1", val7));
	print_test("Guardo 'Clave -6 | Valor <Ocho>' en arbol: ", abb_guardar(arbol, "-6", val8));
	print_test("Guardo 'Clave 15 | Valor <Nueve>' en arbol: ", abb_guardar(arbol, "15", val9));

	print_test("Borro nodo con un solo hijo, clave -1, devuelve el dato <Siete>: ", abb_borrar(arbol, "-1") == val7);
	print_test("Busco el nodo borrado con abb_pertenece, devuelve false: ", !abb_pertenece(arbol, "-1"));
	print_test("Cantidad de arbol despues de borrar es 6: ", abb_cantidad(arbol) == 6);

	print_test("Borro nodo con un solo hijo, clave 30, devuelve el dato <Seis>: ", abb_borrar(arbol, "30") == val6);
	print_test("Busco el nodo borrado con abb_pertenece, devuelve false: ", !abb_pertenece(arbol, "30"));
	print_test("Cantidad de arbol despues de borrar es 5: ", abb_cantidad(arbol) == 5);

	print_test("Guardo 'Clave -7 | Valor <Diez>' en arbol: ", abb_guardar(arbol, "-7", val10));
	print_test("Guardo 'Clave 0 | Valor <Once>' en arbol: ", abb_guardar(arbol, "0", val11));

	print_test("Borro nodo con un dos hijos, clave 2, devuelve el dato <Cinco>: ", abb_borrar(arbol, "2") == val5);
	print_test("Busco el nodo borrado con abb_pertenece, devuelve false: ", !abb_pertenece(arbol, "2"));
	print_test("Cantidad de arbol despues de borrar es 6: ", abb_cantidad(arbol) == 6);

	print_test("Borro nodo raiz con un dos hijos, clave 52, devuelve el dato <Uno>: ", abb_borrar(arbol, "52") == val1);
	print_test("Busco el nodo borrado con abb_pertenece, devuelve false: ", !abb_pertenece(arbol, "52"));
	print_test("Cantidad de arbol despues de borrar es 5: ", abb_cantidad(arbol) == 5);
	
	abb_destruir(arbol);
}

void pruebas_abb_alumno() {
	pruebas_abb();
}
