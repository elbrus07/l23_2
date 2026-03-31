#include <iostream>

// Узел дерева
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Класс дерева поиска
class BinarySearchTree {
private:
    Node* root;

    // Рекурсивная вставка
    Node* insert(Node* node, int value) {
        if (node == nullptr) return new Node(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        return node;
    }

    // Рекурсивный обход (Inorder)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void print() {
        inorder(root);
        std::cout << std::endl;
    }
};

int main() {
    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(30);
    bst.insert(7);
    bst.insert(20);
    bst.insert(4);

    bst.print(); 

    return 0;
}

