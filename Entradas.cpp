/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

Entradas.cpp
*/

#include "Entradas.hpp"
using namespace std;

// Implementación de constructor de la clase "Entradas", inicializa argumentos de objeto "Entradas" con valores dados
// Parámetros son los valores usados para establecer los campos privados de clase "Entradas"
Entradas::Entradas(const string &fecha, const string &hora, const string &ipOrigen,
                   const string &puertoOrigen, const string &nombreOrigen,
                   const string &ipDestino, const string &puertoDestino,
                   const string &nombreDestino)
    // Inicialización para asignar valores de los parámetros privados de la clase. (Los parámetros privados son los que tienen "_" al final.)
    : fecha_(fecha), hora_(hora), ipOrigen_(ipOrigen), puertoOrigen_(puertoOrigen),
      nombreOrigen_(nombreOrigen), ipDestino_(ipDestino), puertoDestino_(puertoDestino),
      nombreDestino_(nombreDestino)
{
}
// Métodos públicos que nos permiten acceder a los campos privados de la clase. Cada uno de estos métodos devuelve el valor correspondiente de uno de los campos privados.
string Entradas::getFecha() const
{
    return fecha_;
}

string Entradas::getHora() const
{
    return hora_;
}

string Entradas::getIPOrigen() const
{
    return ipOrigen_;
}

string Entradas::getPuertoOrigen() const
{
    return puertoOrigen_;
}

string Entradas::getNombreOrigen() const
{
    return nombreOrigen_;
}

string Entradas::getIPDestino() const
{
    return ipDestino_;
}

string Entradas::getPuertoDestino() const
{
    return puertoDestino_;
}

string Entradas::getNombreDestino() const
{
    return nombreDestino_;
}

//Sobrecarga de operador "<", nos permite comparar objetos de la clase "Entradas". En este caso la comparación se realiza en función de la fecha de otro objeto, la función regresa "true", lo que nos permite ordenar los objetos "Entradas" por fecha 
bool Entradas::operator<(const Entradas &other) const
{
    return fecha_ < other.fecha_;
}
