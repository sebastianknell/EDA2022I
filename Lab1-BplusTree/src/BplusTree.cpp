//
// Created by Sebastian Knell on 31/03/22.
//

#include "BplusTree.h"

static int insert_ordered(vector<int> &arr, const int key) {
    auto iter = arr.begin();
    while (*iter < key && iter != arr.end()){
        if (key > *iter) iter++;
    }
    int index = distance(arr.begin(), iter);
    arr.insert(iter, key);
    return index;
}

static void print_arr(const vector<int> &arr) {
    for (const auto &i : arr) cout << i << " ";
    cout << endl;
}

BplusTree::BplusTree() {
    root = nullptr;
}

void BplusTree::insertar(int key) {
    if (!root) {
        root = new Node();
        root->keys.push_back(key);
        return;
    }
    // Buscar nodo
    auto curr = root;
    while (curr && !curr->isLeaf) {
        if (key <= curr->keys.front()) {
            curr = curr->childs[0];
            continue;
        }
        for (int i = 0; i < curr->keys.size() - 1; i++) {
            if (key > curr->keys[i] && key <= curr->keys[i+1]) {
                curr = curr->childs[i+1];
                break;
            }
        }
        if (key > curr->keys.back()) curr = curr->childs.back();
    }

    // Caso 1: Si hay espacio insertar
    if (curr->keys.size() < node_size) {
        insert_ordered(curr->keys, key);
        return;
    }
}
