#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#define CANT_APILAR 5 //cantidad de valores a apilar en la pila utilizada
#define CANT_ELEM_VEC 10000 //cantidad de valores que tendra el vector utilizado

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
  print_test("Ver primero en cola vacia (true)", !cola_ver_primero(cola_vacia));
  print_test("Encolar en cola vacia (true)", cola_encolar(cola_vacia, &valor));
  print_test("Ver primero de cola (true)", (int*)cola_ver_primero(cola_vacia) == &valor);
  print_test("Ver si la cola esta vacia, luego de encolar un elemento (false)", !cola_esta_vacia(cola_vacia));
  print_test("Desencolar el unico elemento de la cola (true)", (int*)cola_desencolar(cola_vacia) == &valor);
  print_test("Ver si la cola esta vacia (true)", cola_esta_vacia(cola_vacia));
  cola_destruir(cola_vacia, NULL);
  print_test("Cola vacia destruida", true);
}

void pruebas_con_elementos_iguales(void){
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

/*Funciones auxiliares para la pila */
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

  /*Verifico que salgan en el orden correcto*/
  print_test("Desencolar valor double", *valordou == *(double*)cola_desencolar(cola));
  print_test("Desencolar valor int", *valorint == *(int*)cola_desencolar(cola));
  print_test("Desencolar valor char", *valorcha == *(char*)cola_desencolar(cola));
  /*Libero la memoria que pedi para los elementos encolados*/
  free(valordou);
  free(valorint);
  free(valorcha);

  /*Destruyo la cola, dejando un elemento, al cual se lo pidio con malloc*/
  cola_destruir(cola, free);
  print_test("Cola destruida con varios elementos adentro", true);

}

/*Funciones auxiliares para el vector dinámico*/
void llenar_vector(int* vector, int largo){
  for (int i=0; i < largo;i++){
    vector[i] = i + 1;
  }
}

bool agregar_valores(cola_t* cola, int inicio, int fin, int *valores){

  for (int i=inicio; i < fin ; i++){
    if(!cola_encolar(cola, &valores[i])){
      return false;
    }
  }
  return true;
}

bool sacar_valores(cola_t* cola, int inicio, int fin, int *valores){
  int* dato;
  /*Verifico que los valores desencolados se correspondan con los del vector*/
  for (int i=inicio; i < fin; i++){
    dato = cola_desencolar(cola);
    if (*dato != valores[i]){
      return false;
    }
  }
  return true;
}

void pruebas_con_varios_elementos(void){
  cola_t* cola = cola_crear();
  int vector[CANT_ELEM_VEC];

  llenar_vector(vector, CANT_ELEM_VEC);
  print_test("Crear cola vacia", cola );
  print_test("Encolar un serie de valores enteros", agregar_valores(cola, 0, CANT_ELEM_VEC, vector));
  print_test("Ver primero de la cola llena con elementos", vector[0] == *(int*)cola_ver_primero(cola));
  print_test("Desencolar un serie de valores enteros", sacar_valores(cola, 0, CANT_ELEM_VEC/2, vector));
  print_test("Ver primero de la cola con la mitad de los elementos", vector[CANT_ELEM_VEC/2] == *(int*)cola_ver_primero(cola));
  cola_destruir(cola, NULL);
  print_test("Cola destruida con varios elementos adentro", true);
}

void pruebas_cola_alumno(void){

  pruebas_no_cola();
  pruebas_cola_vacia();
  pruebas_con_elementos_iguales();
  pruebas_con_elementos_distintos();
  pruebas_con_varios_elementos();
}
