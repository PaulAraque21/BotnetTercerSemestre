/*
Paúl Araque Fernández
Brenda Romero Martínez
Actividad 5.2

main.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "ConexionesComputadora.hpp"
#include "Graph.hpp"
using namespace std;

/* Conexiones Por Dia */
map<string, int> conexionesPorDia(const string &fecha, const vector<Entradas> &datos)
{
    /* Crear mapa */
    map<string, int> conexionesDia;

    for (const Entradas &entrante : datos)
    {
        /* Verificar que la fecha de la iteración sea igual a la del usuario */
        if (entrante.getFecha() == fecha)
        {
            /* Encontrar el nombre del sitio */
            string sitio = entrante.getNombreDestino();
            /* Verificar que el sitio no es '-' y no contiene reto.com */
            if (sitio != "-" && sitio.find("reto.com") == string::npos)
            {
                conexionesDia[sitio]++;
            }
        }
    }
    return conexionesDia;
}

void printTop(int n, const string &fecha, const vector<Entradas> &datos)
{
    /* Crear mapa con las conexiones de ese día */
    map<string, int> conexionesDia = conexionesPorDia(fecha, datos);

    /* Crear el BST para almacenar las conexiones */
    BST<int> *sitiosConexiones = new BST<int>();
    for (const auto &entrada : conexionesDia)
    {
        /* Se utiliza .second para obtener el segundo dato del mapa */
        TreeNode<int> *cantidad = new TreeNode<int>(entrada.second);
        sitiosConexiones->insert(cantidad);
    }

    /* Obtener los nodos ordenados en un vector */
    vector<TreeNode<int> *> nodosOrdenados = sitiosConexiones->inOrdenToVector(sitiosConexiones->getRoot());

    cout << "Top sitios para la fecha " << fecha << ":" << endl;
    cout << "Los top " << n << " sitios con más acceso son:" << endl;

    /* Obtener los top N sitios con más acceso de atrás para adelante */
    for (int i = nodosOrdenados.size() - 1; i >= max(0, int(nodosOrdenados.size()) - n); i--)
    {
        /* Obtener el valor de la cantidad en el vector */
        TreeNode<int> *node = nodosOrdenados[i];
        int cantidad = node->getInfo();
        string sitio;
        /* Iterar sobre el mapa conexiones día para ver que cantidad es igual a la proporcionada por el vector */
        for (const auto &sitios : conexionesDia)
        {
            if (cantidad == sitios.second)
            {
                sitio = sitios.first;
            }
        }
        cout << "Sitio: " << sitio << ", Conexiones: " << cantidad << endl;
    }

    /* Liberar la memoria */
    delete sitiosConexiones;
}

map<string, int> topMap(int n, const string &fecha, const vector<Entradas> &datos)
{
    map<string, int> conexionesDia = conexionesPorDia(fecha, datos);

    /* Crear el BST para almacenar las conexiones */
    BST<int> *sitiosConexiones = new BST<int>();
    for (const auto &entrada : conexionesDia)
    {
        /* Se utiliza .second para obtener el segundo dato del mapa */
        TreeNode<int> *cantidad = new TreeNode<int>(entrada.second);
        sitiosConexiones->insert(cantidad);
    }

    /* Obtener los nodos ordenados en un vector */
    vector<TreeNode<int> *> nodosOrdenados = sitiosConexiones->inOrdenToVector(sitiosConexiones->getRoot());

    /* Mapa con los nombres y cantidad de conexiones */
    map<string, int> sitiosMasVisitados;

    /* Obtener los top N sitios con más acceso */
    for (int i = nodosOrdenados.size() - 1; i >= max(0, int(nodosOrdenados.size()) - n); i--)
    {
        /* Obtener el valor de la cantidad en el vector */
        TreeNode<int> *node = nodosOrdenados[i];
        int cantidad = node->getInfo();
        string sitio;
        /* Iterar sobre el mapa conexiones día para ver que cantidad es igual a la proporcionada por el vector */
        for (const auto &sitios : conexionesDia)
        {
            if (cantidad == sitios.second)
            {
                sitio = sitios.first;
            }
        }
        /* Agregar el nombre del sitio y su cantidad al mapa */
        sitiosMasVisitados[sitio] = cantidad;
    }

    /* Liberar la memoria */
    delete sitiosConexiones;
    return sitiosMasVisitados;
}

/* Construir un grafo en base a una ip específica */
Graph<std::string, std::string> construirGrafo(const std::vector<Entradas> &datos, std::string &redIp)
{
    /* Crear grafo */
    Graph<std::string, std::string> grafo;

    /* Agregar un vértice para la IP específica */
    grafo.addVertex(redIp);

    /* Recorrer el vector */
    for (const auto &entrada : datos)
    {
        /* Ver si la entrada contiene la ip interna */
        if (entrada.getIPOrigen() == redIp || entrada.getIPDestino() == redIp)
        {
            /* Determina la otra ip en la conexión */
            std::string nuevaIp = (entrada.getIPOrigen() == redIp) ? entrada.getIPDestino() : entrada.getIPOrigen();

            /* Verificar que la otra ip también sea interna */
            if (EsDireccionRedInterna(nuevaIp))
            {
                /* Ver si ya existe un vértice */
                Vertex<std::string, std::string> *verticeNuevaIp = grafo.search(nuevaIp);
                /* Agregarlo al grafo si no existe */
                if (!verticeNuevaIp)
                {
                    grafo.addVertex(nuevaIp);
                    verticeNuevaIp = grafo.search(nuevaIp);
                }

                /* Agregar arista dependiendo si la Ip interna es origen o destino */
                if (entrada.getIPOrigen() == redIp)
                {
                    /* Agregarla desde la ip interna a la nueva ip */
                    grafo.addEdge(grafo.search(redIp), verticeNuevaIp, entrada.getFecha());
                }
                else
                {
                    /* Agregarla desde la nueva ip a la ip interna */
                    grafo.addEdge(verticeNuevaIp, grafo.search(redIp), entrada.getFecha());
                }
            }
        }
    }
    return grafo;
}

/* Construir un grafo en base a una ip específica */
Graph<std::string, std::string> construirGrafoSitiosWeb(const std::vector<Entradas> &datos, std::string &redIp)
{
    /* Crear grafo */
    Graph<std::string, std::string> grafo;

    /* Agregar un vértice para la IP específica */
    grafo.addVertex(redIp);

    /* Recorrer el vector */
    for (const auto &entrada : datos)
    {
        /* Verificar que se conecte a un sitio Web (Puertos 80 y 443) */
        if (entrada.getPuertoDestino() == "80" || entrada.getPuertoDestino() == "443")
        {
            /* Ver si la entrada contiene la ip interna */
            if (entrada.getIPDestino() == redIp)
            {
                /* Determina la IP origen en la conexión */
                std::string ipOrigen = entrada.getIPOrigen();

                /* Ver si ya existe un vértice para ipOrigen */
                Vertex<std::string, std::string> *verticeOrigen = grafo.search(ipOrigen);
                /* Agregarlo al grafo si no existe */
                if (!verticeOrigen)
                {
                    grafo.addVertex(ipOrigen);
                    verticeOrigen = grafo.search(ipOrigen);
                }

                /* Agregar arista desde la ip origen a redIp */
                grafo.addEdge(verticeOrigen, grafo.search(redIp), entrada.getFecha());
            }
        }
    }
    return grafo;
}

/* Función para crear mapa con el nombre de la computadora y su respectiva IP */
std::map<std::string, std::string> mapNomIP(const vector<Entradas> &datos)
{
    std::map<std::string, std::string> nomIP;
    for (const Entradas &dato : datos)
    {
        /* Encontrar el nombre del sitio destino */
        std::string sitioDestino = dato.getNombreDestino();
        /* Verificar que el sitio no contiene reto.com */
        if (sitioDestino != "-" && sitioDestino.find("reto.com") == std::string::npos)
        {
            /* Agregar si no existe en el mapa */
            if (nomIP.find(sitioDestino) == nomIP.end())
            {
                nomIP[sitioDestino] = dato.getIPDestino();
            }
        }
        /* Realizar lo mismo pero con el nombre origen */
        std::string sitioOrigen = dato.getNombreOrigen();
        if (sitioOrigen != "-" && sitioOrigen.find("reto.com") == std::string::npos)
        {
            if (nomIP.find(sitioOrigen) == nomIP.end())
            {
                nomIP[sitioOrigen] = dato.getIPOrigen();
            }
        }
    }
    return nomIP;
}

/* Diccionario <IP, ConexionesComputadora> */
std::map<std::string, ConexionesComputadora<std::string>> mapConexCompus(const vector<Entradas> &datos)
{
    /* Crear mapa a devolver */
    std::map<std::string, ConexionesComputadora<std::string>> conexCompu;
    /* Iterar sobre los registros */
    for (const Entradas &dato : datos)
    {
        /* Verificar si la IP Origen ya está en el mapa */
        if (conexCompu.find(dato.getIPOrigen()) == conexCompu.end())
        {
            conexCompu[dato.getIPOrigen()] = ConexionesComputadora<std::string>(dato.getIPOrigen());
        }
        /* Verificar si la IP Destino ya está en el mapa*/
        if (conexCompu.find(dato.getIPDestino()) == conexCompu.end())
        {
            conexCompu[dato.getIPDestino()] = ConexionesComputadora<std::string>(dato.getIPDestino());
        }
    }

    /* LLenar las conexiones entrantes y salientes de las ConexionesComputadoras */
    for (auto &par : conexCompu)
    {
        par.second.completarConexiones(datos);
    }

    return conexCompu;
}

/* Función para obtener 10 IPs que no sean "server.reto.com" y no pertenezcan al servidor DHCP */
std::set<std::string> obtenerIPs(const std::vector<Entradas> &datos)
{
    /* Obtener la direccion de red interna y restarle los últimos dígitos que representan '.00' */
    std::string direccionRed = EncontrarDireccionRedInterna(datos);
    std::string direccionRedFinal;
    if (direccionRed.length() >= 3 && direccionRed.substr(direccionRed.length() - 3) == ".00")
    {
        direccionRedFinal = direccionRed.substr(0, direccionRed.length() - 3);
    }
    else
    {
        direccionRedFinal = direccionRed;
    }
    /* Crear set */
    std::set<std::string> IPs;
    for (const auto &dato : datos)
    {
        /* Verificar que no sea ni 'server.reto.com' ni del servidor DHCP y que contiene la dirección de red interna */
        if (dato.getNombreDestino() != "server.reto.com" && dato.getPuertoDestino() != "67" && dato.getPuertoDestino() != "68" && dato.getIPDestino().find(direccionRedFinal) != std::string::npos)
        {
            /* Añadir la IP al set */
            IPs.insert(dato.getIPDestino());

            /* Parar si ya se tienen 10 IPs */
            if (IPs.size() >= 10)
                break;
        }
    }
    return IPs;
}

int main()
{
    /* Se crea vector llamado "EntradasV" y se le asigna resultado de la función LeerCSV, que lee datos desde el archivo "equipo4.csv" y los guarda en el vector. */
    vector<Entradas> EntradasV = LeerCSV("equipo4.csv");
    cout << "---------------------------------------------------" << endl;

    /* PREGUNTA #1: ¿Qué dirección ip estás usando? */
    /* Pedir al usuario la dirección IP que está usando */
    int direccion;
    cout << "Por favor ingresa un número entre 1 y 150: ";
    cin >> direccion;
    cout << endl;
    /* Verificar que el número esté dentro del rango, sino salir del programa */
    if (direccion < 1 || direccion > 150)
    {
        cout << "La dirección es inválida. Por favor verifique que esté entre el 1 y el 150." << endl;
        cout << "Si desea intentar de nuevo, vuelva a correr el programa." << endl;
        /* Salir del programa */
        return 1;
    }
    /* Generar la ip internar que se va a utilizar */
    string redInterna = EncontrarDireccionRedInterna(EntradasV);
    redInterna = redInterna.substr(0, redInterna.length() - 3);
    string ipInterna = redInterna + "." + to_string(direccion);
    ConexionesComputadora<string> computadora(ipInterna);
    computadora.asignarNombre(EntradasV);
    cout << "---------------------------------------------------" << endl;

    /* PREGUNTA #2: ¿Cuál fue la dirección IP de la última conexión que recibió esta computadora? ¿Es interna o externa? */
    /* Definir variable para guardar la ultima conexion */
    string ultimaConexion;
    /* Iterar por todo el vector de EntradasV */
    for (const Entradas &conexiones : EntradasV)
    {
        if (conexiones.getIPOrigen() == ipInterna)
        {
            ultimaConexion = conexiones.getIPDestino();
        }
        else if (conexiones.getIPDestino() == ipInterna)
        {
            ultimaConexion = conexiones.getIPOrigen();
        }
    }
    /* Si ultimaConexion no está vacía, verificar si es interna o externa */
    if (!ultimaConexion.empty())
    {
        cout << "La última conexión recibida es de la siguiente dirección IP: " << ultimaConexion << endl;
        if (EsDireccionRedInterna(ultimaConexion))
        {
            cout << "La dirección IP es interna." << endl;
        }
        else
        {
            cout << "La dirección IP es externa." << endl;
        }
    }
    else
    {
        cout << "No se encontraron direcciones IP entrantes para esta computadora." << endl;
    }
    cout << "---------------------------------------------------" << endl;

    /* PREGUNTA #3: ¿Cuántas conexiones entrantes tiene esta computadora? */
    computadora.completarConexiones(EntradasV);
    cout << "Esta computadora tiene " << computadora.entrantesTotal() << " conexiones entrantes" << endl;
    cout << "---------------------------------------------------" << endl;

    /* PREGUNTA #4: ¿Cuántas conexiones salientes tiene esta computadora? */
    cout << "Esta computadora tiene " << computadora.salientesTotal() << " conexiones salientes" << endl;
    cout << "---------------------------------------------------" << endl;

    /* PREGUNTA #5: ¿Tiene esta computadora 3 conexiones seguidas a un mismo sitio web? */
    computadora.tresConexionesConsecutivas(EntradasV);
    cout << "---------------------------------------------------" << endl;

    /* ACTIVIDAD 3.2 EVIDENCIA */

    /* Utiliza estas funciones para imprimir por cada día diferente del archivo CSV, el top 5. */
    cout << "IMPRIMIR EL TOP 5 DE CADA FECHA DEL ARCHIVO" << endl;

    /* Variable para la fecha que va a ir cambiando */
    string fechaActual = "";

    /* Definir un mapa para llevar el registro de cuántos días cada sitio ha estado en el top 5 */
    map<string, int> contadorTop5;
    int cantDias = 0;

    /*Definir mapas para llevar registro de sitios subsecuentes */
    map<string, bool> sitiosSubsecuentes;
    map<string, int> sitSubse;

    /* Definir mapa para los sitios con tráfico alto */
    map<string, int> traficoAlto;

    for (const Entradas &entrada : EntradasV)
    {
        string fecha = entrada.getFecha();

        /* Verificar si ya se corrió el código en esa fecha para saltarla */
        if (fecha == fechaActual)
        {
            continue;
        }

        /* Imprimir los sitios top en esa fecha */
        printTop(5, fecha, EntradasV);

        /* Contador de cuantas veces un sitio ha estado en el top 5 */
        map<string, int> sitiosMasVisitados = topMap(5, fecha, EntradasV);
        /* Incrementar ambos contadores para cada sitio en el top 5 */
        for (const auto &sitio : sitiosMasVisitados)
        {
            contadorTop5[sitio.first]++;
            sitSubse[sitio.first]++;
        }

        /* Verificar si algún sitio nuevo ha entrado al top 5 y se ha mantenido en los días subsecuentes */
        if (fechaActual != "")
        {
            for (const auto &sitio : sitiosSubsecuentes)
            {
                /* Si el sitio no estuvo en el top 5 del día anterior, eliminarlo de sitSubse */
                if (sitio.second && sitiosMasVisitados.find(sitio.first) == sitiosMasVisitados.end())
                {
                    sitSubse.erase(sitio.first);
                }
            }
        }
        /* Incrementar el contador de días */
        cantDias++;
        /* Actualizar la fecha */
        fechaActual = fecha;
        /* Limpiar el mapa de sitios subsecuentes para utilizarlo en la siguiente iteración */
        sitiosSubsecuentes.clear();
        /* Iterar sobre los sitios más visitados y marcarlos como subsecuentes */
        for (const auto &sitio : sitiosMasVisitados)
        {
            sitiosSubsecuentes[sitio.first] = true;
        }
    }

    /* 1. ¿Existe algún sitio que se mantenga en el top 5 todos los días? */
    cout << "-----------------------------------------------------" << endl;
    /* Verificar si hay algún sitio que esté en el top 5 todos los días */
    bool algunSitioEnTop5TodosLosDias = false;
    string sitioTodosLosDias = "";
    cout << "Los sitios que se mantienen en el top 5 todos los días son:" << endl;
    for (const auto &sitios : contadorTop5)
    {
        if (sitios.second == cantDias)
        {
            sitioTodosLosDias = sitios.first;
            cout << sitioTodosLosDias << endl;
            algunSitioEnTop5TodosLosDias = true;
        }
    }

    if (!algunSitioEnTop5TodosLosDias)
    {
        cout << "No hay sitios que se mantengan en el top 5 todos los días." << endl;
    }

    /* Verificar si hay algún sitio que esté en el top 5 todos los días */

    /* 2. ¿Existe algún sitio que entre al top 5 a partir de un día y de ahí aparezca en todos los días subsecuentes? */
    cout << "-----------------------------------------------------" << endl;
    cout << "Sitios que entran al top 5 y se mantienen en los días subsecuentes:" << endl;
    for (const auto &sitios : sitSubse)
    {
        if (sitios.first != sitioTodosLosDias && sitios.second > 1)
        {
            string sitioSub = sitios.first;
            cout << sitioSub << endl;
        }
    }

    /* 3. ¿Existe algún sitio que aparezca en el top 5 con una cantidad más alta de trafico que lo normal? */
    cout << "-----------------------------------------------------" << endl;
    string fechaAc = "";
    for (const Entradas &entrada : EntradasV)
    {
        string fechaFinal = entrada.getFecha();

        /* Verificar si ya se corrió el código en esa fecha para saltarla */
        if (fechaFinal == fechaAc)
        {
            continue;
        }

        /* Contador de cuantas veces un sitio ha estado en el top 5 */
        map<string, int> sitiosParaTrafico = topMap(5, fechaFinal, EntradasV);
        /* Incrementar ambos contadores para cada sitio en el top 5 */
        cout << "Sitios con más tráfico de lo normal en el día: " << fechaFinal << endl;
        for (const auto &sitio : sitiosParaTrafico)
        {
            /* Ver si el tráfico es más alto de lo normal e imprimir aquellos que sí */
            if (sitio.second >= 100)
            {
                cout << "Sitio: " << sitio.first << ", Conexiones: " << sitio.second << endl;
            }
        }
        cout << endl;
        /* Actualizar la fecha */
        fechaAc = fechaFinal;
    }

    /* ACTIVIDAD 4.2 EVIDENCIA */
    std::cout << "ACTIVIDAD 4.2" << std::endl;
    std::string a = ipInterna;
    std::string b = "kdkkgs7z6ptuhv2f8jub.ru";
    std::string c = "spotify.com";

    /* Crear vector con las fechas */
    std::vector<std::string> fechas;
    for (const auto &entrada : EntradasV)
    {
        /* Encontrar la fecha de la iteración */
        std::string fecha = entrada.getFecha();
        /* Si no se encuentra en el vector fechas, agregarlo */
        if (find(fechas.begin(), fechas.end(), fecha) == fechas.end())
        {
            fechas.push_back(fecha);
        }
    }

    /* 1. Utilizando un grafo con las conexiones entre las ip de la red interna, determina la cantidad de computadoras con las que se ha conectado A por día. ¿Es el vértice que más conexiones salientes tiene hacia la red interna? */
    std::cout << "-----------------------------------------------------" << std::endl;
    Graph<std::string, std::string> grafoConexionesA = construirGrafo(EntradasV, a);

    /* Obtener el vértice correspondiente a la IP actual en el grafo de conexiones internas */
    Vertex<std::string, std::string> *verticeActual = grafoConexionesA.search(a);

    int conexionesA = 0;
    if (verticeActual)
    {
        /* Obtener la cantidad de conexiones salientes desde la IP actual */
        conexionesA = verticeActual->getEdges()->size();
        std::cout << "Esta computadora tiene " << conexionesA << " conexiones salientes hacia la red interna." << std::endl;

        std::cout << "Conexiones salientes de " << a << " hacia la red interna por día:" << std::endl;

        /* Iterar por el vector de fechas */
        for (const auto &fecha : fechas)
        {
            int conexionesPorDia = 0;

            /* Iterar sobre las aristas del vértice actual para contar conexiones salientes por día */
            for (const auto &edge : *verticeActual->getEdges())
            {
                /* Obtener la información de la fecha de la arista */
                std::string info = edge->getInfo();
                /* Obtener el vértice destino */
                Vertex<std::string, std::string> *verticeDestino = edge->getTarget();

                /* Verificar si el vértice destino está en la red interna y si la fecha coincide */
                if (EsDireccionRedInterna(verticeDestino->getInfo()) && info == fecha)
                {
                    conexionesPorDia++;
                }
            }

            std::cout << "Fecha: " << fecha << ", Conexiones Salientes: " << conexionesPorDia << std::endl;
        }
    }

    int maxConexiones = 0;
    /* Ciclo para crear grafo para todas las ip de 1 a 150 y comparar la mayor */
    for (int i = 1; i <= 150; ++i)
    {
        /* Obtener la direccion ip completa para construir el grafo */
        string redIn = EncontrarDireccionRedInterna(EntradasV);
        redIn = redIn.substr(0, redIn.length() - 3);
        string ipIn = redIn + "." + to_string(i);

        Graph<std::string, std::string> nuevoGrafo = construirGrafo(EntradasV, ipIn);

        /* Iterar sobre los vértices del grafo */
        for (auto &vertice : nuevoGrafo.getNodes())
        {
            /* Obtener el ip del vértice actual */
            std::string ipVertice = vertice->getInfo();
            /* Contar el número de aristas de la conexión actual */
            int numConexiones = vertice->getEdges()->size();

            /* Encontrar el mayor número de conexiones salientes de todos los vértices */
            if (numConexiones > maxConexiones)
            {
                maxConexiones = numConexiones;
            }
        }
    }
    /* Comparar si "a" tiene el mayor número de conexiones salientes */
    if (conexionesA == maxConexiones)
    {
        std::cout << "La IP " << a << " sí tiene el máximo de conexiones salientes en la red interna." << std::endl;
    }
    else
    {
        std::cout << "La IP " << a << " no tiene el máximo de conexiones salientes en la red interna." << std::endl;
    }

    /* 2. Utilizando el grafo del punto anterior, ubica la cantidad de computadoras que se han conectado hacia A por día. ¿Existen conexiones de las demás computadoras hacia A? */
    std::cout << "-----------------------------------------------------" << std::endl;
    if (verticeActual)
    {
        /* Imprimir las conexiones entrantes hacia "a" por día */
        std::cout << "Conexiones entrantes hacia " << a << " desde otras computadoras por día:" << std::endl;
        /* Iterar por el vector de fechas */
        for (const auto &fecha : fechas)
        {
            int conexionesPorDia = 0;

            /* Iterar sobre los vértices del grafo para contar conexiones entrantes por día */
            for (auto &vertice : grafoConexionesA.getNodes())
            {
                /* Ignorar la IP de A */
                if (vertice->getInfo() == a)
                {
                    continue;
                }

                /* Iterar sobre las aristas del vértice actual */
                for (const auto &edge : *vertice->getEdges())
                {
                    /* Obtener la información de la fecha de la arista */
                    std::string info = edge->getInfo();
                    /* Obtener el vértice destino */
                    Vertex<std::string, std::string> *verticeDestino = edge->getTarget();

                    /* Verificar si la IP de destino es A y si la fecha coincide */
                    if (verticeDestino->getInfo() == a && info == fecha)
                    {
                        conexionesPorDia++;
                        /* No es necesario seguir buscando en esta computadora para esta fecha */
                        break;
                    }
                }
            }

            std::cout << "Fecha: " << fecha << ", Conexiones Entrantes: " << conexionesPorDia << std::endl;
        }
    }

    /* 3. Utilizando un grafo de conexiones a sitios web, determina cuántas computadoras se han conectado a B por día. */
    std::cout << "-----------------------------------------------------" << std::endl;
    std::string ipB;
    std::string ipC;
    /* Iterar sobre todos los registros para obtener las respectivas direccions IP */
    for (const auto entrada : EntradasV)
    {
        if (entrada.getNombreOrigen() == b)
        {
            ipB = entrada.getIPOrigen();
        }
        else if (entrada.getNombreOrigen() == c)
        {
            ipC = entrada.getIPOrigen();
        }
        else if (entrada.getNombreDestino() == b)
        {
            ipB = entrada.getIPDestino();
        }
        else if (entrada.getNombreDestino() == c)
        {
            ipC = entrada.getIPDestino();
        }
    }
    Graph<std::string, std::string> grafoConexionesSitiosWebB = construirGrafoSitiosWeb(EntradasV, ipB);

    /* Obtener el vértice correspondiente a la IP actual en el grafo de conexiones internas */
    Vertex<std::string, std::string> *verticeActualB = grafoConexionesSitiosWebB.search(ipB);

    int conexionesB = 0;
    int maxConexionesB = 0;
    if (verticeActualB)
    {
        /* Imprimir las conexiones entrantes hacia "b" por día */
        std::cout << "Conexiones entrantes hacia " << b << " desde otras computadoras por día:" << std::endl;

        /* Iterar sobre el vector de fechas */
        for (const auto &fecha : fechas)
        {
            int conexionesPorDia = 0;

            /* Iterar sobre los vértices del grafo para contar conexiones entrantes por día */
            for (auto &vertice : grafoConexionesSitiosWebB.getNodes())
            {
                /* Ignorar la IP de B */
                if (vertice->getInfo() == ipB)
                {
                    continue;
                }

                /* Iterar sobre las aristas del vértice actual */
                for (const auto &edge : *vertice->getEdges())
                {
                    /* Obtener la información de la fecha de la arista */
                    std::string info = edge->getInfo();
                    /* Obtener el vértice destino */
                    Vertex<std::string, std::string> *verticeDestino = edge->getTarget();

                    /* Verificar si la IP de destino es B y si la fecha coincide */
                    if (verticeDestino->getInfo() == ipB && info == fecha)
                    {
                        conexionesPorDia++;
                        /* No es necesario seguir buscando en esta computadora para esta fecha */
                        break;
                    }
                }
            }
            /* Calcular el total de conexiones entrantes a B*/
            maxConexionesB = maxConexionesB + conexionesPorDia;

            std::cout << "Fecha: " << fecha << ", Conexiones Entrantes: " << conexionesPorDia << std::endl;
        }
        std::cout << "Conexiones totales entrantes hacia " << b << " desde otras computadoras: " << maxConexionesB << std::endl;
    }

    /* 4. Utilizando el mismo grafo del punto anterior, indica cuántas computadoras se han conectado a C por día. */
    std::cout << "-----------------------------------------------------" << std::endl;
    Graph<std::string, std::string> grafoConexionesSitiosWebC = construirGrafoSitiosWeb(EntradasV, ipC);

    /* Obtener el vértice correspondiente a la IP actual en el grafo de conexiones internas */
    Vertex<std::string, std::string> *verticeActualC = grafoConexionesSitiosWebC.search(ipC);

    int conexionesC = 0;
    int maxConexionesC = 0;
    if (verticeActualB)
    {
        /* Imprimir las conexiones entrantes hacia "c" por día */
        std::cout << "Conexiones entrantes hacia " << c << " desde otras computadoras por día: " << std::endl;

        /* Iterar sobre el vector de fechas */
        for (const auto &fecha : fechas)
        {
            int conexionesPorDia = 0;

            /* Iterar sobre los vértices del grafo para contar conexiones entrantes por día */
            for (auto &vertice : grafoConexionesSitiosWebC.getNodes())
            {
                /* Ignorar la IP de C */
                if (vertice->getInfo() == ipC)
                {
                    continue;
                }

                /* Iterar sobre las aristas del vértice actual */
                for (const auto &edge : *vertice->getEdges())
                {
                    /* Obtener la información de las fechas de las aristas */
                    std::string info = edge->getInfo();
                    /* Obtener el vértice destino */
                    Vertex<std::string, std::string> *verticeDestino = edge->getTarget();

                    /* Verificar si la IP de destino es A y si la fecha coincide */
                    if (verticeDestino->getInfo() == ipC && info == fecha)
                    {
                        conexionesPorDia++;
                        /* No es necesario seguir buscando en esta computadora para esta fecha */
                        break;
                    }
                }
            }
            /* Calcular el total de conexiones entrantes a C*/
            maxConexionesC = maxConexionesC + conexionesPorDia;

            std::cout << "Fecha: " << fecha << ", Conexiones Entrantes: " << conexionesPorDia << std::endl;
        }
        std::cout << "Conexiones totales entrantes hacia " << c << " desde otras computadoras: " << maxConexionesC << std::endl;
        std::cout << "-----------------------------------------------------" << std::endl;
    }

    /* ACTIVIDAD 5.2 EVIDENCIA */
    std::cout << "ACTIVIDAD 5.2" << std::endl;

    /* 1. Hay algún nombre de dominio en el conjunto que sea anómalo (Esto puede ser con inspección visual). */
    /* 2. De los nombres de dominio encontrados en el paso anterior, ¿cuál es su IP? ¿Cómo determinarías esta información de la manera más óptima en complejidad temporal? */
    std::map<std::string, std::string> nomIP = mapNomIP(EntradasV);
    for (const auto &conexion : nomIP)
    {
        std::cout << "Sitio: " << conexion.first << " ---> IP: " << conexion.second << std::endl;
    }
    std::cout << "-----------------------------------------------------" << std::endl;

    /* 3. De las computadoras pertenecientes al dominio reto.com determina la cantidad de IPs que tienen al menos una conexión entrante. (Recuerda que ya tienes la dirección de la red y el último octeto puede tener computadoras del .1 al .254. Imprime la cantidad de computadoras. */

    /* Obtener la direccion de red interna y restarle los últimos dígitos que representan '.00' */
    std::string direccionRed = EncontrarDireccionRedInterna(EntradasV);
    std::string direccionRedFinal;
    if (direccionRed.length() >= 3 && direccionRed.substr(direccionRed.length() - 3) == ".00")
    {
        direccionRedFinal = direccionRed.substr(0, direccionRed.length() - 3);
    }
    else
    {
        direccionRedFinal = direccionRed;
    }

    std::map<std::string, ConexionesComputadora<std::string>> ipConexCompu = mapConexCompus(EntradasV);
    int contConexEntrantes = 0;
    for (auto &par : ipConexCompu)
    {
        if (par.second.getConexionesEntrantes()->size() > 0 && par.first.find(direccionRedFinal) != std::string::npos)
        {
            contConexEntrantes++;
            std::cout << contConexEntrantes << ". IP: " << par.first << " Conexiones Entrantes: " << par.second.getConexionesEntrantes()->size() << std::endl;
        }
    }

    std::cout << "La cantidad de IPs pertenecientes al dominio 'reto.com' que tienen al menos una conexión entrante son: " << contConexEntrantes << std::endl;

    std::cout << "-----------------------------------------------------" << std::endl;

    /* 4. Toma algunas computadoras que no sean server.reto.com o el servidor DHCP. Pueden ser entre 5 y 10. Obtén las IPs únicas de las conexiones entrantes. */
    std::set<std::string> IPs10 = obtenerIPs(EntradasV);
    std::set<std::string> IPsUnicas;
    for (const auto &ip10 : IPs10)
    {
        /* Buscar la computadora en el mapa */
        auto iterador = ipConexCompu.find(ip10);
        /* Verificar si se encuentra en el mapa */
        if (iterador != ipConexCompu.end())
        {
            /* Obtener el Stack de Conexiones Entrantes */
            Stack<std::string> *conexionesEntrantes = iterador->second.getConexionesEntrantes();
            /* Iterar sobre el Stack para obtener las IPs entrantes */
            while (!conexionesEntrantes->empty())
            {
                /* Obtener nodo superior del Stack */
                Node<std::string> *nodeEntrante = conexionesEntrantes->top();
                /* Extraer la información */
                std::string ipEntrante = nodeEntrante->getInfo();
                /* Eliminar el nodo superior */
                conexionesEntrantes->pop();

                /* Insertar la IP entrante en el set de IPs Unicas */
                IPsUnicas.insert(ipEntrante);
            }
        }
    }

    std::cout << "Estas son las 10 IPs seleccionadas: " << std::endl;
    for (const std::string &IP10 : IPs10)
    {
        std::cout << IP10 << std::endl;
    }
    std::cout << "IPs únicas de las Conexiones Entrantes: " << std::endl;
    for (const std::string &ipUnica : IPsUnicas)
    {
        std::cout << ipUnica << std::endl;
    }
    std::cout << "-----------------------------------------------------" << std::endl;

    /* 6. Para las IPs encontradas en el paso anterior, determina si se han comunicado con los datos encontrados en la pregunta 1 */
    /* Variables de los nombres anómalos */
    std::string nombre1 = "kdkkgs7z6ptuhv2f8jub.ru";
    std::string nombre2 = "nyvbcosk2llkngjncf9o.net";
    /* ariable para almacenar si se encontró conexión */
    bool comunicacionNombre1 = false;
    bool comunicacionNombre2 = false;
    /* Variable para almacenar la fecha y puertos */
    std::map<std::string, std::string> primeraFecha;
    std::string primerPuerto = "";
    std::map<std::string, std::string> primeraNombre1;
    std::string puertoNumero1 = "";
    std::map<std::string, std::string> primeraNombre2;
    std::string puertoNumero2 = "";

    /* Verificación de la comunicación con los nombres anómalos */
    for (const auto &ipComu : IPsUnicas)
    {
        for (const auto &entrada : EntradasV)
        {
            /* Verificar condiciones para ver si se conectaron */
            if (entrada.getIPOrigen() == ipComu && entrada.getNombreDestino() == nombre1 || entrada.getIPDestino() == ipComu && entrada.getNombreOrigen() == nombre1)
            {
                comunicacionNombre1 = true;
                /* Condición para primera fecha en general */
                if (primeraFecha.empty() && primerPuerto.empty())
                {
                    /* Agregar al mapa la fecha */
                    primeraFecha[nombre1] = entrada.getFecha();
                    primerPuerto = entrada.getPuertoDestino();
                }
                /* Condición para primera fecha del kdkkgs7z6ptuhv2f8jub.ru */
                if (primeraNombre1.empty() && puertoNumero1.empty())
                {
                    /* Agregar al mapa la fecha */
                    primeraNombre1[nombre1] = entrada.getFecha();
                    puertoNumero1 = entrada.getPuertoDestino();
                }
            }
            if (entrada.getIPOrigen() == ipComu && entrada.getNombreDestino() == nombre2 || entrada.getIPDestino() == ipComu && entrada.getNombreOrigen() == nombre2)
            {
                comunicacionNombre2 = true;
                /* Condición para primera fecha en general */
                if (primeraFecha.empty() && primerPuerto.empty())
                {
                    /* Agregar al mapa la fecha */
                    primeraFecha[nombre2] = entrada.getFecha();
                    primerPuerto = entrada.getPuertoDestino();
                }
                /* Condición para primera fecha del nyvbcosk2llkngjncf9o.net */
                if (primeraNombre2.empty() && puertoNumero2.empty())
                {
                    /* Agregar al mapa la fecha */
                    primeraNombre2[nombre2] = entrada.getFecha();
                    puertoNumero2 = entrada.getPuertoDestino();
                }
            }
        }
        if (comunicacionNombre1)
        {
            std::cout << "Hay conexion entre la IP única " << ipComu << " y el nombre " << nombre1 << std::endl;
        }
        if (comunicacionNombre2)
        {
            std::cout << "Hay conexion entre la IP única " << ipComu << " y el nombre " << nombre2 << std::endl;
        }
    }

    /* 7. En caso de que hayas encontrado que las computadoras del paso 1 y 4 se comunican, determina en qué fecha ocurre la primera comunicación entre estas dos y qué protocolo se usa. */
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "Primera comunicación entre las IPs únicas y las computadoras anómalas: " << std::endl;
    if (!primeraFecha.empty())
    {
        for (auto &par : primeraFecha)
        {
            std::cout << "La primera conexión entre las IPs únicas y las computadoras con nombres anómalos se realizó en la fecha " << par.second << " a la computadora " << par.first << " a través del puerto " << primerPuerto << std::endl;
        }
    }
    else
    {
        std::cout << "No se realizó ninguna conexión de las IPs únicas a las computadoras con nombres anómalos. " << std::endl;
    }
    /* Imprimir primera conexión a kdkkgs7z6ptuhv2f8jub.ru*/
    std::cout << "Primera comunicación entre las IPs únicas y la computadora " << nombre1 << ": " << std::endl;
    if (!primeraNombre1.empty())
    {
        for (auto &par : primeraNombre1)
        {
            std::cout << "La primera conexión entre las IPs únicas y la computadora " << par.first << " se realizó en la fecha " << par.second << " a través del puerto " << puertoNumero1 << std::endl;
        }
    }
    else
    {
        std::cout << "No se realizó ninguna conexión de las IPs únicas a la computadora " << nombre1 << std::endl;
    }
    /* Imprimir primera conexión a nyvbcosk2llkngjncf9o.net*/
    std::cout << "Primera comunicación entre las IPs únicas y la computadora " << nombre2 << ": " << std::endl;
    if (!primeraNombre2.empty())
    {
        for (auto &par : primeraNombre2)
        {
            std::cout << "La primera conexión entre las IPs únicas y la computadora " << par.first << " se realizó en la fecha " << par.second << " a través del puerto " << puertoNumero2 << std::endl;
        }
    }
    else
    {
        std::cout << "No se realizó ninguna conexión de las IPs únicas a la computadora " << nombre2 << std::endl;
    }

    return 0;
}