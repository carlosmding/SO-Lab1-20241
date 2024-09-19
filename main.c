#include <stdio.h>
#include <stdlib.h>

void leerArchivo(char *nombreArchivo);
void ingresarTexto();

int main(int argc, char *argv[])
{
 //Creación de main inicial
 printf("Práctica #1 - Sistemas Operativos\n");

 //Validación de los diferentes escenarios
 if (argc == 1) { 
    printf("Primer escenario (Sin archivo de entrada ni salida)\n");
    //Función para leer desde pantalla Stdin
    ingresarTexto();
    //Funcion para invertir el texto
    //Imprimir el resultado final en pantalla
    exit(0); }

 else if (argc == 2) { 
    printf("Segundo escenario (Sólo archivo de entrada)\n");
    //Función para leer el archivo de entrada
    leerArchivo(argv[1]);

    //Funcion para invertir el texto
    //Imprimir el resultado final en pantalla 
    exit(0); }

 else if (argc == 3) { 
    printf("Tercer escenario (Archivo de entrada y salida)\n");
    leerArchivo(argv[1]);
    //Funcion para invertir el texto
    //Función para escribir el texo invertido en archivo de salida
    exit(0); }

 else if (argc > 3) { 
    fprintf(stderr, "usage: reverse <input> <output>\n"); 
    exit(1); }

}

void ingresarTexto() {
    char *linea = NULL;  // Puntero para almacenar la línea leída
    size_t tamano = 0;   // Tamaño del buffer que usará getline
    ssize_t leidos;      // Resultado de getline (número de caracteres leídos)

    printf("Escriba a continuación el texto que desea ingresar (Ctrl+D para finalizar):\n");

    // Leer líneas desde stdin hasta que se detecte EOF
    while ((leidos = getline(&linea, &tamano, stdin)) != -1) {
        printf("Línea ingresada: %s", linea);  // Imprimir la línea leída
    }
    free(linea); 
}

void leerArchivo(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        fprintf(stderr, "error: cannot open file %s\n", nombreArchivo);
        exit(1);
    }
    
    char *linea = NULL;   // Puntero para la línea
    size_t tamano = 0;    // Tamaño del buffer para `getline`
    ssize_t leidos;       // Tamaño de la línea leída, o -1 en caso de error o EOF

    // Leer cada línea del archivo e imprimirla
    while ((leidos = getline(&linea, &tamano, archivo)) != -1) {
        printf("%s", linea);
    }

    free(linea);
    fclose(archivo);
}



