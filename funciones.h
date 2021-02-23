#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "estructuras.h"
#if defined(_WIN32)
#include <windows.h>
#else
#include "eliminar_error_windows.h"
#endif

//Entrada: No recibe
//Salida: Un entero, 0 para windows, 1 Para Linux o MAC
//Función: Detecta el sistema operativo en el que se está trabajando

int detectarSO()
{
#if defined(_WIN32)
#define SISTEMA 0
#else
#define SISTEMA 1
#endif
    return SISTEMA;
}

//------------------------------------------------------

//Entrada: No recibe
//Salida: No retorSin costo hasta los 30 años:na
//Función: Detecta el sistema operativo en uso y limpia la consola
void limpiarConsola()
{
    int sistema = detectarSO();
    switch (sistema)
    {
    case 0:
        system("cls");
        break;
    case 1:
        system("clear");
        break;
    }
}

//------------------------------------------------------

//Entrada: un "string" que se utilizará para decirle al usuario que debe ingresar y 2 enteros, que representan el numero minimo y maximo respectivamente que el usuario puede ingresar
//Salida: un entero, que es el numero ingresado por el usuario
//Funcion: Pide un entero hasta que se ingrese un numero y que esté dentro del rango esperado

int pedirNumero(char *string, int cotaInferior, int cotaSuperior)
{
    printf("%s ", string);
    char numero[5];
    fflush(stdin);
    fgets(numero, 5, stdin);
    int longitud = strlen(numero);
    if (numero[longitud - 1] == '\n')
    {
        numero[longitud - 1] = '\0';
    }
    for (int i = 0; i < longitud - 1; i++)
    {
        if (!(isdigit(numero[i])))
        {
            printf("Ingrese un numero correcto, por favor vuelva a intentarlo\n");
            return pedirNumero(string, cotaInferior, cotaSuperior);
        }
    }
    int numeroFinal = atoi(numero);
    if (numeroFinal < cotaInferior || numeroFinal > cotaSuperior)
    {
        printf("Ingrese un numero correcto, por favor vuelva a intentarlo\n");
        return pedirNumero(string, cotaInferior, cotaSuperior);
    }
    return numeroFinal;
}

//---------------------------------

//Entrada: No recibe
//Salidas: Una matriz de 32 filas de numeros enteros, son las posibles filas a formar con 2 estados y 5 posiciones.
//Funcion:

int **crearFilas()
{
    int **matrizDeFilas = (int **)malloc(sizeof(int *) * 32);
    for (int fila = 0; fila < 32; fila++)
    {
        matrizDeFilas[fila] = (int *)malloc(sizeof(int) * 5);
    }
    int posicion = 0;
    while (posicion < 32)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        for (int m = 0; m < 2; m++)
                        {
                            matrizDeFilas[posicion][0] = i;
                            matrizDeFilas[posicion][1] = j;
                            matrizDeFilas[posicion][2] = k;
                            matrizDeFilas[posicion][3] = l;
                            matrizDeFilas[posicion][4] = m;
                            posicion++;
                        }
                    }
                }
            }
        }
    }
    return matrizDeFilas;
}

//-------------------------------

//Entrada: Un char que representa el nombre del archivo que contiene las instrucciones y una estructura de tipo matriz
//         en la cual se guardaran las instrucciones, la cual es pasada por referencia
//Salida: No entrega
//Funcion: Intenta leer un archivo con instrucciones, si es posible guarda las instrucciones en la variable lectura y deja como
//         1 el atributo sePudo de la estructura lectura, sino se pudo deja este atributo como 0.

void leerArchivo(char *nombreArchivo, matriz *lectura)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    char *aux = (char *)malloc(sizeof(char) * 3);
    lectura->filas = (int **)malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
    {
        lectura->filas[i] = (int *)malloc(sizeof(int) * 2);
    }

    if (!(archivo == NULL))
    {
        lectura->sePudo = 1;
        for (int i = 0; i < 5; i++)
        {
            fscanf(archivo, "%c%c%c", &aux[0], &aux[1], &aux[2]);
            lectura->filas[i][0] = aux[0] - '0';
            lectura->filas[i][1] = aux[1] - '0';
        }
        fclose(archivo);
    }
    else
    {
        lectura->sePudo = 0;
    }
    free(aux);
}

//----------------------------------

//Entrada: Un array de array de enteros, la cual es una matriz de 5*2 que contiene las posibles instrucciones
//         y un array de array de entero que contiene las instrucciones que se pueden tener
//Salida: Un entero, valor 1 si cumple o 0 si no cumple
//Funcion: Verifica que la lista de instrucciones ingresada tenga solo instrucciones correctas

int verificarEntradaArchivo(int **filas, int **EntradasPosibles)
{
    int contador = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (filas[i][0] == EntradasPosibles[j][0] && filas[i][1] == EntradasPosibles[j][1])
            {
                contador++;
                continue;
            }
        }
    }
    if (contador == 5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//----------------------------------

//Entrada: No recibe
//Salida: Un array de array de enteros, la cual representa la lista de posibles instrucciones que se pueden entregar
//Funcion: Genera las posibles instrucciones que se pueden entregar

int **generarEntradasPosibles()
{
    int **entradasPosibles = (int **)malloc(sizeof(int *) * 12);
    for (int i = 0; i < 12; i++)
    {
        entradasPosibles[i] = (int *)malloc(sizeof(int) * 2);
    }
    //00
    entradasPosibles[0][0] = 0;
    entradasPosibles[0][1] = 0;
    //01
    entradasPosibles[1][0] = 0;
    entradasPosibles[1][1] = 1;
    //02
    entradasPosibles[2][0] = 0;
    entradasPosibles[2][1] = 2;
    //03
    entradasPosibles[3][0] = 0;
    entradasPosibles[3][1] = 3;
    //04
    entradasPosibles[4][0] = 0;
    entradasPosibles[4][1] = 4;
    //05
    entradasPosibles[5][0] = 0;
    entradasPosibles[5][1] = 5;
    //11
    entradasPosibles[6][0] = 1;
    entradasPosibles[6][1] = 1;
    //12
    entradasPosibles[7][0] = 1;
    entradasPosibles[7][1] = 2;
    //13
    entradasPosibles[8][0] = 1;
    entradasPosibles[8][1] = 3;
    //21
    entradasPosibles[9][0] = 2;
    entradasPosibles[9][1] = 1;
    //22
    entradasPosibles[10][0] = 2;
    entradasPosibles[10][1] = 2;
    //31
    entradasPosibles[11][0] = 3;
    entradasPosibles[11][1] = 1;

    return entradasPosibles;
}

//---------------------------

//Entrada: un entero, si es 1 es para pedir el archivo de las instrucciones de filas, si es 0 analogamente para las columnas
//         y un "string" en el cual se va a guardar el nombre del archivo
//Salida: no entrega
//Funcion: pide el nombre para las filas o columnas y concatena la ubicacion del nombre con la ruta correcta del archivo

void pedirNombreDeArchivos(int filaOColumna, char *ubicacion)
{
    char nombre[50];
    strcpy(ubicacion, "Pistas/");
    switch (filaOColumna)
    {
    case 1:
        printf("Ingrese el nombre del archivo de las filas sin extension: ");
        break;

    default:
        printf("Ingrese el nombre del archivo de las columnas sin extension: ");
        break;
    }
    fgets(nombre, 50, stdin);
    int longitud = strlen(nombre);
    if (nombre[longitud - 1] == '\n')
    {
        nombre[longitud - 1] = '\0';
    }
    strcat(nombre, ".txt\0");
    fflush(stdin);
    strcat(ubicacion, nombre);
}
//----------------------------------

//Entrada: un numero, el cual se desea convertir a char
//Salida: un char
//Funcion: convierte un entero a char

char convertirAChar(int numero)
{
    return numero + '0';
}

//----------------------------------

//Entrada: No recibe
//Salida: Un archivo de texto plano llamado soluciones.txt
//Funcion: Crea el conjunto de soluciones general, el cual se genera a partir de todas las posibles combinaciones y se escriben en un archivo

void crearConjuntoDeSolucionesInicial()
{
    FILE *soluciones = fopen("soluciones.txt", "w");
    if (soluciones == NULL)
    {
        printf("Error!\n");
        exit(1);
    }
    int **filas = crearFilas();
    int i, j, k, l, m;
    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 32; j++)
        {
            for (k = 0; k < 32; k++)
            {
                for (l = 0; l < 32; l++)
                {
                    for (m = 0; m < 32; m++)
                    {
                        fprintf(soluciones, "%c", convertirAChar(filas[i][0]));
                        // printf("%d ", filas[i][0]);
                        fprintf(soluciones, "%c", convertirAChar(filas[i][1]));
                        // printf("%d ", filas[i][1]);
                        fprintf(soluciones, "%c", convertirAChar(filas[i][2]));
                        // printf("%d ", filas[i][2]);
                        fprintf(soluciones, "%c", convertirAChar(filas[i][3]));
                        // printf("%d ", filas[i][3]);
                        fprintf(soluciones, "%c", convertirAChar(filas[i][4]));
                        // printf("%d ", filas[i][4]);
                        fprintf(soluciones, "%c", convertirAChar(filas[j][0]));
                        fprintf(soluciones, "%c", convertirAChar(filas[j][1]));
                        fprintf(soluciones, "%c", convertirAChar(filas[j][2]));
                        fprintf(soluciones, "%c", convertirAChar(filas[j][3]));
                        fprintf(soluciones, "%c", convertirAChar(filas[j][4]));
                        // // printf("%d ", filas[j][0]);
                        // // printf("%d ", filas[j][1]);
                        // // printf("%d ", filas[j][2]);
                        // // printf("%d ", filas[j][3]);
                        // // printf("%d ", filas[j][4]);
                        fprintf(soluciones, "%c", convertirAChar(filas[k][0]));
                        fprintf(soluciones, "%c", convertirAChar(filas[k][1]));
                        fprintf(soluciones, "%c", convertirAChar(filas[k][2]));
                        fprintf(soluciones, "%c", convertirAChar(filas[k][3]));
                        fprintf(soluciones, "%c", convertirAChar(filas[k][4]));
                        // printf("%d ", filas[k][0]);
                        // printf("%d ", filas[k][1]);
                        // printf("%d ", filas[k][2]);
                        // printf("%d ", filas[k][3]);
                        // printf("%d ", filas[k][4]);
                        fprintf(soluciones, "%c", convertirAChar(filas[l][0]));
                        fprintf(soluciones, "%c", convertirAChar(filas[l][1]));
                        fprintf(soluciones, "%c", convertirAChar(filas[l][2]));
                        fprintf(soluciones, "%c", convertirAChar(filas[l][3]));
                        fprintf(soluciones, "%c", convertirAChar(filas[l][4]));
                        // printf("%d ", filas[l][0]);
                        // printf("%d ", filas[l][1]);
                        // printf("%d ", filas[l][2]);
                        // printf("%d ", filas[l][3]);
                        // printf("%d ", filas[l][4]);
                        fprintf(soluciones, "%c", convertirAChar(filas[m][0]));
                        fprintf(soluciones, "%c", convertirAChar(filas[m][1]));
                        fprintf(soluciones, "%c", convertirAChar(filas[m][2]));
                        fprintf(soluciones, "%c", convertirAChar(filas[m][3]));
                        fprintf(soluciones, "%c", convertirAChar(filas[m][4]));
                        // printf("%d ", filas[m][0]);
                        // printf("%d ", filas[m][1]);
                        // printf("%d ", filas[m][2]);
                        // printf("%d ", filas[m][3]);
                        // printf("%d ", filas[m][4]);
                        fprintf(soluciones, "%c", '\n');
                    }
                }
            }
        }
    }
    free(filas);
    fclose(soluciones);
}

//----------------------------------

//Entrada: Un array de numeros
//Salida: un entero, el cual es la cantidad de 1 que posee el array de entrada
//Funcion: cuenta la cantidad de 1 que posee un array

int contarUnos(int *vector)
{
    int cantidadDeUnos = 0;
    for (int i = 0; i < 5; i++)
    {
        if (vector[i] == 1)
        {
            cantidadDeUnos = cantidadDeUnos + 1;
        }
    }
    return cantidadDeUnos;
}

//----------------------------------

//Entrada:un array de enteros, un numero que se desea contar, un numero que representa la posicion inicial del array y otro numero que es la cantidad de elementos del array
//Salida: un entero, que representa la cantidad de veces consecutivas que se repite el numero
//Funcion: cuenta cuantas veces consecutivas se repite un numero en un array desde cierta posicion

int contarPosicionesConsecutivas(int *vector, int numeroAContar, int posicionInicial, int cantidad)
{
    int cantidadesConsecutivas = 0;
    for (int i = posicionInicial; i < cantidad; i++)
    {
        if (vector[i] == numeroAContar)
        {
            cantidadesConsecutivas++;
        }
        else
        {

            return cantidadesConsecutivas;
        }
    }
    return cantidadesConsecutivas;
}

//----------------------------------

//Entrada: Un array de 5 numeros que representa un vector de la matriz solucion y un array de 2 numeros que representa la instruccion
//Salida: un entero, un 1 si cumple la instruccion y un 0 en caso contrario
//Funcion: verifica que un vector cumpla una instruccion

int verificarInstruccion(int *vector, int *instruccion)
{
    int aux;
    int aux2;
    int cantidadPerforaciones = instruccion[0] + instruccion[1];
    //Verifica que la cantidad de 1 que tenga el vector y la cantidad de perforaciones dadas por la instruccion sean iguales
    if (contarUnos(vector) == cantidadPerforaciones)
    {
        //Si el primer numero de la restriccion es 0 entonces se trata de forma especial porque es mas simple de revisar, los demas casos se tratan igual
        switch (instruccion[0])
        {
        case 0:
            switch (vector[0])
            {
            //Si empieza con 0 el vector se cuentan primero la cantidad de 0 que tiene, para luego contar los 1 consecutivos desde la posicion = cantidad de 0 anteriores
            case 0:
                aux = contarPosicionesConsecutivas(vector, 0, 0, 5);
                //Si la cantidad de 1 desde la posicion = aux es igual al segundo numero de la instruccion se retorna 1, sino retorna 0
                if (contarPosicionesConsecutivas(vector, 1, aux, 5) == instruccion[1])
                {
                    return 1;
                }
                return 0;
                break;
            //Si el vector empieza con 1, se cuentan directamente la cantidad de 1 consecutivas que tiene, si es igual a la instruccion retorna 1, sino retorna 0
            case 1:
                if (contarPosicionesConsecutivas(vector, 1, 0, 5) == instruccion[1])
                {
                    return 1;
                }
                return 0;
                break;
            }
            break;
        //Esto pasa en cualquier caso que no sea instruccion[0] == 0
        default:

            switch (vector[0])
            {

            //Si el vector empieza por 0 pasa lo siquiente:
            case 0:
                //Se cuenta la cantidad de 0 consecutivos en vector desde el inicio y se guarda en la variable aux
                aux = contarPosicionesConsecutivas(vector, 0, 0, 5);
                //Se cuenta la cantidad de 1 consecutivos en vector desde posicion = aux y si es distinto a la primera posicion de la instruccion se retorna 0 inmediatamente
                if (contarPosicionesConsecutivas(vector, 1, aux, 5) != instruccion[0])
                {
                    return 0;
                }
                //Si la cantidad de 1 es igual a la instruccion[0] pasa lo siguiente
                else
                {
                    //Se cuenta la cantidad de 0 que hay entre la primera cantidad de 1 la segunda cantidad de 1 y se guarda en aux2
                    aux2 = contarPosicionesConsecutivas(vector, 0, aux + instruccion[0], 5);
                    //si esa distancia es nula se retorna 0, ya que se debe tener al menos un espacio sin perforar
                    if (aux2 == 0)
                    {
                        return 0;
                    }
                    //Si es distinto a 0, pasa lo siguiente
                    else
                    {
                        //Se cuenta la cantidad de 1 consecutivos en vector desde la ultima posicion que se contó.
                        //Si es igual a instruccion[1] se devuelve 1, sino se retorna 0
                        if (contarPosicionesConsecutivas(vector, 1, aux + aux2 + instruccion[0], 5) == instruccion[1])
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                }
                break;

            //En caso de que el vector comience por 1 pasa lo siguiente
            case 1:
                //Se cuenta la cantidad de 1 consecutivos en el vector desde el inicio y se compara con la instruccion[0]
                //Si son distintos retorna inmediatamente 0
                if (contarPosicionesConsecutivas(vector, 1, 0, 5) != instruccion[0])
                {
                    return 0;
                }

                //Si son iguales pasa lo siguiente
                else
                {
                    //Se cuenta la cantidad de 0 que hay entre la primera cantidad de 1 y la segunda cantidad de 1 del vector y se guarda en aux
                    aux = contarPosicionesConsecutivas(vector, 0, instruccion[0], 5);
                    //si esa distancia es nula se retorna 0, ya que se debe tener al menos un espacio sin perforar
                    if (aux == 0)
                    {
                        return 0;
                    }
                    //Si es distinto a 0, pasa lo siguiente
                    else
                    {
                        //Se cuenta la cantidad de 1 consecutivos en vector desde la ultima posicion que se contó.
                        //Si es igual a instruccion[1] se devuelve 1, sino se retorna 0
                        if (contarPosicionesConsecutivas(vector, 1, instruccion[0] + aux, 5) != instruccion[1])
                        {
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
                break;
            }
            break;
        }
    }
    return 0;
}

//----------------------------------

//Entrada:un archivo y una matriz de 5*5 representada por un array de array de enteros donde se guardaran las soluciones leidas del archivo
//Salida: no entrega
//Funcion: Lee una linea de un archivo y guarda sus numeros en la matriz

void leerSoluciones(FILE *archivo, int **matriz)
{
    char aux;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fscanf(archivo, "%c", &aux);
            if (isdigit(aux) != 0)
            {
                matriz[i][j] = aux - '0';
            }
            else
            {
                j--;
            }
        }
    }
}

//----------------------------------

//Entrada:Una matriz de 5*5 que es una posible solucion, una lista con las instrucciones de las filas y una lista con las instrucciones para las columnas
//Salida: un entero, un 1 si cumple y un 0 si no cumple
//Funcion: verifica que una posible solucion cumpla con las restricciones de las filas y columnas

int verificarSolucion(int **matriz, int **instruccionesFilas, int **instruccionesColumnas)
{
    int contador = 0;
    int *filaAuxiliar = (int *)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; i++)
    {
        if (verificarInstruccion(matriz[i], instruccionesFilas[i]) == 1)
        {
            contador++;
        }
    }
    if (contador == 5)
    {
        contador = 0;
        for (int i = 0; i < 5; i++)
        {
            filaAuxiliar[0] = matriz[0][i];
            filaAuxiliar[1] = matriz[1][i];
            filaAuxiliar[2] = matriz[2][i];
            filaAuxiliar[3] = matriz[3][i];
            filaAuxiliar[4] = matriz[4][i];
            if (verificarInstruccion(filaAuxiliar, instruccionesColumnas[i]))
            {
                contador++;
            }
        }
        if (contador == 5)
        {
            free(filaAuxiliar);
            return 1;
        }
    }
    free(filaAuxiliar);
    return 0;
}

//----------------------------------

//Entrada: una matriz de 5*5 que representa una solucion, una estructura del tipo matriz que tiene las instrucciones de las filas
//         una estructura del tipo matriz que tiene las instrucciones de las columnas
//Salida: no entrega
//Funcion: Imprime por consola la solucion entrega en la entrada

void mostrarSolucion(int **solucion, matriz filas, matriz columnas)
{
    char fila[150];
    printf("    | ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d%d | ", columnas.filas[i][0], columnas.filas[i][1]);
    }
    printf("\n------------------------------\n");
    for (int i = 0; i < 5; i++)
    {
        strcpy(fila, "");
        for (int j = 0; j < 5; j++)
        {
            if (solucion[i][j] == 1)
            {
                strcat(fila, "▣");
            }
            else
            {
                strcat(fila, "□");
            }
            strcat(fila, "  | ");
        }
        printf(" %d%d | %s\n------------------------------\n", filas.filas[i][0], filas.filas[i][1], fila);
    }
}