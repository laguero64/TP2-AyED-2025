#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <map>
#define CANT_GENEROS 20

using namespace std;

struct Libro {
    char genero[51];
    int codigoGenero;
    char titulo[51];
    char autor[51];
    int cantPag;
};
int cantidadLibros = 0;

FILE * libro;
struct NodoLibro{ // declaracion de nodo
   Libro libro;
   NodoLibro* sig;
};

NodoLibro* vectorGeneros[CANT_GENEROS]; //declaracion de vector de punteros

NodoLibro* insertarOrdenado(NodoLibro*& puntero,Libro registro) {
    NodoLibro* nuevo = new NodoLibro();
    nuevo->libro = registro;
    nuevo->sig = NULL;

    NodoLibro* anterior = NULL;
    NodoLibro* actual = puntero;

    while (actual != NULL && actual->libro.cantPag < registro.cantPag) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        nuevo->sig = puntero;
        puntero = nuevo;
    } else {
        anterior->sig = nuevo;
        nuevo->sig = actual;
    }

    return puntero;
}

void cargaVector(NodoLibro* vectorGeneros[]){ //Se abre el archivo y se recorre
   int codGenero;

   FILE* archivoLibros = fopen("libros.dat","rb");

   if(archivoLibros == NULL){
      cout << "No se pudo abrir el archivo." << endl;
      return;
   }

   Libro registro;

   while(fread(&registro,sizeof(Libro),1,archivoLibros)==1) {
      codGenero=registro.codigoGenero-1;
      vectorGeneros[codGenero] = insertarOrdenado(vectorGeneros[codGenero],registro); // se llama a la funcion para insertar
   }
   
   fclose(archivoLibros);
}

void inicializarVector() { // funcion para inicializar el vector
   int i;
   for(i=0; i<20; i++){
      vectorGeneros[i] = NULL; // inicializacion de cada posicion del vector como vacias(cabezas de listas)
   }
   cargaVector(vectorGeneros); // llamada a funcion para comenzar la lectura del archivo y carga del vector
}

void cargarDatoIndividual(Libro &libroCargado, string parametro) {
    if (parametro == "genero") {
        cout << "Ingrese el género literario del libro (no más de 50 caracteres)." << endl;
        cin.ignore();
        cin.getline(libroCargado.genero, 51);
    }
    else if (parametro == "codigoGenero") {
        cout << "Ingrese el código del género literario del libro [1-20]" << endl;
        cin >> libroCargado.codigoGenero;
        while (libroCargado.codigoGenero < 1 || libroCargado.codigoGenero > 20) {
            cout << "Número inválido. Debe estar entre 1 y 20: ";
            cin >> libroCargado.codigoGenero;
        }
    }
    else if (parametro == "titulo") {
        cout << "Ingrese el título del libro (no más de 50 caracteres)." << endl;
        cin.ignore();
        cin.getline(libroCargado.titulo, 51);
    }
    else if (parametro == "autor") {
        cout << "Ingrese el autor del libro (no más de 50 caracteres)." << endl;
        cin.ignore();
        cin.getline(libroCargado.autor, 51);
    }
    else if (parametro == "cantPag") {
        cout << "Ingrese la cantidad de páginas del libro." << endl;
        cin >> libroCargado.cantPag;
    }
}

Libro cargarDatos() {
    Libro libroCargado;
    
    libro = fopen("libros.dat", "ab");
    if (!libro) {
        cout << "Error al abrir el archivo." << endl;
        exit(1);
    }

    cargarDatoIndividual(libroCargado, "genero");
    cargarDatoIndividual(libroCargado, "codigoGenero");
    cargarDatoIndividual(libroCargado, "titulo");
    cargarDatoIndividual(libroCargado, "autor");
    cargarDatoIndividual(libroCargado, "cantPag");

    fwrite(&libroCargado, sizeof(Libro), 1, libro);
    fclose(libro);

    cantidadLibros++;
    return libroCargado;
}

void cantLibrosGenero(NodoLibro* vector[]){

   int i, contador=0, contadorMayorCant=0,generoMasLibros;

   for(i=0;i<20;i++){

      NodoLibro* aux=vector[i];

      while(aux!=NULL){
        contador++;
        aux=aux->sig;
      }

      cout << "El genero " << i+1 << " tiene " << contador << " libros." << endl;

      if(contadorMayorCant==0 || contadorMayorCant<contador){

         contadorMayorCant=contador;
         generoMasLibros=i+1;
      }

      contador=0;
   }

   cout << "El genero " << generoMasLibros << " tiene la mayor cantidad de libros." << endl;
}

void mostrarDatos() {
    inicializarVector(); // llamada a inicializar vector

    cout << "Se han registrado un total de " << cantidadLibros << " libros." << endl;

    cantLibrosGenero(vectorGeneros);
}

#endif