#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>

// === НАСТРОЙКИ ===
struct Settings
{
    int windowWidth = 900;
    int windowHeight = 600;
    float speed = 2.0f;        // Скорость рисования
    int centerX = 450;
    int centerY = 300;
    float amplitude = 100.0f;   // Высота волны
    float frequency = 0.02f;    // Частота
};

// === СОЗДАТЬ ОСЬ X ===
sf::VertexArray createXAxis(int centerY)
{
    sf::VertexArray axis(sf::Lines, 2);
    axis[0].position = sf::Vector2f(100, centerY);
    axis[0].color = sf::Color::Black;
    axis[1].position = sf::Vector2f(800, centerY);
    axis[1].color = sf::Color::Black;
    return axis;
}

// === СОЗДАТЬ ОСЬ Y ===
sf::VertexArray createYAxis(int centerX)
{
    sf::VertexArray axis(sf::Lines, 2);
    axis[0].position = sf::Vector2f(centerX, 100);
    axis[0].color = sf::Color::Black;
    axis[1].position = sf::Vector2f(centerX, 500);
    axis[1].color = sf::Color::Black;
    return axis;
}

// === СОЗДАТЬ СТРЕЛКИ ===
std::vector<sf::VertexArray> createArrows(int centerX, int centerY)
{
    std::vector<sf::VertexArray> arrows;
    
    // Стрелка на оси X (справа)
    sf::VertexArray xArrow1(sf::Lines, 2);
    xArrow1[0].position = sf::Vector2f(800, centerY);
    xArrow1[0].color = sf::Color::Black;
    xArrow1[1].position = sf::Vector2f(790, centerY - 5);
    xArrow1[1].color = sf::Color::Black;
    arrows.push_back(xArrow1);
    
    sf::VertexArray xArrow2(sf::Lines, 2);
    xArrow2[0].position = sf::Vector2f(800, centerY);
    xArrow2[0].color = sf::Color::Black;
    xArrow2[1].position = sf::Vector2f(790, centerY + 5);
    xArrow2[1].color = sf::Color::Black;
    arrows.push_back(xArrow2);
    
    // Стрелка на оси Y (вверху)
    sf::VertexArray yArrow1(sf::Lines, 2);
    yArrow1[0].position = sf::Vector2f(centerX, 100);
    yArrow1[0].color = sf::Color::Black;
    yArrow1[1].position = sf::Vector2f(centerX - 5, 110);
    yArrow1[1].color = sf::Color::Black;
    arrows.push_back(yArrow1);
    
    sf::VertexArray yArrow2(sf::Lines, 2);
    yArrow2[0].position = sf::Vector2f(centerX, 100);
    yArrow2[0].color = sf::Color::Black;
    yArrow2[1].position = sf::Vector2f(centerX + 5, 110);
    yArrow2[1].color = sf::Color::Black;
    arrows.push_back(yArrow2);
    
    return arrows;
}

// === СОЗДАТЬ ШКАЛУ (ДЕЛЕНИЯ) ===
sf::VertexArray createScale(int centerX, int centerY)
{
    sf::VertexArray scale(sf::Lines);
    
    // Деления на оси X
    for (int x = 150; x < 800; x += 50)
    {
        scale.append(sf::Vertex(sf::Vector2f(x, centerY - 3), sf::Color::Black));
        scale.append(sf::Vertex(sf::Vector2f(x, centerY + 3), sf::Color::Black));
    }
    
    // Деления на оси Y
    for (int y = 150; y < 500; y += 50)
    {
        scale.append(sf::Vertex(sf::Vector2f(centerX - 3, y), sf::Color::Black));
        scale.append(sf::Vertex(sf::Vector2f(centerX + 3, y), sf::Color::Black));
    }
    
    return scale;
}

// === СОЗДАТЬ ТЕКСТ (ПОДПИСЬ) ===
sf::Text createText(std::string text, int x, int y, sf::Font& font, int size)
{
    sf::Text t;
    t.setFont(font);
    t.setString(text);
    t.setCharacterSize(size);
    t.setFillColor(sf::Color::Black);
    t.setPosition(x, y);
    return t;
}

// === СОЗДАТЬ ВСЕ ПОДПИСИ ===
std::vector<sf::Text> createAllLabels(sf::Font& font, int centerX, int centerY, float speed)
{
    std::vector<sf::Text> labels;
    
    // Подписи на оси X (p вместо π)
    labels.push_back(createText("O", centerX - 10, centerY + 5, font, 16));
    labels.push_back(createText("p/2", centerX + 90, centerY + 5, font, 16));
    labels.push_back(createText("p", centerX + 140, centerY + 5, font, 16));
    labels.push_back(createText("3p/2", centerX + 190, centerY + 5, font, 16));
    labels.push_back(createText("2p", centerX + 240, centerY + 5, font, 16));
    labels.push_back(createText("-p/2", centerX - 110, centerY + 5, font, 16));
    labels.push_back(createText("-p", centerX - 160, centerY + 5, font, 16));
    labels.push_back(createText("-3p/2", centerX - 210, centerY + 5, font, 16));
    labels.push_back(createText("-2p", centerX - 260, centerY + 5, font, 16));
    
    // Подписи на оси Y
    labels.push_back(createText("1", centerX + 10, centerY - 100, font, 16));
    labels.push_back(createText("1/2", centerX + 10, centerY - 50, font, 16));
    labels.push_back(createText("0", centerX + 10, centerY - 5, font, 16));
    labels.push_back(createText("-1/2", centerX + 10, centerY + 45, font, 16));
    labels.push_back(createText("-1", centerX + 10, centerY + 95, font, 16));
    
    // Название графика
    labels.push_back(createText("y = sin x", centerX + 150, centerY - 150, font, 20));
    
    // Подсказки
    labels.push_back(createText("Speed: " + std::to_string((int)speed), 20, 20, font, 14));
    labels.push_back(createText("+ / - : change speed", 20, 40, font, 14));
    labels.push_back(createText("SPACE : restart", 20, 60, font, 14));
    
    return labels;
}

// === РАССЧИТАТЬ ВСЕ ТОЧКИ ГРАФИКА ===
std::vector<sf::Vector2f> calculatePoints(Settings& s)
{
    std::vector<sf::Vector2f> points;
    
    for (int x = 100; x <= 800; x++)
    {
        float rad = (x - s.centerX) * s.frequency;
        float y = s.centerY - s.amplitude * sin(rad);
        
        if (y >= 100 && y <= 500)
        {
            points.push_back(sf::Vector2f(x, y));
        }
    }
    
    return points;
}

// === СОЗДАТЬ ЧАСТЬ ГРАФИКА ===
sf::VertexArray createGraphPart(std::vector<sf::Vector2f>& allPoints, int count)
{
    sf::VertexArray graph(sf::LineStrip);
    
    for (int i = 0; i < count && i < allPoints.size(); i++)
    {
        graph.append(sf::Vertex(allPoints[i], sf::Color::Red));
    }
    
    return graph;
}

// === ГЛАВНАЯ ФУНКЦИЯ ===
int main()
{
    // Настройки
    Settings s;
    
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(s.windowWidth, s.windowHeight), "y = sin x");
    
    // Загружаем шрифт
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // Если нет arial, пробуем другой
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }
    
    // Создаем все элементы через функции
    sf::VertexArray xAxis = createXAxis(s.centerY);
    sf::VertexArray yAxis = createYAxis(s.centerX);
    std::vector<sf::VertexArray> arrows = createArrows(s.centerX, s.centerY);
    sf::VertexArray scale = createScale(s.centerX, s.centerY);
    std::vector<sf::Vector2f> allPoints = calculatePoints(s);
    
    // Для анимации
    int currentPoint = 0;
    float progress = 0.0f;
    sf::Clock clock;
    
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        // События
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Equal)
                    s.speed += 0.5f;
                if (event.key.code == sf::Keyboard::Hyphen)
                    s.speed -= 0.5f;
                if (event.key.code == sf::Keyboard::Space)
                    currentPoint = 0;
                    progress = 0.0f;
            }
        }
        
        // Анимация
        progress += deltaTime * s.speed;
        int targetPoint = (int)(progress * 30);
        if (targetPoint > currentPoint)
            currentPoint = targetPoint;
        if (currentPoint > allPoints.size())
            currentPoint = allPoints.size();
        
        // Создаем текущую часть графика
        sf::VertexArray graph = createGraphPart(allPoints, currentPoint);
        
        // Обновляем подписи (чтобы видеть скорость)
        std::vector<sf::Text> labels = createAllLabels(font, s.centerX, s.centerY, s.speed);
        
        // Рисуем
        window.clear(sf::Color::White);
        window.draw(xAxis);
        window.draw(yAxis);
        for (auto& arrow : arrows)
            window.draw(arrow);
        window.draw(scale);
        window.draw(graph);
        for (auto& label : labels)
            window.draw(label);
        window.display();
    }
    
    return 0;
}
