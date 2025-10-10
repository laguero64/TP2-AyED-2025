#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "include/main.h"

using namespace std;

int interaction = 0;

int main() {
    cout << "Usted está utilizando el programa para la fomentación de lectura del Ministerio de Cultura y Educación." << endl; 
    cout << "A continuación, se le pedirá que ingrese la opción desea realizar." << endl;

    while(1) {
        cout << "Por favor, ingrese el número de la acción que desea realizar:" << endl;
        cout << "1. Cargar y procesar datos de libros" << endl;
        cout << "2. Mostrar resultados" << endl;
        cout << "3. Salir" << endl;
        cin >> interaction;

        switch (interaction) {
            case 1:
                cout << "Usted ha elegido cargar y procesar datos de libros." << endl;
                cargarDatos();
                interaction = 0;
                cout << "Los libros han sido cargados y procesados exitosamente." << endl;
                break;
            case 2:
                cout << "Usted ha elegido mostrar los resultados." << endl;
                mostrarDatos();
                interaction = 0;
                break;
            case 3:
                cout << "Usted ha elegido salir del programa." << endl;
                interaction = 0;
                exit(0);
                break;
            default:
                cout << "Opción no válida. Por favor, intentelo nuevamente." << endl;
                interaction = 0;
                break;
        }
    }
    return 0;
}