/**
 * @file Genetic.cpp
 * @author Johnny Aguero (johnny.zaet08@gmail.com)
 * @brief Este archivo se encarga de la logica del algortimo genetico para buscar la solucion mas optima al problema
 * @return Retorna una lista de los mejores individuos de cada generacion
 * @version 0.1
 * @date 2021-06-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define POBLACION 4
#define LONG_COD 16

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <tinyxml.h>

//Tipo de estructura la cual contiene el gen de cada individuo y su aptitud (su posicion relativa)
typedef struct {
    int genotipo[LONG_COD];
    int aptitud;
} Individuo;

//Metodos utilizados para la resolucion del problema
int fitness (Individuo);
Individuo * generarInicial(void);
Individuo * generarPoblacion (Individuo *);
Individuo * seleccionTorneos(Individuo * pob);
void cruzarSeleccion (Individuo *);
Individuo elite(Individuo *);
void AG();
void imprimePoblacion (Individuo *);
void imprimeGenotipo(Individuo);
void build_simple_doc(Individuo*, Individuo, Individuo, int);
bool compara(Individuo, Individuo);
bool sigue(Individuo);
 
int main() {
    srand (time(NULL));
    AG();
    return 0;
}
 
/**
 * @brief Recibe un individuo y se encarga de calcular su aptitud
 * 
 * @param ind individuo
 * @return int la aptitud del individuo
 */
int fitness (Individuo ind)
{
    int querido[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int fit = 0;
    for(int i = 0; i < 16; i++){
        if(ind.genotipo[i] != querido[i] && ind.genotipo[i] != 0){
            for(int j = 0; j < 16; i++){
                if(querido[i] == ind.genotipo[j]){
                    break;
                } else{
                    fit++;
                }
            }
        }
    }
    return fit;
}
  

 /**
  * @brief Esta funcion recibe un individuo el cual es el mejor adaptado de la generacion anterior para
  *  luego crear una poblacion con base en sus mutaciones posibles
  * 
  * @param Inicial 
  * @return Individuo* 
  */
Individuo * generarPoblacion(Individuo * Inicial)
{
    Individuo * poblacion;
    Individuo ind1, ind2, ind3, ind4;
    int i;
    int ref = 0;
 
    poblacion = (Individuo *) malloc(sizeof(Individuo)*POBLACION);
    for(i=0;i<LONG_COD;i++){
        if(Inicial->genotipo[i] == 0){
            break;
        }
    }
    if(i == 3 || i == 7 || i == 11 || i == 15){
        if(i + 5 <= 16){
            for(int j=0; j<17; j++){
                ind1.genotipo[j] = Inicial->genotipo[j];
            }
            ind1.genotipo[i] = ind1.genotipo[i+4];
            ind1.genotipo[i+4] = 0;
            ind1.aptitud = fitness(ind1);
            poblacion[ref] = ind1;
            ref++;
        }
        if(i - 5 >= 0){
            for(int j=0; j<17; j++){
                ind2.genotipo[j] = Inicial->genotipo[j];
            }
            ind2.genotipo[i] = ind2.genotipo[i-4];
            ind2.genotipo[i-4] = 0;
            ind2.aptitud = fitness(ind2);
            poblacion[ref] = ind2;
            ref++;
        }
        for(int j=0; j<17; j++){
            ind3.genotipo[j] = Inicial->genotipo[j];
        }
        ind3.genotipo[i] = ind3.genotipo[i-1];
        ind3.genotipo[i-1] = 0;
        ind3.aptitud = fitness(ind3);
        poblacion[ref] = ind3;
        ref++;
    }
    else if(i == 0 || i == 4 || i == 8 || i == 12){
        if(i + 5 <= 16){
            for(int j=0; j<17; j++){
                ind1.genotipo[j] = Inicial->genotipo[j];
            }
            ind1.genotipo[i] = ind1.genotipo[i+4];
            ind1.genotipo[i+4] = 0;
            ind1.aptitud = fitness(ind1);
            poblacion[ref] = ind1;
            ref++;
        }
        if(i - 5 >= 0){
            for(int j=0; j<17; j++){
                ind2.genotipo[j] = Inicial->genotipo[j];
            }
            ind2.genotipo[i] = ind2.genotipo[i-4];
            ind2.genotipo[i-4] = 0;
            ind2.aptitud = fitness(ind2);
            poblacion[ref] = ind2;
            ref++;
        }
        for(int j=0; j<17; j++){
            ind3.genotipo[j] = Inicial->genotipo[j];
        }
        ind3.genotipo[i] = ind3.genotipo[i+1];
        ind3.genotipo[i+1] = 0;
        ind3.aptitud = fitness(ind3);
        poblacion[ref] = ind3;
        ref++;
    }
    else{
        if(i+5 <= 16){
            for(int j=0; j<17; j++){
                ind1.genotipo[j] = Inicial->genotipo[j];
            }
            ind1.genotipo[i] = ind1.genotipo[i+4];
            ind1.genotipo[i+4] = 0;
            ind1.aptitud = fitness(ind1);
            poblacion[ref] = ind1;
            ref++;
        }
        if(i-5 >= 0){
            for(int j=0; j<17; j++){
                ind2.genotipo[j] = Inicial->genotipo[j];
            }
            ind2.genotipo[i] = ind2.genotipo[i-4];
            ind2.genotipo[i-4] = 0;
            ind2.aptitud = fitness(ind2);
            poblacion[ref] = ind2;
            ref++;
        }

        for(int j=0; j<17; j++){
            ind3.genotipo[j] = Inicial->genotipo[j];
        }
        ind3.genotipo[i] = ind3.genotipo[i+1];
        ind3.genotipo[i+1] = 0;
        ind3.aptitud = fitness(ind3);
        poblacion[ref] = ind3;
        ref++;

        for(int j=0; j<17; j++){
            ind4.genotipo[j] = Inicial->genotipo[j];
        }
        ind4.genotipo[i] = ind4.genotipo[i-1];
        ind4.genotipo[i-1] = 0;
        ind4.aptitud = fitness(ind4);
        poblacion[ref] = ind4;
        ref++;
    }
    return poblacion;
}
 
 /**
  * @brief Crea un nuevo vector de individuo de una poblacion, seleccionando el mejor entre un combate
  *  de dos de estos individuos
  * 
  * @param poblacion 
  * @return Individuo* 
  */
Individuo * seleccionTorneos (Individuo * poblacion)
{
    Individuo candidato_a, candidato_b;
    int i;
 
    Individuo * seleccion = (Individuo *) malloc (sizeof(Individuo)*POBLACION);
 
    for (i=0; i<POBLACION-1; i++)
    {
        candidato_a = poblacion[i];
        candidato_b = poblacion[i + 1];
 
        if (candidato_a.aptitud < candidato_b.aptitud)
            seleccion[i] = candidato_a;
        else
            seleccion[i] = candidato_b;
    }
 
    return seleccion;
}
 
/* PROC cruzarSeleccion (Individuo *)                   DEV (void)
 * MODIFICA (Individuo *)
 * EFECTO esta funcion se encarga de cruzar los individuos seleccionados. la seleccion
 *  esta ordenada luego cruzamos los individuos seguidos de dos en dos. para cada una
 *  de las iteraciones se aplica la probabilidad de cruce. en caso de que se crucen
 *  los individuos se genera un punto de cruce y se intercambian las porciones del
 *  vector. luego se llama a la funcion de mutacion. en caso de que no haya cruce, los
 *  padres pasan directamente a la siguiente generacion */
 
void cruzarSeleccion (Individuo * seleccion)
{
    int i, j, k;
    Individuo aux;
 
    for(i=0; i<POBLACION; i+=2)
    {
            for(k=0; k<LONG_COD; k++){
                if(seleccion[i].genotipo[k] == 0){
                    break;
                }
            }
            for(j=0; j<LONG_COD; j++)
            {
                if(seleccion[i].genotipo[j] < seleccion[i+1].genotipo[j] && j != k){
                    aux.genotipo[j] = seleccion[i].genotipo[j];
                } else{
                    aux.genotipo[j] = seleccion[i+1].genotipo[j];
                }
            }
 
            seleccion[i].aptitud = fitness(seleccion[i]);
            seleccion[i+1].aptitud = fitness(seleccion[i+1]);
            aux.aptitud = fitness(aux);
            seleccion[3] = aux;
    }
}
 
 /**
  * @brief La siguiente funcion se encarga de elegir el mejor adaptado de una poblacion para
  *  convertirlo en padre de la siguiente generacion
  * 
  * @param poblacion 
  * @return Individuo 
  */
Individuo elite (Individuo * poblacion)
{
    Individuo best = poblacion[0];
 
    for(int i=0; i<POBLACION; i++){
        int ceros = 0;
        for(int k = 0; k < 16; k++){
            if(poblacion[i].genotipo[k] == 0){
                ceros ++;
            }
        }
        if(best.aptitud > poblacion[i].aptitud && poblacion[i].aptitud != 0 && ceros >= 1)
            best = poblacion[i];
    }
    return best;
}


/**
 * @brief Se encarga de crear aleatoriamente un individuo el cual sera el padre de la primer generacion
 * y en base a el se generara la poblacion
 * 
 * @return Individuo* 
 */
Individuo * generarInicial(void){
    Individuo * correcto = (Individuo *) malloc (sizeof(Individuo));

    int array[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int size = 16;
    int sizePo = 0;
    int pos;

    while(size > 0){
        pos  = rand() % size;
        correcto->genotipo[sizePo] = array[pos];
        sizePo++;

        while(pos<size)
		{
			array[pos]=array[pos+1];
			array[pos+1]=0;
			pos++;
		}
		size--;
    }
    
    correcto->genotipo[rand() % 16] = 0;
    for(int i=0;i<16;i++){
		std::cout << correcto->genotipo[i] << " ";
    }
    return correcto;
}


 /**
* @brief se trata de la funcion que ejecuta el algoritmo. el proceso es el siguiente
 *  1 - Generar la poblacion
 *  2 - Seleccion de candidatos al cruce
 *  3 - Cruce de los candidatos (incluye mutacion)
 *  4 - Incluir al mejor de la generacion anterior en la nueva
 *  5 - Repetir el proceso  
 * */
void AG (void)
{
    Individuo * inicial = generarInicial();
    Individuo best, bestTemp, bestTemp1;
    Individuo * seleccion, * poblacion = generarPoblacion(inicial);
    std::cout << std::endl;
    std::cout << "Poblacion inicial" << std::endl;
    imprimePoblacion(poblacion);
    int generacion = 0;
 
    do
    {
        seleccion = seleccionTorneos(poblacion);
        cruzarSeleccion(seleccion);
        std::cout << "Poblacion despues de cruzar" << std::endl;
        imprimePoblacion(seleccion);
        best = elite(poblacion);
        if(compara(best, bestTemp)){
            best = poblacion[1];
        } else if (compara(best, bestTemp1)){
            best = poblacion[2];
        }

        std::cout << "BEST:" << std::endl;
        
        imprimeGenotipo(best);
        
        build_simple_doc(poblacion , bestTemp, best, generacion);
        
        free(poblacion);

        if(generacion >= 1){
            bestTemp1 = bestTemp;
        }
        bestTemp = best;

        printf ("\n - Es la generacion numero %i\n", generacion+1);

        poblacion = generarPoblacion(&best);
        std::cout << "\nNueva poblacion" << std::endl;
        imprimePoblacion(poblacion);
        generacion++;

        if(generacion > 10){
            break;
        }

    } while (!sigue(best));

    build_simple_doc(poblacion , bestTemp, best, generacion);
    
    free(poblacion);
    std::cout << std::endl;
    printf ("*************************************\n");
    printf ("*          FIN DEL ALGORITMO        *\n");
    printf ("*************************************\n");
    printf (" - Es la generacion numero %i\n", generacion);
    printf ("*************************************\n");
}
 

 /**
  * @brief Recibe una poblacion y se encarga de imprimir toda la poblacion
  * 
  * @param pob 
  */
void imprimePoblacion (Individuo * pob)
{ 
    for(int i = 0; i < POBLACION; i++)
    {
        if(pob[i].genotipo[0] < 16){
            imprimeGenotipo(pob[i]);
            std::cout << std::endl;
        }
    }
}
 
 
 /**
  * @brief Recive un parametro Individuo al cual se le procede a imprimir todo el genotipo
  * 
  * @param x 
  */
void imprimeGenotipo (Individuo x)
{
    int i;
 
    for(i=0; i<LONG_COD; i++){
        std::cout << x.genotipo[i] << " ";
	}
}

std::string to_str(Individuo indi){
	std::string texto = "";
	
	for(int i=0; i<LONG_COD; i++){
        	texto += std::to_string(indi.genotipo[i]) + " ";
        }
 	return texto;
}

std::string to_strPo(Individuo * pobla){
	std::string texto = "";
	for(int j=0; j<4; j++){
		for(int i=0; i<LONG_COD; i++){
        		texto += std::to_string(pobla[j].genotipo[i]) + " ";
        	}
        	texto += ";";
        }
 	return texto;
}


void build_simple_doc(Individuo * Poblacion, Individuo Padre, Individuo Hijo, int Generacion)
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    	doc.LinkEndChild( decl );

	TiXmlElement * elementP = new TiXmlElement( "Padre" );
	TiXmlText * textP = new TiXmlText(to_str(Padre));
	elementP->LinkEndChild( textP );
	doc.LinkEndChild( elementP );

    	TiXmlElement * elementM = new TiXmlElement( "Poblacion/Mutaciones" );
	TiXmlText * textM = new TiXmlText( to_strPo(Poblacion) );
	elementM->LinkEndChild( textM );
	doc.LinkEndChild( elementM );

    	TiXmlElement * elementB = new TiXmlElement( "Mejor hijo" );
	TiXmlText * textB = new TiXmlText( to_str(Hijo) );
	elementB->LinkEndChild( textB );
	doc.LinkEndChild( elementB );

	doc.SaveFile( "./xml/" + std::to_string(Generacion) + ".xml" );
}

/**
 * @brief Recibe dos individuos para comparar si son los mismos, en este caso revisa si indivios
 * anteriores son iguales para realizar otra tipo
 * 
 * @param best 
 * @param bestTemp 
 * @return true 
 * @return false 
 */
bool compara(Individuo best, Individuo bestTemp){
    for(int i = 0; i < LONG_COD; i++){
        if(best.genotipo[i] != bestTemp.genotipo[i]){
            return false;
        }
    }
    return true;
}
/**
 * @brief Recibe el indivudo best para comparar si su genotipo es el correcto y asi
 * parar el ciclo.
 * 
 * @param best 
 * @return true 
 * @return false 
 */
bool sigue(Individuo best){
    int cero = 0;
    for(int i = 0; i < LONG_COD; i++){
        if (best.genotipo[i] != i + 1 && cero != 0)
        {
            return false;
        }
        else if(best.genotipo[i] != i + 1){
            cero++;
        }
    }
    return true;
}
