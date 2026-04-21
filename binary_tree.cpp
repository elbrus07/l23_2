#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <functional>
#include <sstream>
#include <cmath>

using namespace std;

// ==================== ОДИН УЗЕЛ ДЕРЕВА ====================
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;  // ДОБАВЛЕНО: ссылка на родителя (нужна для поворотов)
    sf::CircleShape circle;
    sf::Text text;
    bool highlighted;  // ДЛЯ ПОДСВЕТКИ ВЫБРАННОГО УЗЛА
    
    Node(int value, sf::Font& font) : data(value), left(nullptr), right(nullptr), parent(nullptr), highlighted(false) {
        circle.setRadius(25);
        circle.setFillColor(sf::Color(100, 150, 250));
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(25, 25);
        
        text.setFont(font);
        text.setString(to_string(value));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
    }
    
    void setPosition(float x, float y) {
        circle.setPosition(x, y);
        text.setPosition(x, y);
    }
    
    void highlight(bool on) {
        highlighted = on;
        if (on) {
            circle.setFillColor(sf::Color(255, 200, 100));  // Оранжевый
            circle.setOutlineColor(sf::Color::Red);
            circle.setOutlineThickness(3);
        } else {
            circle.setFillColor(sf::Color(100, 150, 250));  // Синий
            circle.setOutlineColor(sf::Color::Black);
            circle.setOutlineThickness(2);
        }
    }
};

// ==================== ДВОИЧНОЕ ДЕРЕВО ПОИСКА ====================
class BST {
private:
    Node* root;
    sf::Font font;
    sf::RenderWindow* window;
    bool needLayout;
    Node* selectedNode;  // ВЫБРАННЫЙ УЗЕЛ ДЛЯ ПОВОРОТА
    string message;      // СООБЩЕНИЕ О РЕЗУЛЬТАТЕ
    float messageTimer;
    
    // --- ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ---
    
    void updateParentLinks(Node* node, Node* parent) {
        if (!node) return;
        node->parent = parent;
        updateParentLinks(node->left, node);
        updateParentLinks(node->right, node);
    }
    
    Node* insert(Node* node, int value, Node* parent) {
        if (!node) {
            needLayout = true;
            Node* newNode = new Node(value, font);
            newNode->parent = parent;
            return newNode;
        }
        
        if (value < node->data)
            node->left = insert(node->left, value, node);
        else if (value > node->data)
            node->right = insert(node->right, value, node);
        
        return node;
    }
    
    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    
    Node* remove(Node* node, int value) {
        if (!node) return nullptr;
        
        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left && !node->right) {
                delete node;
                needLayout = true;
                return nullptr;
            }
            else if (!node->left) {
                Node* temp = node->right;
                delete node;
                needLayout = true;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                needLayout = true;
                return temp;
            }
            else {
                Node* successor = findMin(node->right);
                node->data = successor->data;
                node->text.setString(to_string(node->data));
                sf::FloatRect bounds = node->text.getLocalBounds();
                node->text.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
                node->right = remove(node->right, successor->data);
            }
        }
        return node;
    }
    
    bool search(Node* node, int value) {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }
    
    Node* findNode(Node* node, int value) {
        if (!node) return nullptr;
        if (value == node->data) return node;
        if (value < node->data) return findNode(node->left, value);
        return findNode(node->right, value);
    }
    
    int getHeight(Node* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
    
    void layout(Node* node, int x, int y, int xOffset, int level) {
        if (!node) return;
        
        node->setPosition(x, y);
        
        int childOffset = max(xOffset / 2, 30);
        
        if (node->left)
            layout(node->left, x - childOffset, y + 80, childOffset, level + 1);
        if (node->right)
            layout(node->right, x + childOffset, y + 80, childOffset, level + 1);
    }
    
    void drawLines(Node* node) {
        if (!node) return;
        
        if (node->left) {
            sf::Vertex line[] = {
                sf::Vertex(node->circle.getPosition(), sf::Color::Black),
                sf::Vertex(node->left->circle.getPosition(), sf::Color::Black)
            };
            window->draw(line, 2, sf::Lines);
            drawLines(node->left);
        }
        
        if (node->right) {
            sf::Vertex line[] = {
                sf::Vertex(node->circle.getPosition(), sf::Color::Black),
                sf::Vertex(node->right->circle.getPosition(), sf::Color::Black)
            };
            window->draw(line, 2, sf::Lines);
            drawLines(node->right);
        }
    }
    
    void drawNodes(Node* node) {
        if (!node) return;
        
        window->draw(node->circle);
        window->draw(node->text);
        
        drawNodes(node->left);
        drawNodes(node->right);
    }
    
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
    // ========== ПОВОРОТЫ ==========
    
    // ПРАВЫЙ ПОВОРОТ вокруг узла
    void rotateRight(Node* y) {
        if (!y || !y->left) {
            setMessage("Cannot rotate right: no left child");
            return;
        }
        
        Node* x = y->left;
        Node* parent = y->parent;
        
        // Переподвешиваем
        y->left = x->right;
        if (x->right) x->right->parent = y;
        
        x->right = y;
        y->parent = x;
        
        x->parent = parent;
        
        // Обновляем ссылку от родителя
        if (parent) {
            if (parent->left == y) parent->left = x;
            else parent->right = x;
        } else {
            root = x;
        }
        
        needLayout = true;
        setMessage("Right rotation around " + to_string(y->data));
    }
    
    // ЛЕВЫЙ ПОВОРОТ вокруг узла
    void rotateLeft(Node* x) {
        if (!x || !x->right) {
            setMessage("Cannot rotate left: no right child");
            return;
        }
        
        Node* y = x->right;
        Node* parent = x->parent;
        
        // Переподвешиваем
        x->right = y->left;
        if (y->left) y->left->parent = x;
        
        y->left = x;
        x->parent = y;
        
        y->parent = parent;
        
        // Обновляем ссылку от родителя
        if (parent) {
            if (parent->left == x) parent->left = y;
            else parent->right = y;
        } else {
            root = y;
        }
        
        needLayout = true;
        setMessage("Left rotation around " + to_string(x->data));
    }
    
    void setMessage(const string& msg) {
        message = msg;
        messageTimer = 3.0f;  // Показываем 3 секунды
    }
    
public:
    BST() : root(nullptr), window(nullptr), needLayout(true), selectedNode(nullptr), messageTimer(0) {
        if (!font.loadFromFile("arial.ttf")) {
            font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
        }
        message = "Ready";
    }
    
    ~BST() {
        clear(root);
    }
    
    void add(int value) {
        root = insert(root, value, nullptr);
        updateParentLinks(root, nullptr);
        setMessage("Inserted: " + to_string(value));
    }
    
    void erase(int value) {
        if (!exists(value)) {
            setMessage("Not found: " + to_string(value));
            return;
        }
        if (selectedNode && selectedNode->data == value) {
            selectNode(nullptr);  // Снимаем выделение
        }
        root = remove(root, value);
        updateParentLinks(root, nullptr);
        setMessage("Removed: " + to_string(value));
    }
    
    bool exists(int value) {
        return search(root, value);
    }
    
    // ВЫБРАТЬ УЗЕЛ ПО ЗНАЧЕНИЮ
    void selectNode(int value) {
        if (selectedNode) selectedNode->highlight(false);
        selectedNode = findNode(root, value);
        if (selectedNode) {
            selectedNode->highlight(true);
            setMessage("Selected: " + to_string(value));
        } else {
            setMessage("Node not found: " + to_string(value));
        }
    }
    
    void selectNode(Node* node) {
        if (selectedNode) selectedNode->highlight(false);
        selectedNode = node;
        if (selectedNode) {
            selectedNode->highlight(true);
            setMessage("Selected: " + to_string(selectedNode->data));
        }
    }
    
    // ПОВЕРНУТЬ ВЫБРАННЫЙ УЗЕЛ ВПРАВО
    void rotateSelectedRight() {
        if (!selectedNode) {
            setMessage("No node selected. Click on a node or enter value to select.");
            return;
        }
        rotateRight(selectedNode);
        // После поворота selectedNode мог измениться
        if (selectedNode->parent) {
            selectNode(selectedNode->parent);
        }
        updateParentLinks(root, nullptr);
    }
    
    // ПОВЕРНУТЬ ВЫБРАННЫЙ УЗЕЛ ВЛЕВО
    void rotateSelectedLeft() {
        if (!selectedNode) {
            setMessage("No node selected. Click on a node or enter value to select.");
            return;
        }
        rotateLeft(selectedNode);
        if (selectedNode->parent) {
            selectNode(selectedNode->parent);
        }
        updateParentLinks(root, nullptr);
    }
    
    // НАЙТИ УЗЕЛ ПОД МЫШКОЙ
    Node* findNodeAtPosition(float x, float y) {
        return findNodeAtPositionRec(root, x, y);
    }
    
    Node* findNodeAtPositionRec(Node* node, float x, float y) {
        if (!node) return nullptr;
        
        sf::Vector2f pos = node->circle.getPosition();
        float dx = pos.x - x;
        float dy = pos.y - y;
        float dist = sqrt(dx*dx + dy*dy);
        
        if (dist <= 30) {  // Радиус круга 25 + запас
            return node;
        }
        
        Node* leftResult = findNodeAtPositionRec(node->left, x, y);
        if (leftResult) return leftResult;
        
        return findNodeAtPositionRec(node->right, x, y);
    }
    
    void updateMessage(float deltaTime) {
        if (messageTimer > 0) {
            messageTimer -= deltaTime;
            if (messageTimer < 0) {
                message = "Ready";
            }
        }
    }
    
    void draw(sf::RenderWindow& win) {
        window = &win;
        
        if (needLayout && root) {
            int startOffset = 300;
            layout(root, win.getSize().x / 2, 80, startOffset, 0);
            needLayout = false;
        }
        
        if (root) {
            drawLines(root);
            drawNodes(root);
        }
    }
    
    void drawMessage(sf::RenderWindow& win, int x, int y) {
        sf::Text msgText;
        msgText.setFont(font);
        msgText.setString(message);
        msgText.setCharacterSize(16);
        msgText.setFillColor(sf::Color(50, 50, 50));
        msgText.setPosition(x, y);
        win.draw(msgText);
    }
    
    void drawInstructions(sf::RenderWindow& win, int x, int y) {
        sf::Text instr;
        instr.setFont(font);
        instr.setCharacterSize(14);
        instr.setFillColor(sf::Color(100, 100, 100));
        
        stringstream ss;
        ss << "Instructions:\n";
        ss << "• Click on a node to select it\n";
        ss << "• Enter value and press 'Select' to select by value\n";
        ss << "• Press 'Rotate Left' or 'Rotate Right' to rotate selected node\n";
        ss << "• Use Insert/Remove to modify tree\n";
        
        instr.setString(ss.str());
        instr.setPosition(x, y);
        win.draw(instr);
    }
};

// ==================== ПОЛЕ ДЛЯ ВВОДА ====================
class InputField {
private:
    sf::RectangleShape box;
    sf::Text display;
    string buffer;
    bool active;
    string label;
    sf::Text labelText;
    
public:
    InputField(int x, int y, int w, int h, const string& lbl, sf::Font& f) 
        : active(false), label(lbl) {
        box.setSize(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(1);
        
        display.setFont(f);
        display.setString("");
        display.setCharacterSize(20);
        display.setFillColor(sf::Color::Black);
        display.setPosition(x + 5, y + 5);
        
        labelText.setFont(f);
        labelText.setString(label);
        labelText.setCharacterSize(14);
        labelText.setFillColor(sf::Color(80, 80, 80));
        labelText.setPosition(x, y - 20);
    }
    
    void handleEvent(sf::Event& event, sf::RenderWindow& win) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
            active = box.getGlobalBounds().contains(mouse);
            box.setOutlineColor(active ? sf::Color::Blue : sf::Color::Black);
        }
        
        if (active && event.type == sf::Event::TextEntered) {
            char c = event.text.unicode;
            if (c == 8 && !buffer.empty()) {
                buffer.pop_back();
            }
            else if ((c >= '0' && c <= '9') || (c == '-' && buffer.empty())) {
                if (buffer.length() < 5) buffer += c;
            }
            display.setString(buffer);
        }
    }
    
    void draw(sf::RenderWindow& win) {
        win.draw(labelText);
        win.draw(box);
        win.draw(display);
    }
    
    int getValue() {
        if (buffer.empty()) return -1;
        return stoi(buffer);
    }
    
    void clear() {
        buffer.clear();
        display.setString("");
    }
};

// ==================== КНОПКА ====================
class Button {
private:
    sf::RectangleShape shape;
    sf::Text label;
    function<void()> action;
    
public:
    Button(int x, int y, int w, int h, const string& text, sf::Font& f) {
        shape.setSize(sf::Vector2f(w, h));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(220, 220, 220));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        
        label.setFont(f);
        label.setString(text);
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::Black);
        
        sf::FloatRect bounds = label.getLocalBounds();
        label.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
        label.setPosition(x + w/2, y + h/2);
    }
    
    void setAction(function<void()> callback) {
        action = callback;
    }
    
    void handleEvent(sf::Event& event, sf::RenderWindow& win) {
        sf::Vector2f mouse(sf::Mouse::getPosition(win));
        
        if (shape.getGlobalBounds().contains(mouse)) {
            shape.setFillColor(sf::Color(180, 180, 180));
            if (event.type == sf::Event::MouseButtonPressed && action) {
                action();
            }
        } else {
            shape.setFillColor(sf::Color(220, 220, 220));
        }
    }
    
    void draw(sf::RenderWindow& win) {
        win.draw(shape);
        win.draw(label);
    }
};

// ==================== ГЛАВНАЯ ПРОГРАММА ====================
int main() {
    BST tree;
    
    // Начальные значения (сбалансированные для демонстрации поворотов)
    int sampleData[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : sampleData) {
        tree.add(val);
    }
    
    int winWidth = 1300;
    int winHeight = 700;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Binary Search Tree Visualizer with Rotations");
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }
    
    // Поля ввода
    InputField valueField(winWidth - 220, 50, 200, 40, "Value:", font);
    InputField selectField(winWidth - 220, 130, 200, 40, "Select value:", font);
    
    // Кнопки
    Button insertBtn(winWidth - 220, 210, 200, 40, "Insert", font);
    Button removeBtn(winWidth - 220, 260, 200, 40, "Remove", font);
    Button selectBtn(winWidth - 220, 310, 200, 40, "Select", font);
    Button rotateLeftBtn(winWidth - 220, 380, 95, 40, "Rotate ←", font);
    Button rotateRightBtn(winWidth - 115, 380, 95, 40, "Rotate →", font);
    
    // Кнопки очистки
    Button clearSelectBtn(winWidth - 220, 430, 200, 30, "Clear Selection", font);
    
    // Часы для сообщений
    sf::Clock clock;
    
    // Назначаем действия
    insertBtn.setAction([&]() {
        int val = valueField.getValue();
        if (val != -1) {
            tree.add(val);
            valueField.clear();
        }
    });
    
    removeBtn.setAction([&]() {
        int val = valueField.getValue();
        if (val != -1) {
            tree.erase(val);
            valueField.clear();
        }
    });
    
    selectBtn.setAction([&]() {
        int val = selectField.getValue();
        if (val != -1) {
            tree.selectNode(val);
            selectField.clear();
        }
    });
    
    clearSelectBtn.setAction([&]() {
        tree.selectNode(nullptr);
    });
    
    rotateLeftBtn.setAction([&]() {
        tree.rotateSelectedLeft();
    });
    
    rotateRightBtn.setAction([&]() {
        tree.rotateSelectedRight();
    });
    
    // Главный цикл
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        tree.updateMessage(deltaTime);
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Обработка клика по узлу дерева
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                Node* clickedNode = tree.findNodeAtPosition(mouse.x, mouse.y);
                if (clickedNode) {
                    tree.selectNode(clickedNode);
                }
            }
            
            valueField.handleEvent(event, window);
            selectField.handleEvent(event, window);
            insertBtn.handleEvent(event, window);
            removeBtn.handleEvent(event, window);
            selectBtn.handleEvent(event, window);
            clearSelectBtn.handleEvent(event, window);
            rotateLeftBtn.handleEvent(event, window);
            rotateRightBtn.handleEvent(event, window);
        }
        
        window.clear(sf::Color(250, 250, 250));
        
        tree.draw(window);
        
        // Рисуем интерфейс
        valueField.draw(window);
        selectField.draw(window);
        insertBtn.draw(window);
        removeBtn.draw(window);
        selectBtn.draw(window);
        clearSelectBtn.draw(window);
        rotateLeftBtn.draw(window);
        rotateRightBtn.draw(window);
        
        tree.drawMessage(window, winWidth - 220, 490);
        tree.drawInstructions(window, winWidth - 220, 530);
        
        window.display();
    }
    
    return 0;
}
