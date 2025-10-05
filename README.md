# TP2-AyED-2025

### Condición de aprobación del TP
Para aprobar el trabajo práctico se deben realizar correctamente todos los requerimientos propuestos, utilizando el lenguaje C. Se deben cumplir las fechas de entrega, no cumplirlas significa quedar fuera de la carrera por la Aprobación Directa. Una vez realizada la entrega, se citará al equipo para hacer un coloquio individual sobre la entrega. El coloquio debe aprobarse.
Se debe entregar una carpeta al docente del curso (una por equipo) que cuente con:
* Una carátula con los integrantes del equipo y el código de grupo asignado.
* Los algoritmos deben ser escritos en código fuente.

### Contexto del proyecto
El Ministerio de Cultura y Educación ha iniciado un programa para fomentar la lectura en distintas instituciones educativas. Para ello, se ha realizado un relevamiento de libros disponibles en distintas bibliotecas escolares. Se requiere una aplicación que permita procesar la información recolectada y mostrar resultados estadísticos sobre el material relevado.

### Requerimientos
Se debe desarrollar una aplicación en lenguaje C que despliegue un menú con las
siguientes opciones:
1. Cargar y procesar datos de libros
2. Mostrar resultados
3. Salir

### Descripción funcional
Si el usuario elige la opción "Cargar y procesar datos de libros", la aplicación deberá invocar a un módulo o función encargada de realizar esta tarea. A su vez, este módulo podrá llamar a otros para efectuar tareas específicas. Un código modular es más fácil de leer y mantener. Los datos deben ser cargados desde un archivo binario con registros que contienen la siguiente información por libro:
* Género literario (cadena de hasta 50 caracteres)
* Código Género literario (entero de 1 a 20).
* Título del libro (cadena de hasta 50 caracteres)
* Autor (cadena de hasta 50 caracteres)
* Cantidad de páginas (entero)

Nota: La carga de datos no requiere validación de duplicados. Si un mismo libro figura más de una vez en el archivo, se considerará como entradas independientes.
La información leída del archivo se debe organizar en un vector de punteros a listas
simplemente enlazadas, donde cada posición del vector representa un género literario determinado. Cada puntero apunta al primer nodo de una lista que contiene los libros correspondientes a ese género. El vector debe ser declarado como un array de punteros: NodoLibro* vector_generos[CANT_GENEROS];

La manipulación de la estructura de lista simplemente enlazada debe realizarse
exclusivamente utilizando las funciones del TAD Lista implementado y visto durante el curso, haciendo las adaptaciones que correspondan conforme a las estructuras de datos correspondientes. Entre estas funciones se incluye, por ejemplo: insertarOrdenado(parametros corresponientes): para insertar elementos manteniendo un criterio de orden. Si el usuario elige la opción "Mostrar resultados", la aplicación deberá invocar a una función que reciba por parámetro el vector de punteros a listas, procese los datos, y muestre por pantalla:
* Cantidad total de libros registrados.
* Promedio de páginas por libro.
* Género con mayor cantidad de libros.
* Cantidad de libros por género.
* Autor más frecuente.
* Título del libro con mayor cantidad de páginas.
Si el usuario elige la opción "Salir", la aplicación debe finalizar correctamente.
El archivo debe ser leído con operaciones de entrada/salida vistas en el curso. El archivo puede estar previamente cargado o ser generado con una función auxiliar.

### Consideraciones técnicas
Para el desarrollo del proyecto se deben utilizar funcionalidades disponibles en el lenguaje C, particularmente las bibliotecas estándar <stdio.h>, <stdlib.h> y <string.h>. Las cadenas de caracteres deben ser manejadas mediante vectores de caracteres (char[]). Se permite el uso de las instrucciones de entrada y salida de C++, es decir, cin y cout (proveídas por la biblioteca <iostream>), para facilitar la interacción con el usuario en caso de ser necesario.