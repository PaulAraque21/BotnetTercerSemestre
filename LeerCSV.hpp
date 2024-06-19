/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

LeerCSV.hpp
*/

#ifndef LeerCSV_hpp
#define LeerCSV_hpp

#include <vector>
#include <string>
#include <algorithm>
#include "Entradas.hpp"
using namespace std;

//Declaración de función "LeerCSV" que toma como referencia constante un string como argumento y devuelve un vector de objetos "Entradas". Esta función se encarga de leer un archivo CSV y guardar los registros en un vector "Entradas"
vector<Entradas> LeerCSV(const string& nombreArchivo);

#endif
