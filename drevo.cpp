#include <iostream>
#include <string>

using namespace std;

// Структура узла
struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Класс Дерева
class BST {
private:
    Node* root;

    // Вспомогательная функция вставки
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    // 1. Прямой обход: Корень -> Лево -> Право
    void preOrder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    // 2. Симметричный обход: Лево -> Корень -> Право
    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    // 3. Обратный обход: Лево -> Право -> Корень
    void postOrder(Node* node) {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    // Функция визуализации (печать дерева на боку)
    void printVisual(Node* node, string indent, bool last) {
        if (node != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->data << endl;
            printVisual(node->left, indent, false);
            printVisual(node->right, indent, true);
        }
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void add(int val) { root = insert(root, val); }

    void showPreOrder() { preOrder(root); cout << endl; }
    void showInOrder() { inOrder(root); cout << endl; }
    void showPostOrder() { postOrder(root); cout << endl; }

    void visualize() {
        if (!root) cout << "Дерево пусто." << endl;
        else printVisual(root, "", true);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    BST tree;
    int choice, val;

    cout << "--- Двоичное дерево поиска (BST) ---\n";
    
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить число\n";
        cout << "2. Показать визуализацию\n";
        cout << "3. Прямой обход (Pre-order)\n";
        cout << "4. Симметричный обход (In-order)\n";
        cout << "5. Обратный обход (Post-order)\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите число: ";
                cin >> val;
                tree.add(val);
                break;
            case 2:
                cout << "\nСтруктура дерева (R - правая ветвь, L - левая):\n";
                tree.visualize();
                break;
            case 3:
                cout << "Pre-order: "; tree.showPreOrder();
                break;
            case 4:
                cout << "In-order: "; tree.showInOrder();
                break;
            case 5:
                cout << "Post-order: "; tree.showPostOrder();
                break;
            case 0:
                return 0;
            default:
                cout << "Неверный выбор.\n";
        }
    }

    return 0;
}