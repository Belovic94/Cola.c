#include <cola.h>


/*Defino la estructura nodo*/
struct Nodo{
  void* dato;
  nodo_t* proximo;
}

/*Defino la estructura cola*/
struct cola{
  nodo_t* primero;
  nodo_t* ultimo;
}

cola_t* cola_crear(void);

void cola_destruir(cola_t *cola, void destruir_dato(void*));

bool cola_esta_vacia(const cola_t *cola);

bool cola_encolar(cola_t *cola, void* valor);

void* cola_ver_primero(const cola_t *cola);

void* cola_desencolar(cola_t *cola);
