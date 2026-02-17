#include <SFML/Graphics.hpp>

void draw_axis(int width, int height, bool vertical, int length) {
    if (not vertical){
        shift = (width - length) / 2
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(shift, height/2); // Начало
        line[0].color = sf::Color::Red;
        line[1].position = sf::Vector2f(shift + length, height/2); // Конец
        line[1].color = sf::Color::Red;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    

    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(line);
        window.display();
    }

    return 0;
}

