#include <fstream>
#include <chrono>
#include <cstdlib>
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
    auto tree = BplusTree(3);
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

    tree.eliminar(40);
    result = tree.bfs();
    print_arr(result);
    cout << endl;
}

// Funciona
void test3() {
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

// Funciona
void test4() {
    auto tree = BplusTree(3);
    tree.insertar(50);
    tree.insertar(45);
    tree.insertar(40);
    tree.insertar(41);
    tree.insertar(51);
    tree.insertar(46);
    tree.insertar(47);
    tree.insertar(46);
    auto result = tree.bfs();
    print_arr(result);
    cout << endl;
}

void test5(int n) {
    int max;
    max = 1000;
    srand(time(nullptr));
    auto tree = new BplusTree(11);
    for (int i = 0; i < n; i++) {
        tree->insertar(rand() % max);
    }
//    auto result = tree->bfs();
//    print_arr(result);
//    cout << endl;
    delete tree;
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
    else return 9;

    int64_t tiempoInseccion = 0;
    for (int t=0; t<1; ++t){
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
    cout << tiempoInseccion << endl;
    return 0;
}*/

int main() {
//    test1();
    test2();
//    test3();
//    test4();
//    test5(1000);
}
