#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Libro {
    char genero[51];
    int codigoGenero;
    char titulo[51];
    char autor[51];
    int cantPag;
};
int cantidadLibros;

FILE * libro;

void cargarDatoIndividual(Libro &libroCargado, string parametro) {
    if (parametro == "genero") {
        cout << "Ingrese el género literario del libro (no más de 50 caracteres)." << endl;
        cin >> libroCargado.genero;
        fwrite(&libroCargado.genero, sizeof(libroCargado.genero), 1, libro);
    }
    else if (parametro == "codigoGenero") {
        cout << "Ingrese el código del género literario del libro [1-20]" << endl;
        cin >> libroCargado.codigoGenero;
        while (libroCargado.codigoGenero < 1 || libroCargado.codigoGenero > 20) {
            cout << "Número inválido. Debe estar entre 1 y 20: ";
            cin >> libroCargado.codigoGenero;
        }
        fwrite(&libroCargado.codigoGenero, sizeof(libroCargado.codigoGenero), 1, libro);
    }
    else if (parametro == "titulo") {
        cout << "Ingrese el título del libro (no más de 50 caracteres)." << endl;
        cin >> libroCargado.titulo;
        fwrite(&libroCargado.titulo, sizeof(libroCargado.titulo), 1, libro);
    }
    else if (parametro == "autor") {
        cout << "Ingrese el autor del libro (no más de 50 caracteres)." << endl;
        cin >> libroCargado.autor;
        fwrite(&libroCargado.autor, sizeof(libroCargado.autor), 1, libro);
    }
    else if (parametro == "cantPag") {
        cout << "Ingrese la cantidad de páginas del libro." << endl;
        cin >> libroCargado.cantPag;
        fwrite(&libroCargado.cantPag, sizeof(libroCargado.cantPag), 1, libro);
    }
}

Libro cargarDatos() {
    Libro libroCargado;
    
    libro = fopen("libros.dat", "ab");
    cargarDatoIndividual(libroCargado, "genero");
    cargarDatoIndividual(libroCargado, "codigoGenero");
    cargarDatoIndividual(libroCargado, "titulo");
    cargarDatoIndividual(libroCargado, "autor");
    cargarDatoIndividual(libroCargado, "cantPag");
    fclose(libro);

    cantidadLibros++;
    return libroCargado;
}

void mostrarDatos() {

}

#endif