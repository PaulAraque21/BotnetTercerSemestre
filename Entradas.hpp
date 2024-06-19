/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

Entradas.hpp
*/

#ifndef Entradas_hpp
#define Entradas_hpp

#include <iostream>
#include <string>
using namespace std;

//Definición de clase "Entradas" la cuál representa un registro en la bitácora de registros (el archivo .csv)
class Entradas
{
private:
    // Guarda los datos de la bitácora. Privado para que solo se puedan acceder dentro de la clase "Entradas"
    string fecha_;
    string hora_;
    string ipOrigen_;
    string puertoOrigen_;
    string nombreOrigen_;
    string ipDestino_;
    string puertoDestino_;
    string nombreDestino_;

public:
    // Constructor que toma 8 argumentos como entrada, (uno para cada campo de la entrada de la bitácora) para poder inicializar un objeto "Entradas" con los valores proporcionados
    Entradas(const string &fecha, const string &hora, const string &ipOrigen,
             const string &puertoOrigen, const string &nombreOrigen,
             const string &ipDestino, const string &puertoDestino,
             const string &nombreDestino);
    // Métodos para acceder a los campos, obtener los valores de estos campos fuera de la clase
    string getFecha() const;
    string getHora() const;
    string getIPOrigen() const;
    string getPuertoOrigen() const;
    string getNombreOrigen() const;
    string getIPDestino() const;
    string getPuertoDestino() const;
    string getNombreDestino() const;
    //Sobrecarga del operador "<", nos permite comparar objetos "Entradas" entre sí. Esto se usa para ordenar los registros por fecha
    bool operator<(const Entradas &other) const;
};

#endif
