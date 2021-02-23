//Se incluye el header "funciones.h" el cual coniene todas las funciones no nativas utilizadas en el programa

#include "funciones.h"

//Se crea la funcion bes para luego poder utilizarla en el main
int BES();

int main()
{
<<<<<<< Updated upstream
    SetConsoleOutputCP(65001);
=======
    //Se utiliza para que acepte los simbolos especiales (tildes, cuadros, etc), lo que hace es cambiar la codificacion a utf-8 de consola windows
        SetConsoleOutputCP(65001);
>>>>>>> Stashed changes
    //Se crea un flag para entrar al bucle que permitirá ejecutar el programa hasta que el usuario indique lo contrario
    int flag = 1;
    while (flag == 1)
    {
        BES();
        printf("¿Desea volver a utilizar el programa?\n");
        printf("1. No\n");
        printf("2. Si\n");
        //El valor de flag dependerá directamente de la desición del usuario, pudiendo solo ingresar 1 o 2
        flag = pedirNumero("Ingrese su opcion aqui (1/2): ", 1, 2) - 1;
        limpiarConsola();
    }
    //Mensaje de despedida cuando el ususario decida salir del programa
    printf("Hasta luego\n\n\n\n");
}

//Función BES, la cual realiza la busqueda en espacios de soluciones
int BES()
{
    //Se crean las variables y arrays dinamicos necesarios
    int **matrizDeFilas = crearFilas();
    int **entradasPosibles = generarEntradasPosibles();
    int cantidadDeSolucionesFinal = 0;
    char nombreColumnas[50];
    char nombreFilas[50];
    matriz filas;
    matriz columnas;
    struct stat buffer;
    int **matrizSolucion = (int **)malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
    {
        matrizSolucion[i] = (int *)malloc(sizeof(int) * 5);
    }
    //Se piden los nombres de los archivos y se intentan leer
    pedirNombreDeArchivos(1, nombreFilas);
    pedirNombreDeArchivos(2, nombreColumnas);
    leerArchivo(nombreFilas, &filas);
    leerArchivo(nombreColumnas, &columnas);

    //Se verifica que se hayan podido leer los archivos, es decir que existen en el directorio especificado
    if (filas.sePudo == 1 && columnas.sePudo == 1)
    {
        //Se verifica que el archivo cumpla las caracteristicas de entrada
        if (verificarEntradaArchivo(filas.filas, entradasPosibles) == 1 && verificarEntradaArchivo(columnas.filas, entradasPosibles) == 1)
        {
            printf("Los archivos cumplen las entradas\n");
            //--------Se genera el conjunto general de soluciones si aun no se ha creado(en un archivo de texto plano llamado soluciones.txt)-------

            //Se verifica si el archivo no existe para crearlo
            if (stat("soluciones.txt", &buffer) != 0)
            {
                printf("Generando conjunto general de soluciones\nUn momento por favor...\n");
                crearConjuntoDeSolucionesInicial();
                limpiarConsola();
            }
            else
            {
                printf("El conjunto general de soluciones ya se encuentra creado\n");
            }
            //-----------Se realiza la busqueda en el espacio de soluciones creado en el archivo soluciones.txt------------
            printf("Filtrando soluciones generales para generar soluciones exactas...\n");
            FILE *archivo = fopen("soluciones.txt", "r"); // Se abre el archivo con las soluciones generales
            for (int i = 0; i < 33554432; i++)            //Se itera hasta ese numero porque es la cantidad de posibles combinaciones para las soluciones
            {
                //Se restringe la busqueda a maximo 2 soluciones
                if (cantidadDeSolucionesFinal >= 2)
                {
                    i = 33554433;
                    printf("No es una instruccion unica\n");
                }
                else
                {
                    //Se genera una matriz posible solucion en base al archivo
                    leerSoluciones(archivo, matrizSolucion);
                    //Se verifica que la solucion cumpla las restricciones de filas y columnas
                    if (verificarSolucion(matrizSolucion, filas.filas, columnas.filas) == 1)
                    {
                        //Se muestra la solución y se le suma 1 a la cantidad de soluciones encontradas
                        printf("Fue necesario revisar %d posibles soluciones para llegar a esta\n", i + 1);
                        mostrarSolucion(matrizSolucion, filas, columnas);
                        printf("------------------------------------------------------\n");
                        cantidadDeSolucionesFinal++;
                    }
                }
            }
            // Se imprime que tipo de instruccion se ha ingresado y se notifica el fin de la ejecucion
            if (cantidadDeSolucionesFinal == 1)
            {
                printf("Es una instruccion unica\n");
            }
            else if (cantidadDeSolucionesFinal == 0)
            {
                printf("No es posible representarla\n");
            }
            printf("Ejecucion finalizada\n");
            fclose(archivo);
        }
        else
        {
            printf("Alguno de los archivos no cumple las entradas\n");
        }
    }
    else
    {
        printf("Alguno de los archivos indicados no existe\n");
    }

    //----------------Se libera la memoria de los arrays dinamicos--------------
    for (int i = 0; i < 32; i++)
    {
        free(matrizDeFilas[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        free(matrizSolucion[i]);
        free(filas.filas[i]);
        free(columnas.filas[i]);
    }
    free(matrizSolucion);
    free(entradasPosibles);
    free(filas.filas);
    free(matrizDeFilas);
    return 0;
}
