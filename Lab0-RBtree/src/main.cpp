#include "rbtree.h"

void print(const vector<int> &arr) {
    for (const auto &item : arr) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    auto tree = new RBtree();
    tree->insertar(4);
    tree->insertar(5);
    tree->insertar(10);
    tree->insertar(1);
    tree->insertar(3);

//    tree->preorden();
//    tree->posorden();
    auto datos = tree->inorden();
    print(datos);

//    tree->eliminarNodo(10);
//    tree->inOrder();
    return 0;
}