#include <iostream>
#include <cstring> // Necesario para strlen, strcat y strcmp
using namespace std;

/*
Modelo resulto del primer parcial de Programación I - 2024, Ejercicio 1

Consigna:

Una estación meteorológica quiere procesar mediciones de temperaturas realizadas a lo
largo del día. Cada medición viene dada por los siguientes datos:

● Nombre de estación representada por nombre de provincia y número (ej. Mendoza1, Córdoba2, etc.): char[]
● Franja del día (‘M’ mañana, ‘T’ tarde, ‘N’ Noche, ‘G’ Madrugada) char
● Temperatura registrada (en grados Celsius): float

Se procesarán mediciones hasta que el nombre de la estación sea “fin”. Todos los datos
ingresados por el usuario son correctos en su tipo (si pide números, ingresa números, por
ejemplo).

Procesar las mediciones para informar:
    a) Temperatura máxima del día y en qué franja se registró.
    b) Promedio de temperatura de la mañana.

*/



/*
    Es muy importante pasar los parametros por referencia (&). Si no, los cambios que se hagan en la función
    no se verán reflejados en la función main.
*/ 

void ingresarDatos(char nombreEstacion[],  char &franjaDia, float &temperatura) {
    cout << "Ingrese el nombre de la estación (o 'fin' para terminar): ";
    cin >> nombreEstacion;

    // Otra alternativa es
    /*
        cin.clear(); // Limpia el estado de error si lo hubiera
        cin.getline(nombreEstacion, MAX_NOMBRE);
    */
    // cuando se use  cin.getline(nombreEstacion, MAX_NOMBRE) en un ciclo es necesario limpiar el buffer
    // con cin.ignore() antes de la siguiente lectura de datos. Sino, al ingresar la temperatura seguida de un
    // "enter" el getline tomará ese enter como el final de la cadena y no permitirá ingresar datos

    // NO SE PUEDE COMPARAR if (nombreEstacion != "fin") !!
    if (strcmp(nombreEstacion, "fin") != 0) {
        cout << "Ingrese la franja del día ('M' mañana, 'T' tarde, 'N' noche, 'G' madrugada): ";
        cin >> franjaDia;

        cout << "Ingrese la temperatura registrada (en grados Celsius): ";
        cin >> temperatura;
    }
}

/*
    Función para registrar la temperatura máxima y la franja en la que se registró.
    Se pasa por referencia tempMaxima y franjaTempMaxima para actualizar sus valores si es necesario.
*/
void registrarTemperaturaMaxima(float temperatura, char franjaDia, float &tempMaxima, char &franjaTempMaxima) {
    if (temperatura > tempMaxima) {
        tempMaxima = temperatura;
        franjaTempMaxima = franjaDia;
    }
}

void contabilizarTemperaturaManana(float temperatura, char franjaDia, float &sumaTempManana, int &contadorManana) {
    if (franjaDia == 'M') {
        sumaTempManana += temperatura;
        contadorManana++;
    }
}

void mostarResultados(float tempMaxima, char franjaTempMaxima, float sumaTempManana, int contadorManana) {
    cout << "Temperatura máxima del día: " << tempMaxima << " en la franja: " << franjaTempMaxima << endl;

    if (contadorManana > 0) {
        float promedioManana = sumaTempManana / contadorManana;
        cout << "Promedio de temperatura de la mañana: " << promedioManana << endl;
    } else {
        cout << "No se registraron temperaturas en la mañana." << endl;
    }
}

int main() {

    //// constantes para evitar usar valores "mágicos"
    const int MAX_NOMBRE = 20;

    //// variables a ingresar por el usuario

    //Nombre de estación representada por nombre de provincia y número.
    char nombreEstacion[MAX_NOMBRE];
    //Franja del día (‘M’ mañana, ‘T’ tarde, ‘N’ Noche, ‘G’ Madrugada).
    char franjaDia;
    //Temperatura registrada (en grados Celsius).
    float temperatura;

    //// variables para el procesamiento

    //a) Temperatura máxima del día y en qué franja se registró.
    float tempMaxima = -1000; // Inicializo con un valor muy bajo
    char franjaTempMaxima = 'X';

    //b) Promedio de temperatura de la mañana.
    float sumaTempManana = 0;
    int contadorManana = 0;


    // Ingreso de datos
    ingresarDatos(nombreEstacion, franjaDia, temperatura);

    // Repetir mientras el nombre de la estación no sea "fin"
    while (strcmp(nombreEstacion, "fin") != 0) {
        //Punto A: procesamiento de datos
        registrarTemperaturaMaxima(temperatura, franjaDia, tempMaxima, franjaTempMaxima);
        //Punto B: procesamiento de datos
        contabilizarTemperaturaManana(temperatura, franjaDia, sumaTempManana, contadorManana);

        ingresarDatos(nombreEstacion, franjaDia, temperatura);
    }

    // Mostrar resultados
    mostarResultados(tempMaxima, franjaTempMaxima, sumaTempManana, contadorManana);
    

    return 0;
}
