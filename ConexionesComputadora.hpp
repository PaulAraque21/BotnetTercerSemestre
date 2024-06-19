/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 1.3

ConexionesComputadora.hpp
*/

#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include <iostream>
#include <map>
#include "Menu.hpp"
#include "Stack.hpp"
#include "BST.hpp"

template <class T>
class ConexionesComputadora
{
private:
    string ip = "";
    string nombre = "";
    Stack<T> *conexionesEntrantes = new Stack<T>();
    LinkedList<T> *conexionesSalientes = new LinkedList<T>();

public:
    /* Constructores */
    ConexionesComputadora() = default;
    ConexionesComputadora(string _ip) : ip(_ip){};

    /* COnstructor de copias */
    ConexionesComputadora(const ConexionesComputadora &otra) : ip(otra.ip), nombre(otra.nombre), conexionesEntrantes(new Stack<T>(*otra.conexionesEntrantes)), conexionesSalientes(new LinkedList<T>(*otra.conexionesSalientes)){};

    /* Destructor */
    ~ConexionesComputadora();

    /* Getters */
    Stack<T> *getConexionesEntrantes() { return conexionesEntrantes; };
    LinkedList<T> *getConexionesSalientes() { return conexionesSalientes; };

    /* Asignar nombre */
    void asignarNombre(const vector<Entradas> &);

    /* Agregar las conexiones */
    void agregarEntrantes(const T &);
    void agregarSalientes(const T &);
    void completarConexiones(const vector<Entradas> &);

    /* Otras funciones */
    int entrantesTotal();
    int salientesTotal();
    T ultimoEntrante();
    void tresConexionesConsecutivas(const vector<Entradas> &);

    /* Operadopr de asignación */
    ConexionesComputadora &operator=(const ConexionesComputadora &);
};

/* Destructor */
template <class T>
ConexionesComputadora<T>::~ConexionesComputadora()
{
    delete conexionesEntrantes;
    delete conexionesSalientes;
}

/* Asignar nombre */
template <class T>
void ConexionesComputadora<T>::asignarNombre(const vector<Entradas> &entradas)
{
    for (const Entradas &entrada : entradas)
    {
        if (entrada.getIPOrigen() == ip)
        {
            nombre = entrada.getNombreOrigen();
            break;
        }
        else if (entrada.getIPDestino() == ip)
        {
            nombre = entrada.getNombreDestino();
            break;
        }
    }
    if (nombre.empty())
    {
        nombre = "No Existe";
    }
}

/* Función para agregar entrantes utilizando push() de Stack */
template <class T>
void ConexionesComputadora<T>::agregarEntrantes(const T &entrante)
{
    conexionesEntrantes->push(entrante);
}

/* Función para agregar salientes utilizando insert_back() de LinkedList */
template <class T>
void ConexionesComputadora<T>::agregarSalientes(const T &saliente)
{
    conexionesSalientes->insert_back(saliente);
}

/* Se utiliza vector<Entradas> para poder utilizar las funciones de Entradas como getIPOrigen, etc */
template <class T>
void ConexionesComputadora<T>::completarConexiones(const vector<Entradas> &conexiones)
{
    /* Comparar que el IPOrigen o IPDestino sea igual al ingresado por el usuario */
    for (const auto &conexion : conexiones)
    {
        if (conexion.getIPOrigen() == ip)
        {
            agregarSalientes(conexion.getIPDestino());
        }
        else if (conexion.getIPDestino() == ip)
        {
            agregarEntrantes(conexion.getIPOrigen());
        }
    }
}

/* Función para calcular el tamaño de cnexionesSalientes */
template <class T>
int ConexionesComputadora<T>::salientesTotal()
{
    return conexionesSalientes->size();
}

/* Función para calcular el tamaño de cnexionesEntrantes */
template <class T>
int ConexionesComputadora<T>::entrantesTotal()
{
    return conexionesEntrantes->size();
}

/* Función para obtener el último entrante */
template <class T>
T ConexionesComputadora<T>::ultimoEntrante()
{
    return conexionesEntrantes->top();
}

/* Función para verificar si la ip ingresada por el usuario tienen tres conexiones consecutivas a sitios web */
template <class T>
void ConexionesComputadora<T>::tresConexionesConsecutivas(const vector<Entradas> &datos)
{
    /* Crear variables de contador y conexionesConsecutivas */
    int contador = 0;
    bool conexionesConsecutivas = false;
    for (int i = 2; i < datos.size(); ++i)
    {
        /* Verificar que el IPOrigen de esa posición sea el mismo que el de las dos anteriores */
        if (datos[i].getIPOrigen() == datos[i - 1].getIPOrigen() && datos[i - 1].getIPOrigen() == datos[i - 2].getIPOrigen()) /* Mover las condiciones del if de los puertos a este if*/
        {
            /* Verificar que los puertos destinos sean 80 o 443 */
            if (datos[i].getPuertoDestino() == "80" || datos[i].getPuertoDestino() == "443")
            {
                /* Verificar que el IPOrigen sea el mismo que el ip ingresado por el usuario */
                if (datos[i].getIPOrigen() == ip)
                {
                    contador++;
                    /* Si el contador llega a 3, cambiar conexionesConsecutivas a true */
                    if (contador == 3)
                    {
                        conexionesConsecutivas = true;
                    }
                    else
                    {
                        conexionesConsecutivas = false;
                    }
                }
            }
            else
            {
                contador = 0;
            }
        }
        else
        {
            contador = 0;
        }
    }

    /* Si conexionesConsecutivas es true, imprimir que sí se encontró */
    if (conexionesConsecutivas == true)
    {
        cout << "La computadora " << ip << " SÍ tiene tres conexiones consecutivas a un mismo sitio web." << endl;
    }
    /* Si permanece en false, no se encontró */
    else if (conexionesConsecutivas == false)
    {
        cout << "La computadora " << ip << " NO tiene tres conexiones consecutivas a un mismo sitio web." << endl;
    }
}

template <class T>
ConexionesComputadora<T> &ConexionesComputadora<T>::operator=(const ConexionesComputadora<T> &otra)
{
    /* Proteger contra auto asignación */
    /* Ver si la instancia actual es distinta a la que se está asignando */
    if (this != &otra)
    {
        /* Liberar memoria antes de asignar los datos */
        delete conexionesEntrantes;
        delete conexionesSalientes;

        /* Copiar datos */
        ip = otra.ip;
        nombre = otra.nombre;
        conexionesEntrantes = new Stack<T>(*otra.conexionesEntrantes);
        conexionesSalientes = new LinkedList<T>(*otra.conexionesSalientes);
    }
    return *this;
}

#endif