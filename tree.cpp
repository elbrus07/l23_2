#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <sstream>
#include <memory>

// ============================================
// СТРУКТУРА УЗЛА ДЕРЕВА (вместо класса)
// ============================================

struct Uzel {
    int data;
    Uzel* left;
    Uzel* right;
    sf::CircleShape circle;
    sf::Text text;
    sf::Font* font;

    Uzel(int value, sf::Font& f) : data(value), left(nullptr), right(nullptr) {
        font = &f;

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
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
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

    void updateSize(float newRadius) {
        circle.setRadius(newRadius);
        circle.setOrigin(newRadius, newRadius);
        text.setCharacterSize(static_cast<unsigned int>(newRadius * 0.8f));
        updateText(data);  // Обновляем позицию текста
    }
};

// ============================================
// КЛАСС ДВОИЧНОГО ДЕРЕВА ПОИСКА
// ============================================

class BinarySearchTree {
private:    
    Uzel* root;     // Корень дерева
    sf::Font* font;

    // Вспомогательные рекурсивные функции
    Uzel* insertRecursive(Uzel* node, int value) {
        if (node == nullptr) {
            return new Uzel(value, *font);     // если узел пуст то создается новый  узел
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);    //если новое значение меньше узла то новое значение уходит влево
        }
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);      //если новое значение больше узла то новое значение уходит вправо
        }
        return node;
    }

    Uzel* findMin(Uzel* node) {     //поиск минимального значения ( самого левого)
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

        //рекурсивное удаление
    Uzel* removeRecursive(Uzel* node, int value) {
        if (node == nullptr) {
            return nullptr; //// Элемент не найден
        }

        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        }
        else {
            // Нашли узел для удаления
            // первый случай Нет левого ребенка (Правый ребенок встает на место удаляемого)
            if (node->left == nullptr) {
                Uzel* temp = node->right;
                delete node;
                return temp;
            }
            // второй случай Нет правого ребенка(Левый ребенок встает на место)
            else if (node->right == nullptr) {
                Uzel* temp = node->left;
                delete node;
                return temp;
            }

            // третий случай оба ребенка существуют (Находим минимум справа, копируем значение, удаляем минимум)
            Uzel* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = removeRecursive(node->right, minNode->data);
        }
        return node;
    }

    //поиск
    bool searchRecursive(Uzel* node, int value) const {
        if (node == nullptr) return false; //Не нашли
        if (value == node->data) return true;       // Нашли
        if (value < node->data) return searchRecursive(node->left, value);  // Ищем слева
        return searchRecursive(node->right, value);     // Ищем справа
    }

    void clearRecursive(Uzel* node) {
        if (node == nullptr) return;
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }

    void inorderRecursive(Uzel* node, std::vector<int>& result) const {
        if (node == nullptr) return;
        inorderRecursive(node->left, result);
        result.push_back(node->data);
        inorderRecursive(node->right, result);
    }

    int getHeightRecursive(Uzel* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(getHeightRecursive(node->left), getHeightRecursive(node->right));
    }

    // Функция для получения количества узлов на каждом уровне
    void getNodesPerLevel(Uzel* node, int level, std::vector<int>& nodesPerLevel) const {
        if (node == nullptr) return;

        if (level >= nodesPerLevel.size()) {
            nodesPerLevel.push_back(0);
        }
        nodesPerLevel[level]++;

        getNodesPerLevel(node->left, level + 1, nodesPerLevel);
        getNodesPerLevel(node->right, level + 1, nodesPerLevel);
    }

public:
    BinarySearchTree(sf::Font& f) : root(nullptr), font(&f) {}   // создаем пустое дерево и передаем шрифт

    ~BinarySearchTree() {   // очищаем память
        clear();
    }

    void insert(int value) {    //Добавляет число в дерево
        root = insertRecursive(root, value);
    }

    bool remove(int value) {    //Удаляет число из дерева
        if (!search(value)) return false;
        root = removeRecursive(root, value);
        return true;
    }

    bool search(int value) const {  //Проверяет, есть ли число
        return searchRecursive(root, value);
    }

    void clear() {      //Удаляет все узлы
        clearRecursive(root);
        root = nullptr;
    }

    bool isEmpty() const {      //Проверяет, пустое ли дерево
        return root == nullptr;
    }

    std::vector<int> inorder() const {
        std::vector<int> result;
        inorderRecursive(root, result);
        return result;
    }

    int getHeight() const {     //Возвращает высоту дерева
        return getHeightRecursive(root);
    }

    Uzel* getRoot() const {
        return root;
    }

    // Получить максимальное количество узлов на одном уровне (Возвращает максимум узлов на одном уровне)
    int getMaxNodesOnLevel() const {
        std::vector<int> nodesPerLevel;
        getNodesPerLevel(root, 0, nodesPerLevel);

        int maxNodes = 0;
        for (int count : nodesPerLevel) {
            if (count > maxNodes) maxNodes = count;
        }
        return maxNodes;
    }
};

// ============================================
// КЛАСС ДЛЯ ВИЗУАЛИЗАЦИИ ДЕРЕВА (С АДАПТИВНЫМ РАССТОЯНИЕМ)
// ============================================

class TreeVisualizer {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    float RADIUS;
    float LEVEL_HEIGHT;  // Расстояние между уровнями
    float HORIZONTAL_FACTOR; //коэффициент горизонтального расстояния
    float START_X;       // Начальная X координата (центр окна)
    float START_Y;        // Начальная Y координата

    // Функция для расчета размера в зависимости от глубины
    void calculateScale(int treeHeight) {
        // Чем выше дерево, тем меньше элементы
        if (treeHeight <= 4) {
            RADIUS = 25.0f;
            LEVEL_HEIGHT = 70.0f;
            HORIZONTAL_FACTOR = 1.0f;
            START_X = 500.0f;
            START_Y = 80.0f;
        } else if (treeHeight <= 6) {
            RADIUS = 20.0f;      // меньше кружки
            LEVEL_HEIGHT = 55.0f;
            HORIZONTAL_FACTOR = 0.8f;// меньше расстояние
            START_X = 500.0f;
            START_Y = 60.0f;
        } else if (treeHeight <= 8) {
            RADIUS = 16.0f;      // еще меньше
            LEVEL_HEIGHT = 45.0f;
            HORIZONTAL_FACTOR = 0.65f;
            START_X = 500.0f;
            START_Y = 50.0f;
        } else {
            RADIUS = 12.0f;      // самые маленькие
            LEVEL_HEIGHT = 35.0f;
            HORIZONTAL_FACTOR = 0.5f;
            START_X = 500.0f;
            START_Y = 40.0f;
        }
    }

    // Получение максимальной глубины дерева
    int getMaxLevel(Uzel* node, int level = 0) {
        if (node == nullptr) return level;
        return std::max(getMaxLevel(node->left, level + 1),
            getMaxLevel(node->right, level + 1));
    }

    // Расчет позиций узлов 
    void calculatePositions(Uzel* node, int x, int y, int xBaseOffset, int level) {
        if (node == nullptr) return;

        node->setPosition(x, y);

        int xOffset = xBaseOffset;

        // Увеличиваем смещение для каждого уровня
        for (int i = 0; i < level; i++) {
            xOffset = xOffset * 2 + xBaseOffset;
        }

        //  Смещение зависит от RADIUS
        float horizontalShift = xOffset * (RADIUS / 25.0f) * HORIZONTAL_FACTOR;

        if (node->left) {
            calculatePositions(node->left, x - horizontalShift, y + LEVEL_HEIGHT, xBaseOffset, level - 1);
        }
        if (node->right) {
            calculatePositions(node->right, x + horizontalShift, y + LEVEL_HEIGHT, xBaseOffset, level - 1);
        }
    }

    // Рисование связей (линий) 
    void drawLines(Uzel* node) {
        if (node == nullptr) return;

        sf::VertexArray lines(sf::Lines);

        //  Толщина линии зависит от RADIUS
        float lineThickness = RADIUS / 12.5f;

        if (node->left) {
            lines.append(sf::Vertex(node->circle.getPosition(), sf::Color::Black));
            lines.append(sf::Vertex(node->left->circle.getPosition(), sf::Color::Black));
            window.draw(lines);
            drawLines(node->left);
        }

        if (node->right) {
            lines.append(sf::Vertex(node->circle.getPosition(), sf::Color::Black));
            lines.append(sf::Vertex(node->right->circle.getPosition(), sf::Color::Black));
            window.draw(lines);
            drawLines(node->right);
        }
    }

    // Рисование узлов
    void drawNodes(Uzel* node) {
        if (node == nullptr) return;

        window.draw(node->circle);
        window.draw(node->text);

        drawNodes(node->left);
        drawNodes(node->right);
    }

public:
    TreeVisualizer(sf::RenderWindow& win, sf::Font& f) : window(win), font(f), RADIUS(25), LEVEL_HEIGHT(70), HORIZONTAL_FACTOR(1.0f), START_X(500), START_Y(80) {}


    // Обновление размеров всех узлов
    void updateNodesSize(Uzel* node) {
        if (node == nullptr) return;

        // Обновляем кружок
        node->circle.setRadius(RADIUS);
        node->circle.setOrigin(RADIUS, RADIUS);

        // Обновляем текст
        node->text.setCharacterSize(static_cast<unsigned int>(RADIUS * 0.8f));

        // Рекурсивно обновляем детей
        updateNodesSize(node->left);
        updateNodesSize(node->right);
    }

    void draw(const BinarySearchTree& tree) {
        Uzel* root = tree.getRoot();
        if (root == nullptr) {
            sf::Text emptyText;
            emptyText.setFont(font);
            emptyText.setString("derevo pusto");
            emptyText.setCharacterSize(20);
            emptyText.setFillColor(sf::Color::Red);
            emptyText.setPosition(START_X - 100, START_Y + 100);
            window.draw(emptyText);
            return;
        }
        // Получаем высоту дерева
        int treeHeight = tree.getHeight();

        //  расчитываем масштаб  в зависимости от высоты
        calculateScale(treeHeight);

        // Обновляем размеры кружков у всех узлов
        updateNodesSize(root);

        // Получаем максимальную глубину дерева
        int level = getMaxLevel(root);

        // Базовое смещение 
        int baseOffset = (treeHeight <= 4) ? 4 : (treeHeight <= 6) ? 6 : (treeHeight <= 8) ? 8 : 10;
        baseOffset = static_cast<int>(baseOffset * HORIZONTAL_FACTOR);

        // Рассчитываем позиции (начальная позиция в центре окна)
        calculatePositions(root, START_X, START_Y, baseOffset, level);

        // Рисуем линии
        drawLines(root);

        // Рисуем узлы
        drawNodes(root);
    }
};

// ============================================
// КЛАСС ПОЛЬЗОВАТЕЛЬСКОГО ИНТЕРФЕЙСА
// ============================================

class UI {
private:
    sf::Font& font;
    sf::RectangleShape inputBox;
    sf::RectangleShape inputBo;
    sf::RectangleShape addButton;
    sf::RectangleShape removeButton;
    sf::RectangleShape searchButton;
    sf::RectangleShape clearButton;
    sf::Text inputText;
    sf::Text addText;
    sf::Text removeText;
    sf::Text searchText;
    sf::Text clearText;
    sf::Text statusText;
    sf::Text titleText;
    

    std::string currentInput;
    bool isActive;
    sf::Clock statusClock;

public:
    UI(sf::Font& f) : font(f), currentInput(""), isActive(false) {
        inputBo.setSize(sf::Vector2f(300, 700));
        inputBo.setPosition(1200, 0);
        inputBo.setFillColor(sf::Color::White);
        inputBo.setOutlineColor(sf::Color::Black);
        inputBo.setOutlineThickness(1);
        

        // Поле ввода
        inputBox.setSize(sf::Vector2f(150, 30));
        inputBox.setPosition(1225, 50);
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineColor(sf::Color::Black);
        inputBox.setOutlineThickness(2);

        // Кнопка ADD
        addButton.setSize(sf::Vector2f(80, 30));
        addButton.setPosition(1250, 100);
        addButton.setFillColor(sf::Color::White);
        addButton.setOutlineColor(sf::Color::Black);
        addButton.setOutlineThickness(1);

        // Кнопка REMOVE
        removeButton.setSize(sf::Vector2f(80, 40));
        removeButton.setPosition(1250, 150);
        removeButton.setFillColor(sf::Color::White);
        removeButton.setOutlineColor(sf::Color::Black);
        removeButton.setOutlineThickness(1);

        // Кнопка SEARCH
        searchButton.setSize(sf::Vector2f(80, 40));
        searchButton.setPosition(1250,200);
        searchButton.setFillColor(sf::Color::White);
        searchButton.setOutlineColor(sf::Color::Black);
        searchButton.setOutlineThickness(1);

        // Кнопка CLEAR
        clearButton.setSize(sf::Vector2f(80, 40));
        clearButton.setPosition(1250, 250);
        clearButton.setFillColor(sf::Color::White);
        clearButton.setOutlineColor(sf::Color::Black);
        clearButton.setOutlineThickness(1);

        // Тексты на кнопках
        addText.setFont(font);
        addText.setString("ADD");
        addText.setCharacterSize(16);
        addText.setFillColor(sf::Color::Black);
        addText.setPosition(1250, 100);

        removeText.setFont(font);
        removeText.setString("DEL");
        removeText.setCharacterSize(16);
        removeText.setFillColor(sf::Color::Black);
        removeText.setPosition(1250, 150);

        searchText.setFont(font);
        searchText.setString("FIND");
        searchText.setCharacterSize(16);
        searchText.setFillColor(sf::Color::Black);
        searchText.setPosition(1250, 200);

        clearText.setFont(font);
        clearText.setString("CLEAR");
        clearText.setCharacterSize(14);
        clearText.setFillColor(sf::Color::Black);
        clearText.setPosition(1250, 250);

        // Поле для ввода текста
        inputText.setFont(font);
        inputText.setCharacterSize(16);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(1225, 50);

        // Текст статуса
        statusText.setFont(font);
        statusText.setCharacterSize(16);
        statusText.setFillColor(sf::Color::Blue);
        statusText.setPosition(125, 110);

        // Заголовок
        titleText.setFont(font);
        titleText.setString("Binary Search Tree Visualizer");
        titleText.setCharacterSize(24);
        titleText.setFillColor(sf::Color(50, 50, 150));
        titleText.setPosition(350, 10);

        
    }

    void handleEvent(const sf::Event& event, BinarySearchTree& tree) {
        // Обработка кликов мыши
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            // Проверка клика по полю ввода
            if (inputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                isActive = true;
                inputText.setFillColor(sf::Color::Black);
            }
            else {
                isActive = false;
            }

            // Проверка клика по кнопке ADD
            if (addButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!currentInput.empty()) {
                    int value = std::stoi(currentInput);
                    tree.insert(value);
                    statusText.setString("dobavlen element: " + std::to_string(value));
                    statusText.setFillColor(sf::Color::Green);
                    statusClock.restart();
                    currentInput.clear();
                    inputText.setString("");
                }
            }

            // Проверка клика по кнопке REMOVE
            if (removeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!currentInput.empty()) {
                    int value = std::stoi(currentInput);
                    if (tree.remove(value)) {
                        statusText.setString("udalen element: " + std::to_string(value));
                        statusText.setFillColor(sf::Color(255, 140, 0));
                    }
                    else {
                        statusText.setString("Error: element " + std::to_string(value) + " ne naiden");
                        statusText.setFillColor(sf::Color::Red);
                    }
                    statusClock.restart();
                    currentInput.clear();
                    inputText.setString("");
                }
            }

            // Проверка клика по кнопке SEARCH
            if (searchButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!currentInput.empty()) {
                    int value = std::stoi(currentInput);
                    if (tree.search(value)) {
                        statusText.setString("element " + std::to_string(value) + " naiden v dereve");
                        statusText.setFillColor(sf::Color::Green);
                    }
                    else {
                        statusText.setString("element " + std::to_string(value) + " ne naiden");
                        statusText.setFillColor(sf::Color::Red);
                    }
                    statusClock.restart();
                    currentInput.clear();
                    inputText.setString("");
                }
            }

            // Проверка клика по кнопке CLEAR
            if (clearButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                tree.clear();
                statusText.setString("derevo ochisheno!");
                statusText.setFillColor(sf::Color::Blue);
                statusClock.restart();
                currentInput.clear();
                inputText.setString("");
            }
        }

        // Обработка ввода текста
        if (isActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) { // Backspace
                if (!currentInput.empty()) {
                    currentInput.pop_back();
                    inputText.setString(currentInput);
                }
            }
            else if (event.text.unicode == 13) { // Enter
                isActive = false;
                if (!currentInput.empty()) {
                    int value = std::stoi(currentInput);
                    tree.insert(value);
                    statusText.setString("dobavlen element: " + std::to_string(value));
                    statusClock.restart();
                    currentInput.clear();
                    inputText.setString("");
                }
            }
            else if (event.text.unicode >= '0' && event.text.unicode <= '9') { // Только цифры
                currentInput += static_cast<char>(event.text.unicode);
                inputText.setString(currentInput);
                inputText.setFillColor(sf::Color::Black);
            }
        }

        // Сброс цвета статуса через 2 секунды
        if (statusClock.getElapsedTime().asSeconds() > 2.0f) {
            statusText.setFillColor(sf::Color::Blue);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(inputBo);
        window.draw(inputBox);
        window.draw(addButton);
        window.draw(removeButton);
        window.draw(searchButton);
        window.draw(clearButton);

        window.draw(addText);
        window.draw(removeText);
        window.draw(searchText);
        window.draw(clearText);
        window.draw(titleText);
        window.draw(statusText);


        // Отображаем подсказку в поле ввода
        if (currentInput.empty() && !isActive) {
            sf::Text hint;
            hint.setFont(font);
            hint.setString("Enter number...");
            hint.setCharacterSize(16);
            hint.setFillColor(sf::Color::Red);
            hint.setPosition(60, 62);
            window.draw(hint);
        }
        else {
            window.draw(inputText);
        }
    }
};

// ============================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================

int main() {
    // Создаем окно SFML
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Binary Search Tree Visualizer");
    window.setFramerateLimit(60);

    // Загружаем шрифт
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }
    else {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    // Создаем объекты
    BinarySearchTree tree(font);
    TreeVisualizer visualizer(window, font);
    UI ui(font);

    // Добавляем начальные элементы для демонстрации
    std::cout << "Добавляем начальные элементы: ";
    std::vector<int> initialValues = { 50, 30, 70, 20, 40, 60, 80, 35, 65, 55, 75, 25, 45 };
    for (int val : initialValues) {
        tree.insert(val);
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Высота дерева: " << tree.getHeight() << std::endl;
    std::cout << "Максимум узлов на уровне: " << tree.getMaxNodesOnLevel() << std::endl;

    // Главный цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            ui.handleEvent(event, tree);
        }

        // Отрисовка
        window.clear(sf::Color(240, 240, 240)); // Светло-серый фон

        visualizer.draw(tree);
        ui.draw(window);

        window.display();
    }

    return 0;
}