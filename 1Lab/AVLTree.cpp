#include "AVLTree.h"
#include <iostream>
#include <algorithm>

using namespace std;

int GETH(AVLNode* node) {
    return node ? node -> height : 0;
}

// вычислить бф: разница высот левого и правого
int GETBF(AVLNode* node) {
    if (!node) return 0;
    return GETH(node -> left) - GETH(node -> right);
}

// обновить высоту узла после изменений
void updateHeight(AVLNode* node) {
    if (node) {
        node -> height = 1 + max(GETH(node -> left), GETH(node -> right));
    }
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x -> right;
    AVLNode* T2 = y -> left;

    y -> left = x;
    x -> right = T2;

    updateHeight(x);
    updateHeight(y);

    return y; // y становится новым корнем
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y -> left;
    AVLNode* T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    updateHeight(y);
    updateHeight(x);
    
    return x; // x становится новым корнем
}

AVLNode* TINSERT(AVLNode* node, const string& key) {
    if (!node) {
        return new AVLNode(key);
    } 
    if (key < node -> key) {
        node  -> left = TINSERT(node -> left, key);
    } else if (key > node->key) {
        node -> right = TINSERT(node -> right, key);
    } else {
        return node; // дубликаты не допускаются
    }

    updateHeight(node);

    int balance = GETBF(node);
    
    // Левый-Левый случай
    if (balance > 1 && key < node -> left -> key) {
        return rotateRight(node);
    }

    // Правый-Правый случай
    if (balance < -1 && key > node -> right -> key) {
        return rotateLeft(node);
    }

    // Левый-Правый случай
    if (balance > 1 && key > node -> left -> key) {
        node -> left = rotateLeft(node -> left);
        return rotateRight(node);
    }

    // Правый-Левый случай
    if (balance < -1 && key < node -> right -> key) {
        node -> right = rotateRight(node -> right);
        return rotateLeft(node);
    }
    return node;
}

AVLNode* TGET(AVLNode* root, const string& key) {
    if (root == nullptr || root -> key == key) {
        return root;
    }
    if (key < root->key) {
        return TGET(root -> left, key);
    }
    return TGET(root -> right, key);
}

void TPRINT(AVLNode* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        cout << "\"" << root->key << "\"" << "(h:" << root->height << ", bf:" << GETBF(root) << ")" << endl;
        TPRINT(root -> left, indent, false);
        TPRINT(root -> right, indent, true);
    }
}

// поиск узла с минимальным значением в поддереве
AVLNode* findMinValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLNode* TDEL(AVLNode* root, const string& key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root -> key) {
        root -> left = TDEL(root -> left, key);
    } else if (key > root->key) {
        root -> right = TDEL(root -> right, key);
    } else {
        // У узла нет или есть один дочерний узел
        if (root -> left == nullptr || root->right == nullptr) {
            AVLNode* temp = root -> left ? root -> left : root -> right;

            // Если нет дочерних узлов
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else { // если 1 дочерний узел
                *root = *temp; // копируем содржимое доч узла
            }
            delete temp;
        } else { // у узла два дочерних узла
            // Находим наименьший узел в правом поддереве
            AVLNode* temp = findMinValueNode(root -> right);
            root -> key = temp -> key; // Копируем его ключ в текущий узел 
            root -> right = TDEL(root -> right, temp -> key);
        }
    }
    
    if (root == nullptr) {
        return root;
    }

    // Обновление высоты и балансировка
    updateHeight(root);
    int balance = GETBF(root);

    // Левый-Левый случай
    if (balance > 1 && GETBF(root -> left) >= 0) {
        return rotateRight(root);
    }

    // Левый-Правый случай
    if (balance > 1 && GETBF(root -> left) < 0) {
        root->left = rotateLeft(root -> left);
        return rotateRight(root);
    }

    // Правый-Правый случай
    if (balance < -1 && GETBF(root -> right) <= 0) {
        return rotateLeft(root);
    }

    // Правый-Левый случай
    if (balance < -1 && GETBF(root -> right) > 0) {
        root->right = rotateRight(root -> right);
        return rotateLeft(root);
    }

    return root;
} 