//
// Created by Sebastian Knell on 31/03/22.
//

#ifndef LAB1_BPLUSTREE_BPLUSTREE_H
#define LAB1_BPLUSTREE_BPLUSTREE_H


#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

enum pos {
    LEFT,
    RIGHT
};

struct Node {
    bool isLeaf = true;
    Node* father = nullptr;
    vector<int> keys;
    vector<Node*> childs;
    Node* next = nullptr;
    Node() = default;
    Node(bool isLeaf): isLeaf(isLeaf) {}
};

typedef struct {Node* node; int index; pos pos;} key_pos;


class BplusTree {
    Node* root;
    int orden;
    int min, max;

    static Node* split_node(Node* node, int key);
    void split_up(Node* node, int key);
    int find_child_index(Node* node);
    void merge(Node* node_a, Node* node_b);
    key_pos find_brother(Node *node);
    void removeInternalNode(key_pos pos);
    void fixTree(Node* curr);
public:
    explicit BplusTree(int orden = 21);
    ~BplusTree();
    void insertar(int key);
    void eliminar(int key);
    vector<int> bfs();
};

void print_arr(const vector<int> &arr);

#endif //LAB1_BPLUSTREE_BPLUSTREE_H
