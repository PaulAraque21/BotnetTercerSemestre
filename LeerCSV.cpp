/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

LeerCSV.cpp
*/

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
//#include "Entradas.hpp"
#include "LeerCSV.hpp"

//Implementación de función "LeerCSV" que toma el nombre del archivo CSV como entrada y devuelve un vector de objetos "Entradas". Esta función lee el archivo línea por línea, divide cada línea en campos y crea objetos "Entradas" con estos datos de cada línea. Luego estos objetos sse agregan a vector "EntradasV" que se devuelve al final de la función 
vector<Entradas> LeerCSV(const string &nombreArchivo)
{
    // Función para leer archivo y almacenar registros en un vector
    // Declaración de vector llamado "EntradasV" que guarda objetos en "Entradas", este vector se usa para guardar las entradas de la bitácora
    vector<Entradas> EntradasV;
    // Objeto tipo ifstream llamado "file" que sirve para abrir y leer archivo llamado "bitacora.csv"
    ifstream file(nombreArchivo);
    // Declarar un string llamado "line" que se usa para leer cada línea del archivo CSV
    string line;
    // Ciclo while que se ejecutará mientras haya líneas por leer en archivo CSV. Cada línea se guardará en string "line"
    while (getline(file, line))
    {
        // Objeto tipo istringstream llamado "coma" se usa para dividiar la línea leída en los campos correspondientes utilizando comas
        istringstream coma(line);
        // Declaración de variables para guardar los valores de cada campo
        string fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino;
        //"getline" sirve para dividir la línea en campos, se extrae cada campo como por ejemplo la fecha y se separa por comas de los tros campos.
        if (getline(coma, fecha, ',') && getline(coma, hora, ',') && getline(coma, ipOrigen, ',') &&
            getline(coma, puertoOrigen, ',') && getline(coma, nombreOrigen, ',') &&
            getline(coma, ipDestino, ',') && getline(coma, puertoDestino, ',') &&
            getline(coma, nombreDestino))
        {
            // Se crea objeto de "Entradas" y los valores (Entradas(fecha, hora, etc...) se agregan al final del vector "EntradasV" utilizando push_back.
            Entradas registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino);
            EntradasV.push_back(registro);
        }
        else
        {
            cout << "Error al leer línea" << endl;
        }
    }
    file.close();
    // Ordenar registros por fecha en orden ascendente
    sort(EntradasV.begin(), EntradasV.end(), [](const Entradas &a, const Entradas &b)
         { return a.getFecha() < b.getFecha(); });
    return EntradasV;
}

