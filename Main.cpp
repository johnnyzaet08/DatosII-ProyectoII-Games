#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "listasimple.h"

int main(){
    int array[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    ListaSimple<int> * poblacion = new ListaSimple<int>();
    int size = 16;
    int sizePo = 0;
    int pos;

    while(size > 0){
        pos  = rand() % size;
        poblacion->insertar(array[pos]);
        sizePo++;

        while(pos<size)
		{
			array[pos]=array[pos+1];
			array[pos+1]=0;
			pos++;
		}
		size--;
    }
    poblacion->
    for(int i=0;i<16;i++)
			std::cout<<poblacio<<" ";

    return 0;
}