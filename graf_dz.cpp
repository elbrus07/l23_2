#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graph y = sin(x)");

    float scaleX = 50.0f;
    float scaleY = 100.0f;

    float centerX = WIDTH / 2.0f;
    float centerY = HEIGHT / 2.0f;

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

    sf::VertexArray graph(sf::LineStrip, WIDTH);

    for (int px = 0; px < WIDTH; px++)
    {
        float x = (px - centerX) / scaleX;
        float y = sin(x);
        float py = centerY - y * scaleY;

        graph[px].position = sf::Vector2f((float)px, py);
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

        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);
        window.draw(graph);

        window.display();
    }

    return 0;
}
