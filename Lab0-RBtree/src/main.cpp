#include "rbtree.h"

int main() {
    auto tree = new RBtree();
    tree->insertar(4);
    tree->insertar(5);
    tree->insertar(10);
    tree->insertar(1);
    tree->insertar(3);

//    tree->preOrder();
//    tree->postOrder();
    tree->inOrder();

    tree->eliminarNodo(3);
    tree->inOrder();
    return 0;
}