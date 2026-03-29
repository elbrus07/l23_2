#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Класс для отрисовки чисел на осях
class NumberDrawer {
private:
    sf::Font& font;

public:
    NumberDrawer(sf::Font& f) : font(f) {}

    void draw(sf::RenderWindow& window, int value, float x, float y, bool isVertical, sf::Color color = sf::Color::Black) {
        if (value == 0) return; // Просто ничего не делаем

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(value));
        text.setCharacterSize(11);
        text.setFillColor(color);

        // Центрируем текст по горизонтали
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);

        // Позиционирование:
        // Для оси X: число ниже оси (y + 15)
        // Для оси Y: число левее оси (x - 20)
        if (isVertical) {
            text.setPosition(x - 20, y);    // Слева от вертикальной оси
        }
        else {
            text.setPosition(x, y + 15);    // Снизу от горизонтальной оси
        }

        window.draw(text);
    }
};

// Класс для отрисовки стрелок
class ArrowDrawer {
public:
    void draw(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, sf::Color color = sf::Color::Black) {
        // Основная линия
        sf::Vertex line[] = {
            sf::Vertex(start, color),
            sf::Vertex(end, color)
        };
        window.draw(line, 2, sf::Lines);

        // Наконечник стрелки
        float arrowSize = 12.f;
        float angle = std::atan2(end.y - start.y, end.x - start.x);

        sf::Vector2f leftPoint(
            end.x - arrowSize * std::cos(angle - M_PI / 6),
            end.y - arrowSize * std::sin(angle - M_PI / 6)
        );
        sf::Vector2f rightPoint(
            end.x - arrowSize * std::cos(angle + M_PI / 6),
            end.y - arrowSize * std::sin(angle + M_PI / 6)
        );

        sf::Vertex arrow[] = {
            sf::Vertex(end, color),
            sf::Vertex(leftPoint, color),
            sf::Vertex(end, color),
            sf::Vertex(rightPoint, color)
        };
        window.draw(arrow, 4, sf::Lines);
    }
};

// Класс для отрисовки шкалы
class ScaleDrawer {
private:
    NumberDrawer numberDrawer;

public:
    ScaleDrawer(sf::Font& font) : numberDrawer(font) {}

    void draw(sf::RenderWindow& window, sf::Font& font, bool isVertical, int scale,
        int center_x, int center_y, int length, int windowWidth, int windowHeight) {
        /*
        функция рисует шкалу на оси
            :param isVertical - признак вертикальная ось: 1 или горизонтальная: 0
            :param scale - масштаб
            :param length - длина оси
            :param center_x - x координата центра системы координат
            :param center_x - x координата центра системы координат
        */


        sf::Color markColor = sf::Color::Black;

        if (!isVertical) {  // горизонтальная ось
            int pixelsLeft = center_x - (windowWidth - length) / 2;
            int pixelsRight = (windowWidth + length) / 2 - center_x;

            int divisionsLeft = pixelsLeft / scale;
            int divisionsRight = pixelsRight / scale;

            // Основные деления (положительная часть)
            for (int i = 0; i <= divisionsRight; i++) {
                int xPos = center_x + i * scale;
                int value = i;  // Значение всегда начинается с 1

                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(xPos, center_y - 5), markColor),
                    sf::Vertex(sf::Vector2f(xPos, center_y + 5), markColor)
                };
                window.draw(mark, 2, sf::Lines);

                //Числа
                numberDrawer.draw(window, value, xPos, center_y, false);
            }

            // Основные деления (отрицательная часть)
            for (int i = 0; i <= divisionsLeft; i++) {
                int xPos = center_x - i * scale;
                int value = -i;     // Отрицательные значения

                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(xPos, center_y - 5), markColor),
                    sf::Vertex(sf::Vector2f(xPos, center_y + 5), markColor)
                };
                window.draw(mark, 2, sf::Lines);

                //Числа
                numberDrawer.draw(window, value, xPos, center_y, false);
            }

            // Промежуточные деления
            for (int i = 0; i <= divisionsRight * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x + pos, center_y - 2), markColor),
                    sf::Vertex(sf::Vector2f(center_x + pos, center_y + 2), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
            for (int i = 0; i <= divisionsLeft * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - pos, center_y - 2), markColor),
                    sf::Vertex(sf::Vector2f(center_x - pos, center_y + 2), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
        }
        else {  // вертикальная ось
            int pixelsUp = center_y - (windowHeight - length) / 2;
            int pixelsDown = (windowHeight + length) / 2 - center_y;

            int divisionsUp = pixelsUp / scale;
            int divisionsDown = pixelsDown / scale;

            // Основные деления
            for (int i = 0; i <= divisionsDown; i++) {
                int yPos = center_y + i * scale;
                int value = -i;

                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 5, yPos), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 5, yPos), markColor)
                };
                window.draw(mark, 2, sf::Lines);

                //Числа
                numberDrawer.draw(window, value, center_x, yPos, true);
            }
            for (int i = 0; i <= divisionsUp; i++) {
                int yPos = center_y - i * scale;
                int value = i;

                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 5, yPos), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 5, yPos), markColor)
                };
                window.draw(mark, 2, sf::Lines);

                //Числа
                numberDrawer.draw(window, value, center_x, yPos, true);
            }

            // Промежуточные деления
            for (int i = 0; i <= divisionsDown * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 2, center_y + pos), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 2, center_y + pos), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
            for (int i = 0; i <= divisionsUp * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 2, center_y - pos), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 2, center_y - pos), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
        }
    }
};

// Класс для отрисовки осей координат
class AxeDrawer {
private:
    ArrowDrawer arrowDrawer;
    ScaleDrawer scaleDrawer;

public:
    AxeDrawer(sf::Font& font) : scaleDrawer(font) {}

    void draw(sf::RenderWindow& window, sf::Font& font, bool isVertical, int length,
        bool isNeededLines, int width, int height, int center_x, int center_y, int scale) {
        /*функция рисует ось координат (горизонтальную или вертикальную)

            :param isVertical - признак вертикальная ось: 1 или горизонтальная: 0
            :param length - длина оси
            :isNeededLines - нужна ли шкала на оси
            :param center_x = координата центра координат по x
            :param center_y = координата центра координат по y
            :param scale - масштаб
            :param width: - ширина полотна
            :param height: - высота полотна
        */

        sf::Color axisColor = sf::Color::Black;

        if (isVertical) {
            int y_shift = (height - length) / 2;
            // Стрелка вверх
            arrowDrawer.draw(window,
                sf::Vector2f(center_x, y_shift + length),
                sf::Vector2f(center_x, y_shift),
                axisColor);
            if (isNeededLines)
                scaleDrawer.draw(window, font, true, scale, center_x, center_y, length, width, height);
        }
        else {
            int x_shift = (width - length) / 2;
            // Стрелка вправо
            arrowDrawer.draw(window,
                sf::Vector2f(x_shift, center_y),
                sf::Vector2f(x_shift + length, center_y),
                axisColor);
            if (isNeededLines)
                scaleDrawer.draw(window, font, false, scale, center_x, center_y, length, width, height);
        }
    }
};

// Класс для отрисовки декартовой системы координат
class CartesianSystem {
private:
    AxeDrawer axeDrawer;

public:
    CartesianSystem(sf::Font& font) : axeDrawer(font) {}

    void draw(sf::RenderWindow& window, sf::Font& font, bool axesx, bool axesy,
        int width, int height, int center_x, int center_y, int scale) {
        /*Функция рисует Декартову систему координат на плокости
        :param axesx: - наличие осей координат Оx 0 - нет, 1 -есть
        :param axesy: - наличие осей координат Оy 0 - нет, 1 -есть
        :param scale: - масштаб
        :param width: - ширина полотна
        :param height: - высота полотна
        :param center_x = координата центра координат по x
        :param center_y = координата центра координат по y
        */

        if (axesy)
            axeDrawer.draw(window, font, true, height, true, width, height, center_x, center_y, scale);
        if (axesx)
            axeDrawer.draw(window, font, false, width, true, width, height, center_x, center_y, scale);
    }
};

// Класс для вычисления и отрисовки графиков функций
class FunctionPlotter {
private:
    float evaluateFunction(const std::string& expr, float x) {
        if (expr == "x*x") return x * x;
        if (expr == "sin(x)") return std::sin(x);
        if (expr == "cos(x)") return std::cos(x);
        if (expr == "x") return x;
        if (expr == "2*x") return 2 * x;
        if (expr == "x/2") return x / 2;
        if (expr == "x^3" || expr == "x*x*x") return x * x * x;
        return x * x;   // По умолчанию возвращаем x*x
    }

public:
    // Рисование графика функции
    void draw(sf::RenderWindow& window, const std::string& funcStr, float a, float b,
        int scale, int center_x, int center_y, sf::Color colour = sf::Color::Black) {
        float h = 0.01f;

        float prevX = a;
        float prevY = evaluateFunction(funcStr, a);

        for (float x = a + h; x <= b; x += h) {
            float y = evaluateFunction(funcStr, x);

            if (std::abs(prevY) < 1000 && std::abs(y) < 1000) {
                sf::Vector2f p1(center_x + prevX * scale, center_y - prevY * scale);
                sf::Vector2f p2(center_x + x * scale, center_y - y * scale);

                sf::Vertex line[] = {
                    sf::Vertex(p1, colour),
                    sf::Vertex(p2, colour)
                };

                window.draw(line, 2, sf::Lines);
               
            }

            prevX = x;
            prevY = y;
            
        }
    }
};

// Класс для пользовательского интерфейса
class UI {
private:
    sf::Font& font;
    bool textFieldActive;
    std::string function_str;
    std::string displayed_function;
    bool graphDrawn;
    int offset_x, offset_y;
    sf::Clock cursorClock;

public:
    UI(sf::Font& f) : font(f), textFieldActive(false), function_str("x*x"),
        displayed_function("x*x"), graphDrawn(false), offset_x(0), offset_y(0) {}

    void handleEvents(sf::Event& event, sf::RenderWindow& window, int width, int height,
        int& center_x, int& center_y, int& scale, bool& needRedraw, bool& graphDrawnOut) {

        // Обработка кликов для активации поля ввода
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Проверяем клик по полю ввода (x: width до width+200, y: 20 до 50)
                if (event.mouseButton.x >= width && event.mouseButton.x <= width + 200 &&
                    event.mouseButton.y >= 20 && event.mouseButton.y <= 50) {
                    textFieldActive = true;     // Активируем поле ввода
                }
                // Проверяем клик по кнопке "Рисовать"
                else if (event.mouseButton.x >= width && event.mouseButton.x <= width + 100 &&
                    event.mouseButton.y >= 100 && event.mouseButton.y <= 130) {
                    displayed_function = function_str;
                    graphDrawn = true;
                    graphDrawnOut = true;
                    textFieldActive = false;    // Деактивируем поле ввода
                }
                else {
                    textFieldActive = false;    // Клик вне поля - деактивируем
                }
            }
        }

        // Обработка ввода текста
        if (textFieldActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) {  // Backspace - стирание
                if (!function_str.empty()) {
                    function_str.pop_back();
                }
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {    // Печатные символы
                function_str += static_cast<char>(event.text.unicode);
            }
        }

        // Масштабирование  с помощью колесика мыши
        if (event.type == sf::Event::MouseWheelScrolled) {
            float zoomSpeed = 0.1f;
            if (event.mouseWheelScroll.delta > 0) { // Увеличение масштаба
                scale *= (1.0f + zoomSpeed);
            }
            else if (event.mouseWheelScroll.delta < 0) {    // Уменьшение масштаба
                scale /= (1.0f + zoomSpeed);
            }
            // Ограничение масштаба
            if (scale < 10.0f) scale = 10.0f;
            if (scale > 500.0f) scale = 500.0f;
        }

        // Управление стрелками
        if (!textFieldActive && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                offset_x -= 1;
                needRedraw = true;
            }
            if (event.key.code == sf::Keyboard::Right) {
                offset_x += 1;
                needRedraw = true;
            }
            if (event.key.code == sf::Keyboard::Up) {
                offset_y -= 1;
                needRedraw = true;
            }
            if (event.key.code == sf::Keyboard::Down) {
                offset_y += 1;
                needRedraw = true;
            }
        }

        // Обновляем центр с учетом смещения
        center_x = 500 + offset_x * 3;
        center_y = 400 + offset_y * 3;
    }

    void draw(sf::RenderWindow& window, int width, int height) {
        // Фоновое окно
        sf::RectangleShape inputBo(sf::Vector2f(300, height));
        inputBo.setPosition(width, 0);
        inputBo.setFillColor(sf::Color::White);
        inputBo.setOutlineColor(sf::Color::Black);
        inputBo.setOutlineThickness(1);
        window.draw(inputBo);

        // Окно ввода
        sf::RectangleShape inputBox(sf::Vector2f(200, 30));
        inputBox.setPosition(width, 20);
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineColor(textFieldActive ? sf::Color::Blue : sf::Color::Black);
        inputBox.setOutlineThickness(textFieldActive ? 2 : 1);
        window.draw(inputBox);

        sf::Text inputLabel;
        inputLabel.setFont(font);
        inputLabel.setString("f(x) =");
        inputLabel.setCharacterSize(16);
        inputLabel.setFillColor(sf::Color::Black);
        inputLabel.setPosition(width, 0);
        window.draw(inputLabel);

        sf::Text inputfun;
        inputfun.setFont(font);
        inputfun.setString("Function:");
        inputfun.setCharacterSize(16);
        inputfun.setFillColor(sf::Color::Black);
        inputfun.setPosition(width, height / 3 - 30);
        window.draw(inputfun);

        sf::Text inputfunc;
        inputfunc.setFont(font);
        inputfunc.setString("x*x  | sin(x) | cos(x) | x | 2*x | x/2 | x^3");
        inputfunc.setCharacterSize(16);
        inputfunc.setFillColor(sf::Color::Black);
        inputfunc.setPosition(width, height / 3);
        window.draw(inputfunc);

        // Отображение текста с курсором
        std::string displayText = function_str;
        if (textFieldActive) {
            if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
                cursorClock.restart();
            }
            bool showCursor = cursorClock.getElapsedTime().asSeconds() < 0.25f;
            if (showCursor) {
                displayText += "_";     // Добавляем символ курсора
            }
        }

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setString(displayText);
        inputText.setCharacterSize(16);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(width, 25);
        window.draw(inputText);

        // Кнопка "Рисовать"
        sf::RectangleShape drawButton(sf::Vector2f(100, 30));
        drawButton.setPosition(width, 100);
        drawButton.setOutlineColor(sf::Color::Black);
        drawButton.setOutlineThickness(1);
        window.draw(drawButton);

        sf::Text drawText;
        drawText.setFont(font);
        drawText.setString("Paint");
        drawText.setCharacterSize(16);
        drawText.setFillColor(sf::Color::Black);
        drawText.setPosition(width, 105);
        window.draw(drawText);
    }

    std::string getDisplayedFunction() const { return displayed_function; }
    bool isGraphDrawn() const { return graphDrawn; }
};

int main() {
    // Создаём окно SFML
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph Plotter - SFML C++");
    window.setFramerateLimit(60);

    // ЗАГРУЗКА ШРИФТА 
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }

    // Параметры системы координат
    const int width = 900;
    const int height = 800;
    int center_x = 450;
    int center_y = 400;
    int scale = 50;
    bool needRedraw = true;

    // Диапазон отрисовки функции f(x) = x²
    float func_a = -4.f;
    float func_b = 4.f;


    // Создаем объекты классов
    CartesianSystem cartesianSystem(font);
    FunctionPlotter functionPlotter;
    UI ui(font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            ui.handleEvents(event, window, width, height, center_x, center_y, scale, needRedraw, needRedraw);
        }

        window.clear(sf::Color::White);

        // Рисуем систему координат
        cartesianSystem.draw(window, font, true, true, width, height, center_x, center_y, scale);

        // Рисуем график функции
        if (ui.isGraphDrawn()) {
            functionPlotter.draw(window, ui.getDisplayedFunction(), func_a, func_b, scale, center_x, center_y, sf::Color::Green);
        }

        // Рисуем интерфейс
        ui.draw(window, width, height);

        window.display();
    }

    return 0;
}
