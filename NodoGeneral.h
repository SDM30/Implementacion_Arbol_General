#ifndef __NODOGENERAL__H__
#define __NODOGENERAL__H__

#include <list>

template <class T> class NodoGeneral {

  protected:
    T dato;
    std::list<NodoGeneral<T> *> desc;
  
  public:
    NodoGeneral();
    ~NodoGeneral();
    T &obtenerDato();
    std::list<NodoGeneral<T>*>& obtenerDescendientes();
    void fijarDato(T& val);
    void limpiarLista();
    void adicionarDesc(T& nval);
    bool eliminarDesc(T& val);
    bool esHoja();

};

#include "NodoGeneral.hxx"

#endif