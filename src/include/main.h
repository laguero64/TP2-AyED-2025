#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <string.h>
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

void cargaVector(NodoLibro* vectorGeneros[]){ 
   int codGenero;
   FILE* archivoLibros = fopen("libros.dat","rb");

   if(archivoLibros == NULL){
      cout << "No se pudo abrir el archivo libros.dat." << endl;
      return;
   }

   Libro registro;
   int leidos = 0;

   while(fread(&registro,sizeof(Libro),1,archivoLibros)==1) {
      codGenero=registro.codigoGenero-1;
      if (codGenero >= 0 && codGenero < CANT_GENEROS)
         vectorGeneros[codGenero] = insertarOrdenado(vectorGeneros[codGenero],registro);
      leidos++;
   }
   
   fclose(archivoLibros);

   if (leidos == 0)
       cout << "El archivo esta vacio, no hay libros cargados." << endl;
   else
       cout << "Se cargaron " << leidos << " libros desde el archivo." << endl;
}

void inicializarVector(NodoLibro* vectorGeneros[]) { // funcion para inicializar el vector
   int i;
   for(i=0; i<20; i++){
      vectorGeneros[i] = NULL; // inicializacion de cada posicion del vector como vacias(cabezas de listas)
   }
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

void cantLibrosGenero(NodoLibro* vector[]) {

   int i, contador = 0, contadorMayorCant = 0, generoMasLibros;

   for(i = 0; i < 20; i++){

      NodoLibro* aux=vector[i];

      while (aux != NULL) {
        contador++;
        aux=aux->sig;
      }
      
      if (contador == 1) {
        cout << "El genero " << i+1 << " tiene " << contador << " libro." << endl;
      }
      else {
        cout << "El genero " << i+1 << " tiene " << contador << " libros." << endl;
      }

      if (contadorMayorCant == 0 || contadorMayorCant < contador) {
         contadorMayorCant = contador;
         generoMasLibros = i + 1;
      }

      contador=0;
   }

   cout << "El género " << generoMasLibros << " tiene la mayor cantidad de libros." << endl;
}

void autorMasFrecuente(NodoLibro* vector[]) {
    char autores[50][51]; // Se establece un maximo de 50 autores
    int contador[50] = {0};
    int cantAutores = 0;
    int maxFrecuencia = 0;
    char autorMasFrecuente[51] = "";

    // Recorrer todas las listas del vector
    for (int i = 0; i < CANT_GENEROS; i++) {
        NodoLibro* aux = vector[i];

        while (aux != NULL) {
            // Comprobar si el autor existe en el array
            int encontrado = -1;
            for (int j = 0; j < cantAutores; j++) {
                if (strcmp(autores[j], aux->libro.autor) == 0){
                    encontrado = j;
                    break;
                }
            }

            // Si el autor no existe, agregarlo
            if (encontrado == -1) {
                strcpy(autores[cantAutores], aux->libro.autor);
                contador[cantAutores] = 1;
                cantAutores++;
            } else {
                contador[encontrado]++;
            }

            aux = aux->sig;
        }
    }

    // Buscar el autor mas frecuente
    for (int i = 0; i < cantAutores; i++) {
        if (contador[i] > maxFrecuencia) {
            maxFrecuencia = contador[i];
            strcpy(autorMasFrecuente, autores[i]);
        }
    }

    if (maxFrecuencia == 0) {
        cout << "No hay libros cargados." << endl;
    } else {
        cout << "El autor mas frecuente es: " << autorMasFrecuente << " (" << maxFrecuencia << " libros)." << endl;
    }
}

void libroMasPaginas(NodoLibro* vector[]) {
    string tituloMax;
    int maxPag = -1;

    for (int i = 0; i < CANT_GENEROS; i++) {
        NodoLibro* aux = vector[i];
        while (aux != NULL) {
            if (aux->libro.cantPag > maxPag) {
                maxPag = aux->libro.cantPag;
                tituloMax = aux->libro.titulo;
            }

            aux = aux->sig;
        }
    }

    if (maxPag == -1) {
        cout << "No hay libros cargados." << endl;
    } else {
        cout << "El libro con mas paginas es: \"" << tituloMax << "\" con " << maxPag << " paginas." << endl;
    }
}

void promedioPaginas(NodoLibro* vector[]) {
    int totalPaginas = 0, totalLibros = 0;

    for (int i = 0; i < CANT_GENEROS; i++) {
        NodoLibro* aux = vector[i];
        
        while (aux != NULL) {
            totalPaginas += aux->libro.cantPag;
            totalLibros++;
            aux = aux->sig;
        }
    }

    if (totalLibros == 0){
        cout << "No hay libros cargados." << endl;
    } else {
        cout << "El promedio de paginas por libros es: " << (float)totalPaginas / totalLibros << endl;
    }
}

void mostrarDatos() {
   inicializarVector(vectorGeneros); // llamada a inicializar 
   cargaVector(vectorGeneros); // llamada a funcion para comenzar la lectura del archivo y carga del vector

   if (cantidadLibros == 0) {
     cout << "No hay libros cargados." << endl;
     return;
   }

   cout << "Resultados: " << endl;
   cout << "Total de libros registrados: " << cantidadLibros << endl;
   cantLibrosGenero(vectorGeneros);
   autorMasFrecuente(vectorGeneros);
   libroMasPaginas(vectorGeneros);
   promedioPaginas(vectorGeneros);

   for (int i = 0; i < CANT_GENEROS; i++) { // para evitar memory leaks
    NodoLibro* aux = vectorGeneros[i];
    while (aux != NULL) {
        NodoLibro* temp = aux;
        aux = aux->sig;
        delete temp;
    }
    vectorGeneros[i] = NULL;
}
}

#endif