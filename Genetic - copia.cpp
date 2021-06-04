#define POBLACION 5
#define LONG_COD 20
#define LIMITE -5.12
#define PROB_CRUCE 0.3
#define PROB_MUTACION 0.001
#define INTERVALO 10.24/pow(2,LONG_COD/2)
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct {
    int genotipo[LONG_COD];
    double aptitud;
} Individuo;
 
void decoder (double *, double *, int *);
double fitness (double, double);
int generarBinario (void);
Individuo generarIndividuo (void);
Individuo * generarPoblacion (void);
Individuo * seleccionTorneos(Individuo * pob);
void mutacionHijos (Individuo *);
void cruzarSeleccion (Individuo *);
Individuo elite(Individuo *);
void AG();
void imprimePoblacion (Individuo *);
void imprimeGenotipo(Individuo);
 
int main() {
    AG();
    return 0;
}
 
/* PROC decoder (double *x, double *y, int *genotipo)                       DEV (double)
 * MODIFICA (double *x double *y)
 * EFECTO recibe un vector de enteros compuesto de 0 y 1 que representa dos numeros
 *  codificados en binario. se encarga de convertir estos dos numeros binarios a su
 *  equivalente en decimal con ayuda de la macro PRECISION (incremento del valor entre
 *  cada binario) y la macro LIMITE que es el valor del limite inferior de la repre-
 *  sentacion que en el problema es -5.12   */
 
void decoder (double * x, double * y, int * genotipo)
{
    int i;
    *x = *y = 0.0;
 
    // calculo del primer decimal
    for(i=0; i<LONG_COD/2; i++)
        *x += genotipo[i] * pow(2, (LONG_COD/2)-(i+1));
    *x = (*x) * INTERVALO + LIMITE;
 
    //calculo del segundo decimal
    for(;i<LONG_COD;i++)
        *y += genotipo[i] * pow(2, LONG_COD-(i+1));
    *y = (*y) * INTERVALO + LIMITE;
}
 
/* PROC fitness (double p1, double p2)                  DEV (double)
 * MODIFICA nada
 * EFECTO recibe dos valores que representan los puntos que caracterizan a un individuo
 *  la funcion sirve para calcular la aptitud o fitness de cierto individuo segun sus
 *  puntos. este valor de aptitud es el que devuelve la funcion. */
 
double fitness (double p1, double p2)
{
    return pow(p1,2) + pow(p2,2);
}
 
/* PROC generarBinario (void)                               DEV (void)
 * MODIFICA nada
 * EFECTO se encarga de devolver un valor entero que siempre sera cero o uno. lo vamos a
 *  utilizar para generar los individuos al principio dado que su genoma es una cadena
 *  binaria que se genera aleatoriamente    */
 
int generarBinario (void) {
    if (1 + (int) (10.0*rand()/(RAND_MAX+1.0)) > 5)
        return 1;
    else
        return 0;
}
 
/* PROC generarIndividuo (void)                         DEV (Individuo)
 * MODIFICA nada
 * EFECTO se encarga de generar un individuo utilizando valores aleatorios. primero crea
 *  la cadena de bits del genotipo utilizando la funcion generaBinario y luego evalua
 *  la aptitud del individuo utilizando la funcion decoder para decodificar el genotipo
 *  y la funcion fitness para obtener la aptitud.   */
 
Individuo generarIndividuo (void){
    Individuo ind;
    int i;
    double x, y;
 
    for (i=0; i<LONG_COD; i++)
        ind.genotipo[i]=generarBinario();
 
    decoder(&x, &y, ind.genotipo);
    ind.aptitud = fitness(x,y);
 
    return ind;
}
 
/* PROC generarPoblacion (void)                         DEV (Individuo *)
 * MODIFICA nada
 * EFECTO esta funcion genera una poblacion con la cantidad de individuos dada por la
 *  macro POBLACION. para generar cada individuo utiliza la funcion generarIndividuo()
 *  y una vez ha terminado el bucle, devuelve el puntero al primer individuo    */
 
Individuo * generarPoblacion(void)
{
    Individuo * poblacion;
    int i;
 
    poblacion = (Individuo *) malloc(sizeof(Individuo)*POBLACION);
    for(i=0;i<POBLACION;i++)
        poblacion[i] = generarIndividuo();
 
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
        candidato_a = poblacion[(int) (((double) POBLACION)*rand()/(RAND_MAX+1.0))];
        candidato_b = poblacion[(int) (((double) POBLACION)*rand()/(RAND_MAX+1.0))];
 
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
    int i, j, punto, aux;
    double x, y;
 
    for(i=0; i<POBLACION-1; i+=2)
    {
        if((double) rand()/(RAND_MAX+1.0) < PROB_CRUCE)
        {
            punto = (int) (((double) LONG_COD)*rand()/(RAND_MAX+1.0));
 
            for(j=punto; j<LONG_COD; j++)
            {
                aux=seleccion[i].genotipo[j];
                seleccion[i].genotipo[j]=seleccion[i+1].genotipo[j];
                seleccion[i+1].genotipo[j]=aux;
            }
 
            mutacionHijos(&seleccion[i]);
 
            decoder(&x, &y, seleccion[i].genotipo);
            seleccion[i].aptitud = fitness(x,y);
 
            decoder(&x, &y, seleccion[i+1].genotipo);
            seleccion[i+1].aptitud = fitness(x,y);
        }
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
        if(best.aptitud > poblacion[i].aptitud)
            best = poblacion[i];
 
    return best;
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
    Individuo * seleccion, * poblacion = generarPoblacion();
    Individuo best;
    int generacion = 0;
    double x, y;
 
    do
    {
        seleccion = seleccionTorneos(poblacion);
        cruzarSeleccion(seleccion);
        seleccion[POBLACION-1] = elite(poblacion);
        free(poblacion);
        poblacion = seleccion;
        generacion++;
    } while (elite(poblacion).aptitud > pow(10,-2));
 
    best = elite(poblacion);
    free(poblacion);
    decoder(&x, &y, best.genotipo);
 
    printf ("*************************************\n");
    printf ("*          FIN DEL ALGORITMO        *\n");
    printf ("*************************************\n");
    printf (" - En el punto (%.5f, %.5f)\n", x, y);
    printf (" - Su fenotipo es %.5f\n", best.aptitud);
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
    int i;
    double x, y;
 
    for(i=0;i<POBLACION;i++)
    {
        decoder(&x, &y, pob[i].genotipo);
        printf ("INDIVIDUO NUMERO %i \t", i+1);
        printf ("(%f,", x);
        printf (" %f)", y);
        printf ("\tAptitud = %.20f\n", pob[i].aptitud);
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
        printf ("%i  ", x.genotipo[i]);
    printf ("\n");
}
 
