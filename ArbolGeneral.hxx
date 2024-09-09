#include "ArbolGeneral.h" 

#include <queue>

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
  this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T& val) {
  NodoGeneral<T>* nodo = new NodoGeneral<T>;
  nodo->fijarDato(val);
  this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
  delete this->raiz;
  this->raiz = NULL;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
  return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
  return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
  this->raiz = nraiz;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T& padre, T& n) {
  
  bool insertado = false;
  //Revisar si el arbol es vacio:
  // crear un nuevo nodo, asignar dato, poner ese nodo como raiz
  if (this->esVacio()) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>;
    nodo->fijarDato(n);
    this->raiz = nodo;
    insertado = true;
  }

  // si hay al menos un nodo en el arbol
  // - revisar el nodo donde estoy para ver si coincide con padre
  if ((this->raiz)->obtenerDato() == padre) {
    (this->raiz)->adicionarDesc(n);
    insertado = true;
  } else {
    insertado = this->insertarNodo(this->raiz, padre, n);
  }

  return insertado;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(NodoGeneral<T>* nodo, T& padre, T& n){
  // - si es el padre, insertar ahi el nuevo hijo
  if (nodo->obtenerDato() == padre){
    nodo->adicionarDesc(n);
    return true;
  }
  // - si no es el padre, revisar cada nodo hijo y llamar a insertar ahi
  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); it++) {
    if ((*it)->obtenerDato() == padre) {  // Llama a la función no miembro buscar recursivamente.
      (*it)->adicionarDesc(n);
      return true;  // Si se encuentra el nodo, retorna true.
    }
    this->insertarNodo(*it, padre, n);
  }

  return false;
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T& n) {
  // Si el árbol es vacío, retornar false
  if (this->esVacio()){
    return false;
  }

  // Si el nodo raíz es el que queremos eliminar
  if (this->raiz->obtenerDato() == n) {
    // Llamar al destructor para eliminar el nodo raíz y sus descendientes
    delete this->raiz;
    this->raiz = NULL;
    return true;
  }

  // Llamar a la función auxiliar para eliminar el nodo
  return eliminarNodo(this->raiz, n);
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(NodoGeneral<T>* nodo, T& n) {
  // Recorrer los descendientes para encontrar el nodo a eliminar
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); ++it) {
    if ((*it)->obtenerDato() == n) {
      // Si encontramos el nodo, lo eliminamos y actualizamos la lista de descendientes
      delete *it;
      nodo->obtenerDescendientes().erase(it);
      return true;
    }
    // Llamar recursivamente para eliminar en los subárboles
    if (eliminarNodo(*it, n)) {
      return true;
    }
  }

  return false;
}


template <class T>
bool ArbolGeneral<T>::buscar(T& n) {
  bool encontrado = false;
  //si el arbol esta vacio:
  if (this->esVacio()) {
    return encontrado;  
  }

  // si el arbol no esta vacio:
  // comparo dato en el nodo actual con dato parametro
  if ((this->raiz)->obtenerDato() == n) {
    encontrado = true;
  } else {
    encontrado = this->buscar(this->raiz, n);
  }

  return encontrado;
}

template <class T>
bool ArbolGeneral<T>::buscar(NodoGeneral<T>* nodo, T& n) {
  // si es ese, retorno que lo encontre
  if (nodo->obtenerDato() == n){
    return true;
  }

  // si no, para cada nodo hijo hacer el llamado a buscar
  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); it++){
    if (buscar(*it, n)) {  // Llama a la función no miembro buscar recursivamente.
      return true;  // Si se encuentra el nodo, retorna true.
    }
  }

  return false;
}

template <class T>
int ArbolGeneral<T>::altura() {
  if (this->esVacio()) {
    return -1;
  } else {
    return this->altura(this->raiz);
  }
}

template <class T>
int ArbolGeneral<T>::altura(NodoGeneral<T>* nodo) {
  int alt = -1;

  if (nodo->esHoja()){
    alt = 0;
  } else {
    int alth;
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); it++) {
      alth = this->altura(*it);
      if (alt < alth + 1) {
        alt = alth + 1;
      }
    }
  }

  return alt;
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
  // si esta vacio, retornar 0
  if (this->esVacio())
    return 0;
  // para cada uno de los hijos, llamar a tamaño
  int tam = 0;
  // acumulo esos tamaños en una varible
  tam += tamano(this->raiz);
  // retorno ese valor acumulado más 1
  return tam;
}

template <class T>
unsigned int ArbolGeneral<T>::tamano(NodoGeneral<T>* nodo) {

    int contador = 1; // Contar el nodo actual
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); it++) {
        contador += tamano(*it); // Contar los nodos en los subárboles
    }
    
    return contador;
}

template <class T>
void ArbolGeneral<T>::preOrden() {
  if (!this->esVacio())
    this->preOrden(this->raiz);
}

template <class T>
void ArbolGeneral<T>::preOrden(NodoGeneral<T>* nodo) {
  std::cout << nodo->obtenerDato() << " ";

  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); it++){
    this->preOrden(*it);
  }
}

template <class T>
void ArbolGeneral<T>::posOrden() {
  if (!this->esVacio())
    this->posOrden(this->raiz);
}

template <class T>
void ArbolGeneral<T>::posOrden(NodoGeneral<T>* nodo){
  // llamar a posorden sobre cada hijo
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = nodo->obtenerDescendientes().begin(); it != nodo->obtenerDescendientes().end(); it++) {
    this->posOrden(*it);
  }

// imprimo en pantalla el dato del nodo actual
  std::cout << nodo->obtenerDato() << " ";
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
  // NO ES RECURSIVO
  // ubicarme en la raiz
  // poner la raiz en una cola
  std::queue<NodoGeneral<T>*> colaRaiz;
  colaRaiz.push(this->raiz);
  // hacer un ciclo mientar haya algo en la cola
  while (!colaRaiz.empty())
  {
    // - saco el primero disponible en la cola
    NodoGeneral<T>* elem = colaRaiz.front();
    // - imprimo su dato
    std::cout<< elem->obtenerDato() <<" ";
    typename std::list<NodoGeneral<T>*>::iterator it;
    // - inserto en la cola todos sus hijos
    for (it = elem->obtenerDescendientes().begin(); it != elem->obtenerDescendientes().end(); it++) {
      colaRaiz.push(*it);
    }
    colaRaiz.pop();    
  }
} 
