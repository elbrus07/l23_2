#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    const int W = 800;
    const int H = 600;
    sf::RenderWindow window(sf::VideoMode(W, H), "Simple Graph Calc");

    // Центр экрана (наша точка 0,0)
    sf::Vector2f center(W / 2.0f, H / 2.0f);
    float scale = 50.0f; // 50 пикселей = 1 единица

    // 1. Создаем оси
    sf::VertexArray axes(sf::Lines, 4);
    // Горизонтальная (X)
    axes[0] = sf::Vertex(sf::Vector2f(0, center.y), sf::Color::White);
    axes[1] = sf::Vertex(sf::Vector2f(W, center.y), sf::Color::White);
    // Вертикальная (Y)
    axes[2] = sf::Vertex(sf::Vector2f(center.x, 0), sf::Color::White);
    axes[3] = sf::Vertex(sf::Vector2f(center.x, H), sf::Color::White);

    // 2. Создаем график функции
    sf::VertexArray graph(sf::LineStrip);

    for (int pixel_x = 0; pixel_x < W; pixel_x++) {
        // Переводим пиксели в математические X
        float x = (pixel_x - center.x) / scale;

        // САМА ФУНКЦИЯ: y = sin(x)
        float y = std::sin(x);
        // Если хотите параболу, напишите: float y = x * x;

        // Переводим математические Y обратно в пиксели
        float pixel_y = center.y - (y * scale);

        graph.append(sf::Vertex(sf::Vector2f(pixel_x, pixel_y), sf::Color::Yellow));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(axes);  // Рисуем оси
        window.draw(graph); // Рисуем график
        window.display();
    }

    return 0;
}
