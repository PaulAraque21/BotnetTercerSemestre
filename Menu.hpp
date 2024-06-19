/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

Menu.hpp
*/

#ifndef Menu_hpp
#define Menu_hpp

#include <iostream>
#include "LeerCSV.hpp"
using namespace std;

// FUNCIÓN PARA BUSCAR SEGUNDO DÍA
// Declaración de función #BuscarSegundoDia" que toma un argumenta, que ees referencia constante a un vector de objetos "Entradas".
string BuscarSegundoDia(const vector<Entradas> &registros);

// FUNCIÓN PARA BUSCAR NOMBRES
void buscarNombre(const vector<Entradas> &nombres);

// BUSCAR DIRECCION INTERNA
// Declaración de la función EsDireccionRedInterna que toma una referencia constante a un string como argumento y devuelve un bool. Esta función verifica si una dirección IP es una dirección de red interna
bool EsDireccionRedInterna(const string &direccionIp);
// Declaración de función "EncontrarDireccionRedInterna" que toma una referencia constante a un vector de objetos "Entradas" y devuelve un string. Esta función busca y devuelve la dirección de red interna en los registros.
string EncontrarDireccionRedInterna(const vector<Entradas> &registros);

// FUNCIÓN PARA CONTAR REGISTROS CON NOMBRES
// Declaración de función "ContarRegistrosConNombre" que toma una referencia constante a un vector de objetos "Entradas" y un string "nombreBuscado" y devuelve un int. Esta función cuenta los registros que tienen el nombre buscado (tanto en el campo "Nombre Origen" como en "Nombre Destino") y devuelve el conteo.
int ContarRegistrosConNombre(const vector<Entradas> &registros, const string &nombreBuscado);

// FUNCIÓN PARA BUSCAR LOS NOMBRES DESTINO
void buscarNombreDestino(const vector<Entradas> &nombres);

// FUNCIÓN PARA ENCONTRAR PUERTOS DESTINO POR DEBAJO DE 1000
// Declaración de función "LisrarPuertosDestinoAbajo1000" que no devuelve ningún valor y toma como parámetro, que es un vector de objetos "Entradas" llamado "registros"
void ListarPuertosDestinoAbajo1000(const vector<Entradas> &registros);

#endif
