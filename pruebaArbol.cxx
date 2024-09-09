#include <iostream>
#include "ArbolGeneral.h"
#include "NodoGeneral.h"

int main() {

    // Crear un árbol vacío
    ArbolGeneral<int> arbol;
    std::cout << "Árbol vacío creado." << std::endl;

    // Insertar el nodo raíz
    int raiz = 10;
    arbol.fijarRaiz(new NodoGeneral<int>());
    arbol.obtenerRaiz()->fijarDato(raiz);
    std::cout << "Raíz fijada con valor: " << raiz << std::endl;

    // Insertar otros nodos
    int valor1 = 5, valor2 = 15, valor3 = 2, valor4 = 7;
    arbol.insertarNodo(raiz, valor1);
    arbol.insertarNodo(raiz, valor2);
    arbol.insertarNodo(valor1, valor3);
    arbol.insertarNodo(valor1, valor4);
    
    std::cout << "Nodos insertados." << std::endl;

    // Mostrar si el árbol está vacío
    std::cout << "¿El árbol está vacío? " << (arbol.esVacio() ? "Sí" : "No") << std::endl;

    // Recorrer el árbol en preorden
    std::cout << "Recorrido en preorden: ";
    arbol.preOrden();
    std::cout << std::endl;

    // Recorrer el árbol en posorden
    std::cout << "Recorrido en posOrden: ";
    arbol.posOrden();
    std::cout << std::endl;

    // Recorrer el árbol en nivel orden
    std::cout << "Recorrido en nivel orden: ";
    arbol.nivelOrden();
    std::cout << std::endl;

    // Buscar un valor
    int buscarVal = 15;
    std::cout << "¿El valor " << buscarVal << " está en el árbol? " << (arbol.buscar(buscarVal) ? "Sí" : "No") << std::endl;


    // Obtener la altura del árbol
    std::cout << "Altura del árbol: " << arbol.altura() << std::endl;

    // Obtener el tamaño
    // Volver a probar el tamaño después de la eliminación
    std::cout << "Tamaño del árbol: " << arbol.tamano() << std::endl;

    int eliminarVal = 7;
    if (arbol.eliminarNodo(eliminarVal)) {
        std::cout << "Nodo con valor " << eliminarVal << " eliminado." << std::endl;
    } else {
        std::cout << "Nodo con valor " << eliminarVal << " no encontrado." << std::endl;
    }

    // Volver a probar el tamaño después de la eliminación
    std::cout << "Tamaño del árbol después de eliminar el nodo " << eliminarVal << ": " << arbol.tamano() << std::endl;

    return 0;
}
