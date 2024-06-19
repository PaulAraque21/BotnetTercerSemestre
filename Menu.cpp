/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

Menu.cpp
*/

#include <iostream>
#include <set>
#include <algorithm>
#include "Menu.hpp"
using namespace std;

// FUNCIÓN PARA BUSCAR SEGUNDO DÍA
// Implementación de función "BuscarSegundoDia".
string BuscarSegundoDia(const vector<Entradas> &registros)
{
    // Verificar si el vector "registros" tiene menos de dos elementos. Si es asó, significa que no hay suficientes registros para determinar un segundo día, por lo que devuelve un error
    if (registros.size() < 2)
    {
        return "No hay suficientes registros para determinar el segundo día";
    }
    // Se crea una copia del vector "registros" llamada "registrosOrdenados". Hacemos esto para no cambiar el vector original durante el proceso de clasificación
    vector<Entradas> registrosOrdenados = registros;
    // Se usa la función sort() para ordenar el vector "registrosOrdenados" en orden ascendente.
    sort(registrosOrdenados.begin(), registrosOrdenados.end());
    // Se obtiene la fecha del primer registro en el vector ordenado y se guarda en la variable "primerDia"
    string primerDia = registrosOrdenados[0].getFecha();
    // Se declara cadena vacía llamada "segundoDia" para almacenar la fecha del segundo día registrado
    string segundoDia = "";
    // Agregamos un contador para contar los registros del segundo día
    int contadorSegundoDia = 0;
    // Se inicia ciclo "for" que recorre cada registro en el vector ordenado
    for (const Entradas &registro : registrosOrdenados)
    {
        // Se verifica si la fecha del registro actual es diferente de la fecha del primer registro. Si es diferente significa que se enontro el segundo día
        if (registro.getFecha() != primerDia)
        {
            // Se asigna la fecha del registro actual a la variable "segundoDia"
            segundoDia = registro.getFecha();
            // Usamos "break" para salir del ciclo una ves que se haya encontrado el segundo día.
            break;
        }
    }
    // Después del ciclo, se verifica si "segundoDia" todavía está vacía. Si si, significa que no se encontró un segundo día diferente al primero, entonces omite este paso.
    if (segundoDia.empty())
    {
        // No se encontró un segundo día diferente al primero;
        return "No se encontró un segundo día diferente al primero";
    }
    else
    {
        // Contar cuántos regustros tienen la fecha del segundo día
        for (const Entradas &registro : registrosOrdenados)
        {
            if (registro.getFecha() == segundoDia)
            {
                contadorSegundoDia++;
            }
        }
        // Se devuelve la fecha del segundo día y la cantidad de registros de ese día
        return "Segundo día registrado: " + segundoDia + ". Cantidad de registros: " + to_string(contadorSegundoDia);
    }
    return "No se encontró un segundo día diferente al primero";
}

// FUNCIÓN PARA BUSCAR NOMBRES
void buscarNombre(const vector<Entradas> &nombres)
{
    // Crear vector para guardar los nombres
    vector<string> nombresCompus;
    for (const Entradas &entrada : nombres)
    {
        // Adicionar al nuevo vector el NombreOrigen
        nombresCompus.push_back(entrada.getNombreOrigen());
    }
    for (string &nom : nombresCompus)
    {
        // Encontrar la posición del punto "." en el nombre
        int dotPosition = nom.find('.');
        // Si find('.') no encontró ningún punto, devuelve "npos"
        if (dotPosition != string::npos)
        {
            // Al vector nombresCompus, restare en cada valor el texto después del primer punto
            nom = nom.substr(0, dotPosition);
        }
    }

    bool jeffrey = false, betty = false, katherine = false, scott = false, benjamin = false, samuel = false, raymond = false;
    // Si el programa encuentra un nombre en el nuevo vecotr, cambiar su variable a true
    for (string &nom : nombresCompus)
    {
        if (nom == "jeffrey")
        {
            jeffrey = true;
        }
        else if (nom == "betty")
        {
            betty = true;
        }
        else if (nom == "katherine")
        {
            katherine = true;
        }
        else if (nom == "scott")
        {
            scott = true;
        }
        else if (nom == "benjamin")
        {
            benjamin = true;
        }
        else if (nom == "samuel")
        {
            samuel = true;
        }
        else if (nom == "raymond")
        {
            raymond = true;
        }
    }

    // Imprimir si una computadora pertenece a Jeffrey
    if (jeffrey == true)
    {
        cout << "Una de las computadoras sí pertenece a Jeffrey." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Jeffrey." << endl;
    }

    // Imprimir si una computadora pertenece a Betty
    if (betty == true)
    {
        cout << "Una de las computadoras sí pertenece a Betty." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Betty." << endl;
    }

    // Imprimir si una computadora pertenece a Katherine
    if (katherine == true)
    {
        cout << "Una de las computadoras sí pertenece a Katherine." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Katherine." << endl;
    }

    // Imprimir si una computadora pertenece a Scott
    if (scott == true)
    {
        cout << "Una de las computadoras sí pertenece a Scott." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Scott." << endl;
    }

    // Imprimir si una computadora pertenece a Benjamin
    if (benjamin == true)
    {
        cout << "Una de las computadoras sí pertenece a Benjamin." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Benjamin." << endl;
    }

    // Imprimir si una computadora pertenece a Samuel
    if (samuel == true)
    {
        cout << "Una de las computadoras sí pertenece a Samuel." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Samuel." << endl;
    }

    // Imprimir si una computadora pertenece a Raymond
    if (raymond == true)
    {
        cout << "Una de las computadoras sí pertenece a Raymond." << endl;
    }
    else
    {
        cout << "Ninguna de las computadoras pertenece a Raymond." << endl;
    }
}

// FUNCIÓN PARA BUSCAR DIRECCIÓN INTERNA
// Implementación de la función "EsDireccionRedInterna" que checa si una dirección IP empieza con 172.17. Regresa "true" si es una direccipon de red interna.
bool EsDireccionRedInterna(const string &direccionIp)
{
    // Comprueba si la dirección IP comienza con "172.17"
    return direccionIp.find("172.17") == 0;
}

// Implementación de función "EncontrarDireccionRedInterna" que busca la dirección de red interna en los registros. Itera a través de los registros, checa si alguna dirección IP coincide con el patrón de red iterna utilizando "EsDireccionRedInterna". Si coincide, remueve últimos dos gígitos de la IP de origen y asigna la dirección de red interna a "direccionRedInterna" y devuelve este string
string EncontrarDireccionRedInterna(const vector<Entradas> &registros)
{
    string direccionRedInterna; // Esta variable guarda la dirección de la red interna

    for (const Entradas &entrada : registros)
    {
        string ipOrigen = entrada.getIPOrigen();
        string ipDestino = entrada.getIPDestino();

        // Verificar si IP coincide con el patrón de red interna
        if (EsDireccionRedInterna(ipOrigen) || EsDireccionRedInterna(ipDestino))
        {
            // Remover los últimos dos dígitos de la IP de origen y establecer la dirección de red interna
            size_t found = ipOrigen.rfind('.');
            if (found != string::npos)
            {
                string parteInicial = ipOrigen.substr(0, ipOrigen.rfind('.')); // Remover los últimos dos dígitos
                direccionRedInterna = parteInicial + ".00";                    // Asignar la dirección de red interna
                break;                                                         // Se detiene la búsqueda al encontrar la primera IP de la red interna
            }
        }
    }
    return direccionRedInterna;
}

// FUNCIÓN PARA CONTAR LOS REGISTROS CON NOMBRES
// Implementación de la función "ContarRegistrosConNombre" que cuenta los registros con nombre específico en los registros proporcionados. El contador aumenta cada ves que se encuentra una coincidencia.
int ContarRegistrosConNombre(const vector<Entradas> &registros, const string &nombreBuscado)
{
    int contador = 0;

    for (const Entradas &entrada : registros)
    { // Ciclo for para recorrer cada elemento de vector "registros", itera a través de los objetos "Entradas" en "registros" y "entrada"
        // Verificar nombre de destino o nombre de origen con objeto "entrada" coincide con el "nombreBuscado"
        if (entrada.getNombreDestino() == nombreBuscado || entrada.getNombreOrigen() == nombreBuscado)
        {
            contador++;
        }
    }
    return contador;
}

// FUNCIÓN PARA BUSCAR LOS NOMBRES DESTINO
void buscarNombreDestino(const vector<Entradas> &nombres)
{
    // Crear vector para guardar los nombres
    vector<string> nombresDestino;
    for (const Entradas &entrada : nombres)
    {
        // Adicionar al nuevo vector el NombreDestino
        nombresDestino.push_back(entrada.getNombreDestino());
    }
    // Crear un nuevo vector para eliminar todos aquellos nombres que se repitan
    vector<string> nombresDestinoFinal;
    for (const string &nombres_ : nombresDestino)
    {
        /* Encontrar nombres_ desde el principio del rango del vector hasta el final del
        range del vector. Si no encuentra nombres_, la función devuelve el último iterador,
        por lo que tenemos que añadir nombres_ al nuevo vector
         */
        if (std::find(nombresDestinoFinal.begin(), nombresDestinoFinal.end(), nombres_) == nombresDestinoFinal.end())
        {
            nombresDestinoFinal.push_back(nombres_);
        }
    }
    cout << "Los servicios de correo electrónico que se utilizan son: " << endl;
    // Imprimir nombresDestinoFinal
    for (const string &element : nombresDestinoFinal)
    {
        if (element != "-")
        {
            // Imprimir solo si coincide con alguno de estos 4 nombres
            if (element == "gmail.com" || element == "hotmail.com" || element == "outlook.com" || element == "protonmail.com")
            {
                cout << element << endl;
            }
        }
    }
}

// FUNCIÓN PARA ENCONTRAR PUERTOS DESTINO
// Definición de función "ListarPuertosDestinoAbajo1000". La función toma un parámetro que es una referencia constante a un vector de objetos "Entradas" llamado "registros".
void ListarPuertosDestinoAbajo1000(const vector<Entradas> &registros)
{
    cout << "Puertos de destino por debajo de 1000:" << endl;
    // Conjunto para llevar un registro de los puertos ya impresos
    set<int> puertosImpresos;
    // Inicio de ciclo "for" que recorre todos los elementos del vector "registros". Cada elemento se almacena en la variable "entrada" que de tipo "Entradas" y el ciclo se ejecuta una ves por cada elemento del vector
    for (const Entradas &entrada : registros)
    {
        // Se obtiene el valor del pierto de destino de la entrada actual "entrada". Luego se convierte ese valor a un entero y se almacena en variable "puertoDestino"        int puertoDestino = stoi(entrada.getPuertoDestino());
        if (entrada.getPuertoDestino() != "-")
        {
            int puertoDestino = stoi(entrada.getPuertoDestino());
            // Checar si puertoDestino es menor que 1000 y si no ha sido impreso
            if (puertoDestino < 1000 && puertosImpresos.find(puertoDestino) == puertosImpresos.end())
            {
                cout << puertoDestino << endl;
                // Agregamos el puerto encontrado a los puertosImpresos
                puertosImpresos.insert(puertoDestino);
            }
        }
    }
}
