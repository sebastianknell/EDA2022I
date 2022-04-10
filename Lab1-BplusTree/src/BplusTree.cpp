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

static void re_sort(vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i+1]) {
            int j = i+1;
            while (j < arr.size() && arr[j] > arr[i]) j++;
            swap(arr[i], arr[j]);
            return;
        }
    }
}

BplusTree::BplusTree(int orden): orden(orden) {
    assert(orden > 2);
    root = nullptr;
    min = ceil(double(orden / 2.0)) - 1;
    max = orden - 1;
}

BplusTree::~BplusTree() {
    // Hacer un bfs e ir eliminando nodos
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

int BplusTree::find_child_index(Node *node) {
    int index = 0;
    while (index < node->father->childs.size() && node->father->childs[index] != node) index++;
    return index;
}

void BplusTree::split_up(Node *node, int key) {
    // Encontrar el indice del medio
    insert_ordered(node->keys, key);
    int middle = int(node->keys.size() / 2);
    auto new_key = node->keys[middle];

    // Crear padre si no existe
    if (!node->father) {
        node->father = new Node(false);
        root = node->father;
        node->father->childs.push_back(node);
    }

    // Si hay espacio en el padre insertar y dividir nodo
    if (node->father->keys.size() < orden - 1) {
        auto index = insert_ordered(node->father->keys, new_key);
        auto brother = split_node(node, new_key);

        // Asignar hijos del padre
        if (index + 1 >= node->father->childs.size())
            node->father->childs.push_back(brother);
        else node->father->childs.insert(node->father->childs.begin() + index + 1, brother);
    }
    // Si no hay espacio, dividir al nodo y asignar nuevo hijo al padre (temporalmente). Luego dividir al padre
    else {
        auto brother = split_node(node, new_key);

        // Encontrar posicion de nodo respecto al padre
        int index = find_child_index(node);

        // Insertar hermano al costado
        if (index + 1 >= node->father->childs.size()) {
            node->father->childs.push_back(brother);
        }
        else node->father->childs.insert(node->father->childs.begin() + index + 1, brother);

        // Dividir al padre
        split_up(node->father, new_key);
    }
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
        int i = 0;
        for (; i < curr->keys.size(); ++i) {
            if (key < curr->keys[i]) break;
        }
        curr = curr->childs[i];
    }

    // Caso 1: Si hay espacio insertar
    if (curr->keys.size() < orden - 1) {
        insert_ordered(curr->keys, key);
        return;
    }
    // Empezar el proceso recursivo
    split_up(curr, key);
}

// Busca al hermano de un nodo. Si existe devuelve el puntero y si tambien puede prestar devuelve el indice.
// Sino este es -1
key_pos BplusTree::find_brother(Node *node) {
    Node* brother = nullptr;
    int brother_index = -1;
    pos pos = LEFT;
    if (node->father->childs.size() < 2) {
        return {
            brother,
            brother_index
        };
    }
    // Buscar indice en el padre
    int index = find_child_index(node);

    // Si es el primero, prestar de la derecha
    if (index == 0) {
        brother = node->father->childs[index+1];
        pos = RIGHT;
        if (brother->keys.size() > min)
            brother_index = 0;
    }
    // Si es el ultimo, prestar de la izquierda
    else if (index == node->father->childs.size()-1) {
        brother = node->father->childs[index-1];
        if (brother->keys.size() > min)
            brother_index = brother->keys.size() - 1;
    }
    // Sino prestar de la izquierda o de la derecha
    else {
        brother = node->father->childs[index-1];
        if (brother->keys.size() > min)
            brother_index = brother->keys.size() - 1;
        else if (node->father->childs[index+1]->keys.size() > min) {
            brother = node->father->childs[index+1];
            pos = RIGHT;
            brother_index = 0;
        }
    }
    return {
        brother,
        brother_index,
        pos
    };
}

void BplusTree::removeInternalNode(int key) {
    // Buscar nodo
    auto curr = root;
    int i;
    bool found = false;
    while (curr && !curr->isLeaf) {
        i = 0;
        for (; i < curr->keys.size(); ++i) {
            if (key < curr->keys[i]) break;
            else if (key == curr->keys[i]) {
                found = true;
                break;
            }
        }
        if (found) break;
        curr = curr->childs[i];
    }
    if (found) {
        auto succesor = curr->childs[i + 1];
        while (!succesor->isLeaf) succesor = succesor->childs.front();
        curr->keys[i] = succesor->keys.front();
    }
}

void BplusTree::fixTree(Node *curr) {
    if (curr == root) return;
    if (curr->keys.size() >= min) return;
    auto brother_pos = find_brother(curr);
    // Si existe un hermano
    if (brother_pos.node) {
        // Si el hermano puede prestar,
        if (brother_pos.index != -1) {
            auto index = find_child_index(curr);
            // Rotar derecha
            if (brother_pos.pos == LEFT) {
                // El padre le da una llave al actual
                curr->keys.insert(curr->keys.begin(), curr->father->keys[index-1]);
                // El hermano izquierdo le da una llave al padre
                curr->father->keys[index-1] = brother_pos.node->keys.back();
                brother_pos.node->keys.pop_back();
                // El mayor hijo del hermano se va al inicio del actual
                curr->childs.insert(curr->childs.begin(), brother_pos.node->childs.back());
                curr->childs.front()->father = curr;
                brother_pos.node->childs.pop_back();
            }
            // Rotar izquierda
            else {
                // El padre le da una llave al actual
                curr->keys.insert(curr->keys.begin(), curr->father->keys[index+1]);
                // El hermano derecho le da una llave al padre
                curr->father->keys[index+1] = brother_pos.node->keys.front();
                brother_pos.node->keys.erase(brother_pos.node->keys.begin());
                // El menor hijo del hermano se va al final del actual
                curr->childs.push_back(brother_pos.node->childs.front());
                curr->childs.back()->father = curr;
                brother_pos.node->childs.erase(brother_pos.node->childs.begin());
            }
            return;
        }
        // Si no puede prestar, hacer merge
        else {
            bool is_root_updated;
            if (brother_pos.pos == LEFT) {
                is_root_updated = merge(brother_pos.node, curr);
                curr = brother_pos.node;
            }
            else is_root_updated = merge(curr, brother_pos.node);
            if (is_root_updated) return;
        }
    }
    if (curr == root) return;
    if (curr->keys.size() >= min) return;
    fixTree(curr->father);
}

// Une el nodo b al a. Se asume que b esta a la derecha de a
bool BplusTree::merge(Node *node_a, Node *node_b) {
    if (!node_a->father || !node_b->father) return false;
    if (node_a->father != node_b->father) return false;
    for (auto key : node_b->keys) {
        node_a->keys.push_back(key);
    }
    // Copiar hijos
    if (!node_a->isLeaf) {
        for (auto &child : node_b->childs) {
            child->father = node_a;
            node_a->childs.push_back(child);
        }
//        for (int i = 0; i < node_b->childs.size(); i++) {
//
//        }
    }
    else
        node_a->next = node_b->next;

    if (node_a->father == root && node_a->father->keys.size() == 1) {
        root = node_a;
        if ((int)node_a->keys.size() < (int)node_a->childs.size() - 1) {
            insert_ordered(node_a->keys, node_a->father->keys.front());
        }
        delete node_a->father;
        node_a->father = nullptr;
        delete node_b;
        return true;
    }
    else {
        int index = find_child_index(node_b);
        node_a->father->keys.erase(node_a->father->keys.begin() + index - 1);
        node_a->father->childs.erase(node_a->father->childs.begin() + index);
        delete node_b;
    }
    return false;
}

void BplusTree::eliminar(int key) {
    // Buscar nodo
    bool has_internal_node = false;
    auto curr = root;
    while (curr && !curr->isLeaf) {
        int i = 0;
        for (; i < curr->keys.size(); ++i) {
            if (key < curr->keys[i]) break;
            else if (key == curr->keys[i]) {
                has_internal_node = true;
            }
        }
        curr = curr->childs[i];
    }

    // Buscar key en la hoja
    int leaf_node_index = -1;
    for (int i = 0; i < curr->keys.size(); i++) {
        if (curr->keys[i] == key) {
            leaf_node_index = i;
            break;
        }
    }
    // Si no esta, terminar
    if (leaf_node_index == -1) return;

    // Eliminar key en la hoja
    curr->keys.erase(curr->keys.begin() + leaf_node_index);

    // Si es root terminar
    if (curr == root) {
        // Si root esta vacio eliminar memoria
        if (curr->keys.empty()) {
            root = nullptr;
            delete curr;
        }
        return;
    }

    // Si el nodo es valido, terminar
    if (curr->keys.size() >= min) {
        // Eliminar nodo interno si existe
        if (has_internal_node) removeInternalNode(key);
        return;
    }

    auto brother_pos = find_brother(curr);
    // Si existe un hermano
    if (brother_pos.node) {
        // Si el hermano puede prestar, prestar, remover nodo interno y terminar
        if (brother_pos.index != -1) {
            if (brother_pos.pos == LEFT) {
                curr->keys.insert(curr->keys.begin(), brother_pos.node->keys[brother_pos.index]);
                brother_pos.node->keys.erase(brother_pos.node->keys.begin() + brother_pos.index);
                auto index = find_child_index(brother_pos.node);
                curr->father->keys[index] = curr->keys.front();
            }
            else {
                curr->keys.push_back(brother_pos.node->keys[brother_pos.index]);
                brother_pos.node->keys.erase(brother_pos.node->keys.begin() + brother_pos.index);
                auto index = find_child_index(brother_pos.node);
                curr->father->keys[index - 1] = curr->keys.front();
            }
            if (has_internal_node) removeInternalNode(key);
            return;
        }
        // Sino puede prestar, hacer merge
        else {
            bool is_root_updated;
            if (brother_pos.pos == LEFT) {
                is_root_updated = merge(brother_pos.node, curr);
                curr = brother_pos.node;
            }
            else is_root_updated = merge(curr, brother_pos.node);
            if (is_root_updated) return;
        }
    }

    // Iniciar proceso recursivo
    fixTree(curr->father);
    if (has_internal_node) removeInternalNode(key);
}

vector<int> BplusTree::bfs() {
    queue<Node*> queue;
    vector<int> result;
    queue.push(root);
    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();
        for (const auto &key : curr->keys)
            result.push_back(key);
        for (const auto &child : curr->childs)
            queue.push(child);
    }
    return result;
}
