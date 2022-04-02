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


struct Node {
    bool isLeaf = true;
    Node* father = nullptr;
    vector<int> keys;
    vector<Node*> childs;
    Node* next = nullptr;
    Node() = default;
    Node(bool isLeaf): isLeaf(isLeaf) {}
};


class BplusTree {
    Node* root;
    int node_size;

    static Node* split_node(Node* node, int key);
    void split_up(Node* node, int key);
public:
    explicit BplusTree(int node_size = 20);
    ~BplusTree();
    void insertar(int key);
    vector<int> bfs();
};

void print_arr(const vector<int> &arr);

#endif //LAB1_BPLUSTREE_BPLUSTREE_H
