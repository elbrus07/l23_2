#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

// ==================== КЛАСС НАСТРОЕК ====================
class Settings
{
public:
    // Размеры окна
    int windowWidth = 1000;
    int windowHeight = 700;
    
    // Границы отрисовки
    float xMin = -2 * M_PI;   // Левая граница по X
    float xMax = 2 * M_PI;    // Правая граница по X
    float yMin = -1.5f;       // Нижняя граница по Y
    float yMax = 1.5f;        // Верхняя граница по Y
    
    // Отступы для осей (в пикселях)
    int marginLeft = 80;
    int marginRight = 80;
    int marginTop = 60;
    int marginBottom = 80;
    
    // Параметры функции
    float amplitude = 1.0f;
    float frequency = 1.0f;
    
    // Настройки анимации (без ограничения скорости)
    float animationSpeed = 50.0f;  // Точек в секунду (можно очень быстро)
    
    // Цвета
    sf::Color graphColor = sf::Color::Red;
    sf::Color axesColor = sf::Color::Black;
    sf::Color gridColor = sf::Color(200, 200, 200);
    
    // Настройки шкалы
    float xTickStep = M_PI / 2;  // Шаг делений по X (π/2)
    float yTickStep = 0.5f;       // Шаг делений по Y
};

// ==================== КЛАСС ДЛЯ ПРЕОБРАЗОВАНИЯ КООРДИНАТ ====================
class CoordinateTransformer
{
private:
    Settings& s;
    float worldToPixelX(float worldX) const
    {
        float worldWidth = s.xMax - s.xMin;
        float pixelWidth = s.windowWidth - s.marginLeft - s.marginRight;
        return s.marginLeft + (worldX - s.xMin) / worldWidth * pixelWidth;
    }
    
    float worldToPixelY(float worldY) const
    {
        float worldHeight = s.yMax - s.yMin;
        float pixelHeight = s.windowHeight - s.marginTop - s.marginBottom;
        return s.marginTop + (s.yMax - worldY) / worldHeight * pixelHeight;
    }
    
public:
    CoordinateTransformer(Settings& settings) : s(settings) {}
    
    sf::Vector2f worldToPixel(float worldX, float worldY) const
    {
        return sf::Vector2f(worldToPixelX(worldX), worldToPixelY(worldY));
    }
    
    float worldToPixelX(float worldX) const
    {
        float worldWidth = s.xMax - s.xMin;
        float pixelWidth = s.windowWidth - s.marginLeft - s.marginRight;
        return s.marginLeft + (worldX - s.xMin) / worldWidth * pixelWidth;
    }
    
    float worldToPixelY(float worldY) const
    {
        float worldHeight = s.yMax - s.yMin;
        float pixelHeight = s.windowHeight - s.marginTop - s.marginBottom;
        return s.marginTop + (s.yMax - worldY) / worldHeight * pixelHeight;
    }
    
    float pixelToWorldX(float pixelX) const
    {
        float worldWidth = s.xMax - s.xMin;
        float pixelWidth = s.windowWidth - s.marginLeft - s.marginRight;
        return s.xMin + (pixelX - s.marginLeft) / pixelWidth * worldWidth;
    }
    
    float pixelToWorldY(float pixelY) const
    {
        float worldHeight = s.yMax - s.yMin;
        float pixelHeight = s.windowHeight - s.marginTop - s.marginBottom;
        return s.yMax - (pixelY - s.marginTop) / pixelHeight * worldHeight;
    }
};

// ==================== КЛАСС ДЛЯ ОСЕЙ И СЕТКИ ====================
class AxesAndGrid
{
private:
    sf::VertexArray xAxis;
    sf::VertexArray yAxis;
    sf::VertexArray grid;
    std::vector<sf::VertexArray> xTicks;
    std::vector<sf::VertexArray> yTicks;
    
    void updateAxes(const CoordinateTransformer& transformer, const Settings& s)
    {
        // Ось X
        float yZero = transformer.worldToPixelY(0);
        xAxis = sf::VertexArray(sf::Lines, 2);
        xAxis[0].position = sf::Vector2f(s.marginLeft, yZero);
        xAxis[0].color = s.axesColor;
        xAxis[1].position = sf::Vector2f(s.windowWidth - s.marginRight, yZero);
        xAxis[1].color = s.axesColor;
        
        // Ось Y
        float xZero = transformer.worldToPixelX(0);
        yAxis = sf::VertexArray(sf::Lines, 2);
        yAxis[0].position = sf::Vector2f(xZero, s.marginTop);
        yAxis[0].color = s.axesColor;
        yAxis[1].position = sf::Vector2f(xZero, s.windowHeight - s.marginBottom);
        yAxis[1].color = s.axesColor;
    }
    
    void updateGrid(const CoordinateTransformer& transformer, const Settings& s)
    {
        grid = sf::VertexArray(sf::Lines);
        
        // Вертикальные линии сетки (по X)
        for (float x = -10; x <= 10; x += s.xTickStep)
        {
            if (x >= s.xMin && x <= s.xMax && std::abs(x) > 0.001f)
            {
                float pixelX = transformer.worldToPixelX(x);
                grid.append(sf::Vertex(sf::Vector2f(pixelX, s.marginTop), s.gridColor));
                grid.append(sf::Vertex(sf::Vector2f(pixelX, s.windowHeight - s.marginBottom), s.gridColor));
            }
        }
        
        // Горизонтальные линии сетки (по Y)
        for (float y = -2; y <= 2; y += s.yTickStep)
        {
            if (y >= s.yMin && y <= s.yMax && std::abs(y) > 0.001f)
            {
                float pixelY = transformer.worldToPixelY(y);
                grid.append(sf::Vertex(sf::Vector2f(s.marginLeft, pixelY), s.gridColor));
                grid.append(sf::Vertex(sf::Vector2f(s.windowWidth - s.marginRight, pixelY), s.gridColor));
            }
        }
    }
    
    void updateTicks(const CoordinateTransformer& transformer, const Settings& s)
    {
        xTicks.clear();
        yTicks.clear();
        
        int tickLength = 6;
        
        // Деления на оси X
        float yAxisPixel = transformer.worldToPixelY(0);
        for (float x = -10; x <= 10; x += s.xTickStep)
        {
            if (x >= s.xMin && x <= s.xMax)
            {
                float pixelX = transformer.worldToPixelX(x);
                sf::VertexArray tick(sf::Lines, 2);
                tick[0].position = sf::Vector2f(pixelX, yAxisPixel - tickLength/2);
                tick[0].color = s.axesColor;
                tick[1].position = sf::Vector2f(pixelX, yAxisPixel + tickLength/2);
                tick[1].color = s.axesColor;
                xTicks.push_back(tick);
            }
        }
        
        // Деления на оси Y
        float xAxisPixel = transformer.worldToPixelX(0);
        for (float y = -2; y <= 2; y += s.yTickStep)
        {
            if (y >= s.yMin && y <= s.yMax)
            {
                float pixelY = transformer.worldToPixelY(y);
                sf::VertexArray tick(sf::Lines, 2);
                tick[0].position = sf::Vector2f(xAxisPixel - tickLength/2, pixelY);
                tick[0].color = s.axesColor;
                tick[1].position = sf::Vector2f(xAxisPixel + tickLength/2, pixelY);
                tick[1].color = s.axesColor;
                yTicks.push_back(tick);
            }
        }
    }
    
public:
    void update(const CoordinateTransformer& transformer, const Settings& s)
    {
        updateAxes(transformer, s);
        updateGrid(transformer, s);
        updateTicks(transformer, s);
    }
    
    void draw(sf::RenderWindow& window) const
    {
        window.draw(grid);
        window.draw(xAxis);
        window.draw(yAxis);
        for (const auto& tick : xTicks) window.draw(tick);
        for (const auto& tick : yTicks) window.draw(tick);
    }
};

// ==================== КЛАСС ДЛЯ ПОДПИСЕЙ ====================
class Labels
{
private:
    std::vector<sf::Text> labels;
    sf::Font font;
    Settings& s;
    CoordinateTransformer& transformer;
    
    std::string formatNumber(float value)
    {
        std::stringstream ss;
        if (std::abs(value - M_PI) < 0.01)
            return "π";
        else if (std::abs(value - M_PI/2) < 0.01)
            return "π/2";
        else if (std::abs(value + M_PI/2) < 0.01)
            return "-π/2";
        else if (std::abs(value - M_PI) < 0.01)
            return "π";
        else if (std::abs(value + M_PI) < 0.01)
            return "-π";
        else if (std::abs(value - 2*M_PI) < 0.01)
            return "2π";
        else if (std::abs(value + 2*M_PI) < 0.01)
            return "-2π";
        else if (std::abs(value - 3*M_PI/2) < 0.01)
            return "3π/2";
        else if (std::abs(value + 3*M_PI/2) < 0.01)
            return "-3π/2";
        else
        {
            ss << std::fixed << std::setprecision(2) << value;
            return ss.str();
        }
    }
    
    sf::Text createText(const std::string& text, float x, float y, int size, sf::Color color = sf::Color::Black)
    {
        sf::Text t;
        t.setFont(font);
        t.setString(text);
        t.setCharacterSize(size);
        t.setFillColor(color);
        t.setPosition(x, y);
        return t;
    }
    
public:
    Labels(Settings& settings, CoordinateTransformer& trans) 
        : s(settings), transformer(trans)
    {
        if (!font.loadFromFile("arial.ttf"))
        {
            font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
        }
    }
    
    void update()
    {
        labels.clear();
        
        // Подписи на оси X
        float yZeroPixel = transformer.worldToPixelY(0);
        for (float x = -10; x <= 10; x += s.xTickStep)
        {
            if (x >= s.xMin && x <= s.xMax && std::abs(x) > 0.001f)
            {
                float pixelX = transformer.worldToPixelX(x);
                std::string label = formatNumber(x);
                labels.push_back(createText(label, pixelX - 15, yZeroPixel + 5, 14));
            }
        }
        
        // Подпись 0
        float xZeroPixel = transformer.worldToPixelX(0);
        labels.push_back(createText("0", xZeroPixel - 8, transformer.worldToPixelY(0) + 5, 14));
        
        // Подписи на оси Y
        float xZeroPixelY = transformer.worldToPixelX(0);
        for (float y = -2; y <= 2; y += s.yTickStep)
        {
            if (y >= s.yMin && y <= s.yMax && std::abs(y) > 0.001f)
            {
                float pixelY = transformer.worldToPixelY(y);
                std::string label = formatNumber(y);
                labels.push_back(createText(label, xZeroPixelY + 8, pixelY - 8, 14));
            }
        }
        
        // Название функции
        labels.push_back(createText("y = sin x", s.windowWidth - 150, s.marginTop - 30, 20, sf::Color::Blue));
        
        // Информационные подсказки
        labels.push_back(createText("УПРАВЛЕНИЕ:", 20, 20, 16, sf::Color(100, 100, 100)));
        labels.push_back(createText("Колесико мыши - масштаб", 20, 45, 14, sf::Color(100, 100, 100)));
        labels.push_back(createText("Стрелки влево/вправо - движение", 20, 65, 14, sf::Color(100, 100, 100)));
        labels.push_back(createText("Пробел - перезапустить анимацию", 20, 85, 14, sf::Color(100, 100, 100)));
        labels.push_back(createText("R - сбросить вид", 20, 105, 14, sf::Color(100, 100, 100)));
        
        // Текущий масштаб
        std::stringstream ss;
        ss << "Диапазон X: [" << std::fixed << std::setprecision(2) << s.xMin 
           << ", " << s.xMax << "]";
        labels.push_back(createText(ss.str(), 20, s.windowHeight - 60, 14, sf::Color(150, 150, 150)));
        
        ss.str("");
        ss << "Диапазон Y: [" << s.yMin << ", " << s.yMax << "]";
        labels.push_back(createText(ss.str(), 20, s.windowHeight - 40, 14, sf::Color(150, 150, 150)));
    }
    
    void draw(sf::RenderWindow& window) const
    {
        for (const auto& label : labels)
            window.draw(label);
    }
};

// ==================== КЛАСС ГРАФИКА ====================
class Graph
{
private:
    std::vector<sf::Vector2f> allPoints;
    sf::Color color;
    int currentPoint;
    float progress;
    sf::Clock clock;
    Settings& s;
    CoordinateTransformer& transformer;
    
public:
    Graph(Settings& settings, CoordinateTransformer& trans, sf::Color graphColor = sf::Color::Red)
        : s(settings), transformer(trans), color(graphColor), currentPoint(0), progress(0.0f)
    {
        calculateAllPoints();
    }
    
    void calculateAllPoints()
    {
        allPoints.clear();
        
        float step = (s.xMax - s.xMin) / 1000;  // 1000 точек для плавности
        
        for (float x = s.xMin; x <= s.xMax; x += step)
        {
            float y = s.amplitude * sin(s.frequency * x);
            
            if (y >= s.yMin - 0.5 && y <= s.yMax + 0.5)
            {
                sf::Vector2f pixel = transformer.worldToPixel(x, y);
                allPoints.push_back(pixel);
            }
        }
    }
    
    void update()
    {
        float deltaTime = clock.restart().asSeconds();
        
        // Нет ограничения скорости - можно очень быстро
        progress += deltaTime * s.animationSpeed;
        int targetPoint = static_cast<int>(progress);
        
        if (targetPoint > currentPoint)
            currentPoint = targetPoint;
            
        if (currentPoint > allPoints.size())
            currentPoint = allPoints.size();
    }
    
    void restart()
    {
        currentPoint = 0;
        progress = 0.0f;
        clock.restart();
    }
    
    void recalculate()
    {
        calculateAllPoints();
        restart();
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
    Settings s;
    sf::RenderWindow window;
    CoordinateTransformer transformer;
    AxesAndGrid axesAndGrid;
    Labels labels;
    Graph graph;
    
    bool isDragging;
    sf::Vector2i lastMousePos;
    float lastXMin, lastXMax;
    
    void handleZoom(float delta, sf::Vector2i mousePos)
    {
        // Получаем мировые координаты мыши до зумирования
        float mouseWorldX = transformer.pixelToWorldX(mousePos.x);
        
        // Коэффициент масштабирования
        float zoomFactor = (delta > 0) ? 0.9f : 1.1f;
        
        // Масштабируем X
        float newWidth = (s.xMax - s.xMin) * zoomFactor;
        if (newWidth > 0.1f && newWidth < 50.0f)
        {
            s.xMin = mouseWorldX - (mouseWorldX - s.xMin) * zoomFactor;
            s.xMax = s.xMin + newWidth;
        }
        
        // Масштабируем Y (автоматически, чтобы сохранить пропорции)
        float newHeight = (s.yMax - s.yMin) * zoomFactor;
        if (newHeight > 0.1f && newHeight < 10.0f)
        {
            s.yMin = -newHeight / 2;
            s.yMax = newHeight / 2;
        }
        
        // Обновляем все
        updateAll();
    }
    
    void handlePan(float deltaX, float deltaY)
    {
        // Перемещаем по X
        float worldDeltaX = (s.xMax - s.xMin) * (-deltaX / (s.windowWidth - s.marginLeft - s.marginRight));
        s.xMin += worldDeltaX;
        s.xMax += worldDeltaX;
        
        // Перемещаем по Y
        float worldDeltaY = (s.yMax - s.yMin) * (deltaY / (s.windowHeight - s.marginTop - s.marginBottom));
        s.yMin += worldDeltaY;
        s.yMax += worldDeltaY;
        
        updateAll();
    }
    
    void resetView()
    {
        s.xMin = -2 * M_PI;
        s.xMax = 2 * M_PI;
        s.yMin = -1.5f;
        s.yMax = 1.5f;
        updateAll();
    }
    
    void updateAll()
    {
        axesAndGrid.update(transformer, s);
        graph.recalculate();
        labels.update();
    }
    
public:
    SinGraphApp()
        : window(sf::VideoMode(s.windowWidth, s.windowHeight), "y = sin x - Интерактивный график")
        , transformer(s)
        , axesAndGrid()
        , labels(s, transformer)
        , graph(s, transformer, s.graphColor)
        , isDragging(false)
    {
        window.setFramerateLimit(120);
        updateAll();
    }
    
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Масштабирование колесиком мыши
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    handleZoom(event.mouseWheelScroll.delta, mousePos);
                }
            }
            
            // Начало перетаскивания (для движения)
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDragging = true;
                    lastMousePos = sf::Mouse::getPosition(window);
                    lastXMin = s.xMin;
                    lastXMax = s.xMax;
                }
            }
            
            // Конец перетаскивания
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDragging = false;
                }
            }
            
            // Перетаскивание (движение)
            if (event.type == sf::Event::MouseMoved && isDragging)
            {
                sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                float deltaX = currentMousePos.x - lastMousePos.x;
                float deltaY = currentMousePos.y - lastMousePos.y;
                
                // Перемещаем график
                float worldDeltaX = (s.xMax - s.xMin) * (-deltaX / (s.windowWidth - s.marginLeft - s.marginRight));
                float worldDeltaY = (s.yMax - s.yMin) * (deltaY / (s.windowHeight - s.marginTop - s.marginBottom));
                
                s.xMin = lastXMin + worldDeltaX;
                s.xMax = lastXMax + worldDeltaX;
                s.yMin += worldDeltaY;
                s.yMax += worldDeltaY;
                
                updateAll();
            }
            
            // Клавиатура
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Space:
                        graph.restart();
                        break;
                    case sf::Keyboard::R:
                        resetView();
                        graph.restart();
                        break;
                    case sf::Keyboard::Left:
                        handlePan(50, 0);
                        break;
                    case sf::Keyboard::Right:
                        handlePan(-50, 0);
                        break;
                    case sf::Keyboard::Up:
                        handlePan(0, 50);
                        break;
                    case sf::Keyboard::Down:
                        handlePan(0, -50);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    
    void update()
    {
        graph.update();
    }
    
    void draw()
    {
        window.clear(sf::Color::White);
        
        axesAndGrid.draw(window);
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
