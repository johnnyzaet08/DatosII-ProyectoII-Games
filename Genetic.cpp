#define POBLACION 4
#define LONG_COD 16
#define LIMITE -5.12
#define PROB_CRUCE 0.3
#define PROB_MUTACION 0.001
#define INTERVALO 10.24/pow(2,LONG_COD/2)
 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tinyxml/tinyxml.h"
 
typedef struct {
    int genotipo[LONG_COD];
    int aptitud;
} Individuo;
 
int fitness (Individuo);
Individuo * generarInicial(void);
Individuo * generarPoblacion (Individuo *);
Individuo * seleccionTorneos(Individuo * pob);
void mutacionHijos (Individuo *);
void cruzarSeleccion (Individuo *);
Individuo elite(Individuo *);
void AG();
void imprimePoblacion (Individuo *);
void imprimeGenotipo(Individuo);
void build_simple_doc();
 
int main() {
    AG();
    return 0;
}
 
/* PROC fitness (double p1, double p2)                  DEV (double)
 * MODIFICA nada
 * EFECTO recibe dos valores que representan los puntos que caracterizan a un individuo
 *  la funcion sirve para calcular la aptitud o fitness de cierto individuo segun sus
 *  puntos. este valor de aptitud es el que devuelve la funcion. */
 
int fitness (Individuo ind)
{
    int fit = 0;
    for(int i = 0; i < 16; i++){
        if(ind.genotipo[i] != i+1 && ind.genotipo[i] != 0){
            for(int j = 0; j < 16; i++){
                if(ind.genotipo[i] == j + 1){
                    break;
                } else{
                    fit++;
                }
            }
        }
    }
    return fit;
}
  
/* PROC generarPoblacion (void)                         DEV (Individuo *)
 * MODIFICA nada
 * EFECTO esta funcion genera una poblacion con la cantidad de individuos dada por la
 *  macro POBLACION. para generar cada individuo utiliza la funcion generarIndividuo()
 *  y una vez ha terminado el bucle, devuelve el puntero al primer individuo    */
 
Individuo * generarPoblacion(Individuo * Inicial)
{
    Individuo * poblacion;
    Individuo ind1, ind2, ind3, ind4;
    int i;
 
    poblacion = (Individuo *) malloc(sizeof(Individuo)*POBLACION);
    for(i=0;i<LONG_COD;i++)
        if(Inicial->genotipo[i] == 0){
            break;
        }
        
    if(i == 3 || i == 7 || i == 11 || i == 15){
        if(i + 5 < 16){
            for(int j=0; j<17; j++){
                ind1.genotipo[j] = Inicial->genotipo[j];
            }
            ind1.genotipo[i] = ind1.genotipo[i+4];
            ind1.genotipo[i+4] = 0;
            ind1.aptitud = fitness(ind1);
            poblacion[1] = ind1;
        }
        if(i - 5 > 0){
            for(int j=0; j<17; j++){
                ind2.genotipo[j] = Inicial->genotipo[j];
            }
            ind2.genotipo[i] = ind2.genotipo[i-4];
            ind2.genotipo[i-4] = 0;
            ind2.aptitud = fitness(ind2);
            poblacion[2] = ind2;
        }
        for(int j=0; j<17; j++){
            ind3.genotipo[j] = Inicial->genotipo[j];
        }
        ind3.genotipo[i] = ind3.genotipo[i-1];
        ind3.genotipo[i-1] = 0;
        ind3.aptitud = fitness(ind3);
        poblacion[0] = ind3;
    }
    else if(i == 0 || i == 4 || i == 8 || i == 12){
        if(i + 5 < 16){
            for(int j=0; j<17; j++){
                ind1.genotipo[j] = Inicial->genotipo[j];
            }
            ind1.genotipo[i] = ind1.genotipo[i+4];
            ind1.genotipo[i+4] = 0;
            ind1.aptitud = fitness(ind1);
            poblacion[1] = ind1;
        }
        if(i - 5 > 0){
            for(int j=0; j<17; j++){
                ind2.genotipo[j] = Inicial->genotipo[j];
            }
            ind2.genotipo[i] = ind2.genotipo[i+4];
            ind2.genotipo[i-4] = 0;
            ind2.aptitud = fitness(ind2);
            poblacion[2] = ind2;
        }
        for(int j=0; j<17; j++){
            ind3.genotipo[j] = Inicial->genotipo[j];
        }
        ind3.genotipo[i] = ind3.genotipo[i+1];
        ind3.genotipo[i+1] = 0;
        ind3.aptitud = fitness(ind3);
        poblacion[0] = ind3;
    }
    else{
        for(int j=0; j<17; j++){
            ind1.genotipo[j] = Inicial->genotipo[j];
        }
        ind1.genotipo[i] = ind1.genotipo[i+4];
        ind1.genotipo[i+4] = 0;
        ind1.aptitud = fitness(ind1);
        poblacion[2] = ind1;

        for(int j=0; j<17; j++){
            ind2.genotipo[j] = Inicial->genotipo[j];
        }
        ind2.genotipo[i] = ind2.genotipo[i+4];
        ind2.genotipo[i-4] = 0;
        ind2.aptitud = fitness(ind2);
        poblacion[3] = ind2;

        for(int j=0; j<17; j++){
            ind3.genotipo[j] = Inicial->genotipo[j];
        }
        ind3.genotipo[i] = ind3.genotipo[i+1];
        ind3.genotipo[i+1] = 0;
        ind3.aptitud = fitness(ind3);
        poblacion[0] = ind3;

        for(int j=0; j<17; j++){
            ind4.genotipo[j] = Inicial->genotipo[j];
        }
        ind4.genotipo[i] = ind4.genotipo[i-1];
        ind4.genotipo[i-1] = 0;
        ind4.aptitud = fitness(ind4);
        poblacion[1] = ind4;
    }
    return poblacion;
}
 
/* PROC seleccionTorneos (Individuo *)                  DEV (Individuo *)
 * MODIFICA nada
 * EFECTO se crea un nuevo vector de individuos que contendra a los individuos seleccionados
 *  para el cruce. la seleccion se hace por torneos por tanto cada individuo seleccionado
 *  sera el que tenga mejor aptitud de dos candidatos. el proceso se repite en POBLACION-1
 *  iteraciones, que es la cantidad de individuos que se deben seleccionar. la reserva de
 *  memoria se hace sobre POBLACION individuos dado que, como luego vamos a seleccionar el
 *  mejor de la poblacion anterior por elitismo, debemos dejar una plaza de la siguiente
 *  generacion libre. la seleccion es con repeticion */
 
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
 
/* PROC mutacionHijos (Individuo *)                         DEV (void)
 * MODIFICA (Individuo *)
 * EFECTO esta funcion aplica la mutacion segun la probabilidad dada por PROB_MUTACION.
 *  recibe un vector de individuos en el que debe ocurrir que los dos primeros sean
 *  los hijos correspondientes a un cruce. el genotipo de cada uno de los individuos
 *  se recorre por completo calculando la probabilidad de que el bit mute y cambiando
 *  si se diera el caso positivo    */
 
void mutacionHijos (Individuo * hijos)
{
    int i, j;
 
    for(i=0; i<2; i++)
        for(j=0; j<LONG_COD; j++)
            if ((double) rand()/(RAND_MAX+1.0) < PROB_MUTACION)
            {
                if(hijos[i].genotipo[j])
                    hijos[i].genotipo[j] = 0;
                else hijos[i].genotipo[j] = 1;
            }
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
            seleccion[2] = aux;
    }
}
 
/* PROC elite (Individuo * poblacion)                   DEV (Individuo)
 * MODIFICA nada
 * EFECTO se trata de una funcion que devuelve el mejor individuo de una poblacion
 *  que se pasa como argumento. utiliza un individuo como comparador y devuelve
 *  el que para nuestro caso tiene el mejor fitness, es decir, aptitud mas baja */
 
Individuo elite (Individuo * poblacion)
{
    int i;
    Individuo best = poblacion[0];
 
    for(i=0; i<POBLACION; i++)
        if(best.aptitud > poblacion[i].aptitud && poblacion[i].aptitud != 0)
            best = poblacion[i];
 
    return best;
}

/* PROC generarInicial (void)                   DEV (Individuo)
 * MODIFICA nada
 * EFECTO Se trata de una funcion que genera el caso especifico
 * en este caso genera el individuo de inicio */

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

/* PROC AG(void)                                                DEV (void)
 * MODIFICA nada
 * EFECTO se trata de la funcion que ejecuta el algoritmo. el proceso es el siguiente
 *  1 - Generar la poblacion
 *  2 - Seleccion de candidatos al cruce
 *  3 - Cruce de los candidatos (incluye mutacion)
 *  4 - Incluir al mejor de la generacion anterior en la nueva
 *  5 - Repetir el proceso  */
 
void AG (void)
{
    Individuo * inicial = generarInicial();
    Individuo best;
    Individuo * seleccion, * poblacion = generarPoblacion(inicial);

    /*Individuo * correcto;
    for(int i=1; i<17; i++){
        correcto->genotipo[i-1] = i;
    }
    for(int i=0;i<16;i++){
		std::cout << correcto->genotipo[i] << " ";
    }*/

    imprimePoblacion(poblacion);
    int generacion = 0;
 
    do
    {
        seleccion = seleccionTorneos(poblacion);
        cruzarSeleccion(seleccion);
        best = elite(seleccion);
        std::cout << std::endl;
        std::cout << std::endl;
        imprimeGenotipo(best);
        free(poblacion);
        std::cout << std::endl;
        poblacion = generarPoblacion(&best);
        std::cout << std::endl;
        imprimePoblacion(poblacion);
        generacion++;
    } while (generacion < 1);
    build_simple_doc();
    free(poblacion);
    std::cout << std::endl;
    printf ("*************************************\n");
    printf ("*          FIN DEL ALGORITMO        *\n");
    printf ("*************************************\n");
    printf (" - Es la generacion numero %i\n", generacion);
    printf ("*************************************\n");
}
 
/* PROC imprimePoblacion (Individuo * pob)                      DEV (void)
 * MODIFICA nada
 * EFECTO   es una funcion auxiliar que imprime por pantalla toda la informacion
 *  relativa a una poblacion que se debe pasar como argumento. recorre con un
 *  bucle for todos los individuos para imprimirlos uno a uno y se ayuda de la
 *  funcion decoder para sacar la aptitud   */
 
void imprimePoblacion (Individuo * pob)
{ 
    for(int i = 0; i < POBLACION; i++)
    {
        std::cout << std::endl;
        imprimeGenotipo(pob[i]);
    }
}
 
/* PROC imprimeGenotipo (Individuo x)                           DEV (void)
 * MODIFICA nada
 * EFECTO esta funcion se encarga de imprimir por pantalla el genotipo asociado a
 *  un individuo que se pasa como argumento. recorre el genotipo por medio de
 *  un bucle for y no necesita funciones auxiliares */
 
void imprimeGenotipo (Individuo x)
{
    int i;
 
    for(i=0; i<LONG_COD; i++)
        std::cout << x.genotipo[i] << " ";

}
 
void build_simple_doc()
{
	// Make xml: <?xml ..><Hello>World</Hello>
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	TiXmlElement * element = new TiXmlElement( "Hello" );
	TiXmlText * text = new TiXmlText( "World" );
	element->LinkEndChild( text );
	doc.LinkEndChild( decl );
	doc.LinkEndChild( element );
	doc.SaveFile( "madeByHand.xml" );
}