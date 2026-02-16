#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    
    sf::Vertex line_ver[] =
    {
        sf::Vertex(sf::Vector2f(100.f, 10.f)),
        sf::Vertex(sf::Vector2f(100.f, 190.f))
    };
    sf::Vertex line_left_strel_vert[] =
    {
        sf::Vertex(sf::Vector2f(100.f, 10.f)),
        sf::Vertex(sf::Vector2f(95.f, 20.f))
    };
    sf::Vertex line_right_strel_vert[] =
    {
        sf::Vertex(sf::Vector2f(100.f, 10.f)),
        sf::Vertex(sf::Vector2f(105.f, 20.f))
    };


    sf::Vertex line_gor[] =
    {
        sf::Vertex(sf::Vector2f(10.f, 100.f)),
        sf::Vertex(sf::Vector2f(190.f, 100.f))
    };
    sf::Vertex line_left_strel_gor[] =
    {
        sf::Vertex(sf::Vector2f(190.f, 100.f)),
        sf::Vertex(sf::Vector2f(180.f, 95.f))
    };
    sf::Vertex line_right_strel_gor[] =
    {
        sf::Vertex(sf::Vector2f(190.f, 100.f)),
        sf::Vertex(sf::Vector2f(180.f, 105.f))
    };
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(line_ver, 2, sf::Lines);
        window.draw(line_left_strel_vert, 2, sf::Lines);
        window.draw(line_right_strel_vert, 2, sf::Lines);

        window.draw(line_gor, 2, sf::Lines);
        window.draw(line_left_strel_gor, 2, sf::Lines);
        window.draw(line_right_strel_gor, 2, sf::Lines);

        window.display();
    }

    return 0;
}