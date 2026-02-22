#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
    
 
   

    void drawArrow(sf::RenderWindow & window,
        sf::Vector2f start,
        sf::Vector2f end,
        sf::Color color = sf::Color::Black)
    {
        // Основная линия
        sf::Vertex line[] = {
            sf::Vertex(start, color),
            sf::Vertex(end , color)
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

    void drawScale(sf::RenderWindow & window, bool isVertical = true,
        int scale = 10,
        int center_x = 500,
        int center_y = 400,
        int length = 500,
        int windowWidth = 1000,
        int windowHeight = 800)
    {
        /*
        функция рисует шкалу на оси
            :param isVertical - признак вертикальная ось: 1 или горизонтальная: 0
            :param scale - масштаб
            :param length - длина оси
            :param center_x - x координата центра системы координат
            :param center_x - x координата центра системы координат
        */
        sf::Color markColor = sf::Color::Black;
        if (isVertical == 0) {  //отчсечки на горизонтальной оси
            int x_shift = (windowWidth - length) / 2;
            int start = center_x - x_shift;
            int n = (length - start) / scale; //количество отсечек на  положительной части оси x
            int m = (start) / scale; //количество отсеек на отрицательной части оси x

            // Основные деления (положительная часть)
            for (int i = 0; i <= n; i++) {
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x + i * scale, center_y - 5), markColor),
                    sf::Vertex(sf::Vector2f(center_x + i * scale, center_y + 5), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
            // Основные деления (отрицательная часть)
            for (int i = 0; i <= m; i++) {
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - i * scale, center_y - 5), markColor),
                    sf::Vertex(sf::Vector2f(center_x - i * scale, center_y + 5), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }

            // Промежуточные деления (x5)
            for (int i = 0; i <= n * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x + pos, center_y - 2), markColor),
                    sf::Vertex(sf::Vector2f(center_x + pos, center_y + 2), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
            for (int i = 0; i <= m * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - pos, center_y - 2), markColor),
                    sf::Vertex(sf::Vector2f(center_x - pos, center_y + 2), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }


        }
        else {  // === ВЕРТИКАЛЬНАЯ ОСЬ ===
            int y_shift = (windowHeight - length) / 2;
            int start = center_y - y_shift;
            int n = (length - start) / scale;
            int m = start / scale;

            // Основные деления
            for (int i = 0; i <= n; i++) {
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 5, center_y + i * scale), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 5, center_y + i * scale), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
            for (int i = 0; i <= m; i++) {
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 5, center_y - i * scale), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 5, center_y - i * scale), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }

            // Промежуточные деления
            for (int i = 0; i <= n * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 2, center_y + pos), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 2, center_y + pos), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
            for (int i = 0; i <= m * 5; i++) {
                float pos = i * (scale / 5.f);
                sf::Vertex mark[] = {
                    sf::Vertex(sf::Vector2f(center_x - 2, center_y - pos), markColor),
                    sf::Vertex(sf::Vector2f(center_x + 2, center_y - pos), markColor)
                };
                window.draw(mark, 2, sf::Lines);
            }
        }

    }
    void drawAxe(sf::RenderWindow& window, bool isVertical = true, int length = 500, bool isNeededLines = true, int width = 1000, int height = 800, int center_x = 500, int center_y = 400, int scale = 10)
    {
                           
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
            drawArrow(window,
                sf::Vector2f(center_x, y_shift + length),
                sf::Vector2f(center_x, y_shift),
                axisColor);
            if (isNeededLines)
                drawScale(window, true, scale, center_x, center_y, length, width, height);
        }
        else {
            int x_shift = (width - length) / 2;
            // Стрелка вправо
            drawArrow(window,
                sf::Vector2f(x_shift, center_y),
                sf::Vector2f(x_shift + length, center_y),
                axisColor);
            if (isNeededLines)
                drawScale(window, false, scale, center_x, center_y, length, width, height);
        }

    }
    void create_dpsk(sf::RenderWindow& window,
        bool axesx = true,
        bool axesy = true,
        int width = 1000,
        int height = 800,
        int center_x = 500,
        int center_y = 400,
        int scale = 10)
    {
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
            drawAxe(window, true, height - 100, true, width, height, center_x, center_y, scale);
        if (axesx)
            drawAxe(window, false, width - 100, true, width, height, center_x, center_y, scale);
    }

 

    // ФУНКЦИИ ДЛЯ ГРАФИКОВ


    // Пример функции: f(x) = x²
    float f(float x) {
        return x * x;
    }

    // Рисование графика функции
    void draw_func(sf::RenderWindow& window,
        float (*func)(float),
        float a,
        float b,
        int scale,
        int center_x,
        int center_y,
        sf::Color colour = sf::Color::Black)
    {
        float h = 0.01f;  // шаг дискретизации

        float prevX = a;
        float prevY = func(a);

        for (float x = a + h; x <= b; x += h) {
            float y = func(x);

            // Преобразование координат: SFML Y растёт вниз → инвертируем
            sf::Vector2f p1(center_x + prevX * scale, center_y - prevY * scale);
            sf::Vector2f p2(center_x + x * scale, center_y - y * scale);

            sf::Vertex line[] = {   //рисуется маленький отрезок графика

                sf::Vertex(p1, colour),
                sf::Vertex(p2, colour)
            };
            window.draw(line, 2, sf::Lines);

            prevX = x;
            prevY = y;
        }
    }

    int main() {
        // Создаём окно SFML
        sf::RenderWindow window(sf::VideoMode(1000, 800), "Graph Plotter - SFML C++");
        window.setFramerateLimit(60);

        // Параметры системы координат
        const int width = 1000;
        const int height = 800;
        const int center_x = 500;
        const int center_y = 400;
        const int scale = 10;  // 1 единица = 50 пикселей

        // Диапазон отрисовки функции f(x) = x²
        float func_a = -4.f;
        float func_b = 4.f;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // Очистка экрана
            window.clear(sf::Color::White);

            // 1. Рисуем систему координат
            create_dpsk(window, true, true, width, height, center_x, center_y, scale);

            // 2. Рисуем график f(x) = x² зелёным цветом
            draw_func(window, f, func_a, func_b, scale, center_x, center_y, sf::Color::Green);

            // Отображение результата
            window.display();
        }

        return 0;

    }
