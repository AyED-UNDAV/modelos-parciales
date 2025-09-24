#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

using namespace std;

/*
Realizar una función que reciba una cadena char[] y un carácter char y que devuelva
cuántas veces aparece ese carácter solamente dentro de palabras que tienen más
de 4 letras.
*/

int contarApariciones(char cad[], char caracter){
    int cantTotal = 0, longPalabra = 0, cantPalabra = 0, tope = strlen(cad) + 1;

   for (int pos = 0; cad[pos] != '\0' || pos < tope; pos++)
    {
       if(cad[pos] != ' ' || cad[pos] != '\0'){
            longPalabra++;

            if(cad[pos] == caracter){
                cantPalabra++;
            }
        }else{
            if (longPalabra > 4)
            {
                cantTotal += cantPalabra;
            }
            longPalabra = 0;
            cantPalabra = 0;
        }
    }

    if (longPalabra > 4)
    {
        cantTotal += cantPalabra;
    }

    return cantTotal;
}

int main(){
    char cadena[] = "Hoy llueve y hay viento fuerte en la zona este";
    char letra;

    cout << "Ingrese una letra: ";
    cin >> letra;

    cout << "La cantidad de letras \'" << letra 
    << "\' en la cadena \"" << cadena 
    << "\" para las palabras con mas de 4 letras es: " 
    << contarApariciones(cadena,letra);

    return EXIT_SUCCESS;
}