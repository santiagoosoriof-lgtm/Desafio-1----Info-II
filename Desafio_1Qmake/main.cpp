#include <iostream>
#include "tablero.h"
using namespace std;

/* Aqui se escribira el codigo para la interfaz en consola
 *  y se llamaran todas las funciones creadas para que el juego funcione correctamente
 por el momento aqui haremos las pruebas de depuracion de las funciones que vayamos creando*/

int main() {
    int filas1 = 0, columnas1 = 0, bytes_reservados = 0;

    cout << "++++++++++++++++++ BIENVENIDO AL JUEGO +++++++++++++++++\n" <<
            "               Desafio 1 - Informatica II               \n" <<
            "                      Integrantes :                     \n" <<
            "               Santiago Osorio Fernandez                \n" <<
            "               Juan Jose Guarin Atehortua               \n" <<
            "\n"<<
            "                Universidad de Antioquia                \n" <<
            "                        2026-2                          \n" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
            "                       SWEET CRUSH                      \n" <<
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" << endl;

    // Ciclo de verificacion de ingreso de las dimensiones de la matriz
    do{
    cout << "Por favor ingresa el tamanio del tablero de juego : \n"
         << "Numero de filas: " << endl;
    cin >> filas1;

    cout << "Numero de Columnas: " << endl;
    cin >> columnas1;

        if(filas1 <= 0 || columnas1 <= 0){
        cout << "ERROR : El valor de las filas o columnas debe ser mayor a cero" << endl;
        }else if(filas1 >= 50 || columnas1 >= 50) {
        cout << "ERROR : El valor de las filas o columnas es demasiado grande para mostrar en pantalla" << endl;
        }
    } while(filas1 <= 0 || columnas1 <= 0 || filas1 >= 50 || columnas1 >= 50);
    cout << "El tablero de " << filas1 << " filas y " << columnas1 << "  ha sido creado : \n"
         <<"\n"<<endl;

    unsigned char* tablero = crear_tablero(filas1, columnas1, bytes_reservados);

    // Agregar las fichas al tablero

    // Imprimir el tablero en Fichas y en binario

    // Opciones de Juego
    int opcion = 0;
    cout << "+++++++++++++++ Elija una de las siguientes opciones +++++++++++++++ \n"
         << "\n"
         << "                  1. Eliminar una ficha.\n"
         << "                  2. Agregar una nueva fila.\n"
         << "                  3. Eliminar una fila existente.\n"
         << "                  4. Agregar una nueva columna.\n"
         << "                  5. Eliminar una columna existente.\n"
         << "                  6. Salir del juego. \n" <<endl;
    cin >> opcion;

    // seleccion de la acion a realizar
    switch (opcion){
    case 1 :
    case 2 :
    case 3 :
    case 4 :
    case 5 :
    case 6 :
        // Destrucción del tablero para limpiar memoria
        destruir_tablero(tablero);
        }



    return 0;
}



/*
 *
 *
    // Simulamos un tablero estándar de 3 filas y 4 columnas (12 fichas totales)
    int filas = 3;
    int columnas = 4;
    int bytes_reservados = 0;

    unsigned char* mi_tablero = crear_tablero(filas, columnas, bytes_reservados);

    // Inyectamos valores manuales en la memoria para forzar los desalineamientos
    // Cada byte representa combinaciones reales de fichas empaquetadas
    if (bytes_reservados >= 5) {
        mi_tablero[0] = 0b10001000; // Letras ABCDEF repetidas
        mi_tablero[1] = 0b11000110; //
        mi_tablero[2] = 0b00100010; //
        mi_tablero[3] = 0b00011010; //
        mi_tablero[4] = 0b00001011; // Bloque final de ceros (bits inválidos a la izquierda)
    }

    // crear funcion de visualizacion de la matriz para validar que la logica del guardado de la matriz sea correcta, el get y el set



    // Destrucción del tablero para limpiar memoria
    destruir_tablero(mi_tablero);

    return 0;
}
*/
