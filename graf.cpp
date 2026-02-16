
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sin(x) Graph");
    
    // Создаем массив точек для графика
    sf::VertexArray graph(sf::LineStrip);
    
    // Настраиваем параметры графика
    float amplitude = 100.0f;  // Высота волны
    float frequency = 0.01f;   // Частота
    int centerY = 300;         // Центр по Y
    
    // Создаем точки графика
    for (int x = 0; x < 800; x++)
    {
        // Вычисляем значение sin
        float y = centerY - amplitude * sin(x * frequency);
        
        // Добавляем точку в график (синего цвета)
        graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Blue));
    }
    
    // Главный цикл программы
    while (window.isOpen())
    {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Очищаем окно белым цветом
        window.clear(sf::Color::White);
        
        // Рисуем график
        window.draw(graph);
        
        // Отображаем на экране
        window.display();
    }
    
    return 0;
}
