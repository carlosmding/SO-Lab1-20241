#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define INITIAL_CAPACITY 10  // Capacidad inicial de la pila

// Definición de la estructura de la pila
typedef struct {
    char **lineas;    // Arreglo de punteros a las líneas
    int cima;         // Índice del elemento superior (cima) en la pila
    int capacidad;    // Capacidad actual de la pila
} Stack;

void leerArchivo(char *nombreArchivo, Stack *pila);           // Función para leer un texto y guardarlo en la pila
void ingresarTexto(Stack *pila);                              // Función para ingresar texto entrada estandar
void inicializarPila(Stack *pila);                            // Función para inicializar la pila
void push(Stack *pila, char *linea);                          // Función para empujar una línea a la pila
char *pop(Stack *pila);                                       // Función para sacar una línea de la pila
void imprimirInverso(Stack *pila);                            // Función para imprimir texto orden inverso
void liberarPila(Stack *pila);                                // Función para liberar la memoria de la pila
void escribirArchivo(Stack *pila, char *nombreArchivoSalida); // Función para escribir en archivo de salida


int main(int argc, char *argv[])
{
 //Creación de main inicial
 //printf("Práctica #1 - Sistemas Operativos\n");
 Stack pila;       // Definición de la pila
 inicializarPila(&pila);  // Inicializamos la pila

 //Validación de los diferentes escenarios
 if (argc == 1) { 
    //printf("Primer escenario (Sin archivo de entrada ni salida)\n");
    //Función para leer desde pantalla Stdin
    ingresarTexto(&pila);
    //Funcion para imprimir en orden inverso en pantalla
    imprimirInverso(&pila);
    
    liberarPila(&pila);      // Liberar la memoria de la pila

    exit(0); }

 else if (argc == 2) { 
    //printf("Segundo escenario (Sólo archivo de entrada)\n");
    //Función para leer el archivo de entrada y guardar en pila
    leerArchivo(argv[1], &pila);
    //Funcion para imprimir en orden inverso en pantalla
    imprimirInverso(&pila);

    liberarPila(&pila);      // Liberar la memoria de la pila
    exit(0); }

 else if (argc == 3) { 
    //printf("Tercer escenario (Archivo de entrada y salida)\n");
    // Verifica si el archivo de entrada y salida son el mismo, incluido harlink y si existen

    struct stat stat1;
    if (stat(argv[1], &stat1) == -1) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
        exit(1);
    }

    // Verifica si el archivo de salida existe
    struct stat stat2;
    if (stat(argv[2], &stat2) == -1) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
        exit(1);
    }

    // Verifica si el archivo de entrada y salida son el mismo
    if (stat1.st_ino == stat2.st_ino) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }

    //Función para leer el archivo de entrada y guardar en pila
    leerArchivo(argv[1], &pila);

    //Función para escribir el texo invertido en archivo de salida
    escribirArchivo(&pila, argv[2]);

    liberarPila(&pila);      // Liberar la memoria de la pila
    exit(0); }

 else if (argc > 3) { 
    fprintf(stderr, "usage: reverse <input> <output>\n"); 
    exit(1); }

}

void ingresarTexto(Stack *pila) {
    char *linea = NULL;  // Puntero para almacenar la línea leída
    size_t tamano = 0;   // Tamaño del buffer que usará getline
    ssize_t leidos;      // Resultado de getline (número de caracteres leídos)

    //printf("Escriba a continuación el texto que desea ingresar (Ctrl+D para finalizar):\n");

    // Leer líneas desde stdin hasta que se detecte EOF
    while ((leidos = getline(&linea, &tamano, stdin)) != -1) {
        push(pila, linea);  // Empuja la línea a la pila
    }
    free(linea); 
}

void leerArchivo(char *nombreArchivo, Stack *pila) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", nombreArchivo);
        exit(1);
    }
    
    char *linea = NULL;   // Puntero para la línea
    size_t tamano = 0;    // Tamaño del buffer para `getline`
    ssize_t leidos;       // Tamaño de la línea leída, o -1 en caso de error o EOF

    // Leer cada línea del archivo y guardarlo en la pila
    while ((leidos = getline(&linea, &tamano, archivo)) != -1) {
        push(pila, linea);  // Empuja la línea a la pila
    }
    free(linea);

    fclose(archivo);
}

// Función para inicializar la pila
void inicializarPila(Stack *pila) {
    pila->capacidad = INITIAL_CAPACITY; // Establece la capacidad inicial de la pila
    pila->cima = -1;                    // La pila está vacía, así que la cima es -1
    pila->lineas = (char **)malloc(pila->capacidad * sizeof(char *)); // Asigna memoria para el arreglo de punteros
    if (pila->lineas == NULL) { // Verifica si la asignación de memoria fue exitosa
        fprintf(stderr, "Error: No se pudo asignar memoria para la pila\n");
        exit(1);
    }
}

// Función para empujar una línea a la pila
void push(Stack *pila, char *linea) {
    // Si la pila está llena, duplicamos su capacidad
    if (pila->cima == pila->capacidad - 1) {
        pila->capacidad *= 2;  // Duplica la capacidad de la pila
        pila->lineas = (char **)realloc(pila->lineas, pila->capacidad * sizeof(char *)); // Redimensiona el arreglo
        if (pila->lineas == NULL) { // Verifica si la redimensión de la memoria fue exitosa
            fprintf(stderr, "Error: No se pudo redimensionar la pila\n");
            exit(1);
        }
    }

    pila->lineas[++(pila->cima)] = strdup(linea);  // Copia la línea a la pila y actualiza la cima
}

// Función para sacar una línea de la pila
char *pop(Stack *pila) {
    if (pila->cima == -1) {
        return NULL;  // La pila está vacía
    }
    
    char *linea = pila->lineas[pila->cima];  // Guarda la línea en la cima
    pila->cima--;  // Reduce la cima de la pila
    return linea;  // Retorna la línea
}

// Función para imprimir las líneas en orden inverso (sacándolas de la pila)
void imprimirInverso(Stack *pila) {
    char *linea;
    // Imprimir líneas mientras haya elementos en la pila
    while ((linea = pop(pila)) != NULL) {
        printf("%s", linea);  // Imprime la línea (las líneas ya incluyen el salto de línea)
        free(linea);  // Libera la memoria de la línea
    }
}

// Función para liberar la memoria de la pila
void liberarPila(Stack *pila) {
    while (pila->cima != -1) {
        free(pila->lineas[pila->cima--]);  // Libera las líneas restantes en la pila
    }
    free(pila->lineas);  // Libera el arreglo de punteros
}

void escribirArchivo(Stack *pila, char *nombreArchivoSalida) {

    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
    if (archivoSalida == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", nombreArchivoSalida);
        exit(1);
    }

    char *linea;
    while ((linea = pop(pila)) != NULL) {
        fprintf(archivoSalida, "%s", linea);  // Escribe la línea en el archivo de salida
        free(linea);  // Libera la memoria de la línea
    }

    fclose(archivoSalida);  // Cierra el archivo de salida
}



