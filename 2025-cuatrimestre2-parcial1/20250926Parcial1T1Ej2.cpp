#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/*
Ejercicio 2: 

Ingresar un texto en un arreglo de caracteres definido de TOPE 
elementos. Solicitar al usuario que ingrese 2 caracteres.
Desarrollar una función que reciba:
●	El arreglo de caracteres
●	El valor TOPE
●	Los 2 caracteres ingresados
La función debe mostrar la posición de la última ocurrencia de cada
 uno de los 2 caracteres. En el caso de que alguno de los caracteres 
 no se encuentre debe informar que no lo encontró.
*/

const int TOPE = 100;

void mostrarPosiciones(char car1, char car2, char texto[], int TOPE){
    int posCar1 = -1, posCar2 = -1;

    for (int i = 0; i < TOPE && texto; i++)
    {
        if(car1 == texto[i]){
            posCar1 = i;
        }

        if(car2 == texto[i]){
            posCar2 = i;
        }
    }

    if(posCar1 != -1){
        cout << "La última ocurrencia para el caracter \'" << car1 
        << "\' fue en la posicion: " << posCar1 << endl;
    }else{
        cout << "No se encotro el caracter \'" << car1 << "\'" << endl;
    }

    if(posCar2 != -1){
        cout << "La última ocurrencia para el caracter \'" << car2 
        << "\' fue en la posicion: " << posCar2 << endl;
    }else{
        cout << "No se encotro el caracter \'" << car2 << "\'" << endl;
    }
    

} 


int main(){
    char texto[TOPE] = "esto es un ejemplo de cadena de caracteres";
    char car1 = ' ', car2 = ' ';

    cout << "Ingrese dos caracteres para encontrar en la cadena: " 
    << "\'" << texto << "\'" << endl;

    cout << "Ingrese el primer caracter: ";
    cin >> car1;
    cout << "Ingrese el segundo caracter: ";
    cin >> car2;
    
    mostrarPosiciones(car1, car2, texto, TOPE);

    return EXIT_SUCCESS;
}