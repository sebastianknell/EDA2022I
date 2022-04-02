#include <fstream>
#include <chrono>
#include "BplusTree.h"

// Funciona
void test1() {
    auto tree = BplusTree(2);
    tree.insertar(5);
    tree.insertar(15);
    tree.insertar(25);
    tree.insertar(35);
    tree.insertar(45);
    auto result = tree.bfs();
    print_arr(result);
    cout << endl;
}

// Funciona
void test2() {
    auto tree = BplusTree(2);
    tree.insertar(20);
    tree.insertar(15);
    tree.insertar(12);
    tree.insertar(8);
    tree.insertar(40);
    tree.insertar(65);
    tree.insertar(1);
    tree.insertar(30);
    auto result = tree.bfs();
    print_arr(result);
    cout << endl;
}

// Funciona
void test3() {
    auto tree = BplusTree(3);
    tree.insertar(1);
    tree.insertar(4);
    tree.insertar(7);
    tree.insertar(10);
    tree.insertar(17);
    tree.insertar(21);
    tree.insertar(31);
    tree.insertar(25);
    tree.insertar(19);
    tree.insertar(20);
    tree.insertar(28);
    tree.insertar(42);
    auto result = tree.bfs();
    print_arr(result);
    cout << endl;
}

// Funciona
void test4() {
    auto tree = BplusTree(4);
    tree.insertar(1);
    tree.insertar(4);
    tree.insertar(7);
    tree.insertar(10);
    tree.insertar(17);
    tree.insertar(21);
    tree.insertar(31);
    tree.insertar(25);
    tree.insertar(19);
    tree.insertar(20);
    tree.insertar(28);
    tree.insertar(42);
    auto result = tree.bfs();
    print_arr(result);
    cout << endl;
}

/*int main() {
    // Read file
    std::ifstream texto;
    texto.open("../output.txt");

    int datos[ 1000000 ];
    int element;
    if (texto.is_open()) {
        int i = 0;
        while (texto >> element) {
            datos[i++] = element;
        }
    }

    int64_t tiempoInseccion = 0;
    for (int t=0; t<10; ++t){
        auto tree = new BplusTree();

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (int i=0; i<1000000; ++i) {
            tree->insertar( datos[i] );
        }

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        // Calcular tiempo
        auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        tiempoInseccion += tiempo;
    }

    return 0;
}*/

int main() {
    test1();
    test2();
    test3();
    test4();
}
