//
// Created by Sebastian Knell on 31/03/22.
//

#include "BplusTree.h"

static size_t insert_ordered(vector<int> &arr, const int key) {
    if (arr.empty()) {
        arr.push_back(key);
        return 0;
    }
    auto iter = arr.begin();
    while (*iter < key && iter != arr.end()) iter++;
    auto index = distance(arr.begin(), iter);
    arr.insert(iter, key);
    return index;
}

void print_arr(const vector<int> &arr) {
    for (const auto &i : arr) cout << i << " ";
}

// Get middle
static int try_insert(const vector<int> &arr, const int key) {
    int i = 0;
    while (arr[i] < key) i++;
    return i;
}

BplusTree::BplusTree(int node_size): node_size(node_size) {
    root = nullptr;
}

BplusTree::~BplusTree() {
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();
        for (const auto &child : curr->childs) {
            queue.push(child);
        }
        delete curr;
    }
}

Node *BplusTree::split_node(Node *node, int key) {
    auto brother = new Node(node->isLeaf);
    // Copiar nodos al hermano
    auto iter = node->keys.begin();
    while ( iter != node->keys.end()) {
        // Solo copiar key que sube si es un nodo hoja
        if (*iter == key) {
            if (node->isLeaf) {
                brother->keys.push_back(*iter);
            }
            node->keys.erase(iter);
        }
        else if (*iter > key) {
            brother->keys.push_back(*iter); // las keys ya estan ordenadas
            node->keys.erase(iter);
        }
        else iter++;
    }
    // Copiar hijos
    if (!node->isLeaf) {
        int i = 0;
        while (i <= node->keys.size()) i++;
        while (i < node->childs.size()) {
            node->childs[i]->father = brother;
            brother->childs.push_back(node->childs[i]);
            node->childs.erase(node->childs.begin() + i);
        }
    }

    if (node->isLeaf) {
        auto temp = node->next;
        node->next = brother;
        brother->next = temp;
    }

    brother->father = node->father;
    return brother;
}

void BplusTree::split_up(Node *node, int key) {
    // Encontrar el indice del medio
    insert_ordered(node->keys, key);
    int middle = int(node->keys.size() / 2);
    auto new_key = node->keys[middle];

    if (!node->father) {
        node->father = new Node(false);
        root = node->father;
        node->father->childs.push_back(node);
    }

    if (node->father->keys.size() < node_size) {
        auto index = insert_ordered(node->father->keys, new_key);
        auto brother = split_node(node, new_key);

        // Asignar hijos del padre
        if (index + 1 >= node->father->childs.size())
            node->father->childs.push_back(brother);
        else node->father->childs.insert(node->father->childs.begin() + index + 1, brother);
    }
    else {
        auto brother = split_node(node, new_key);

        // Encontrar posicion de nodo respecto al padre
        int index = 0;
        while (index < node->father->childs.size() && node->father->childs[index] != node) index++;

        // Insertar hermano al costado
        if (index + 1 >= node->father->childs.size()) {
            node->father->childs.push_back(brother);
        }
        else node->father->childs.insert(node->father->childs.begin() + index + 1, brother);

        split_up(node->father, new_key);
    }
}

void BplusTree::insertar(int key) {
//    cout << "Insertando " << key << endl;
    if (!root) {
        root = new Node();
        root->keys.push_back(key);
        return;
    }
    // Buscar nodo
    auto curr = root;
    bool curr_updated;
    while (curr && !curr->isLeaf) {
        curr_updated = false;
        if (key <= curr->keys.front()) {
            curr = curr->childs[0];
            continue;
        }
        for (int i = 0; i < curr->keys.size() - 1; i++) {
            if (key > curr->keys[i] && key <= curr->keys[i + 1]) {
                curr = curr->childs[i + 1];
                curr_updated = true;
                break;
            }
        }
        if (!curr_updated && key > curr->keys.back()) curr = curr->childs.back();
    }
    if (curr == nullptr) {
        cout << "Algo esta mal\n";
        return;
    }

    // Caso 1: Si hay espacio insertar
    if (curr->keys.size() < node_size) {
        insert_ordered(curr->keys, key);
        return;
    }
    split_up(curr, key);
}

vector<int> BplusTree::bfs() {
    queue<Node*> queue;
    vector<int> result;
    queue.push(root);
//    int nodes = 1;
//    int i = 1;
    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();
        for (const auto &key : curr->keys)
            result.push_back(key);
        for (const auto &child : curr->childs)
            queue.push(child);
//        print_arr(curr->keys);
//        if (i == nodes) {
//            nodes *= 3;
//            i = 0;
//            cout << endl;
//        }
//        else {
//            i++;
//            cout << "\t";
//        }
    }
    return result;
}
