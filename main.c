#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
 //Creación de main inicial
 printf("Práctica #1 - Sistemas Operativos\n");

 //Validación de los diferentes escenarios
 if (argc == 1) { 
    printf("Primer escenario (Sin archivo de entrada ni salida)\n");
    //Función para leer desde pantalla Stdin
    //Funcion para invertir el texto
    //Imprimir el resultado final en pantalla
    exit(0); }

 else if (argc == 2) { 
    printf("Segundo escenario (Sólo archivo de entrada)\n");
    //Función para leer el archivo de entrada
    //Funcion para invertir el texto
    //Imprimir el resultado final en pantalla 
    exit(0); }

 else if (argc == 3) { 
    printf("Tercer escenario (Archivo de entrada y salida)\n");
    //Función para leer el archivo de entrada
    //Funcion para invertir el texto
    //Función para escribir el texo invertido en archivo de salida
    exit(0); }

 else if (argc > 3) { 
    fprintf(stderr, "usage: reverse <input> <output>\n"); 
    exit(1); }

}