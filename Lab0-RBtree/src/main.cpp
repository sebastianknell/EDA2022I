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
    tree->insertar(1);
    tree->insertar(8);
    tree->insertar(3);

//    tree->preorden();
//    tree->posorden();
    auto datos_antes = tree->inorden();
    print(datos_antes);

    tree->eliminarNodo(5);
    auto datos_despues = tree->inorden();
    print(datos_despues);

    return 0;
}