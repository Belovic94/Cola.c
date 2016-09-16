#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#define CANT_APILAR 5

void pruebas_no_cola(void){
  cola_t* cola_no_creada = NULL;
  double valor = 2.45 ;

  /*Pruebas con una cola que no se creo*/
  print_test("Encolar en cola no creada (false)", !cola_encolar(cola_no_creada, &valor));
  print_test("Desencolar en cola no creada (false)", !cola_desencolar(cola_no_creada));
  print_test("Ver si la cola no creada esta vacia (true)", cola_esta_vacia(cola_no_creada));
  print_test("Ver primero de cola no creada (false)", !cola_ver_primero(cola_no_creada));
}

void pruebas_cola_vacia(void){
  cola_t* cola_vacia = cola_crear();
  int valor = 2;

  print_test("Cola vacia creada con exito", cola_vacia);
  print_test("Desencolar en cola vacia (false)", !cola_desencolar(cola_vacia));
  print_test("Ver si la cola esta vacia (true)", cola_esta_vacia(cola_vacia));
  print_test("Encolar en cola vacia (true)", cola_encolar(cola_vacia, &valor));
  print_test("Ver primero de cola (true)", (int*)cola_ver_primero(cola_vacia) == &valor);
  print_test("Ver si la cola esta vacia, luego de encolar un elemento (false)", !cola_esta_vacia(cola_vacia));
  print_test("Desencolar el unico elemento de la cola (true)", (int*)cola_desencolar(cola_vacia) == &valor);
  print_test("Ver si la cola esta vacia (true)", cola_esta_vacia(cola_vacia));
  cola_destruir(cola_vacia, NULL);
  print_test("Cola vacia destruida", true);
}

void pruebas_con_varios_elementos(void){
  cola_t* cola_con_elementos = cola_crear();
  float valor1 = 0.8F, valor2 = 1.6F, valor3 = 2.4F, valor4 = 3.2F, *pvalor;

  print_test("Cola creada con exito", cola_con_elementos);
  print_test("Encolar valor de prueba 1 (true)", cola_encolar(cola_con_elementos, &valor1));
  print_test("Encolar valor de prueba 2 (true)", cola_encolar(cola_con_elementos, &valor2));
  print_test("Desencolar el valor de prueba 1 (true)", (float*)cola_desencolar(cola_con_elementos) == &valor1);
  print_test("Ver primero de cola con elementos (true)", (float*)cola_ver_primero(cola_con_elementos) == &valor2);
  print_test("Encolar valor de prueba 3 (true)", cola_encolar(cola_con_elementos, &valor3));
  print_test("Encolar valor de prueba 4 (true)", cola_encolar(cola_con_elementos, &valor4));
  print_test("Ver si la cola esta vacia (false)", !cola_esta_vacia(cola_con_elementos));
  print_test("Desencolar el valor de prueba 2", (float*)cola_desencolar(cola_con_elementos) == &valor2);
  pvalor = cola_desencolar(cola_con_elementos);
  print_test("Desencolar el valor de prueba 3", *pvalor == valor3);
  cola_destruir(cola_con_elementos, NULL);
  print_test("Cola con elementos destruida", true);
}

void llenar_pila(pila_t* pila, int* vector){

  for(int i=0; i<CANT_APILAR; i++){
    vector[i] = i + 1;
    pila_apilar(pila, &vector[i]);
  }
}

void wrapper_pila_destruir(void* pila){
  pila_destruir((pila_t*)pila);
}

void pruebas_con_elementos_distintos(void){
  pila_t* pila_prueba = pila_crear();
  cola_t* cola = cola_crear();
  int vector[CANT_APILAR];
  double* valordou  = malloc(sizeof(double));
  int *valorint = malloc(sizeof(int));
  char *valorcha = malloc(sizeof(char));
  long *valorlon = malloc(sizeof(long));

  *valordou  = 3.5;
  *valorint = 10;
  *valorlon = 1000000000;
  *valorcha = 'T';

  llenar_pila(pila_prueba, vector);
  print_test("Encolar una pila de números enteros", cola_encolar(cola, pila_prueba));
  cola_destruir(cola, wrapper_pila_destruir);
  print_test("Destruir cola con pila encolada", true);
  cola = cola_crear();
  print_test("Encolar valor double", cola_encolar(cola, valordou));
  print_test("Encolar valor int", cola_encolar(cola, valorint));
  print_test("Encolar valor char", cola_encolar(cola, valorcha));
  print_test("Encolar valor long", cola_encolar(cola, valorlon));
  cola_destruir(cola, free);
  print_test("Cola destruida con varios elementos adentro", true);

}

void pruebas_cola_alumno(void){

  pruebas_no_cola();
  pruebas_cola_vacia();
  pruebas_con_varios_elementos();
  pruebas_con_elementos_distintos();
}
