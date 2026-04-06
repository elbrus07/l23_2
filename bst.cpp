#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <functional>
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
    
    bool search(Node* node, int value) {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    // Рекурсивная вставка
    Node* insert(Node* node, int value) {
        if (node == nullptr) return new Node(value, font);
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
        } else {
            // Нашли узел для удаления
            
            // Случай 1: нет детей
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Случай 2: только правый ребенок
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Случай 3: только левый ребенок
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Случай 4: два ребенка
            else {
                // Находим минимальный узел в правом поддереве
                Node* successor = minNode(node->right);
                // Копируем значение
                node->setData(successor->data);
                // Удаляем successor из правого поддерева
                node->right = remove(node->right, successor->data);
            }
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
    
    int getMaxLevel(Node* node, int level = 0) {
        if (!node) return level;
        return std::max(getMaxLevel(node->left, level + 1), getMaxLevel(node->right, level + 1));
    }
    
    // Расчет позиций узлов
    void calculatePositions(Node* node, int x, int y, int xBaseOffset, int level) {
        if (node == nullptr) return;
        
        node->setPosition(x, y);
        
        int xOffset = xBaseOffset;
        
        for (int i = 0; i < level; i++) {
            xOffset = xOffset*2 + xBaseOffset;
        }
        
        // Рекурсивно расставляем детей со смещением
        if (node->left) {
            calculatePositions(node->left, x - xOffset, y + 70, xBaseOffset, level-1);
        }
        if (node->right) {
            calculatePositions(node->right, x + xOffset, y + 70, xBaseOffset, level-1);
        }
    }
    
    // Рисование связей (линий)
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
    
    // Рисование узлов
    void drawNodes(Node* node) {
        if (node == nullptr) return;
        
        window->draw(node->circle);
        window->draw(node->text);
        
        drawNodes(node->left);
        drawNodes(node->right);
    }
    

public:
    BinarySearchTree() : root(nullptr) {
        if (!font.loadFromFile("fonts/Caladea-Regular.ttf"))
        {
            std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
            return ;
        }
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
    
    void draw(sf::RenderWindow &win) {
        window = &win;
        if (root == nullptr) return;
        
        int level = getMaxLevel(root);
        
        // Рассчитываем позиции (начальная позиция в центре окна)
        calculatePositions(root, (win.getSize().x-200)/2, 80, 4, level);
        
        // Рисуем линии
        drawLines(root);
        
        // Рисуем узлы
        drawNodes(root);
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
        
        // Настройка текста для ввода
        inputText.setFont(this->font);
        inputText.setString(str);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(this->x, this->y);
        
        // Настройка фона поля ввода
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
    
    // Обновление ввода
    void handleEvent(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            // Проверка клика по полю
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (inputBox.getGlobalBounds().contains(mousePos)) {
                setActive(true);
            } else {
                setActive(false);
            }
        }

        if (active && event.type == sf::Event::TextEntered) {
            char c = event.text.unicode;

            // Обработка Backspace
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
    function<void()> onClickAction;  // Действие при нажатии
    
public:
    Button(int x, int y, int w, int h, sf::Font& font, string str = "", function<void()> action = nullptr) {
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
        text.setPosition(this->x, this->y);
        
        // Центрируем текст
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, 
                      textRect.top + textRect.height/2.0f);
        text.setPosition(x + w/2.0f, y + h/2.0f);
    }
    
    void draw_button(sf::RenderWindow &window) {
        // Меняем цвет при наведении
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
                    onClickAction();  // Выполняем действие
                }
            }
        } else {
            isHovered = false;
        }
    }
    
    void setAction(std::function<void()> action) {
        onClickAction = action;
    }
};

int main() {
    BinarySearchTree bst;

    int arr[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 45, 55, 65, 75, 85}; 
    
    for (int i: arr) {
        bst.insert(i);
    }
    
    bst.print();
    
    int width = 1000;
    int height = 800;
    
    sf::RenderWindow window(sf::VideoMode(width + 200, height), "Binary Search Tree", 
                           sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("fonts/Caladea-Regular.ttf")) {
        std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
        return 1;
    }
    
    TextInput inputField(1020, 50, 180, 40, font);
    
    // Статусная строка
    sf::Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::Black);
    statusText.setPosition(1015, 400);
    statusText.setString("Ready");
    
    // Создаем кнопки с действиями
    Button insertBtn(1015, 120, 180, 40, font, "Insert", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            bst.insert(value);
            statusText.setString("Inserted: " + currentInput);
            inputField.setActive(false);
        } else {
            statusText.setString("Error: Empty input!");
        }
    });
    
    Button removeBtn(1015, 180, 180, 40, font, "Remove", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            bst.remove(value);
            statusText.setString("Removed: " + currentInput);
            inputField.setActive(false);
        } else {
            statusText.setString("Error: Empty input!");
        }
    });
    
    Button searchBtn(1015, 240, 180, 40, font, "Search", [&]() {
        string currentInput = inputField.get_text();
        if (!currentInput.empty()) {
            int value = stoi(currentInput);
            // ВАЖНО: нужно добавить метод search в класс BinarySearchTree
            if (bst.search(value)) {
                 statusText.setString("Found: " + currentInput);
            } else {
                 statusText.setString("Not found: " + currentInput);
            }
            inputField.setActive(false);
        } else {
            statusText.setString("Error: Empty input!");
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
            
        }
        
        window.clear(sf::Color(240, 240, 240));
        
        bst.draw(window);
        
        inputField.draw_text_input(window);
        insertBtn.draw_button(window);
        removeBtn.draw_button(window);
        searchBtn.draw_button(window);
        
        window.draw(statusText);
        
        window.display();
    }
    
    return 0;
}
