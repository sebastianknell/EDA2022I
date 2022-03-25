#ifndef RBTREE_H
#define RBTREE_H

// Lista de colores del arbol
enum Color {
    RED, BLACK
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

    static int getColor(Nodo *&);

    static void setColor(Nodo *&, int);

    void rotarIzquierda(Nodo *&);

    void rotarDerecha(Nodo *&);

    void preOrderRec(Nodo *&);

    void postOrderRec(Nodo *&);

    void inOrderRec(Nodo *&);

public:
    RBtree();

    void insertar(int);

    void eliminarNodo(int);

    void preOrder();

    void postOrder();

    void inOrder();

    ~RBtree();
};


#endif