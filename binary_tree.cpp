#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <functional>

using namespace std;

// ==================== ОДИН УЗЕЛ ДЕРЕВА ====================
// Хранит число, ссылки на детей, кружок и текст для рисования
class Node {
public:
    int data;
    Node* left;
    Node* right;
    sf::CircleShape circle;
    sf::Text text;
    
    Node(int value, sf::Font& font) : data(value), left(nullptr), right(nullptr) {
        // Настройка круга
        circle.setRadius(25);
        circle.setFillColor(sf::Color(100, 150, 250));
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(25, 25);
        
        // Настройка текста
        text.setFont(font);
        text.setString(to_string(value));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        
        // Центрируем текст внутри круга
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
    }
    
    void setPosition(float x, float y) {
        circle.setPosition(x, y);
        text.setPosition(x, y);
    }
};

// ==================== ДВОИЧНОЕ ДЕРЕВО ПОИСКА ====================
// Содержит все операции: вставка, удаление, поиск, рисование
class BST {
private:
    Node* root;           // Корень дерева
    sf::Font font;        // Шрифт для текста
    sf::RenderWindow* window;  // Окно для рисования
    
    // --- ВСПОМОГАТЕЛЬНЫЕ РЕКУРСИВНЫЕ МЕТОДЫ ---
    
    // Вставка числа (рекурсивно)
    Node* insert(Node* node, int value) {
        if (!node) return new Node(value, font);  // Пустое место → новый узел
        
        if (value < node->data)
            node->left = insert(node->left, value);   // Идём влево
        else if (value > node->data)
            node->right = insert(node->right, value); // Идём вправо
        
        return node;
    }
    
    // Поиск самого левого (минимального) узла
    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    
    // Удаление числа (рекурсивно)
    Node* remove(Node* node, int value) {
        if (!node) return nullptr;
        
        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            // Нашли узел для удаления
            if (!node->left && !node->right) {  // Нет детей
                delete node;
                return nullptr;
            }
            else if (!node->left) {              // Только правый ребёнок
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {             // Только левый ребёнок
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {                               // Два ребёнка
                Node* successor = findMin(node->right);
                node->data = successor->data;
                node->right = remove(node->right, successor->data);
            }
        }
        return node;
    }
    
    // Поиск числа (рекурсивно)
    bool search(Node* node, int value) {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }
    
    // Вычисление высоты дерева
    int getHeight(Node* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
    
    // Расстановка узлов по координатам
    void layout(Node* node, int x, int y, int xOffset, int level) {
        if (!node) return;
        
        node->setPosition(x, y);
        
        int childOffset = max(xOffset / 2, 30);  // Смещение для детей
        
        if (node->left)
            layout(node->left, x - childOffset, y + 80, childOffset, level + 1);
        if (node->right)
            layout(node->right, x + childOffset, y + 80, childOffset, level + 1);
    }
    
    // Рисование линий (связей между узлами)
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
    
    // Рисование кружков и текста
    void drawNodes(Node* node) {
        if (!node) return;
        
        window->draw(node->circle);
        window->draw(node->text);
        
        drawNodes(node->left);
        drawNodes(node->right);
    }
    
    // Очистка всей памяти
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
public:
    BST() : root(nullptr), window(nullptr) {
        // Загружаем шрифт (пробуем разные пути)
        if (!font.loadFromFile("arial.ttf")) {
            font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
        }
    }
    
    ~BST() {
        clear(root);
    }
    
    // Публичные методы (обёртки)
    void add(int value) {
        root = insert(root, value);
    }
    
    void erase(int value) {
        root = remove(root, value);
    }
    
    bool exists(int value) {
        return search(root, value);
    }
    
    // Главный метод отрисовки
    void draw(sf::RenderWindow& win) {
        window = &win;
        if (!root) return;
        
        int treeHeight = getHeight(root);
        int startOffset = 300;  // Начальное смещение для детей
        
        layout(root, win.getSize().x / 2, 80, startOffset, 0);
        drawLines(root);
        drawNodes(root);
    }
};

// ==================== ПОЛЕ ДЛЯ ВВОДА ЧИСЕЛ ====================
// Позволяет пользователю вводить числа с клавиатуры
class InputField {
private:
    sf::RectangleShape box;
    sf::Text display;
    string buffer;
    bool active;
    
public:
    InputField(int x, int y, int w, int h, sf::Font& f) : active(false) {
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
    }
    
    void handleEvent(sf::Event& event, sf::RenderWindow& win) {
        // Клик мыши — активируем/деактивируем поле
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
            active = box.getGlobalBounds().contains(mouse);
            box.setOutlineColor(active ? sf::Color::Blue : sf::Color::Black);
        }
        
        // Ввод текста, если активно
        if (active && event.type == sf::Event::TextEntered) {
            char c = event.text.unicode;
            if (c == 8 && !buffer.empty()) {      // Backspace
                buffer.pop_back();
            }
            else if (c >= '0' && c <= '9' && buffer.length() < 5) {  // Только цифры
                buffer += c;
            }
            display.setString(buffer);
        }
    }
    
    void draw(sf::RenderWindow& win) {
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
// Простая кнопка с текстом и действием при нажатии
class Button {
private:
    sf::RectangleShape shape;
    sf::Text label;
    function<void()> action;
    bool hovered;
    
public:
    Button(int x, int y, int w, int h, const string& text, sf::Font& f)
        : hovered(false) {
        shape.setSize(sf::Vector2f(w, h));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(220, 220, 220));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        
        label.setFont(f);
        label.setString(text);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::Black);
        
        // Центрируем текст
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
    // Создаём дерево
    BST tree;
    
    // Добавляем начальные значения для примера
    int sampleData[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : sampleData) {
        tree.add(val);
    }
    
    // Настройки окна
    int winWidth = 1200;
    int winHeight = 700;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Binary Search Tree Visualizer");
    
    // Шрифт
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }
    
    // Элементы интерфейса
    InputField inputField(winWidth - 200, 50, 180, 40, font);
    Button insertBtn(winWidth - 200, 110, 180, 40, "Insert", font);
    Button removeBtn(winWidth - 200, 170, 180, 40, "Remove", font);
    Button searchBtn(winWidth - 200, 230, 180, 40, "Search", font);
    
    // Текст для вывода результатов
    sf::Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(16);
    statusText.setFillColor(sf::Color(50, 50, 50));
    statusText.setPosition(winWidth - 200, 300);
    statusText.setString("Ready");
    
    // Назначаем действия кнопкам
    insertBtn.setAction([&]() {
        int val = inputField.getValue();
        if (val != -1) {
            tree.add(val);
            statusText.setString("Inserted: " + to_string(val));
            inputField.clear();
        } else {
            statusText.setString("Error: enter a number");
        }
    });
    
    removeBtn.setAction([&]() {
        int val = inputField.getValue();
        if (val != -1) {
            tree.erase(val);
            statusText.setString("Removed: " + to_string(val));
            inputField.clear();
        } else {
            statusText.setString("Error: enter a number");
        }
    });
    
    searchBtn.setAction([&]() {
        int val = inputField.getValue();
        if (val != -1) {
            bool found = tree.exists(val);
            if (found) {
                statusText.setString("Found: " + to_string(val));
            } else {
                statusText.setString("Not found: " + to_string(val));
            }
            inputField.clear();
        } else {
            statusText.setString("Error: enter a number");
        }
    });
    
    // Главный цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            inputField.handleEvent(event, window);
            insertBtn.handleEvent(event, window);
            removeBtn.handleEvent(event, window);
            searchBtn.handleEvent(event, window);
        }
        
        // Отрисовка
        window.clear(sf::Color(250, 250, 250));
        
        tree.draw(window);          // Рисуем дерево
        
        inputField.draw(window);
        insertBtn.draw(window);
        removeBtn.draw(window);
        searchBtn.draw(window);
        window.draw(statusText);
        
        window.display();
    }
    
    return 0;
}
