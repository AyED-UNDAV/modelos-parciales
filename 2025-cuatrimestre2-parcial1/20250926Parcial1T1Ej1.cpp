#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

/*
Ejercicio 1

Nuestra agencia de turismo comenzó a vender pasajes a distintos destinos del interior del país.
Por cada venta se informan los siguientes datos:
●	Tipo de destino: char ('M' para montaña, 'P' para playa).
●	Nombre del destino: cadena de caracteres (máximo 30 caracteres).
●	Precio del pasaje: float (mayor que cero).
●	Cantidad de pasajes vendidos: int (mayor que cero).
Los datos NO deben ser validados, se supone que son correctos.
Se pide mostrar:
a) Por cada venta ingresada:
●	Nombre del destino
●	Cantidad de pasajes vendidos
●	Importe total de la venta
b) Al finalizar el ingreso de datos:
●	Cantidad total de pasajes vendidos a destinos de montaña y playa
●	Precio promedio de los pasajes vendidos a destinos de montaña
●	Nombre del destino y tipo que corresponden a la venta de menor importe
*/
const int MAX_NOMBRE = 30;

void datosAIngresar(char &desTipo, char desNombre[], float &precio, int &cantPasajesVend){

    cout << "Ingrese tipo de destino (m: montaña / p: playa): ";
    cin >> desTipo;
    
    cout << "Ingrese nombre destino: ";
    cin >> desNombre;
    
    cout << "Ingrese precio: ";
    cin >> precio;
    
    cout << "Ingrese cantidad de pasajes: ";
    cin >> cantPasajesVend;
}

void imprimirVenta(char desNombre[], int cantPasajesVend, float precio){
    cout << "****************** Venta realizada ******************" << endl;
    cout << "Nombre del destino: " << desNombre << endl;
    cout << "Cantidad de pasajes: " << cantPasajesVend << endl;
    cout << "Importe total de la venta: " << cantPasajesVend*precio << endl << endl;
}

void procesarDatos(char desTipo, int &totalVendMon, int cantPasajesVend,
                    float &totalPrecioVendMon, float precio,
                    int &totalVendPla, float &minVenta, char minNomDes[], 
                    char desNombre[], char &mintipoDes

){
    switch (desTipo)
    {
    case 'm':
        totalVendMon += cantPasajesVend;
        totalPrecioVendMon += precio;
        break;

    case 'p':
        totalVendPla += cantPasajesVend;
        break;
    }

    if (minVenta > precio*cantPasajesVend)
    {
        minVenta = precio*cantPasajesVend;
        strcpy(minNomDes, desNombre);
        mintipoDes = desTipo; 
    }
}

void imprimirDatosProcesados(int totalVendMon, int totalVendPla, float totalPrecioVendMon,
                            char minNomDes[], char mintipoDes
){
    cout << "****************** Datos Procesados ******************" << endl;

    cout << "Cantidad total de pasajes vendidos a destinos de montaña: " 
    << totalVendMon << endl;
    cout << "Cantidad total de pasajes vendidos a destinos de playa: " 
    << totalVendPla << endl;

    cout << "Precio promedio de los pasajes vendidos a destinos de montaña: " 
    << totalPrecioVendMon/totalVendMon << endl;

    cout << "La venta de menor importe es al destino: " << minNomDes << " y es de tipo: " 
    << mintipoDes << endl;
}

int main(){
    char desTipo = ' ', ingresaValores = ' ', mintipoDes = ' ';
    char desNombre[MAX_NOMBRE] = " ", minNomDes[MAX_NOMBRE] = " " ;
    float precio = 0;
    int cantPasajesVend = 0;
    int totalVendMon = 0;
    int totalVendPla = 0;
    float totalPrecioVendMon = 0;
    float minVenta = 9999999.99;

    cout << "Desea ingresar valores? (s / n): ";
    cin >> ingresaValores;
    
    while (ingresaValores == 's')
    {
        datosAIngresar(desTipo, desNombre, precio, cantPasajesVend);

        imprimirVenta(desNombre, cantPasajesVend, precio);

        procesarDatos(desTipo, totalVendMon, cantPasajesVend, totalPrecioVendMon, 
                    precio, totalVendPla, minVenta, minNomDes, desNombre, mintipoDes);

        cout << "Desea ingresar valores? (s / n): ";
        cin >> ingresaValores;
    }
    
    imprimirDatosProcesados(totalVendMon, totalVendPla, totalPrecioVendMon,
                            minNomDes, mintipoDes);

    return EXIT_SUCCESS;
}