#include <iostream>
#include "BplusTree.h"

int main() {
    auto tree = BplusTree();
    tree.insertar(5);
    tree.insertar(15);
    tree.insertar(25);
    tree.insertar(35);
    tree.insertar(45);
    auto result = tree.bfs();
    print_arr(result);
    return 0;
}
