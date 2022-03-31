//
// Created by Sebastian Knell on 31/03/22.
//

#ifndef LAB1_BPLUSTREE_BPLUSTREE_H
#define LAB1_BPLUSTREE_BPLUSTREE_H


#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define NODE_SIZE 20

struct Node {
    bool isLeaf = true;
    vector<int> keys;
    vector<Node*> childs;
    Node* next = nullptr;
};


class BplusTree {
    Node* root;
    int node_size = NODE_SIZE;
public:
    BplusTree();
    void insertar(int key);

};


#endif //LAB1_BPLUSTREE_BPLUSTREE_H
