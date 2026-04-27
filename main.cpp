#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// ƒерево
class Der {
public:
    Der() : root(nullptr) {}
    ~Der() { clear(root); }

    void insert(int value) {
        root = insertRec(root, value);
    }

    void remove(int value) {
        root = removeRec(root, value);
    }

    bool contains(int value) const {
        return containsRec(root, value);
    }

    Node* getRoot() const { return root; }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void buildBalanced(const std::vector<int>& values) {
        clear();
        root = buildBalancedRec(values, 0, values.size() - 1);
    }

private:
    Node* root;

    Node* insertRec(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = insertRec(node->left, value);
        else if (value > node->value)
            node->right = insertRec(node->right, value);
        // если равны Ц ничего не делаем
        return node;
    }

    Node* removeRec(Node* node, int value) {
        if (!node) return nullptr;
        if (value < node->value)
            node->left = removeRec(node->left, value);
        else if (value > node->value)
            node->right = removeRec(node->right, value);
        else {
            // найден удал€емый узел
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                // два потомка: ищем минимальный в правом поддереве
                Node* minNode = findMin(node->right);
                node->value = minNode->value;
                node->right = removeRec(node->right, minNode->value);
            }
        }
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    bool containsRec(Node* node, int value) const {
        if (!node) return false;
        if (value == node->value) return true;
        if (value < node->value) return containsRec(node->left, value);
        else return containsRec(node->right, value);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* buildBalancedRec(const std::vector<int>& values, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        Node* node = new Node(values[mid]);
        node->left = buildBalancedRec(values, start, mid - 1);
        node->right = buildBalancedRec(values, mid + 1, end);
        return node;
    }
};

// геометри€
int countNodes(Node* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

void computePositions(Node* node, int depth, int& inorderIndex,
    float spacingX, float leftMargin, float spacingY,
    std::unordered_map<Node*, sf::Vector2f>& positions) {
    if (!node) return;
    computePositions(node->left, depth + 1, inorderIndex, spacingX, leftMargin, spacingY, positions);
    float x = leftMargin + inorderIndex * spacingX;
    float y = 100.0f + depth * spacingY;   // отступ сверху 100
    positions[node] = sf::Vector2f(x, y);
    inorderIndex++;
    computePositions(node->right, depth + 1, inorderIndex, spacingX, leftMargin, spacingY, positions);
}

void drawLines(sf::RenderWindow& window,
    const std::unordered_map<Node*, sf::Vector2f>& positions,
    Node* root) {
    if (!root) return;
    // рекурсивно рисуем линии от родител€ к дет€м
    auto it = positions.find(root);
    if (it != positions.end()) {
        sf::Vector2f parentPos = it->second;
        if (root->left) {
            auto childIt = positions.find(root->left);
            if (childIt != positions.end()) {
                sf::Vertex line[] = {
                    sf::Vertex(parentPos, sf::Color::Black),
                    sf::Vertex(childIt->second, sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);
            }
        }
        if (root->right) {
            auto childIt = positions.find(root->right);
            if (childIt != positions.end()) {
                sf::Vertex line[] = {
                    sf::Vertex(parentPos, sf::Color::Black),
                    sf::Vertex(childIt->second, sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }
    drawLines(window, positions, root->left);
    drawLines(window, positions, root->right);
}

void drawNodes(sf::RenderWindow& window,
    const std::unordered_map<Node*, sf::Vector2f>& positions,
    sf::Font& font) {
    const float radius = 20.0f;
    const sf::Color fillColor = sf::Color::White;
    const sf::Color outlineColor = sf::Color::Black;

    for (const auto& pair : positions) {
        Node* node = pair.first;
        sf::Vector2f pos = pair.second;

        //кружок
        sf::CircleShape circle(radius);
        circle.setFillColor(fillColor);
        circle.setOutlineColor(outlineColor);
        circle.setOutlineThickness(2.0f);
        circle.setOrigin(radius, radius);
        circle.setPosition(pos);
        window.draw(circle);

        //текст
        sf::Text text(std::to_string(node->value), font, 18);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(pos);
        window.draw(text);
    }
}

// интерфейс
class InputBox {
public:
    InputBox(sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size)
        : rect(size), text("", font, 20), active(false) {
        rect.setPosition(position);
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2.0f);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position.x + 10, position.y + 5);
    }

    void handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::FloatRect bounds = rect.getGlobalBounds();
            if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                active = true;
            }
            else {
                active = false;
            }
        }
        if (active && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) { 
                if (!inputString.empty())
                    inputString.pop_back();
            }
            else if (event.text.unicode == 13) { // ввод
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                char c = static_cast<char>(event.text.unicode);
                // разрешаем цифры и знак минус (только в начале)
                if (std::isdigit(c) || (c == '-' && inputString.empty()))
                    inputString.push_back(c);
            }
            text.setString(inputString + (active ? "_" : ""));
        }
    }

    std::string getString() const { return inputString; }
    void clear() { inputString.clear(); text.setString(""); }
    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }

    void draw(sf::RenderWindow& window) {
        window.draw(rect);
        window.draw(text);
    }

    sf::FloatRect getGlobalBounds() const { return rect.getGlobalBounds(); }

private:
    sf::RectangleShape rect;
    sf::Text text;
    std::string inputString;
    bool active;
};

class Button {
public:
    Button(sf::Font& font, const std::string& label, const sf::Vector2f& position, const sf::Vector2f& size)
        : rect(size), text(label, font, 20), pressed(false) {
        rect.setPosition(position);
        rect.setFillColor(sf::Color(200, 200, 200));
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2.0f);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
    }

    bool handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (rect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                pressed = true;
                return true;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && pressed) {
            pressed = false;
            if (rect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                return true;
            }
        }
        return false;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rect);
        window.draw(text);
    }

private:
    sf::RectangleShape rect;
    sf::Text text;
    bool pressed;
};

// мане
int main() {
    const unsigned int windowWidth = 1280;
    const unsigned int windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Derevo");
    window.setFramerateLimit(60);

    // шрифт
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // системный шрифт дл€ Linux/Windows
        if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf") &&
            !font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error loading font. Place arial.ttf in working directory." << std::endl;
            return -1;
        }
    }

    // инициализаци€
    Der tree;
    std::vector<int> initialValues = { 1, 3, 5, 7, 11, 13, 17 };
    tree.buildBalanced(initialValues);

    // интерфейс
    InputBox inputBox(font, sf::Vector2f(20, 20), sf::Vector2f(200, 35));
    Button addButton(font, "Dobavit", sf::Vector2f(240, 20), sf::Vector2f(100, 35));
    Button removeButton(font, "Udalit", sf::Vector2f(360, 20), sf::Vector2f(100, 35));

    sf::Text statusText("Gotovo", font, 18);
    statusText.setFillColor(sf::Color::Black);
    statusText.setPosition(20, 70);

    // параметры
    const float verticalSpacing = 80.0f;
    const float horizontalMargin = 80.0f;

    std::unordered_map<Node*, sf::Vector2f> positions;

    // осн
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(viewRect));
            }

            // обработка интерфейс
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            inputBox.handleEvent(event, mousePos);

            if (addButton.handleEvent(event, mousePos)) {
                std::string str = inputBox.getString();
                if (!str.empty()) {
                    try {
                        int val = std::stoi(str);
                        if (tree.contains(val)) {
                            statusText.setString("Element " + std::to_string(val) + " uzhe ispolzuetsya.");
                        }
                        else {
                            tree.insert(val);
                            statusText.setString("Vstavili " + std::to_string(val));
                            inputBox.clear();
                        }
                    }
                    catch (...) {
                        statusText.setString("Napishi normalno. Ciframi.");
                    }
                }
                else {
                    statusText.setString("Vvedi chislo.");
                }
                // деактивируем ввод после нажати€ кнопки
                inputBox.setActive(false);
            }
            else if (removeButton.handleEvent(event, mousePos)) {
                std::string str = inputBox.getString();
                if (!str.empty()) {
                    try {
                        int val = std::stoi(str);
                        if (!tree.contains(val)) {
                            statusText.setString("Elementa " + std::to_string(val) + " net. Smotri vnimatelnee.");
                        }
                        else {
                            tree.remove(val);
                            statusText.setString("Udalen " + std::to_string(val));
                            inputBox.clear();
                        }
                    }
                    catch (...) {
                        statusText.setString("Napishi normalno. Ciframi.");
                    }
                }
                else {
                    statusText.setString("Vvedi chislo.");
                }
                inputBox.setActive(false);
            }

            // если Enter нажат Ц добавл€ем
            if (event.type == sf::Event::TextEntered && event.text.unicode == 13 && inputBox.isActive()) {
                std::string str = inputBox.getString();
                if (!str.empty()) {
                    try {
                        int val = std::stoi(str);
                        if (tree.contains(val)) {
                            statusText.setString("Element " + std::to_string(val) + " uzhe ispolzuetsya.");
                        }
                        else {
                            tree.insert(val);
                            statusText.setString("Vstavlen " + std::to_string(val));
                            inputBox.clear();
                        }
                    }
                    catch (...) {
                        statusText.setString("Napishi normalno. Ciframi.");
                    }
                }
                inputBox.setActive(false);
            }
        }

        // пересчет
        positions.clear();
        Node* root = tree.getRoot();
        if (root) {
            int nodeCount = countNodes(root);
            float availableWidth = window.getSize().x - 2 * horizontalMargin;
            float spacingX = (nodeCount > 1) ? availableWidth / (nodeCount - 1) : availableWidth;
            if (spacingX < 40.0f) spacingX = 40.0f; // минимум дл€ читаемости
            int inorderIndex = 0;
            computePositions(root, 0, inorderIndex, spacingX, horizontalMargin, verticalSpacing, positions);
        }

        // отрисовка
        window.clear(sf::Color(240, 240, 240));

        // рисуем дерево
        if (root && !positions.empty()) {
            drawLines(window, positions, root);
            drawNodes(window, positions, font);
        }
        else {
            sf::Text emptyText("Derevo pustoe. Kak karman studenta.", font, 24);
            emptyText.setFillColor(sf::Color::Black);
            emptyText.setPosition(window.getSize().x / 2.0f - 80, window.getSize().y / 2.0f);
            window.draw(emptyText);
        }

        // рисуем интерфейс
        inputBox.draw(window);
        addButton.draw(window);
        removeButton.draw(window);
        window.draw(statusText);

        window.display();
    }

    return 0;
}