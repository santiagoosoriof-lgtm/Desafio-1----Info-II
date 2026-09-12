#include "tablero.h"
#include <iostream>
using namespace std;


/* Aqui se definen todas las funciones que gestionaran el tablero del juego (creacion y destruccion)
 * tambien las funciones de creacion y modificacion de las fichas*/

// Funcion para crear el tablero e inicializarlo
unsigned char* crear_tablero(int filas, int columnas, int &bytes_reservados){
    //formula para calcular los bytes necesartios para crear el tablero
    bytes_reservados = (3 * filas * columnas + 7) /8;

    // creacion del arreglo dinamico para el tablero
    unsigned char* tablero = new unsigned char[bytes_reservados];

    // se inicializan los valores del arreglo en 0
    for(int i = 0; i < bytes_reservados; i++){
        tablero[i]= 0b00000000;
    }
    return tablero;
}

// Funcion para determinar la posicion de una ficha dentro del board dinamico

unsigned char get_ficha(const unsigned char* tablero, int columnas, int fila, int columna){
    // Formulas de mapeo
    int indice = (fila * columnas) + columna;  //encontramos el indice de la ficha en bits segun la posicion matricial de la ficha
    int bit_inicio = indice * 3;   //bit donde inicia la ficha
    int byte_N = bit_inicio / 8;   // identificamos el numero del byte donde estamos almacenando la ficha
    int desplazamiento = bit_inicio % 8;  // identificamos si hay problema de frontera entre bits

    unsigned char ficha_aislada = 0;
    //Aislamiento de una ficha si esta en un solo byte o entre dos bytes
    if(desplazamiento >=0 && desplazamiento <= 5){
        // caso 1 : ficha dentro de un solo byte
        ficha_aislada = (tablero[byte_N] >> desplazamiento) & 0x007; // desplazo los bits hacia la izquieda del byte y luego le aplico una mascara para aislar los 3 bites que me interesan
    } else if(desplazamiento == 6){
        //Caso 2 : Ficha separada 2 bits en byte N y 1 en byte N+1
        unsigned char parte1 = (tablero[byte_N] >>6) ; // mando los dos primeros bits de la ficha a las posiciones 0 y 1 del byte quedan aislados
        unsigned char parte2 = (tablero[byte_N + 1] << 2) & 0x007 ;//  mando el bit separado a la posicion 2 del byte y se aplica mascara para aislarlo
        ficha_aislada = parte1 | parte2;  //Uno las dos partes en un solo byte y tenemos la ficha aislada
    } else if(desplazamiento == 7){
        //Caso 3 : Ficha separada 1 bits en byte N y 2 en byte N+1
        unsigned char parte1 = tablero[byte_N] >> 7; // mando al primer bit de la ficha a la posicion 0 del byte y queda aislado
        unsigned char parte2 = (tablero[byte_N + 1] << 1) & 0x007;   //mando los dos ultimos bits de la ficha a las posiciones 2 y 1 del byte, se aplica mascara para aislarlos
        ficha_aislada = parte1 | parte2;  //Uno las dos partes en un solo byte y tenemos la ficha aislada
    }
    return ficha_aislada;

}

// Funcion para modificar el valor de una ficha
void set_ficha(unsigned char* tablero, int columnas, int fila, int columna, unsigned char nuevo_valor){
    // Formulas de mapeo
    int indice = (fila * columnas) + columna;  //encontramos el indice de la ficha en bits segun la posicion matricial de la ficha
    int bit_inicio = indice * 3;   //bit donde inicia la ficha
    int byte_N = bit_inicio / 8;   // identificamos el numero del byte donde estamos almacenando la ficha
    int desplazamiento = bit_inicio % 8;  // identificamos si hay problema de frontera entre bits

    // verificacion que la ficha ingresada solo tenga 3 bits
    nuevo_valor &= 0x07;

    if(desplazamiento >=0 && desplazamiento <= 5){
        // caso 1 : ficha dentro de un solo byte
        unsigned char limpiar = ~(0x007<<desplazamiento);
        unsigned char byte_limpio = tablero[byte_N] & limpiar;
        unsigned char nuevo_despl = nuevo_valor<<desplazamiento;
        tablero[byte_N] = byte_limpio | nuevo_despl;

    } else if(desplazamiento == 6){
        //Caso 2 : Ficha separada 2 bits en byte N y 1 en byte N+1
        unsigned char nuevo_n = nuevo_valor << 6;  // desplazamos los bits de la ficha nueva a la posicion de la ficha original en el byte N
        unsigned char nuevo_n1 = nuevo_valor >> 2;  // desplazamos los bits de la ficha nueva a la posicion de la ficha original en el byte N+1
        unsigned char byte_nlimpio = tablero[byte_N] & ~(0xC0); // aplico una mascara para poner en 0 los bits de la ficha original en byte N
        unsigned char byte_n1limpio = tablero[byte_N+1] & ~(0x01);  // aplico una mascara para poner en 0 el bit de la ficha original en byte N+1
        tablero[byte_N] = byte_nlimpio | nuevo_n; // agrego el nuevo valor al byte N
        tablero[byte_N+1] = byte_n1limpio | nuevo_n1; //agrego el nuevo valor al byte N+1

    } else if(desplazamiento == 7){
        //Caso 3 : Ficha separada 1 bits en byte N y 2 en byte N+1
        unsigned char nuevo_n = nuevo_valor << 7;  // desplazo los bits de la ficha nueva a la posicion de la ficha original en el byte N
        unsigned char nuevo_n1 = nuevo_valor >> 1;  // desplazo los bits de la ficha nueva a la posicion de la ficha original en el byte N+1
        unsigned char byte_nlimpio = tablero[byte_N] & ~(0x80); // aplico una mascara para poner en 0 el bit de la ficha original en byte N
        unsigned char byte_n1limpio = tablero[byte_N+1] & ~(0x03);  // aplico una mascara para poner en 0 los bits de la ficha original en byte N+1
        tablero[byte_N] = byte_nlimpio | nuevo_n; // agrego el nuevo valor al byte N
        tablero[byte_N+1] = byte_n1limpio | nuevo_n1; //agrego el nuevo valor al byte N+1

    }

}

// Funcion para destruir la informacion dentro de la tabla
void destruir_tablero(unsigned char* &tablero){
    if(tablero != nullptr){
        delete[] tablero;
        tablero = nullptr;
    }
}