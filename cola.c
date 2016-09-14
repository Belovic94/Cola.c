#include <cola.h>


/*Defino la estructura nodo*/
struct nodo{
  void* dato;
  nodo_t* proximo;
}

/*Defino la estructura cola*/
struct cola{
  nodo_t* primero;
  nodo_t* ultimo;
}

nodo_t* nodo_crear(void* valor){
  nodo_t* nodo = malloc(sizeof(nodo_t));

  if (!nodo){
    return NULL;
  }
  nodo->dato = malloc(sizeof(void*));
  if (!nodo->dato){
    free(nodo);
    return NULL;
  }
  nodo->dato = valor;
  nodo->proximo = NULL;
  return nodo;
}

void nodo_destruir(nodo_t* nodo){

  free(nodo->dato);
  free(nodo);
}

/*Creo una nueva cola */
cola_t* cola_crear(void){
  cola_t* cola = malloc(sizeof(cola_t));
  
  return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){

}

bool cola_esta_vacia(const cola_t *cola){

  if ()(!cola) || (!cola->primero)){
    return true;
  }
  return false;
}

bool cola_encolar(cola_t *cola, void* valor){
  nodo_t* nodo_nuevo = nodo_crear(valor);

  if(!cola || !nodo_nuevo){
    return false;
  }
  if (!cola->primero){
    cola->primero = nodo_nuevo;
    cola->ultimo = nodo_nuevo;
  }
  else{
    if (cola->primero == cola->ultimo){
      cola->primero->proximo = nodo_nuevo;
    }
    cola->ultimo->proximo = nodo_nuevo;
    cola->ultimo = nodo_nuevo;
  }
  return true;
}

void* cola_ver_primero(const cola_t *cola){

  if(!cola){
    return NULL;
  }
  return cola->primero;
}

/*Desencolo un elemento de la cola*/
void* cola_desencolar(cola_t *cola){
  nodo_t* nodo_aux;
  if(!cola){
    return NULL;
  }
  nodo_aux = cola->primero;
  nodo_destruir(cola->primero);
  cola->primero = nodo_aux->proximo;
  if (!cola->primero){
    cola->ultimo = NULL;
  }
  return nodo_aux->dato;
}
