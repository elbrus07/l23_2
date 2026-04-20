#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// Узел дерева
class Node {
public:
    int data;
    Node* left;
    Node* right;
    sf::CircleShape circle;
    sf::Text text;
    sf::Font* font;

    Node(int value, sf::Font& font) : data(value), left(nullptr), right(nullptr) {
        this->font = &font;
        
        circle.setRadius(25);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(25, 25);
        
        updateText(value);
    }
    
    void updateText(int value) {
        text.setFont(*font);
        text.setString(std::to_string(value));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, 
                      textRect.top + textRect.height/2.0f);
        text.setPosition(circle.getPosition());
    }
    
    void setData(int value) {
        data = value;
        updateText(value);
    }
    
    void setPosition(int x, int y) {
        circle.setPosition(x, y);
        text.setPosition(x, y);
    }
};

// Класс дерева поиска
class BinarySearchTree {
private:
    Node* root;
    sf::Font font;
    sf::RenderWindow* window = nullptr;
    sf::Text* statusText = nullptr;  // Указатель на статус текст
    
    bool search(Node* node, int value) {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    Node* insert(Node* node, int value) {
        if (node == nullptr) return new Node(value, font);
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }
    
    Node* minNode(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    
    Node* maxNode(Node* node) {
        while (node && node->right) node = node->right;
        return node;
    }

    Node* findNode(Node* node, int value) {
        if (node == nullptr) return nullptr;
        if (value == node->data) return node;
        if (value < node->data) return findNode(node->left, value);
        return findNode(node->right, value);
    }
    
    Node* findParent(Node* node, int value, Node* parent = nullptr) {
        if (node == nullptr) return nullptr;
        if (value == node->data) return parent;
        if (value < node->data) return findParent(node->left, value, node);
        return findParent(node->right, value, node);
    }

    Node* remove(Node* node, int value) {
        Node* node1 = findNode(root, value);
        if (node1 == nullptr) {
            if (statusText) statusText->setString(L"Узел не найден!");
            
        }
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* successor = minNode(node->right);
                node->setData(successor->data);
                node->right = remove(node->right, successor->data);
            }
        }
        return node;
    }
    
    void preorder(Node* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
    
    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
    
    vector<int> bfs(Node* node) {
        vector<int> nodes;
        if (!node) return nodes;
        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            std::cout << cur->data << " ";
            nodes.push_back(cur->data);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        return nodes;
    }
    
    int getMaxLevel(Node* node, int level = 0) {
        if (!node) return level;
        return std::max(getMaxLevel(node->left, level + 1), getMaxLevel(node->right, level + 1));
    }
    
    void calculatePositions(Node* node, int x, int y, int xBaseOffset, int level) {
        if (node == nullptr) return;
        
        node->setPosition(x, y);
        
        int xOffset = xBaseOffset;
        
        for (int i = 0; i < level; i++) {
            xOffset = xOffset*2 + xBaseOffset;
        }
        
        if (node->left) {
            calculatePositions(node->left, x - xOffset, y + 70, xBaseOffset, level-1);
        }
        if (node->right) {
            calculatePositions(node->right, x + xOffset, y + 70, xBaseOffset, level-1);
        }
    }
    
    void drawLines(Node* node) {
        if (node == nullptr) return;
        
        sf::VertexArray lines(sf::Lines);
        
        if (node->left) {
            lines.append(sf::Vertex(node->circle.getPosition(), sf::Color::Black));
            lines.append(sf::Vertex(node->left->circle.getPosition(), sf::Color::Black));
            window->draw(lines);
            drawLines(node->left);
        }
        
        if (node->right) {
            lines.append(sf::Vertex(node->circle.getPosition(), sf::Color::Black));
            lines.append(sf::Vertex(node->right->circle.getPosition(), sf::Color::Black));
            window->draw(lines);
            drawLines(node->right);
        }
    }
    
    void drawNodes(Node* node) {
        if (node == nullptr) return;
        
        window->draw(node->circle);
        window->draw(node->text);
        
        drawNodes(node->left);
        drawNodes(node->right);
    }
    
    void clear(Node* node) {
        if (node == nullptr) return;
        
        // Сначала удаляем левое поддерево
        clear(node->left);
        // Потом правое поддерево
        clear(node->right);
        // Затем сам узел
        delete node;
    }
    
public:
    BinarySearchTree() : root(nullptr) {
        if (!font.loadFromFile("fonts/LiberationSans-Regular.ttf")) {
            std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
        }
    }
    
    void setStatusText(sf::Text* text) {
        statusText = text;
    }
    
    bool search(int value) {
        return search(root, value);
    }

    void insert(int value) {
        root = insert(root, value);
    }
    
    void remove(int value) { 
        root = remove(root, value); 
    }
    
    void clear() { 
        clear(root);
        root = nullptr;
    }
    
    void draw(sf::RenderWindow &win) {
        window = &win;
        if (root == nullptr) return;
        
        int level = getMaxLevel(root);
        calculatePositions(root, (win.getSize().x-200)/2, 80, 4, level);
        drawLines(root);
        drawNodes(root);
    }
    
    // Правый поворот вокруг указанного узла
    void rotateRight(int value) {
        Node* node = findNode(root, value);
        if (node == nullptr) {
            if (statusText) statusText->setString(L"Узел не найден!");
            return;
        }
        
        Node* parent = findParent(root, value);
        Node* leftChild = node->left;
        
        if (leftChild == nullptr) {
            if (statusText) statusText->setString(L"Невозможно выполнить правый поворот: нет левого ребенка!");
            return;
        }
        
        Node* temp = leftChild->right;
        leftChild->right = node;
        node->left = temp;
        
        if (parent == nullptr) {
            root = leftChild;
        } else if (parent->left == node) {
            parent->left = leftChild;
        } else {
            parent->right = leftChild;
        }
        
        if (statusText) statusText->setString(L"Правый поворот вокруг: " + to_wstring(value));
    }
    
    // Левый поворот вокруг указанного узла
    void rotateLeft(int value) {
        Node* node = findNode(root, value);
        if (node == nullptr) {
            if (statusText) statusText->setString(L"Узел не найден!");
            return;
        }
        
        Node* parent = findParent(root, value);
        Node* rightChild = node->right;
        
        if (rightChild == nullptr) {
            if (statusText) statusText->setString(L"Невозможно выполнить левый поворот: нет правого ребенка!");
            return;
        }
        
        Node* temp = rightChild->left;
        rightChild->left = node;
        node->right = temp;
        
        if (parent == nullptr) {
            root = rightChild;
        } else if (parent->left == node) {
            parent->left = rightChild;
        } else {
            parent->right = rightChild;
        }
        
        if (statusText) statusText->setString(L"Левый поворот вокруг: " + to_wstring(value));
    }

    void print() {
        std::cout<<"preorder: ";
        preorder(root);
        std::cout << std::endl;
        
        std::cout<<"inorder: ";
        inorder(root);
        std::cout << std::endl;
        
        std::cout<<"postorder: ";
        postorder(root);
        std::cout << std::endl;
        
        std::cout<<"bfs: ";
        bfs(root);
        std::cout << std::endl;
    }
    
    vector<int> bfs() {
        return bfs(root);
    }
};

class TextInput {
private:
    bool active = false;
    string inputStr;
    int x;
    int y;
    int w;
    int h;
    sf::Font font;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    
public:
    TextInput(int x, int y, int w, int h, sf::Font& font, string str = "") {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->font = font;
        this->inputStr = str;
        
        inputText.setFont(this->font);
        inputText.setString(str);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(this->x, this->y);
        
        inputBox.setSize(sf::Vector2f(this->w, this->h));
        inputBox.setFillColor(sf::Color(240, 240, 240));
        inputBox.setOutlineColor(sf::Color::Black);
        inputBox.setOutlineThickness(1);
        inputBox.setPosition(inputText.getPosition().x - 5, inputText.getPosition().y - 5);
    }
    
    void draw_text_input(sf::RenderWindow &window) {
        inputText.setString(inputStr);
        window.draw(inputBox);
        window.draw(inputText);
    }
    
    void handleEvent(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (inputBox.getGlobalBounds().contains(mousePos)) {
                setActive(true);
            } else {
                setActive(false);
            }
        }

        if (active && event.type == sf::Event::TextEntered) {
            char c = event.text.unicode;

            if ((c == 8 || c == 127) && !inputStr.empty()) { 
                inputStr.pop_back();
            } else if (c >= 32 && c <= 126 && inputStr.length() < 16) {
                inputStr += c;
            }

            inputText.setString(inputStr);
        }
    }
    
    void setActive(bool state) {
        active = state;
        inputBox.setOutlineColor(active ? sf::Color::Blue : sf::Color::Black);
    }
    
    string get_text() {
        return inputStr;
    }
};

class Button {
private:
    int x;
    int y;
    int w;
    int h;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape button;
    bool isHovered = false;
    function<void()> onClickAction;
    
public:
    Button(int x, int y, int w, int h, sf::Font& font, wstring str = L"", function<void()> action = nullptr) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->font = font;
        this->onClickAction = action;
        
        button.setSize(sf::Vector2f(this->w, this->h));
        button.setPosition(this->x, this->y);
        button.setFillColor(sf::Color::White);
        button.setOutlineColor(sf::Color::Black);
        button.setOutlineThickness(1);
        
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, 
                      textRect.top + textRect.height/2.0f);
        text.setPosition(x + w/2.0f, y + h/2.0f);
    }
    
    void draw_button(sf::RenderWindow &window) {
        if (isHovered) {
            button.setFillColor(sf::Color(200, 200, 200));
        } else {
            button.setFillColor(sf::Color::White);
        }
        
        window.draw(button);
        window.draw(text);
    }
    
    void handleEvent(sf::Event& event, sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        
        if (button.getGlobalBounds().contains(mousePosF)) {
            isHovered = true;
            
            if (event.type == sf::Event::MouseButtonPressed && 
                event.mouseButton.button == sf::Mouse::Left) {
                if (onClickAction) {
                    onClickAction();
                }
            }
        } else {
            isHovered = false;
        }
    }
};

int main() {
    BinarySearchTree bst;
    
    vector<vector<int>> history;
    int pos = 0;
    int size = 0;

    int arr[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 45, 55, 65, 75, 85}; 
    
    for (int i: arr) {
        bst.insert(i);
    }
    
    bst.print();
    
    history.push_back(bst.bfs());
    size = 1;
    
    int width = 1000;
    int height = 800;
    
    sf::RenderWindow window(sf::VideoMode(width + 200, height), L"Бинарное Дерево Поиска", 
                           sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("fonts/LiberationSans-Regular.ttf")) {
        std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
        return 1;
    }
    
    TextInput inputField(1020, 50, 180, 40, font);
    
    sf::Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::Black);
    statusText.setPosition(115, 600);
    statusText.setString(L"Готово");
    
    // Передаем статус текст в дерево
    bst.setStatusText(&statusText);
    
    Button insertBtn(1015, 120, 180, 40, font, L"Вставить", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            bst.insert(value);
            inputField.setActive(false);
            if (pos < size-1) {
                history.resize(pos+1);
                size = pos+1;
            }
            history.push_back(bst.bfs());
            pos++;
            size++;
        } else {
            statusText.setString(L"Ошибка: Пустой ввод!");
        }
    });
    
    Button removeBtn(1015, 180, 180, 40, font, L"Удалить", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            bst.remove(value);
            inputField.setActive(false);
            if (pos < size-1) {
                history.resize(pos+1);
                size = pos+1;
            }
            history.push_back(bst.bfs());
            pos++;
            size++;
        } else {
            statusText.setString(L"Ошибка: Пустой ввод!");
        }
    });
    
    Button searchBtn(1015, 240, 180, 40, font, L"Поиск", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            if (bst.search(value)) {
                statusText.setString(L"Найдено: " + to_wstring(value));
            } else {
                statusText.setString(L"Не найдено: " + to_wstring(value));
            }
            inputField.setActive(false);
        } else {
            statusText.setString(L"Ошибка: Пустой ввод!");
        }
    });
    
    Button rotateRightBtn(1015, 360, 180, 40, font, L"Правый", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            bst.rotateRight(value);
            inputField.setActive(false);
            if (pos < size-1) {
                history.resize(pos+1);
                size = pos+1;
            }
            history.push_back(bst.bfs());
            pos++;
            size++;
        } else {
            statusText.setString(L"Ошибка: Введите значение узла!");
        }
    });
    
    Button rotateLeftBtn(1015, 300, 180, 40, font, L"Левый", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            bst.rotateLeft(value);
            inputField.setActive(false);
            if (pos < size-1) {
                history.resize(pos+1);
                size = pos+1;
            }
            history.push_back(bst.bfs());
            pos++;
            size++;
        } else {
            statusText.setString(L"Ошибка: Введите значение узла!");
        }
    });
    
    Button backBtn(1015, 420, 180, 40, font, L"Назад", [&]() {
        if (pos > 0) {
            bst.clear();
            pos--;
            for (int i: history[pos]) {
                bst.insert(i);
            }
        }
    });
    
    Button forwardBtn(1015, 480, 180, 40, font, L"Вперёд", [&]() {
        if (pos < size-1 && size > 1) {
            bst.clear();
            pos++;
            for (int i: history[pos]) {
                bst.insert(i);
            }
        }
    });
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            inputField.handleEvent(event);
            insertBtn.handleEvent(event, window);
            removeBtn.handleEvent(event, window);
            searchBtn.handleEvent(event, window);
            rotateRightBtn.handleEvent(event, window);
            rotateLeftBtn.handleEvent(event, window);
            backBtn.handleEvent(event, window);
            forwardBtn.handleEvent(event, window);
        }
        
        window.clear(sf::Color(240, 240, 240));
        
        bst.draw(window);
        
        inputField.draw_text_input(window);
        insertBtn.draw_button(window);
        removeBtn.draw_button(window);
        searchBtn.draw_button(window);
        rotateRightBtn.draw_button(window);
        rotateLeftBtn.draw_button(window);
        backBtn.draw_button(window);
        forwardBtn.draw_button(window);
        
        window.draw(statusText);
        
        window.display();
    }
    
    return 0;
}
