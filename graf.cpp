#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    const int W = 800;
    const int H = 600;
    sf::RenderWindow window(sf::VideoMode(W, H), "Simple Graph Calc");
    window.setFramerateLimit(60); // Ограничим FPS для лучшей производительности

    // Центр экрана (наша точка 0,0)
    sf::Vector2f center(W / 2.0f, H / 2.0f);
    float scale = 50.0f; // 50 пикселей = 1 единица

    // 3. Добавляем переменные для управления перемещением
    sf::Vector2f offset(0.0f, 0.0f); // Смещение начала координат

    // 4. Функция для отрисовки графика
    auto drawGraph = [&](sf::VertexArray& graph, const sf::Vector2f& current_center, float current_scale) {
        graph.clear(); // Очищаем предыдущий график
        graph.setPrimitiveType(sf::LineStrip);
        for (int pixel_x = 0; pixel_x < W; pixel_x++) {
            // Переводим пиксели в математические X
            float x = (pixel_x - current_center.x) / current_scale;

            // САМА ФУНКЦИЯ: y = sin(x)
            float y = std::sin(x);
            // Если хотите параболу, напишите: float y = x * x;

            // Переводим математические Y обратно в пиксели
            float pixel_y = current_center.y - (y * current_scale);

            graph.append(sf::Vertex(sf::Vector2f(pixel_x, pixel_y), sf::Color::Yellow));
        }
    };

    sf::VertexArray axes(sf::Lines, 4);
    sf::VertexArray graph(sf::LineStrip);

    // Изначальная отрисовка графика
    drawGraph(graph, center + offset, scale);

    // 5. Обработка событий для масштабирования и перемещения
    float zoomSpeed = 0.1f; // Скорость масштабирования
    sf::Clock dragClock; // Для определения длительности нажатия
    sf::Vector2i lastMousePosition;
    bool isDragging = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Масштабирование с помощью колесика мыши
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) { // Увеличение масштаба
                    scale *= (1.0f + zoomSpeed);
                }
                else if (event.mouseWheelScroll.delta < 0) { // Уменьшение масштаба
                    scale /= (1.0f + zoomSpeed);
                }
                // Ограничение масштаба
                if (scale < 10.0f) scale = 10.0f;
                if (scale > 500.0f) scale = 500.0f;
                // Перерисовываем график с новым масштабом
                drawGraph(graph, center + offset, scale);
            }

            // Перемещение с помощью зажатой левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = true;
                    lastMousePosition = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                    dragClock.restart(); // Запускаем таймер для определения, не было ли это кликом
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (isDragging) {
                    sf::Vector2i currentMousePosition(event.mouseMove.x, event.mouseMove.y);
                    sf::Vector2f delta = sf::Vector2f(static_cast<float>(currentMousePosition.x - lastMousePosition.x),
                        static_cast<float>(currentMousePosition.y - lastMousePosition.y));
                    offset += delta;
                    lastMousePosition = currentMousePosition;

                    // Перерисовываем график с новым смещением
                    drawGraph(graph, center + offset, scale);
                }
            }
        }

        // Обновляем оси
        axes[0] = sf::Vertex(sf::Vector2f(0, center.y + offset.y), sf::Color::White);
        axes[1] = sf::Vertex(sf::Vector2f(W, center.y + offset.y), sf::Color::White);
        axes[2] = sf::Vertex(sf::Vector2f(center.x + offset.x, 0), sf::Color::White);
        axes[3] = sf::Vertex(sf::Vector2f(center.x + offset.x, H), sf::Color::White);

        window.clear();
        window.draw(axes);  // Рисуем оси
        window.draw(graph); // Рисуем график
        window.display();
    }

    return 0;
}
