/*

La cadena de restaurantes "Delicias al Plato" busca desarrollar un programa para analizar la
producción de sus platillos en las distintas sucursales, como parte del control operativo
diario.

Se deben ingresar los siguientes datos por teclado:

● sucursal responsable de la producción: string (verificar que exista en la lista de
sucursales).
● código del platillo producido: int (de 0 a 9).
● cantidad de unidades producidas: int (mayor a 0).
Se dispone de un arreglo en memoria con información de los platillos disponibles (10), que
incluye:
● nombre del platillo: string
● código del platillo: int (de 0 a 9)
● categoría del platillo: string
También contamos con información de las sucursales del restaurante (6):
● nombre de la sucursal: string
● cantidad de empleados en la sucursal: int
Ambos vectores accesibles globalmente y correctamente definidos de la siguiente forma:
tyPlatillo PLATILLOS[CANT_PLATILLOS] = {...}
tySucursal SUCURSALES[CANT_SUCURSAL] = {...}

Excepto el contenido de los vectores, definir tipos y constantes necesarias. Se deben validar
los rangos de los datos ingresados por teclado y que la sucursal exista en el vector
SUCURSALES.

Luego. el programa debe procesar los ingresos y resolver los siguientes puntos:
    1. Generar un listado de producción, indicando el nombre del platillo, la sucursal
    responsable y la cantidad producida.
    2. Identificar el platillo con mayor cantidad producida durante el registro.
    3. Determinar la sucursal con la menor cantidad de unidades producidas al
    finalizar el registro.

*/

#include <iostream>
#include <cstring>
using namespace std;


// Definiciones de tipos y constantes
const int MAX_NOMBRE = 100;

struct TyPlatillo {
    char nombre[MAX_NOMBRE];
    int codigo;
    char categoria[MAX_NOMBRE];
};

struct TySucursal
{
    char nombre[MAX_NOMBRE];
    int cantidadEmpleados;
};

const TyPlatillo PLATILLOS[10] = {
    {"Ensalada Cesar", 0, "Entrada"},
    {"Sopa de Tomate", 1, "Entrada"},
    {"Pasta Alfredo", 2, "Plato Fuerte"},
    {"Pollo a la Parrilla", 3, "Plato Fuerte"},
    {"Tiramisu", 4, "Postre"},
    {"Cheesecake", 5, "Postre"},
    {"Pizza Margherita", 6, "Plato Fuerte"},
    {"Hamburguesa Clasica", 7, "Plato Fuerte"},
    {"Ceviche", 8, "Entrada"},
    {"Brownie con Helado", 9, "Postre"}
};

const TySucursal SUCURSALES[6] = {
    {"Sucursal Centro", 15},
    {"Sucursal Norte", 10},
    {"Sucursal Sur", 12},
    {"Sucursal Este", 8},
    {"Sucursal Oeste", 20},
    {"Sucursal Playa", 5}
};

// Estructura creada por nosotros

struct TyProduccion {
    char nombreSucursal[MAX_NOMBRE];
    int codigoPlatillo;
    int cantidadProducida;
};

//funcion para buscar si una sucursal existe
bool existeSucursal(const char nombreSucursal[MAX_NOMBRE]) {
    bool sucursalValida = false;
    for (int i = 0; i < 6; i++) {
        if (strcmp(nombreSucursal, SUCURSALES[i].nombre) == 0) {
            sucursalValida = true;
        }
    }
    return sucursalValida;
}

// Verificar si el codigo del platillo es valido
bool esCodigoValido(int codigo) {
    bool esValido = false;
    if(codigo >= 0 && codigo <= 9){
        for(int i = 0; i < 10; i++) {
            if(codigo == PLATILLOS[i].codigo) {
                esValido = true;
            }
        }
    } 
    return esValido;
}

//funcion para evluar si los datos ingresados son validos
bool sonDatosValidos(const TyProduccion& produccion) {
    bool datosValidos = true;
    // Verificar si la sucursal existe
    if(existeSucursal(produccion.nombreSucursal) == false) {
        cout << "Sucursal no existe. Intente nuevamente." << endl;
        datosValidos = false;
    }

    // Verificar si el codigo del platillo es valido
    if(esCodigoValido(produccion.codigoPlatillo) == false) {
        cout << "Codigo de platillo invalido. Intente nuevamente." << endl;
        datosValidos = false;
    }

    // Verificar si la cantidad producida es mayor a 0 o -1 para salir
    if(produccion.cantidadProducida <= 0 && produccion.cantidadProducida != -1) {
        cout << "Cantidad producida debe ser mayor a 0 o -1 para finalizar. Intente nuevamente." << endl;
        datosValidos = false;
    }

    return datosValidos;
}

// Ingreso datos de UNA SOLA producción hasta que estos sean validos.
// una vez terminado el ingreso evaluo si son validos.
// en caso de no ser validos vuelvo a pedir los datos.
TyProduccion ingresoDeDatos() {
    TyProduccion produccion;
    bool datosValidos = false;

    do{
        cout << "Ingrese nombre de la sucursal: ";
        cin.getline(produccion.nombreSucursal, MAX_NOMBRE);      
        cout << "Ingrese codigo del platillo (0-9): ";
        cin >> produccion.cantidadProducida;
        cout << "Ingrese cantidad de unidades producidas (mayor a 0): ";
        cin >> produccion.cantidadProducida;
    } while (sonDatosValidos(produccion) == false);

    return produccion;
}

// obtener nombre de sucursal
void obtenerNombreSucursal(int codigoSucursal, char nombreSucursal[MAX_NOMBRE]) {
    bool encontrado = false;
    for(int i = 0; i < 6 && encontrado == false; i++) {
        if(codigoSucursal == i) {
            strcpy(nombreSucursal, SUCURSALES[i].nombre);
        }
    }  
}

void buscarNombrePlatillo(int codigoPlatillo, char nombrePlatillo[MAX_NOMBRE]) {
    bool encontrado = false;
    for(int i = 0; i < 10 && encontrado == false; i++) {
        if(codigoPlatillo == PLATILLOS[i].codigo) {
            strcpy(nombrePlatillo, PLATILLOS[i].nombre);
        }
    }  
}

//     1. Generar un listado de producción, indicando el nombre del platillo, la sucursal responsable y la cantidad producida.
void mostrarProduccion(TyProduccion produccion) {
    // Buscar el nombre del platillo
    char nombrePlatillo[MAX_NOMBRE];
    for(int i = 0; i < 10; i++) {
        if(produccion.codigoPlatillo == PLATILLOS[i].codigo) {
            strcpy(nombrePlatillo, PLATILLOS[i].nombre);
        }
    }

    cout << "Sucursal: " << produccion.nombreSucursal << ", Platillo: " << nombrePlatillo << ", Cantidad Producida: " << produccion.cantidadProducida << endl;
}

void actualizarCantidadPorSucursal(int cantidadPorSucursal[], const TyProduccion& produccion) {
    for(int i = 0; i < 6; i++) {
        if(strcmp(produccion.nombreSucursal, SUCURSALES[i].nombre) == 0) {
            cantidadPorSucursal[i] += produccion.cantidadProducida;
        }
    }
}

void mostrarSucursalMenorCantidad(int cantidadPorSucursal[]) {
    int menorCantidad = cantidadPorSucursal[0];
    char nombreSucursalMenorCantidad[MAX_NOMBRE];
    strcpy(nombreSucursalMenorCantidad, SUCURSALES[0].nombre);

    for(int i = 1; i < 6; i++) {
        if(cantidadPorSucursal[i] < menorCantidad) {
            menorCantidad = cantidadPorSucursal[i];
            strcpy(nombreSucursalMenorCantidad, SUCURSALES[i].nombre);
        }
    }

    cout << "Sucursal con menor cantidad producida: " << nombreSucursalMenorCantidad << " con " << menorCantidad << " unidades." << endl;
}


int main() {
    TyProduccion produccion;
    int mayorCantidad = 0;
    char platilloMayorCantidad[MAX_NOMBRE] = "";

    int cantidadPorSucursal[6] = {0}; // arreglo para almacenar la cantidad producida por cada sucursal
    char nombreSucursalMenorCantidad[MAX_NOMBRE];

    // Ingreso de datos
    do{
        produccion = ingresoDeDatos();

        if(produccion.cantidadProducida != -1) {
            //1. Generar un listado de producción, indicando el nombre del platillo, la sucursal responsable y la cantidad producida.
            mostrarProduccion(produccion);

            //2. Identificar el platillo con mayor cantidad producida durante el registro.
            if(produccion.cantidadProducida > mayorCantidad) {
                mayorCantidad = produccion.cantidadProducida;
                // Buscar el nombre del platillo
                buscarNombrePlatillo(produccion.codigoPlatillo, platilloMayorCantidad);
            }

            //3. Determinar la sucursal con la menor cantidad de unidades producidas al finalizar el registro.
            actualizarCantidadPorSucursal(cantidadPorSucursal, produccion);
        }

    }while (produccion.cantidadProducida != -1); // condicion de salida

    //muestro el platillo con mayor cantidad producida durante el registro.
    cout << "Platillo con mayor cantidad producida: " << platilloMayorCantidad << " con " << mayorCantidad << " unidades." << endl;

    // muestro la sucursal con la menor cantidad de unidades producidas al finalizar el registro.
    mostrarSucursalMenorCantidad(cantidadPorSucursal);

    return 0;
}