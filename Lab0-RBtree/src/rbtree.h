#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Lista de colores del arbol
enum Color {
    RED, BLACK, DOUBLE_BLACK
};

struct Nodo {
    // Atributos
    int dato;
    int color;

    // Relacion con otros Nodos
    Nodo *left;
    Nodo *right;
    Nodo *father;

    // Constructor
    Nodo(int);
};

class RBtree {
private:
    Nodo *root;

    Nodo *insertarNodo(Nodo *&, Nodo *&);

    void corregirArbol(Nodo *&);

    void eliminarDoubleBlack(Nodo *&);

    static int getColor(Nodo *&);

    static void setColor(Nodo *&, int);

    void rotarIzquierda(Nodo *&);

    void rotarDerecha(Nodo *&);

    void preOrderRec(Nodo *&, vector<int> &);

    void postOrderRec(Nodo *&, vector<int> &);

    void inOrderRec(Nodo *&, vector<int> &);

public:
    RBtree();

    void insertar(int);

    void eliminarNodo(int);

    std::vector<int> preorden();

    std::vector<int> posorden();

    std::vector<int> inorden();

    ~RBtree();
};


#endif