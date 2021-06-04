/**
 * @file nodo.h
 * @author Ignacio Morales
 * @brief  Struc of the node
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef NODO_H
#define NODO_H

#include <stddef.h>

/**
 * @brief Node, struc.
 *  
 * @tparam DATO, type of the node
 */
template<class DATO>
class Nodo {
public:
    DATO dato;
    Nodo<DATO> * siguiente;


    // Constructores
    Nodo(){
        dato;
        siguiente = NULL;
    }

    Nodo(DATO _dato){
        dato = _dato;
        siguiente = NULL;
    }

    Nodo(DATO _dato, Nodo<DATO> * _siguiente){
        dato = _dato;
        siguiente = _siguiente;
    }
    /**
     * @brief Delete de memory space of the node
     *  
     * @param p, pointer of the node
     */
    void operator delete(void * p){
        free(p);
    }

    /**
     * @brief Edited the value of the node
     *  
     * @param DATO, node
     */
    void modif(DATO _dato){
        dato = _dato;
    }

    /**
     * @brief Consult the node
     */
    DATO consulta(){
        return dato;
    }
};

#endif
