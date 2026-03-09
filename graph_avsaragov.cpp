
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    int w = 800;
    int h = 600;

    float scale = 50;

    sf::RenderWindow window(sf::VideoMode(w, h), "Graph");

    sf::Font font;
    font.loadFromFile("arial.ttf"); // шрифт для подписей

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // рисуем ось X
        sf::Vertex xAxis[2];
        xAxis[0].position = sf::Vector2f(0, h / 2);
        xAxis[1].position = sf::Vector2f(w, h / 2);
        xAxis[0].color = sf::Color::White;
        xAxis[1].color = sf::Color::White;

        window.draw(xAxis, 2, sf::Lines);

        // рисуем ось Y
        sf::Vertex yAxis[2];
        yAxis[0].position = sf::Vector2f(w / 2, 0);
        yAxis[1].position = sf::Vector2f(w / 2, h);
        yAxis[0].color = sf::Color::White;
        yAxis[1].color = sf::Color::White;

        window.draw(yAxis, 2, sf::Lines);

        // деления по X
        for (int i = -10; i <= 10; i++)
        {
            float x = w / 2 + i * scale;

            sf::Vertex line[2];

            line[0].position = sf::Vector2f(x, h/2 - 5);
            line[1].position = sf::Vector2f(x, h/2 + 5);

            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;

            window.draw(line, 2, sf::Lines);

            if (i != 0)
            {
                sf::Text t;
                t.setFont(font);
                t.setCharacterSize(12);
                t.setFillColor(sf::Color::White);

                t.setString(to_string(i));
                t.setPosition(x - 10, h/2 + 5);

                window.draw(t);
            }
        }

        // деления по Y
        for (int i = -10; i <= 10; i++)
        {
            float y = h / 2 - i * scale;

            sf::Vertex line[2];

            line[0].position = sf::Vector2f(w/2 - 5, y);
            line[1].position = sf::Vector2f(w/2 + 5, y);

            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;

            window.draw(line, 2, sf::Lines);

            if (i != 0)
    
