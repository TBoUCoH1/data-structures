#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <cstddef>

struct AVLNode {
    std::string key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const std::string& k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

struct AVLTree {
    AVLNode* root = nullptr;
    size_t size = 0;
    std::string filename;
};


int GETH(AVLNode* node);
int GETBF(AVLNode* node);
void updateHeight(AVLNode* node);
AVLNode* rotateLeft(AVLNode* x);
AVLNode* rotateRight(AVLNode* y);
AVLNode* findMinValueNode(AVLNode* node);

// основные операции дерева
AVLNode* TINSERT(AVLNode* node, const std::string& key);
AVLNode* TGET(AVLNode* root, const std::string& key);
void TPRINT(AVLNode* root, std::string indent = "", bool last = true);
AVLNode* TDEL(AVLNode* node, const std::string& key);

#endif