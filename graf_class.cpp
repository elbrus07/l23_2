#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

// ==================== КЛАСС ДЛЯ НАСТРОЕК ====================
class Settings
{
public:
    // Размеры окна
    int windowWidth = 900;
    int windowHeight = 600;
    
    // Положение осей
    int centerX = 450;
    int centerY = 300;
    
    // Границы осей
    int axisStartX = 100;
    int axisEndX = 800;
    int axisStartY = 100;
    int axisEndY = 500;
    
    // Настройки графика
    float amplitude = 100.0f;
    float frequency = 0.02f;
    
    // Настройки анимации
    float speed = 2.0f;
    
    // Настройки шкалы
    int scaleStep = 50;
    int scaleSize = 5;
    
    // Настройки текста
    int textSizeNormal = 16;
    int textSizeTitle = 20;
    int textSizeInfo = 14;
};

// ==================== КЛАСС ДЛЯ ОСЕЙ ====================
class Axes
{
private:
    sf::VertexArray xAxis;
    sf::VertexArray yAxis;
    std::vector<sf::VertexArray> arrows;
    sf::VertexArray scale;
    
public:
    Axes(const Settings& s)
    {
        // Создаем ось X
        xAxis = sf::VertexArray(sf::Lines, 2);
        xAxis[0].position = sf::Vector2f(s.axisStartX, s.centerY);
        xAxis[0].color = sf::Color::Black;
        xAxis[1].position = sf::Vector2f(s.axisEndX, s.centerY);
        xAxis[1].color = sf::Color::Black;
        
        // Создаем ось Y
        yAxis = sf::VertexArray(sf::Lines, 2);
        yAxis[0].position = sf::Vector2f(s.centerX, s.axisStartY);
        yAxis[0].color = sf::Color::Black;
        yAxis[1].position = sf::Vector2f(s.centerX, s.axisEndY);
        yAxis[1].color = sf::Color::Black;
        
        // Создаем стрелки
        createArrows(s);
        
        // Создаем шкалу (деления)
        createScale(s);
    }
    
    void createArrows(const Settings& s)
    {
        // Стрелка на оси X (справа)
        sf::VertexArray xArrow1(sf::Lines, 2);
        xArrow1[0].position = sf::Vector2f(s.axisEndX, s.centerY);
        xArrow1[0].color = sf::Color::Black;
        xArrow1[1].position = sf::Vector2f(s.axisEndX - 10, s.centerY - 5);
        xArrow1[1].color = sf::Color::Black;
        arrows.push_back(xArrow1);
        
        sf::VertexArray xArrow2(sf::Lines, 2);
        xArrow2[0].position = sf::Vector2f(s.axisEndX, s.centerY);
        xArrow2[0].color = sf::Color::Black;
        xArrow2[1].position = sf::Vector2f(s.axisEndX - 10, s.centerY + 5);
        xArrow2[1].color = sf::Color::Black;
        arrows.push_back(xArrow2);
        
        // Стрелка на оси Y (вверху)
        sf::VertexArray yArrow1(sf::Lines, 2);
        yArrow1[0].position = sf::Vector2f(s.centerX, s.axisStartY);
        yArrow1[0].color = sf::Color::Black;
        yArrow1[1].position = sf::Vector2f(s.centerX - 5, s.axisStartY + 10);
        yArrow1[1].color = sf::Color::Black;
        arrows.push_back(yArrow1);
        
        sf::VertexArray yArrow2(sf::Lines, 2);
        yArrow2[0].position = sf::Vector2f(s.centerX, s.axisStartY);
        yArrow2[0].color = sf::Color::Black;
        yArrow2[1].position = sf::Vector2f(s.centerX + 5, s.axisStartY + 10);
        yArrow2[1].color = sf::Color::Black;
        arrows.push_back(yArrow2);
    }
    
    void createScale(const Settings& s)
    {
        scale = sf::VertexArray(sf::Lines);
        
        // Деления на оси X
        for (int x = s.axisStartX; x <= s.axisEndX; x += s.scaleStep)
        {
            if (x != s.centerX)
            {
                scale.append(sf::Vertex(sf::Vector2f(x, s.centerY - s.scaleSize/2), sf::Color::Black));
                scale.append(sf::Vertex(sf::Vector2f(x, s.centerY + s.scaleSize/2), sf::Color::Black));
            }
        }
        
        // Деления на оси Y
        for (int y = s.axisStartY; y <= s.axisEndY; y += s.scaleStep)
        {
            if (y != s.centerY)
            {
                scale.append(sf::Vertex(sf::Vector2f(s.centerX - s.scaleSize/2, y), sf::Color::Black));
                scale.append(sf::Vertex(sf::Vector2f(s.centerX + s.scaleSize/2, y), sf::Color::Black));
            }
        }
    }
    
    void draw(sf::RenderWindow& window) const
    {
        window.draw(xAxis);
        window.draw(yAxis);
        for (const auto& arrow : arrows)
            window.draw(arrow);
        window.draw(scale);
    }
};

// ==================== КЛАСС ДЛЯ ПОДПИСЕЙ ====================
class Labels
{
private:
    std::vector<sf::Text> labels;
    sf::Font font;
    
public:
    Labels(const Settings& s)
    {
        // Загружаем шрифт
        if (!font.loadFromFile("arial.ttf"))
        {
            if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"))
            {
                std::cout << "Не удалось загрузить шрифт!" << std::endl;
            }
        }
        
        createAllLabels(s);
    }
    
    sf::Text createText(const std::string& text, int x, int y, int size)
    {
        sf::Text t;
        t.setFont(font);
        t.setString(text);
        t.setCharacterSize(size);
        t.setFillColor(sf::Color::Black);
        t.setPosition(x, y);
        return t;
    }
    
    void createAllLabels(const Settings& s)
    {
        // Подписи на оси X (с p вместо π)
        labels.push_back(createText("O", s.centerX - 10, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("p/2", s.centerX + 90, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("p", s.centerX + 140, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("3p/2", s.centerX + 190, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("2p", s.centerX + 240, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("-p/2", s.centerX - 110, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("-p", s.centerX - 160, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("-3p/2", s.centerX - 210, s.centerY + 5, s.textSizeNormal));
        labels.push_back(createText("-2p", s.centerX - 260, s.centerY + 5, s.textSizeNormal));
        
        // Подписи на оси Y
        labels.push_back(createText("1", s.centerX + 10, s.centerY - 100, s.textSizeNormal));
        labels.push_back(createText("1/2", s.centerX + 10, s.centerY - 50, s.textSizeNormal));
        labels.push_back(createText("0", s.centerX + 10, s.centerY - 5, s.textSizeNormal));
        labels.push_back(createText("-1/2", s.centerX + 10, s.centerY + 45, s.textSizeNormal));
        labels.push_back(createText("-1", s.centerX + 10, s.centerY + 95, s.textSizeNormal));
        
        // Название графика
        labels.push_back(createText("y = sin x", s.centerX + 150, s.centerY - 150, s.textSizeTitle));
    }
    
    void addInfoLabels(float speed)
    {
        // Очищаем старые информационные подписи
        while (labels.size() > 14) // Оставляем только основные подписи
        {
            labels.pop_back();
        }
        
        // Добавляем новые информационные подписи
        labels.push_back(createText("Speed: " + std::to_string((int)speed), 20, 20, 14));
        labels.push_back(createText("+ / - : change speed", 20, 40, 14));
        labels.push_back(createText("SPACE : restart", 20, 60, 14));
    }
    
    void draw(sf::RenderWindow& window) const
    {
        for (const auto& label : labels)
            window.draw(label);
    }
};

// ==================== КЛАСС ДЛЯ ГРАФИКА ====================
class Graph
{
private:
    std::vector<sf::Vector2f> allPoints;
    sf::Color color;
    int currentPoint;
    float progress;
    sf::Clock clock;
    
public:
    Graph(const Settings& s, sf::Color graphColor = sf::Color::Red)
        : color(graphColor), currentPoint(0), progress(0.0f)
    {
        calculateAllPoints(s);
    }
    
    void calculateAllPoints(const Settings& s)
    {
        allPoints.clear();
        
        for (int x = s.axisStartX; x <= s.axisEndX; x++)
        {
            float rad = (x - s.centerX) * s.frequency;
            float y = s.centerY - s.amplitude * sin(rad);
            
            if (y >= s.axisStartY && y <= s.axisEndY)
            {
                allPoints.push_back(sf::Vector2f(x, y));
            }
        }
    }
    
    void update(float speed)
    {
        float deltaTime = clock.restart().asSeconds();
        
        progress += deltaTime * speed;
        int targetPoint = static_cast<int>(progress * 30);
        
        if (targetPoint > currentPoint)
            currentPoint = targetPoint;
            
        if (currentPoint > allPoints.size())
            currentPoint = allPoints.size();
    }
    
    void restart()
    {
        currentPoint = 0;
        progress = 0.0f;
    }
    
    bool isComplete() const
    {
        return currentPoint >= allPoints.size();
    }
    
    sf::VertexArray getCurrentPart() const
    {
        sf::VertexArray graph(sf::LineStrip);
        
        for (int i = 0; i < currentPoint && i < allPoints.size(); i++)
        {
            graph.append(sf::Vertex(allPoints[i], color));
        }
        
        return graph;
    }
    
    void draw(sf::RenderWindow& window) const
    {
        window.draw(getCurrentPart());
    }
};

// ==================== ГЛАВНЫЙ КЛАСС ПРИЛОЖЕНИЯ ====================
class SinGraphApp
{
private:
    Settings settings;
    sf::RenderWindow window;
    Axes axes;
    Labels labels;
    Graph graph;
    
public:
    SinGraphApp()
        : window(sf::VideoMode(settings.windowWidth, settings.windowHeight), "y = sin x - Graph Animation")
        , axes(settings)
        , labels(settings)
        , graph(settings)
    {
        window.setFramerateLimit(60);
    }
    
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed)
            {
                handleKeyPress(event.key.code);
            }
        }
    }
    
    void handleKeyPress(sf::Keyboard::Key key)
    {
        if (key == sf::Keyboard::Equal || key == sf::Keyboard::Add)
        {
            settings.speed += 0.5f;
            if (settings.speed > 10.0f) settings.speed = 10.0f;
        }
        else if (key == sf::Keyboard::Hyphen || key == sf::Keyboard::Subtract)
        {
            settings.speed -= 0.5f;
            if (settings.speed < 0.5f) settings.speed = 0.5f;
        }
        else if (key == sf::Keyboard::Space)
        {
            graph.restart();
        }
        else if (key == sf::Keyboard::R)
        {
            // Дополнительно: перезапуск с обновлением точек
            graph.restart();
        }
    }
    
    void update()
    {
        graph.update(settings.speed);
        labels.addInfoLabels(settings.speed);
    }
    
    void draw()
    {
        window.clear(sf::Color::White);
        
        axes.draw(window);
        graph.draw(window);
        labels.draw(window);
        
        window.display();
    }
    
    void run()
    {
        while (window.isOpen())
        {
            handleEvents();
            update();
            draw();
        }
    }
};

// ==================== ТОЧКА ВХОДА ====================
int main()
{
    SinGraphApp app;
    app.run();
    return 0;
}
