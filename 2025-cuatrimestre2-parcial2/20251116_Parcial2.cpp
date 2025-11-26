#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/*
Un laboratorio de automatización nos contrata para desarrollar un módulo del
sistema que procesa lecturas tomadas por un conjunto de sensores durante una
prueba de campo.

Mediante la función

Medicion obtenerProximaMedicion();

La función devuelve mediciones válidas hasta que el campo cod_sensor viene en -1.

La información que trae el Medicion es la siguiente:

int cod_sensor;   // código del sensor (1 a MAX_SENSORES)
int muestra;      // número de muestra (1 a MAX_MUESTRAS)
int valor;        // valor medido en grados Celsius (entero)

También existe otra función que nos completa la información sobre los sensores
usados para la medición.

void completarInformacionSensores(Sensor sensores[MAX_SENSORES]);

struct Sensor {
    int cod_sensor;
    char modelo[MAX_MODELO]; //nombre modelo
    char lugar[MAX_LUGAR]; // descripción del lugar donde está instalado
    bool esta_activo;
};

En base a esto se necesita:
1. Mostrar el lugar que registró la mayor temperatura promedio.
2. Mostrar por pantalla código de sensor, modelo, número de muestra y valor
cada vez que se obtiene una lectura menor a -10 grados Celsius o mayor a 60
grados Celsius, en el caso que la medición haya sido hecha por un sensor que está
activo.
3. Calcular las temperaturas mínimas censadas por cada sensor.
*/

// definición constantes
const int MAX_MODELO = 5;
const int MAX_LUGAR = 8;
const int MAX_SENSORES = 10;
const int MAX_MUESTRAS = 6;
const int MAX_TEMP = 60;
const int MIN_TEMP = -10;

struct Medicion
{
    int cod_sensor; // código del sensor (1 a MAX_SENSORES)
    int muestra;    // número de muestra (1 a MAX_MUESTRAS)
    int valor;      // valor medido en grados Celsius (entero)
};

Medicion vecMed[20] = {
    {1010, 5, 10},
    {2020, 5, 200},
    {3030, 5, 22},
    {4040, 5, 110},
    {1010, 4, 15},
    {1011, 3, 14},
    {2021, 2, 27},
    {3031, 2, 4},
    {4041, 2, -5},
    {1012, 2, -12},
    {1010, 3, 19},
    {2020, 3, 100},
    {3030, 3, 8},
    {4040, 3, -4},
    {1010, 4, -9},
    {1012, 4, 15},
    {2022, 4, 26},
    {3031, 4, 2},
    {4041, 4, -6},
    {-1, -1, -1},
};

struct Sensor
{
    int cod_sensor;
    char modelo[MAX_MODELO]; // nombre modelo
    char lugar[MAX_LUGAR];   // descripción del lugar donde está instalado
    bool esta_activo;
};

// set de datos necesario para una implementación de completarInformacionSensores.
// ATENCION, ustedes no tenían que codear la función
Sensor datosSensores[MAX_SENSORES] = {
    {1010, "mod1", "lugar1", true},
    {1011, "mod1", "lugar2", true},
    {1012, "mod1", "lugar3", true},
    {2020, "mod2", "lugar4", true},
    {2021, "mod2", "lugar5", true},
    {2022, "mod2", "lugar6", false},
    {3030, "mod3", "lugar7", true},
    {3031, "mod3", "lugar8", true},
    {4040, "mod4", "lugar9", false},
    {4041, "mod4", "lugar10", true},
};

void completarInformacionSensores(Sensor sensores[MAX_SENSORES])
{
    for (int i = 0; i < MAX_SENSORES; i++)
    {
        sensores[i] = datosSensores[i];
    }
}

// variable necesaria para una implementación de obtenerProximaMedicion
// ATENCIÓN, ustedes no tenían que codear esta función.
int intPosMed = 0;

Medicion obtenerProximaMedicion()
{
    return vecMed[intPosMed++];
}

// en vez de la variable "encontrado" como hicimos en clase, usamos la "pos" de retorno para avisar que lo encontramos.
// en el caso que no encuentre el sensor, devuelve -1, aunque se aclaró que SIEMPRE lo iba a encontrar.
int buscarPosSensor(int cod_sensor, Sensor sensores[])
{
    int pos = -1;
    for (int i = 0; i < MAX_SENSORES && pos == -1; i++)
    {
        if (cod_sensor == sensores[i].cod_sensor)
        {
            pos = i;
        }
    }
    return pos;
}

void mostrarMed(Medicion med, Sensor sensores[])
{
    // buscamos la posición del sensor mediante su código para poder acceder al arreglo y leer la información.
    int posSensor = buscarPosSensor(med.cod_sensor, sensores);

    // una vez que tenemos el sensor, podemos preguntar si está activo, si está activo, seguimos chequeando-
    if (sensores[posSensor].esta_activo == true)
    {
        // y acá preguntamos si está fuera del rango
        if (med.valor > MAX_TEMP || med.valor < MIN_TEMP)
        {
            cout << "MEDICION QUE SUPERA UNO DE LOS TOPES: " << endl;
            cout << "Codigo de sensor: " << med.cod_sensor << endl;
            cout << "Modelo de sensor: " << sensores[posSensor].modelo << endl;
            cout << "Nro de muestra: " << med.muestra << endl;
            cout << "Valor de muestra: " << med.valor << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}

// función que usamos mientras procesamos mediciones para agregar información a la matriz
void procesarInfoMatriz(Medicion med, Sensor sensores[], int matMS[][MAX_SENSORES])
{
    // necesitamos traducir el valor del código del sensor, dado que no tenemos información
    // sobre el universo de códigos de sensor, por eso usamos la posición en el arreglo de sensores como dimensión
    int columna = buscarPosSensor(med.cod_sensor, sensores);
    int fila = med.muestra;
    matMS[fila][columna] = med.valor;
}

void mostrarLugarMayorTemp(int matMS[MAX_MUESTRAS][MAX_SENSORES], Sensor sensores[])
{
    int posMax = -1;
    float promMax = -1000000;
    for (int col = 0; col < MAX_SENSORES; col++)
    {
        float sumaSensor = 0;
        float prom = 0;
        // recorremos todas las filas de un sensor, o sea, sumamos las muestras de un sensor.
        for (int fila = 0; fila < MAX_MUESTRAS; fila++)
        {
            sumaSensor += matMS[fila][col];
        }
        // con esa suma, sacamos el promedio, y lo comparamos con el máximo, para ver si tenemos un nuevo campeón.
        // y notar que esto se hace después del ciclo "interno", dado que es el punto donde ya terminamos de procesar los datos de esa columna
        // una vez que lo procesamos, sigue el ciclo "externo", o sea, salta hacia el próximo sensor, reseteando la suma.
        prom = sumaSensor / MAX_MUESTRAS;
        if (prom > promMax)
        {
            promMax = prom;
            posMax = col;
        }
    }
    cout << "El lugar con el promedio de temperatura mas alto es: "
         << sensores[posMax].lugar << endl;
    cout << "----------------------------------------" << endl;
}

void mostrarTempMinimas(int matMS[][MAX_SENSORES], Sensor sensores[MAX_SENSORES])
{
    for (int col = 0; col < MAX_SENSORES; col++)
    {
        // inicializamos el mínimo con un valor fuera de rango positivo
        int min = 1000000;
        for (int fila = 0; fila < MAX_MUESTRAS; fila++)
        {
            // dentro de la misma columna, vamos buscando el mínimo valor de las muestras.
            if (matMS[fila][col] < min)
            {
                min = matMS[fila][col];
            }
        }

        // antes de pasar al siguiente sensor, o sea, a la próxima columna, imprimimos el valor mínimo que encontramos para esa columna
        cout << "El censor " << sensores[col].cod_sensor << " tiene la temperatura minima: " << min << endl;
    }
}

/**
 *
 * Vamos a trabajar con dos estructuras, el arreglo de sensores y una matriz que vamos a generar nosotros que contendrá de una manera estructurada los valores enteros de cada muestra de cada sensor.
 *
 * - el arreglo de sensores debemos instanciarlo vacío y usar la función "completarInformacionSensores" para que nos devuelva el set de sensores con el que se trabaj
 * - la matriz que generaremos tendrá las dimensiones:
 * -- muestras en las filas
 * -- sensores en las columnas
 *
 * o sea, será una matriz de dimensiones MAX_MUESTRAS X MAX_SENSORES que guarda valores de tipo int.
 *
 * Y por qué necesitamos esta estructura?
 *
 * Para responder la pregunta 1 y 3.
 *
 * La 1 nos pide el lugar donde sea la temperatura promedio máxima.
 * Para eso debemos sumar todos los valores de cada muestra, o sea, todos los valores de la columna y dividirlos por la cantidad de elementos (obviando el tema de la inicialización en el valor 0, dejemos eso de lado).
 * Al hacer eso, tenemos un promedio de esa columna y comparandoló con los otros promedios de las otras columnas, nos quedaremos con el número máximo.
 *
 *
 * Por otro lado, el punto 3, nos pide la temperatura mínima de cada sensor, por lo que deberemos recorrer cada columna, buscar el mínimo entre los valores de dicha columna y mostrarlo por pantalla antes de procesar la próxima columna, o sea, el próximo sensor.
 *
 * Ahora, cómo unimos lo que tenemos (Medicion y Sensor) con esa matriz?
 *
 * Primero, debemos procesar esas mediciones con la función
 *
 * obtenerProximaMedicion, que nos devuelve una variable Medicion.
 *
 * eso nos trae tres datos:
 *
 * - el valor del sensor
 * - muestra (que va entre 0 y MAX_MUESTRAS)
 * - cod_sensor (que no sabemos cómo se comporta)
 *
 * Con estos datos, podemos armar la matriz que necesitamos, teniendo:
 *
 * - el valor de la matriz: lo sacamos de Medicion.valor
 * - la coordenada fila: es el número de muestra directamente Medicion.muestra
 * - la coordenada columna, que son los sensores, debemos buscar algo que nos limite el valor, dado que el código de sensor, no nos sirve así como viene
 *   entonces, una posibilidad es usar la posición del sensor en el arreglo de Sensores, dado que va entre 0 y MAX_SENSORES.
 *   de acá, se desprende que necesitamos una función a la cual el pasamos el código del sensor y devolver la posición de donde se encuentra,
 *   esto nos sirve para ingresar datos en la matriz, como también para acceder al Sensor y poder leer su información, como el modelo, el lugar y si está activo.
 *
 *
 *
 */
int main()
{

    Sensor sensores[MAX_SENSORES];
    completarInformacionSensores(sensores);
    int matMS[MAX_MUESTRAS][MAX_SENSORES] = {0};

    Medicion med = obtenerProximaMedicion();

    while (med.cod_sensor != -1)
    {
        mostrarMed(med, sensores);
        procesarInfoMatriz(med, sensores, matMS);
        med = obtenerProximaMedicion();
    }

    mostrarLugarMayorTemp(matMS, sensores);
    mostrarTempMinimas(matMS, sensores);

    return EXIT_SUCCESS;
}