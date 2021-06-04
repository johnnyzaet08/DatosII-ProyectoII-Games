/**
 * @file listasimple.h
 * @author Ignacio Morales
 * @brief List Data Structure
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "nodo.h"
#include <stddef.h>

/**
 * @brief SimpleList class, contains de logic of the list structure.
 *  
 * @tparam DATO, list data type
 */

template<class DATO>
class ListaSimple {

private:

public:
    Nodo<DATO> * inicio;
    int size = 0;

    // Constructores
    ListaSimple(){
        inicio = NULL;
    }

    // Metodos
    void insertar(DATO);
    bool estaVacia();
    void modificar(int);
    void eliminar(DATO);
    DATO obtenerPos(int);
    void print();
};

/**
 * @brief Add node to the list
 *  
 * @tparam DATO, list data type
 * @param _dato, node to add at the list
 */
template<class DATO>
void ListaSimple<DATO>::insertar(DATO _dato){
    if (inicio == NULL) {
        inicio = new Nodo<DATO>(_dato);
        size += 1;
    }else {
        Nodo<DATO> * tmp = inicio;
        while (tmp->siguiente != NULL){
            tmp = tmp->siguiente;
        }
        Nodo<DATO> * nuevo = new Nodo<DATO>(_dato);
        tmp->siguiente = nuevo;
        nuevo->siguiente = NULL;
        size += 1;
    }
}

/**
 * @brief Delete node to the list
 *  
 * @tparam DATO, list data type
 * @param _dato, node to delete at the list
 */
template<class DATO>
void ListaSimple<DATO>::eliminar(DATO _dato){
    if (!estaVacia()){
        if (_dato == inicio->dato) {
            Nodo<DATO> * eliminado = inicio;
            inicio = inicio->siguiente;
            eliminado->siguiente = NULL;
            delete eliminado;
            size -= 1;
        }
        else {
            Nodo<DATO> * nodo_anterior = inicio;
            Nodo<DATO> * tmp;
            tmp = inicio;
            while (tmp != NULL){
                if (tmp->dato == _dato){
                    nodo_anterior->siguiente = tmp->siguiente;
                    tmp->siguiente = NULL;
                    delete tmp;
                    size -= 1;
                }
                nodo_anterior = tmp;
                tmp = tmp->siguiente;
            }
        }
    }
}

/**
 * @brief Get node given a pos
 *  
 * @tparam Pos, pos of the node
 * @return dato in the specific pos
 */
template<class DATO>
DATO ListaSimple<DATO>::obtenerPos(int Pos){
    Nodo<DATO> *tmp = inicio;
    int i=0;
    if(tmp != NULL){
        if(Pos == 0){
            return tmp->dato;
        }
        while(i < Pos && i <= size){
            tmp = tmp->siguiente;
            i += 1; 
    }   return tmp->dato; 
    } return tmp->dato;
}

/**
 * @brief Check the list is empty
 *  
 * @return bool, if the list is empty
 */
template<class DATO>
bool ListaSimple<DATO>::estaVacia(){
    return inicio == NULL;
}

template<class DATO>
void print(){
    if (inicio == NULL) {
        std::cout << NULL << std::endl;
    }else {
        Nodo<DATO> * tmp = inicio;
        while (tmp->siguiente != NULL){
            std::cout << tmp->dato << " ";
            tmp = tmp->siguiente;
        }
        std::cout << std::endl;
    }
}
#endif
