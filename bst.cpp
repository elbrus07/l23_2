#include <iostream>
#include <queue>


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
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }
    
    /* поиск минимального узла в поддереве */
    Node* minNode(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    /* рекурсивное удаление */
    Node* remove(Node* node, int value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {                                   // нашли узел для удаления
            // случай 1 или 2: один или ноль детей
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;                       // подвешиваем temp на родителя
            }
            // случай 3: два ребёнка — заменяем минимальным из правого поддерева
            Node* succ   = minNode(node->right);
            node->data   = succ->data;             // копируем значение
            node->right  = remove(node->right, succ->data); // удаляем succ
        }
        return node;
    }
    
    // Рекурсивный обход (Preorder)
    void preorder(Node* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Рекурсивный обход (Inorder)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
    
    // Рекурсивный обход (Inorder)
    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
    
    void bfs(Node* node) {
        if (!node) return;
        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            std::cout << cur->data << " ";
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }
    
    void remove(int value) { 
        root = remove(root, value); 
    }

    void print() {
        preorder(root);
        std::cout << std::endl;
        inorder(root);
        std::cout << std::endl;
        postorder(root);
        std::cout << std::endl;
        bfs(root);
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
    bst.insert(6);

    bst.print();
    
    bst.remove(30);

    bst.print();

    return 0;
}

