#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sin(x) Graph with Axes");
    
    // Создаем оси координат
    sf::VertexArray xAxis(sf::Lines, 2);
    sf::VertexArray yAxis(sf::Lines, 2);
    
    // Настройка оси X (горизонтальная линия)
    xAxis[0].position = sf::Vector2f(50, 300);  // Начало оси X
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position = sf::Vector2f(750, 300); // Конец оси X
    xAxis[1].color = sf::Color::Black;
    
    // Настройка оси Y (вертикальная линия)
    yAxis[0].position = sf::Vector2f(400, 50);  // Начало оси Y
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(400, 550); // Конец оси Y
    yAxis[1].color = sf::Color::Black;
    
    // Создаем массив точек для графика
    sf::VertexArray graph(sf::LineStrip);
    
    // Настраиваем параметры графика
    float amplitude = 100.0f;  // Высота волны
    float frequency = 0.02f;   // Частота
    int centerY = 300;         // Центр по Y
    
    // Создаем точки графика
    for (int x = 50; x < 750; x++)
    {
        // Вычисляем значение sin (от 0 до 2PI примерно)
        float y = centerY - amplitude * sin((x - 400) * frequency);
        
        // Добавляем точку в график (красного цвета)
        graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Red));
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
        
        // Рисуем оси
        window.draw(xAxis);
        window.draw(yAxis);
        
        // Рисуем график
        window.draw(graph);
        
        // Отображаем на экране
        window.display();
    }
    
    return 0;
}
