#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>


namespace AppConfig {
    constexpr unsigned int WIN_WIDTH  = 850;
    constexpr unsigned int WIN_HEIGHT = 650;
    constexpr float NODE_RADIUS       = 28.f;
    constexpr float ROOT_X            = 425.f;
    constexpr float ROOT_Y            = 60.f;
    constexpr float INITIAL_OFFSET    = 210.f;
    constexpr float LEVEL_STEP        = 75.f;
    constexpr const char* FONT_PATH   = "arial.ttf";
}

struct Node {
    int data;
    Node* left  = nullptr;
    Node* right = nullptr;
    explicit Node(int val) : data(val) {}
};

class VisualBST {
private:
    Node* root = nullptr;
    int markedValue = 0;
    bool showHighlight = false;

    // Рекурсивная вставка
    Node* insertRecursive(Node* current, int value) {
        if (!current) return new Node(value);
        if (value < current->data)
            current->left = insertRecursive(current->left, value);
        else
            current->right = insertRecursive(current->right, value);
        return current;
    }

    // Рекурсивный поиск
    bool findRecursive(Node* current, int value) {
        if (!current) return false;
        if (current->data == value) return true;
        return (value < current->data) 
               ? findRecursive(current->left, value) 
               : findRecursive(current->right, value);
    }

    // Поиск минимального узла в правом поддереве
    Node* getLeftmost(Node* current) {
        while (current && current->left) current = current->left;
        return current;
    }

    // Рекурсивное удаление
    Node* removeRecursive(Node* current, int value) {
        if (!current) return nullptr;

        if (value < current->data)
            current->left = removeRecursive(current->left, value);
        else if (value > current->data)
            current->right = removeRecursive(current->right, value);
        else {
            // Случай 1: Лист
            if (!current->left && !current->right) {
                delete current;
                return nullptr;
            }
            // Случай 2: Один потомок
            if (!current->left) {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            if (!current->right) {
                Node* temp = current->left;
                delete current;
                return temp;
            }
            // Случай 3: Два потомка 
            Node* successor = getLeftmost(current->right);
            current->data = successor->data;
            current->right = removeRecursive(current->right, successor->data);
        }
        return current;
    }

    // Отрисовка дерева
    void renderTree(sf::RenderWindow& win, Node* node, 
                    float x, float y, float offset, const sf::Font& font) {
        if (!node) return;

        sf::CircleShape circle(AppConfig::NODE_RADIUS);
        circle.setPosition(x, y);
        circle.setFillColor(showHighlight && node->data == markedValue 
                            ? sf::Color(200, 50, 50) 
                            : sf::Color(235, 235, 245));
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2.f);
        win.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->data));
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        
        text.setPosition(x + AppConfig::NODE_RADIUS * 0.35f, 
                         y + AppConfig::NODE_RADIUS * 0.35f);
        win.draw(text);

        float nextY = y + AppConfig::LEVEL_STEP;
        if (node->left) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + AppConfig::NODE_RADIUS, y + AppConfig::NODE_RADIUS), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x - offset + AppConfig::NODE_RADIUS, nextY), sf::Color::Black)
            };
            win.draw(line, 2, sf::Lines);
            renderTree(win, node->left, x - offset, nextY, offset / 2.f, font);
        }
        if (node->right) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + AppConfig::NODE_RADIUS, y + AppConfig::NODE_RADIUS), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x + offset + AppConfig::NODE_RADIUS, nextY), sf::Color::Black)
            };
            win.draw(line, 2, sf::Lines);
            renderTree(win, node->right, x + offset, nextY, offset / 2.f, font);
        }
    }

public:
    VisualBST() = default;
    ~VisualBST() {}

    void add(int value) {
        root = insertRecursive(root, value);
        showHighlight = false;
    }

    void erase(int value) {
        root = removeRecursive(root, value);
        showHighlight = false;
    }

    bool lookup(int value) {
        bool found = findRecursive(root, value);
        markedValue = value;
        showHighlight = found;
        return found;
    }

    void draw(sf::RenderWindow& win, const sf::Font& font) {
        renderTree(win, root, AppConfig::ROOT_X, AppConfig::ROOT_Y, AppConfig::INITIAL_OFFSET, font);
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(AppConfig::WIN_WIDTH, AppConfig::WIN_HEIGHT), "Binary Search Tree");
    sf::Font font;
    if (!font.loadFromFile(AppConfig::FONT_PATH)) {
        std::cerr << "Ошибка: не удалось загрузить шрифт '" << AppConfig::FONT_PATH << "'\n";
        return 1;
    }

    VisualBST tree;
    std::string inputBuffer = "";
    std::string activeMode  = "ожидание";

    sf::Text uiText;
    uiText.setFont(font);
    uiText.setCharacterSize(18);
    uiText.setFillColor(sf::Color::Black);
    uiText.setPosition(15, AppConfig::WIN_HEIGHT - 45);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Обработка текстового ввода
            if (event.type == sf::Event::TextEntered) {
                if (std::isdigit(event.text.unicode) || event.text.unicode == '-') {
                    // Защита от повторного ввода минуса
                    if (event.text.unicode == '-' && !inputBuffer.empty()) continue;
                    inputBuffer += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == 8 && !inputBuffer.empty()) {
                    inputBuffer.pop_back(); // Backspace
                }
            }

            // Горячие клавиши
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) { activeMode = "добавить"; inputBuffer.clear(); }
                else if (event.key.code == sf::Keyboard::R) { activeMode = "удалить"; inputBuffer.clear(); }
                else if (event.key.code == sf::Keyboard::F) { activeMode = "поиск"; inputBuffer.clear(); }
                else if (event.key.code == sf::Keyboard::Enter && !inputBuffer.empty()) {
                    try {
                        int value = std::stoi(inputBuffer);
                        if (activeMode == "добавить") tree.add(value);
                        else if (activeMode == "удалить") tree.erase(value);
                        else if (activeMode == "поиск") {
                            std::cout << (tree.lookup(value) ? "[ОК] Найдено: " : "[!] Не найдено: ") 
                                      << value << "\n";
                        }
                    } catch (...) {
                        std::cout << "Ошибка преобразования ввода\n";
                    }
                    inputBuffer.clear();
                }
            }
        }

        // Рендер
        window.clear(sf::Color(240, 240, 245));
        tree.draw(window, font);

        std::string status = "Режим: " + activeMode + " | Ввод: " + 
                             (inputBuffer.empty() ? "_" : inputBuffer) +
                             " | A-добавить  R-удалить  F-поиск  Enter-применить";
        uiText.setString(status);
        window.draw(uiText);
        window.display();
    }

    return 0;
}