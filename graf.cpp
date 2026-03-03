#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>

int main()
{
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(900, 600), "y = sin x");
    
    // Загружаем шрифт
    sf::Font font;
    font.loadFromFile("/home/stud/LiberationMono-Regular.ttf"); // Скачай arial.ttf и положи рядом
    
    // === ОСИ КООРДИНАТ ===
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(100, 300);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position = sf::Vector2f(800, 300);
    xAxis[1].color = sf::Color::Black;
    
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(450, 100);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(450, 500);
    yAxis[1].color = sf::Color::Black;
    
    // === СТРЕЛКИ НА КОНЦАХ ===
    // Стрелка на оси X
    sf::VertexArray xArrow1(sf::Lines, 2);
    xArrow1[0].position = sf::Vector2f(800, 300);
    xArrow1[0].color = sf::Color::Black;
    xArrow1[1].position = sf::Vector2f(790, 295);
    xArrow1[1].color = sf::Color::Black;
    
    sf::VertexArray xArrow2(sf::Lines, 2);
    xArrow2[0].position = sf::Vector2f(800, 300);
    xArrow2[0].color = sf::Color::Black;
    xArrow2[1].position = sf::Vector2f(790, 305);
    xArrow2[1].color = sf::Color::Black;
    
    // Стрелка на оси Y
    sf::VertexArray yArrow1(sf::Lines, 2);
    yArrow1[0].position = sf::Vector2f(450, 100);
    yArrow1[0].color = sf::Color::Black;
    yArrow1[1].position = sf::Vector2f(445, 110);
    yArrow1[1].color = sf::Color::Black;
    
    sf::VertexArray yArrow2(sf::Lines, 2);
    yArrow2[0].position = sf::Vector2f(450, 100);
    yArrow2[0].color = sf::Color::Black;
    yArrow2[1].position = sf::Vector2f(455, 110);
    yArrow2[1].color = sf::Color::Black;
    
    // === ШКАЛА (маленькие черточки) ===
    sf::VertexArray scale(sf::Lines);
    
    // Черточки на оси X
    for (int x = 150; x < 800; x += 50)
    {
        scale.append(sf::Vertex(sf::Vector2f(x, 295), sf::Color::Black));
        scale.append(sf::Vertex(sf::Vector2f(x, 305), sf::Color::Black));
    }
    
    // Черточки на оси Y
    for (int y = 150; y < 500; y += 50)
    {
        scale.append(sf::Vertex(sf::Vector2f(445, y), sf::Color::Black));
        scale.append(sf::Vertex(sf::Vector2f(455, y), sf::Color::Black));
    }
    
    // === ПОДПИСИ ===
    std::vector<sf::Text> labels;
    
    auto addLabel = [&](std::string text, float x, float y, int size = 18)
    {
        sf::Text label;
        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(size);
        label.setFillColor(sf::Color::Black);
        label.setPosition(x, y);
        labels.push_back(label);
    };
    
    // Подписи на оси X (как на твоей картинке)
    addLabel("O", 440, 310, 18);           // Точка O (начало координат)
    addLabel("π/2", 540, 310, 16);         // π/2
    addLabel("π", 590, 310, 16);            // π
    addLabel("3π/2", 640, 310, 16);         // 3π/2
    addLabel("2π", 690, 310, 16);            // 2π
    addLabel("5π/2", 740, 310, 16);          // 5π/2
    addLabel("-π/2", 390, 310, 16);          // -π/2
    addLabel("-π", 340, 310, 16);             // -π
    addLabel("-3π/2", 290, 310, 16);          // -3π/2
    addLabel("-2π", 240, 310, 16);             // -2π
    
    // Подписи на оси Y
    addLabel("1", 460, 200, 16);             // y = 1
    addLabel("1/2", 460, 250, 16);           // y = 1/2
    addLabel("0", 460, 295, 16);              // y = 0
    addLabel("-1/2", 460, 345, 16);           // y = -1/2
    addLabel("-1", 460, 395, 16);              // y = -1
    
    // Подпись самого графика
    addLabel("y = sin x", 600, 150, 20);
    
    // === ГРАФИК y = sin x ===
    sf::VertexArray graph(sf::LineStrip);
    
    // Рисуем от -2π до 2π (примерно от x = 200 до x = 700)
    for (int x = 200; x < 700; x++)
    {
        // Переводим пиксели в радианы
        float rad = (x - 450) * 0.02f;
        float y = 300 - 100 * sin(rad);  // 100 - амплитуда
        
        // Ограничиваем, чтобы график не уходил за пределы
        if (y >= 100 && y <= 500)
        {
            graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Red));
        }
    }
    
    // === ГЛАВНЫЙ ЦИКЛ ===
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::White);
        
        // Рисуем оси
        window.draw(xAxis);
        window.draw(yAxis);
        
        // Рисуем стрелки
        window.draw(xArrow1);
        window.draw(xArrow2);
        window.draw(yArrow1);
        window.draw(yArrow2);
        
        // Рисуем шкалу
        window.draw(scale);
        
        // Рисуем график
        window.draw(graph);
        
        // Рисуем подписи
        for (auto& label : labels)
        {
            window.draw(label);
        }
        
        window.display();
    }
    
    return 0;
}
