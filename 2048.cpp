#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>

// КЛАСС ЯЧЕЙКИ
class Cell {
private:
    int value; //значение
    sf::RectangleShape shape; //прямоугольник
    sf::Text text; //для числа
    bool hasFont; // true, если шрифт уже назначен
    
    sf::Color getColorForValue() {
    //функция возвращает цвет в зависимости от значения
        switch(value) {
            case 0: return sf::Color(205, 193, 180);
            case 2: return sf::Color(238, 228, 218);
            case 4: return sf::Color(237, 224, 200);
            case 8: return sf::Color(242, 177, 121);
            case 16: return sf::Color(245, 149, 99);
            case 32: return sf::Color(246, 124, 95);
            case 64: return sf::Color(246, 94, 59);
            case 128: return sf::Color(237, 207, 114);
            case 256: return sf::Color(237, 204, 97);
            case 512: return sf::Color(237, 200, 80);
            case 1024: return sf::Color(237, 197, 63);
            case 2048: return sf::Color(237, 194, 46);
            default: return sf::Color(60, 58, 50);
        }
    }
    
public:
    Cell() : value(0), hasFont(false) {
        /*
        Конструктор создаёт пустую клетку
         */
        shape.setSize(sf::Vector2f(90, 90)); //размер клетки
        shape.setOutlineThickness(9); //рамка клетки
        shape.setOutlineColor(sf::Color(156, 138, 124));//цвет рамки
        shape.setFillColor(getColorForValue()); //задаём цвет клетки 
    }
    
    void setValue(int newValue) {
        /*
        функция устанавливает значение и перерисовывает клетку
            :param newValue - новое значение
         */
        value = newValue;
        shape.setFillColor(getColorForValue());
        
        if(value != 0 && hasFont) { //выполняем, если значение не 0 и шрифт был задан
            text.setString(std::to_string(value));
            text.setCharacterSize(36);
            
            if(value <= 4) {
                text.setFillColor(sf::Color(119, 110, 101)); // тёмный текст
            } else {
                text.setFillColor(sf::Color(249, 246, 242)); // светлый текст
            }
            
            // центрируем число в квадрате
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
        }
    }
    
    int getValue() {
        /*
        функция возвращает значение клетки
         */
        return value; 
    }
    
    void setPosition(float x, float y) {
        /*
        функция устанавливает позицию на доске
            :param x и y - строка и столбец
         */
        shape.setPosition(x, y);
        if(hasFont) {
            text.setPosition(x + 45, y + 45);
        }
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        if(value != 0 && hasFont) {
            window.draw(text);
        }
    }
    
    void setFont(sf::Font& font) {
        /*
        функция устанавливает шрифт
            :param font - шрифт
         */
        text.setFont(font);
        hasFont = true;
    }
    
    bool isEmpty() {
        /*
        функция возвращает true, если значение 0, иначе false
         */
        return value == 0; 
    }
};

// КЛАСС ИГРОВОГО ПОЛЯ
class Board {
private:
    const int SIZE = 4; //количество клеток 4x4
    std::vector<std::vector<Cell>> cells;
    sf::Font font;
    int score;
    int bestScore;
    bool gameOver;
    
    void loadBestScore() {
        // Загружаем лучший счёт из файла
        std::ifstream file("best_score.txt");
        if (file.is_open()) {
            file >> bestScore;
            file.close();
        } else {
            bestScore = 0;
        }
    }
    
    void saveBestScore() {
        // Сохраняем лучший счёт в файл
        std::ofstream file("best_score.txt");
        if (file.is_open()) {
            file << bestScore;
            file.close();
        }
    }
    
    void updateBestScore() {
        if (score > bestScore) {
            bestScore = score;
            saveBestScore();
        }
    }
    
    void mergeAndMove(std::vector<int>& line, bool& moved, int& lineScore) {
        /*
        функция для слияния строки/столбца в любую сторону
            :param line - массив клеток строки/столбца
            :param moved - было ли изменение строки/столбца
            :param lineScore - счёт строки/столбца
         */
        
        std::vector<int> compressed;
        for(int val : line) {
            if(val != 0) compressed.push_back(val); //убираем нули
        }
        
        for(size_t i = 0; i + 1 < compressed.size(); i++) {
            if(compressed[i] == compressed[i + 1]) { //слили соседей
                compressed[i] *= 2;
                lineScore += compressed[i]; // очки за слияние
                compressed.erase(compressed.begin() + i + 1);
                moved = true; 
                i--;
            }
        }
        
        compressed.resize(SIZE, 0);
        
        for(int i = 0; i < SIZE; i++) {
            if(line[i] != compressed[i]) {
                moved = true; // фиксируем, что изменения были
                break;
            }
        }
        
        line = compressed;
    }
    
    bool moveLeft() {
        bool moved = false;
        for(int i = 0; i < SIZE; i++) {
            std::vector<int> line;
            for(int j = 0; j < SIZE; j++) {
                line.push_back(cells[i][j].getValue());
            }
            
            int lineScore = 0;
            mergeAndMove(line, moved, lineScore);
            score += lineScore;
            
            for(int j = 0; j < SIZE; j++) {
                cells[i][j].setValue(line[j]);
            }
        }
        return moved;
    }
    
    bool moveRight() {
        bool moved = false;
        for(int i = 0; i < SIZE; i++) {
            std::vector<int> line;
            for(int j = SIZE - 1; j >= 0; j--) {
                line.push_back(cells[i][j].getValue());
            }
            
            int lineScore = 0;
            mergeAndMove(line, moved, lineScore);
            score += lineScore;
            
            for(int j = 0; j < SIZE; j++) {
                cells[i][SIZE - 1 - j].setValue(line[j]);
            }
        }
        return moved;
    }
    
    bool moveUp() {
        bool moved = false;
        for(int j = 0; j < SIZE; j++) {
            std::vector<int> line;
            for(int i = 0; i < SIZE; i++) {
                line.push_back(cells[i][j].getValue());
            }
            
            int lineScore = 0;
            mergeAndMove(line, moved, lineScore);
            score += lineScore;
            
            for(int i = 0; i < SIZE; i++) {
                cells[i][j].setValue(line[i]);
            }
        }
        return moved;
    }
    
    bool moveDown() {
        bool moved = false;
        for(int j = 0; j < SIZE; j++) {
            std::vector<int> line;
            for(int i = SIZE - 1; i >= 0; i--) {
                line.push_back(cells[i][j].getValue());
            }
            
            int lineScore = 0;
            mergeAndMove(line, moved, lineScore);
            score += lineScore;
            
            for(int i = 0; i < SIZE; i++) {
                cells[SIZE - 1 - i][j].setValue(line[i]);
            }
        }
        return moved;
    }
    
    void addRandomTile() {
        /*
        функция после каждого хода добавляет «2» (90 %) или «4» (10 %) в случайную свободную клетку
         */
        
        std::vector<std::pair<int, int>> emptyCells;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(cells[i][j].isEmpty()) {
                    emptyCells.push_back({i, j});
                }
            }
        }
        
        if(!emptyCells.empty()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, emptyCells.size() - 1);
            std::uniform_int_distribution<> tileDist(0, 9);
            
            auto pos = emptyCells[dist(gen)];
            int value = (tileDist(gen) == 0) ? 4 : 2;
            cells[pos.first][pos.second].setValue(value);
        }
    }
    
    bool checkGameOver() {
        // Проверка «конец игры» = нет пустых клеток и нет равных соседей
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(cells[i][j].isEmpty()) return false;
                if(i < SIZE - 1 && cells[i][j].getValue() == cells[i + 1][j].getValue()) { return false; }
                if(j < SIZE - 1 && cells[i][j].getValue() == cells[i][j + 1].getValue()) { return false; }
            }
        }
        return true;
    }
    
public:
    Board() : score(0), gameOver(false) {
        // конструктор: загружаем шрифт, даём его плиткам, создаём 2 стартовые плитки
        cells.resize(SIZE, std::vector<Cell>(SIZE));
        
        loadBestScore(); // Загружаем лучший счёт
        
        if (!font.loadFromFile("fonts/LiberationSans-Regular.ttf")) {
            std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
        }
        
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                cells[i][j].setFont(font);
            }
        }
        
        addRandomTile();
        addRandomTile();
    }
    
    void handleMove(sf::Keyboard::Key key) {
        //функция принимает события клавиш, запускает функции перемещения и добавляет новую клетку
        if(gameOver) return;
        
        bool moved = false;
        switch(key) {
            case sf::Keyboard::Left: moved = moveLeft(); break;
            case sf::Keyboard::Right: moved = moveRight(); break;
            case sf::Keyboard::Up: moved = moveUp(); break;
            case sf::Keyboard::Down: moved = moveDown(); break;
            default: return;
        }
        
        if(moved) {
            addRandomTile();
            updateBestScore(); // Обновляем лучший счёт
            gameOver = checkGameOver();
        }
    }
    
    void reset() {
        // функция возвращает поле в начальное состояние
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                cells[i][j].setValue(0);
            }
        }
        score = 0;
        gameOver = false;
        addRandomTile();
        addRandomTile();
    }
    
    void updatePositions(float cellSize, float offset) {
        /*
        функция обновляет позиции клеток
            :param cellSize - размер клетки
            :param offset - общий отступ всей доски от края окна
         */
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                cells[i][j].setPosition(offset + j * cellSize + 5, 
                                       offset + i * cellSize + 100 + 5);
            }
        }
    }
    
    void draw(sf::RenderWindow& window) {
        /*
        функция рисует клетки
            :param window - окно sfml
         */
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                cells[i][j].draw(window);
            }
        }
    }
    
    int getScore() {
        //функция возвращает счёт
        return score; 
    }
    
    int getBestScore() {
        //функция возвращает лучший счёт
        return bestScore;
    }
    
    bool isGameOver() { 
        //функция возвращает true, если игра закончена
        return gameOver; 
    }
};

// ГЛАВНЫЙ КЛАСС ИГРЫ
class Game {
private:
    const int CELL_SIZE = 100; // размер одной плитки
    const int OFFSET = 20; // отступ от края окна
    const int WINDOW_WIDTH = CELL_SIZE * 4 + 2 * OFFSET;
    const int WINDOW_HEIGHT = CELL_SIZE * 4 + 2 * OFFSET + 100;
    
    sf::RenderWindow window;
    Board board;
    sf::Font font;
    sf::Text scoreText;
    sf::Text bestScoreText;
    sf::Text scoreLabelText;
    sf::Text bestScoreLabelText;
    
    // Элементы кнопки "Новая игра"
    sf::RectangleShape newGameButton;
    sf::Text newGameText;
    bool buttonHovered;
    
    void initWindow() {
        //инициализируем окно
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Игра 2048");
        window.setFramerateLimit(60); // 60 FPS - частота кадров
    }
    
    void initText() {
        //функция загружает шрифт и устанавливает текст для счёта 
        if (!font.loadFromFile("fonts/LiberationSans-Regular.ttf")) {
            std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
        }
        
        // Кнопка "Новая Игра"
        newGameButton.setSize(sf::Vector2f(140, 60));
        newGameButton.setPosition(OFFSET, OFFSET + 10);
        newGameButton.setFillColor(sf::Color(140, 112, 99));
        
        newGameText.setFont(font);
        newGameText.setString(L"Новая Игра");
        newGameText.setCharacterSize(24);
        newGameText.setFillColor(sf::Color::White);
        
        sf::FloatRect textRect = newGameText.getLocalBounds();
        newGameText.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);
        newGameText.setPosition(OFFSET + 70, OFFSET + 40.0f);
        
        buttonHovered = false;
        
        // Текст "СЧЁТ"
        scoreLabelText.setFont(font);
        scoreLabelText.setString(L"СЧЁТ");
        scoreLabelText.setCharacterSize(16);
        scoreLabelText.setFillColor(sf::Color(238, 228, 218));
        scoreLabelText.setPosition(OFFSET + 180, OFFSET + 15);
        
        // Значение счёта
        scoreText.setFont(font);
        scoreText.setCharacterSize(26);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setPosition(OFFSET + 180, OFFSET + 35);
        
        // Текст "ЛУЧШИЙ"
        bestScoreLabelText.setFont(font);
        bestScoreLabelText.setString(L"ЛУЧШИЙ");
        bestScoreLabelText.setCharacterSize(16);
        bestScoreLabelText.setFillColor(sf::Color(238, 228, 218));
        bestScoreLabelText.setPosition(OFFSET + 300, OFFSET + 15);
        
        // Значение лучшего счёта
        bestScoreText.setFont(font);
        bestScoreText.setCharacterSize(26);
        bestScoreText.setFillColor(sf::Color::White);
        bestScoreText.setStyle(sf::Text::Bold);
        bestScoreText.setPosition(OFFSET + 300, OFFSET + 35);
    }
    
    void updateUI() {
        //обновляем интерфейс
        scoreText.setString(std::to_string(board.getScore()));
        bestScoreText.setString(std::to_string(board.getBestScore()));
    }
    
    void processEvents() {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed) {
                board.handleMove(event.key.code);
            }
            else if(event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect bounds = newGameButton.getGlobalBounds();
                buttonHovered = bounds.contains(mousePos.x, mousePos.y);
                
                if(buttonHovered) {
                    newGameButton.setFillColor(sf::Color(173, 152, 132));
                } else {
                    newGameButton.setFillColor(sf::Color(140, 112, 99));
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::FloatRect bounds = newGameButton.getGlobalBounds();
                    if(bounds.contains(mousePos.x, mousePos.y)) {
                        board.reset();
                        board.updatePositions(CELL_SIZE, OFFSET);
                    }
                }
            }
        }
    }
    
    void render() {
        window.clear(sf::Color(187, 173, 160));
        
        // Фон для счёта
        sf::RectangleShape scoreBg(sf::Vector2f(120, 60));
        scoreBg.setFillColor(sf::Color(140, 112, 99));
        scoreBg.setPosition(OFFSET + 150, OFFSET + 10);
        window.draw(scoreBg);
        
        // Фон для лучшего счёта
        sf::RectangleShape bestScoreBg(sf::Vector2f(120, 60));
        bestScoreBg.setFillColor(sf::Color(140, 112, 99));
        bestScoreBg.setPosition(OFFSET + 280, OFFSET + 10);
        window.draw(bestScoreBg);
        
        // Кнопка
        window.draw(newGameButton);
        window.draw(newGameText);
        
        // Тексты
        window.draw(scoreLabelText);
        window.draw(scoreText);
        window.draw(bestScoreLabelText);
        window.draw(bestScoreText);
        
        board.draw(window);
        
        window.display();
    }
    
public:
    Game() {
        initWindow();
        initText();
        board.updatePositions(CELL_SIZE, OFFSET);
    }
    
    void run() {
        while(window.isOpen()) {
            processEvents();
            updateUI();
            render();
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
