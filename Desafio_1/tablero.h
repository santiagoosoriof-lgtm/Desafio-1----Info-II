#ifndef TABLERO_H
#define TABLERO_H

// Reservamos la memoria que se necesita para el Tablero y la inicializamos en 0
unsigned char* crear_tablero(int filas, int columnas, int &bytes_reservados);

// Funcion para extraer los 3 bits de una ficha en una coordenada (fila, columna)
unsigned char get_ficha(const unsigned char* tablero, int filas, int columnas, int fila, int columna);

// Funcion para modificar los 3 bits de una ficha en una coordenada (fila, columna)
void set_ficha(unsigned char* tablero, int filas, int columnas, int fila, int columna, unsigned char nuevo_valor);

// funcion para destruir el tablero y liberar la memoria
void destruir_tablero(unsigned char* &tablero);

#endif // TABLERO_H
