#include <iostream>
#include "BplusTree.h"

int main() {
    auto tree = BplusTree();
    tree.insertar(2);
    tree.insertar(1);
    tree.insertar(8);
    return 0;
}
