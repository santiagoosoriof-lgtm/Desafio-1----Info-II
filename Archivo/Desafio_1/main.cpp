#include <iostream>
#include "tablero.h"
using namespace std;

/* Aqui se escribira el codigo para la interfaz en consola
 *  y se llamaran todas las funciones creadas para que el juego funcione correctamente
 por el momento aqui haremos las pruebas de depuracion de las funciones que vayamos creando*/

int main() {
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

    // crear funcion de visualizacion de la matriz para validar que la logica del guardado de la matriz sea correcta


    // Destrucción del tablero para limpiar memoria
    destruir_tablero(mi_tablero);

    return 0;
}
