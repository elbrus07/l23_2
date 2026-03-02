#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
int main()
{
    const int WIDTH = 1000;
    const int HEIGHT = 700;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "y = sin(x)");

    float scaleX = 80.0f;   // 1 радиан = 80 пикселей
    float scaleY = 150.0f;  // 1 по Y = 150 пикселей

    float centerX = WIDTH / 2.0f;
    float centerY = HEIGHT / 2.0f;

    // ===== ШРИФТ =====
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // ===== ГРАФИК =====
    sf::VertexArray graph(sf::LineStrip, WIDTH);

    for (int px = 0; px < WIDTH; px++)
    {
        float x = (px - centerX) / scaleX;
        float y = sin(x);
        float py = centerY - y * scaleY;

        graph[px].position = sf::Vector2f(px, py);
        graph[px].color = sf::Color::Red;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // ===== ОСИ =====
        sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(0, centerY), sf::Color::Black),
            sf::Vertex(sf::Vector2f(WIDTH, centerY), sf::Color::Black)
        };

        sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(centerX, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(centerX, HEIGHT), sf::Color::Black)
        };

        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        // ===== СТРЕЛКИ =====
        sf::CircleShape arrowX(10, 3);
        arrowX.setFillColor(sf::Color::Black);
        arrowX.setPosition(WIDTH - 15, centerY - 5);
        arrowX.setRotation(90);
        window.draw(arrowX);

        sf::CircleShape arrowY(10, 3);
        arrowY.setFillColor(sf::Color::Black);
        arrowY.setPosition(centerX - 5, 10);
        window.draw(arrowY);

        // ===== ШКАЛА ПО X (π/2) =====
        for (int i = -6; i <= 6; i++)
        {
            float xValue = i * (M_PI / 2.0f);
            float px = centerX + xValue * scaleX;

            sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(px, centerY - 6), sf::Color::Black),
                sf::Vertex(sf::Vector2f(px, centerY + 6), sf::Color::Black)
            };
            window.draw(tick, 2, sf::Lines);

            std::ostringstream ss;

            if (i == 0) ss << "0";
            else if (i == 1) ss << "π/2";
            else if (i == -1) ss << "-π/2";
            else if (i == 2) ss << "π";
            else if (i == -2) ss << "-π";
            else ss << i << "π/2";

            sf::Text label;
            label.setFont(font);
            label.setString(ss.str());
            label.setCharacterSize(16);
            label.setFillColor(sf::Color::Black);
            label.setPosition(px - 20, centerY + 10);

            window.draw(label);
        }

        // ===== ШКАЛА ПО Y =====
        for (int i = -1; i <= 1; i++)
        {
            float py = centerY - i * scaleY;

            sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(centerX - 6, py), sf::Color::Black),
                sf::Vertex(sf::Vector2f(centerX + 6, py), sf::Color::Black)
            };
            window.draw(tick, 2, sf::Lines);

            sf::Text label;
            label.setFont(font);
            label.setString(std::to_string(i));
            label.setCharacterSize(16);
            label.setFillColor(sf::Color::Black);
            label.setPosition(centerX + 10, py - 10);

            window.draw(label);
        }

        window.draw(graph);

        window.display();
    }

    return 0;
}