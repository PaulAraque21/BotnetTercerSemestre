//
//  BST.hpp
//  BinaryTree
//
//  Created by Vicente Cubells on 20/10/20.
//  Modified by Paul Araque on 16/10/2023
//

#ifndef BST_hpp
#define BST_hpp

#include "BinaryTree.hpp"
using namespace std;

template <class T>
class BST : public BinaryTree<T>
{

public:
    BST(){};
    virtual ~BST(){};

    TreeNode<T> *search(const T &) const;
    bool insert(T &);
    bool insert(TreeNode<T> *);

    int whatlevelamI(const T &) const;

    /* Act. 3.1 */
    void levelByLevel();
    void visit(int);

    int height();
    int height(int, TreeNode<T> *);

    void ancestors(const T &);

    int whatlevelamI2(const T &);

private:
    /* Ocultar algunos métodos heredados */
    // using BinaryTree<T>::insert;
    /* Altura árbol */
};

/*
 Complejidad: O(log n) si el árbol está balanceado
              O(n) si el árbol está desbalanceado
 */
template <class T>
TreeNode<T> *BST<T>::search(const T &value) const
{
    TreeNode<T> *aux = this->root;

    while (aux != nullptr)
    {
        if (aux->getInfo() == value)
        {
            return aux;
        }
        else
        {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }

    return nullptr;
}

/*
 Complejidad: O(log n) si el árbol está balanceado
              O(n) si el árbol está desbalanceado
 */
template <class T>
bool BST<T>::insert(T &value)
{
    return this->insert(new TreeNode<T>(value));
}

template <class T>
bool BST<T>::insert(TreeNode<T> *node)
{
    /* No se puede insertar un nodo NULL */
    if (node == nullptr)
        return false;

    /* Obtener la info del nodo a insertar */
    T value = node->getInfo();

    /* Establecer un apuntador auxiliar */
    TreeNode<T> *aux = this->root;

    /* Estalecer una variable para el padre */
    TreeNode<T> *parent = nullptr;

    /* Buscar la posición que le corresponde */
    while (aux != nullptr)
    {
        if (aux->getInfo() == value)
        {
            /* Liberar la memoria del nodo porque ya existe */
            delete node;

            return false;
        }
        else
        {
            parent = aux;
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }

    /* Establecer el parent del nodo a insertar */
    node->setParent(parent);

    /* Si el árbol está vacío, se inserta la raiz */
    if (parent == nullptr)
    {
        this->root = node;
    }
    else
    {
        /* Si el value a insertar es menor, se inserta a la izquierda */
        if (parent->getInfo() > value)
        {
            parent->setLeft(node);
        }
        /* Si el value a insertar es mayor, se inserta a la derecha */
        else
        {
            parent->setRight(node);
        }
    }

    return true;
}

/*
 Complejidad: O(log n) si el árbol está balanceado
              O(n) si el árbol está desbalanceado
 */
template <class T>
int BST<T>::whatlevelamI(const T &value) const
{
    int level = 0;

    TreeNode<T> *aux = this->root;

    while (aux != nullptr)
    {
        level++;
        if (aux->getInfo() == value)
        {
            return level;
        }
        else
        {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }

    if (aux == nullptr)
    {
        level = 0;
    }

    return level;
}

/* Función para imprimir los nodos en sus niveles correspondientes */
/*
Complejidad computacional: O(n)  si está desbalanceado.
Compeljidad computacional: O(log n) si está balanceado.
*/
template <class T>
void BST<T>::levelByLevel()
{
    /* Asegurar que el árbol no esté vacío */
    if (this->empty())
    {
        return;
    }
    /* Se crean dos colas, una para el nivel actual y la otra para el siguiente nivel */
    queue<TreeNode<T> *> nivelActual;
    queue<TreeNode<T> *> siguienteNivel;

    /* Iniciar con la raíz */
    nivelActual.push(this->root);

    /* Contadores para imprimir los niveles */
    int contNivelActual = 1;
    int reiniciarContador = 1;
    int nivel = 1;

    while (!nivelActual.empty())
    {
        /* Obtener un nodo del nivel actual */
        TreeNode<T> *nodoActual = nivelActual.front();
        /* Ir eliminando los nodos de la cola */
        nivelActual.pop();

        /* Asegurar que el nodo sea válido e imprimirlo */
        if (nodoActual != nullptr)
        {
            if (contNivelActual == nivel)
            {
                cout << "Nivel " << contNivelActual << ": ";
            }
            cout << *nodoActual << " ";

            /* Agregar los hijos a la siguiente cola */
            siguienteNivel.push(nodoActual->getLeft());
            siguienteNivel.push(nodoActual->getRight());

            contNivelActual++;
        }

        /* Cuando la cola esté vacía, ya se imprimieron todos los nodos */
        if (nivelActual.empty())
        {
            cout << endl;
            /* Cambiar las colas para repetir el proceso con el siguiente nivel */
            swap(nivelActual, siguienteNivel);
            /* Sumar contadores */
            reiniciarContador++;
            contNivelActual = reiniciarContador;
            nivel++;
        }
    }
}

/* Función para imprimir el BST en PreOrden, InOrden, PostOrden o los niveles y nodos correspondientes */
/* Complejidad computacional: O(1)*/
template <class T>
void BST<T>::visit(int opcion)
{
    switch (opcion)
    {
    case 1:
        cout << "Se imprime el BST en PreOrden: " << endl;
        this->preOrden();
        cout << endl;
        break;
    case 2:
        cout << "Se imprime el BST en InOrden: " << endl;
        this->inOrden();
        cout << endl;
        break;
    case 3:
        cout << "Se imprime el BST en PostOrden: " << endl;
        this->postOrden();
        cout << endl;
        break;
    default:
        cout << "Se imprimien los nodos del BST en sus niveles correspondientes: " << endl;
        levelByLevel();
        cout << endl;
        break;
    }
}

/* Función para calcular la altura del BST*/
template <class T>
int BST<T>::height()
{
    return height(0, this->root);
}

/* Función para calcular la altura del BST */
/*
Complejidad computacional: O(n^2)  si está desbalanceado.
Compeljidad computacional: O(n log n) si está balanceado.
*/
template <class T>
int BST<T>::height(int altura, TreeNode<T> *node)
{
    int heightLeft = 0;
    int heightRight = 0;
    /* Regresar la altura actual cuando alcanze un subárbol vacío */
    if (node == nullptr)
    {
        return altura;
    }
    else
    {
        /* Calcular de forma recursiva la altura del subárbol izquierdo */
        heightLeft = height(altura + 1, node->getLeft());
        /* Calcular de forma recursiva la altura del subárbol derecho */
        heightRight = height(altura + 1, node->getRight());
    }
    /* Comparar la altura de los subárboles y regresar el mayor */
    return (heightLeft > heightRight) ? heightLeft : heightRight;
}

/* Función para imprimir todos los ancestros de un nodo específico */
/*
Complejidad computacional: O(n)  si está desbalanceado.
Compeljidad computacional: O(log n) si está balanceado.
*/
template <class T>
void BST<T>::ancestors(const T &valor)
{
    /* Encontrar el nodo del valor */
    TreeNode<T> *nodo = search(valor);
    /* Si el valor se encuentra en el árbol */
    if (nodo != nullptr)
    {
        cout << "Los ancestros de " << valor << " son: ";
        /* Obtener el padre del nodo */
        TreeNode<T> *parent = nodo->getParent();
        /* Mientras sí exista un nodo padre, imprimir todos los ancestros */
        while (parent != nullptr)
        {
            cout << parent->getInfo() << " ";
            /* Obtener los otros ancestros */
            parent = parent->getParent();
        }
    }
    /* Si el valor no se encuentra en el árbol */
    else
    {
        cout << valor << " no se encuentra en el BST." << endl;
    }
}

/* Función para calcular el nivel de un nodo específico */
/*
Complejidad computacional: O(n)  si está desbalanceado.
Compeljidad computacional: O(log n) si está balanceado.
*/
template <class T>
int BST<T>::whatlevelamI2(const T &valor)
{
    /* Encontrar el nodo del valor */
    TreeNode<T> *nodo = search(valor);
    /* Si el nodo no es válido, regresar -1 */
    if (nodo == nullptr)
    {
        return -1;
    }
    else
    {
        /* Obtener un apuntador al nodo padre */
        TreeNode<T> *parent = nodo->getParent();

        /* Contador del nivel */
        int nivel = 1;
        /* Mientras sí exista un nodo padre, obtener su ancestro y sumar uno al nivel. */
        while (parent != nullptr)
        {
            parent = parent->getParent();
            nivel++;
        }
        return nivel;
    }
}

#endif /* BST_hpp */
