#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int value;
    Node* left;
    Node* right;
};

// ===== ДОБАВЛЕНИЕ =====
Node* insert(Node* root, int value)
{
    if (!root)
        return new Node{ value, nullptr, nullptr };

    if (value < root->value)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// ===== ПОИСК =====
bool find(Node* root, int value)
{
    if (!root) return false;
    if (root->value == value) return true;

    if (value < root->value)
        return find(root->left, value);
    else
        return find(root->right, value);
}

// ===== МИНИМУМ =====
Node* findMin(Node* root)
{
    while (root->left)
        root = root->left;
    return root;
}

// ===== УДАЛЕНИЕ =====
Node* remove(Node* root, int value)
{
    if (!root) return nullptr;

    if (value < root->value)
        root->left = remove(root->left, value);
    else if (value > root->value)
        root->right = remove(root->right, value);
    else
    {
        if (!root->left) return root->right;
        if (!root->right) return root->left;

        Node* minNode = findMin(root->right);
        root->value = minNode->value;
        root->right = remove(root->right, minNode->value);
    }

    return root;
}

// ===== DFS =====
void preorder(Node* root)
{
    if (!root) return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root)
{
    if (!root) return;
    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
}

// ===== BFS =====
void bfs(Node* root)
{
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* cur = q.front();
        q.pop();

        cout << cur->value << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

// ===== ВЫВОД =====
void printTree(Node* root, string prefix = "", bool isLeft = true)
{
    if (!root) return;

    cout << prefix;

    cout << (isLeft ? "├── " : "└── ");

    cout << root->value << endl;

    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

// ===== MAIN =====
int main()
{
    Node* root = nullptr;

    root = insert(root, 25);
    root = insert(root, 10);
    root = insert(root, 40);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 30);
    root = insert(root, 50);

    cout << "Дерево:\n";
    cout << "25\n";
    printTree(root->left, "", true);
    printTree(root->right, "", false);

    cout << "\nПоиск 15: ";
    cout << (find(root, 15) ? "Найдено\n" : "Не найдено\n");

    cout << "\nDFS: ";
    preorder(root);

    cout << "\ninorder: ";
    inorder(root);

    cout << "\nBFS: ";
    bfs(root);

    cout << "\n\nУдаляем 10...\n";
    root = remove(root, 10);

    cout << "\nНовое дерево:\n";
    cout << root->value << endl;
    printTree(root->left, "", true);
    printTree(root->right, "", false);

    return 0;
}
