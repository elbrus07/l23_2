#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;


void draw_scale(sf::RenderWindow &window, int width, int height, int isVertical, int scale, int center_x, int center_y, int length, const sf::Font &font){
    /*
    функция рисует шкалу на оси
        :param isVertical - признак вертикальная ось: 1 или горизонтальная: 0
        :param scale - масштаб
        :param length - длина оси
        :param center_x - x координата центра системы координат
        :param center_x - x координата центра системы координат
     */
    
    if (isVertical == 0){ // отсечки на горизонтальной оси
        int x_shift = (width - length) / 2;
        int start = center_x - x_shift;
        int n = (length - start) / scale;  // количество отсечек на  положительной части оси x
        int m = (start) / scale;  // количество отсечек на отрицательной части оси x
        
        
        sf::Text text;
        text.setFont(font);
        text.setString("0");
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::Black);
        text.setPosition(center_x + 5, center_y + 5);
        window.draw(text);
        
        for(int i=0; i < n; i++) { 
            
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x + i * scale, center_y - 5);
            line[0].color = sf::Color::Black;
            line[1].position = sf::Vector2f(center_x + i * scale, center_y + 5);
            line[1].color = sf::Color::Black;
            window.draw(line);
            
            if (i != 0) {
                
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(i));
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setPosition(center_x + i * scale - 4, center_y + 5);
                window.draw(text);
            }
            
            
        }
        for (int i=0; i < m; i++) {
            
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x - i * scale, center_y - 5); 
            line[0].color = sf::Color::Black;
            line[1].position = sf::Vector2f(center_x - i * scale, center_y + 5);
            line[1].color = sf::Color::Black;
            window.draw(line);
            
            if (i != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(i*-1));
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setPosition(center_x - i * scale - 6, center_y + 5);
                window.draw(text);
            }
            
        }
    } else {  // отсечки на вертикальной оси
        int y_shift = (height - length) / 2;
        int start = center_y - y_shift;
        int n = (length - start) / scale;  // количество отсечек на отрицательной части оси y
        int m = (start) / scale;  // количество отсечек на  положительной части оси y
        for (int i=0; i < n; i++) {
            
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x + 5, center_y + i * scale); 
            line[0].color = sf::Color::Black;
            line[1].position = sf::Vector2f(center_x - 5, center_y + i * scale);
            line[1].color = sf::Color::Black;
            window.draw(line);
            
            if (i != 0) {
                
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(i*-1));
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setPosition(center_x + 7, center_y + i * scale - 8);
                window.draw(text);
            }
        }   
        for (int i=0; i < m; i++) {
    
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x + 5, center_y - i * scale); 
            line[0].color = sf::Color::Black;
            line[1].position = sf::Vector2f(center_x - 5, center_y - i * scale);
            line[1].color = sf::Color::Black;
            window.draw(line);
            
            if (i != 0) {
                
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(i));
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setPosition(center_x + 7, center_y - i * scale - 8);
                window.draw(text);
            }
        }    
    }
}

void draw_axis(sf::RenderWindow &window, int width, int height, bool vertical, int length, int scale, int center_x, int center_y, const sf::Font &font) {
    if (vertical){
        int y_shift = (width - length) / 2;
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(center_x, y_shift); 
        line[0].color = sf::Color::Black;
        line[1].position = sf::Vector2f(center_x, y_shift + length); 
        line[1].color = sf::Color::Black;
        window.draw(line);
        draw_scale(window, width, height, 1, scale, center_x, center_y, length, font);
    } else {
        int x_shift = (width - length) / 2;
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x_shift, center_y); 
        line[0].color = sf::Color::Black;
        line[1].position = sf::Vector2f(x_shift + length, center_y);
        line[1].color = sf::Color::Black;
        window.draw(line);
        draw_scale(window, width, height, 0, scale, center_x, center_y, length, font);
    }
}

double f(double x){
    //Функция

    return sin(x);
}

void draw_func(sf::RenderWindow &window, double (*func)(double), int a, int b, int scale, int center_x, int center_y, sf::Color color, int delay){
    
    int length = b - a;  // длина отрезка
    double h = 0.1;  // шаг для рисования графика функции
    int n = (length / h);
    
    sf::Clock clock;
    const sf::Time frameDelay = sf::milliseconds(delay); // 10 мс задержка
    
    for (int i=0; i < n-1; i++) {
        // Обработка событий, чтобы окно не "зависало"
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        double x0 = (a + i * h) * scale;
        double y0 = func(a + i * h) * scale;
        double x1 = (a + (i + 1) * h) * scale;
        double y1 = func(a + (i + 1) * h) * scale;
        
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(center_x + x0, center_y - y0); 
        line[0].color = color;
        line[1].position = sf::Vector2f(center_x + x1, center_y - y1);
        line[1].color = color;
        window.draw(line);
        if (delay > 0) {
            window.display();
            
            sf::Time elapsed = clock.getElapsedTime();
            if (elapsed < frameDelay) {
                sf::sleep(frameDelay - elapsed);
            }
            clock.restart();
        }
        
    }
}

int main()
{
    int scale = 50;
    int center_x = 400;
    int center_y = 400;
    int width = 800;
    int height = 800;
    int length = 700;
    int delay = 10;
    
    sf::RenderWindow window(sf::VideoMode(width + 200, height), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("fonts/Caladea-Regular.ttf"))
    {
        std::cerr << "Ошибка: не удалось загрузить файл шрифта.\n";
        return 1;
    }


    window.clear(sf::Color::White);
    
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(width, 0); 
    line[0].color = sf::Color::Black;
    line[1].position = sf::Vector2f(width, height);
    line[1].color = sf::Color::Black;
    window.draw(line);
    
    // Настройка текста для ввода
    sf::Text inputTextFunc("", font, 24);
    inputTextFunc.setFillColor(sf::Color::Black);
    inputTextFunc.setPosition(810, 50);
    
    sf::Text inputTextScale("", font, 24);
    inputTextScale.setFillColor(sf::Color::Black);
    inputTextScale.setPosition(810, 100);

    // Настройка фона поля ввода
    sf::RectangleShape inputBoxFunc(sf::Vector2f(150, 40));
    inputBoxFunc.setFillColor(sf::Color(240, 240, 240));
    inputBoxFunc.setPosition(inputTextFunc.getPosition().x - 5, inputTextFunc.getPosition().y - 5);
    
    sf::RectangleShape inputBoxScale(sf::Vector2f(60, 40));
    inputBoxScale.setFillColor(sf::Color(240, 240, 240));
    inputBoxScale.setPosition(inputTextScale.getPosition().x - 5, inputTextScale.getPosition().y - 5);

    // Переменная для хранения введенного текста
    string inputStrFunc;
    string inputStrScale;
    
    string m[] = {inputStrFunc, inputStrScale};
    //string m[] = {inputStrFunc, inputStrScale};
    
    int active = -1;
    
    window.draw(inputBoxFunc);
    window.draw(inputTextFunc);
    window.draw(inputBoxScale);
    window.draw(inputTextScale);
    
    
    // Создание кнопки
    sf::RectangleShape button(sf::Vector2f(150, 50));
    button.setPosition(810, 350);
    button.setFillColor(sf::Color::White);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(1);
    window.draw(button);
    
    sf::Text text;
    text.setFont(font);
    text.setString("Draw");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(840, 360);
    window.draw(text);
    
    draw_axis(window, width, height, true, length, scale, center_x, center_y, font);
    draw_axis(window, width, height, false, length, scale, center_x, center_y, font);
    draw_func(window, f, -6, 7, scale, center_x, center_y, sf::Color::Red, delay);
    
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                int step = 1*scale;
                switch (event.key.code) {
                    case sf::Keyboard::Left:  center_x -= step; break;
                    case sf::Keyboard::Right: center_x += step; break;
                    case sf::Keyboard::Up:    center_y -= step; break;
                    case sf::Keyboard::Down:  center_y += step; break;
                    default: break;
                }
                window.clear(sf::Color::White);
        
                        
                window.draw(line);
                
                window.draw(inputBoxFunc);
                window.draw(inputTextFunc);
                window.draw(inputBoxScale);
                window.draw(inputTextScale);
                
                // Создание кнопки
                
                window.draw(button);
                
                
                window.draw(text);
                
                
                draw_axis(window, width, height, true, length, scale, center_x, center_y, font);
                draw_axis(window, width, height, false, length, scale, center_x, center_y, font);
                draw_func(window, f, -6, 7, scale, center_x, center_y, sf::Color::Red, 0);
            }
            
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::MouseButtonPressed) {                   
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (inputBoxFunc.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        active = 0;
                    } else if (inputBoxScale.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        active = 1;
                    } else {
                        active = -1;
                    }
                    
                }
            }
            
            // Обработка ввода текста
            if (event.type == sf::Event::TextEntered && active != -1) {
                if (event.text.unicode == '\b' && !m[active].empty()) {
                    // Удаление последнего символа (Backspace)
                    //inputStrFunc.pop_back();
                    m[active].pop_back();
                } else if (event.text.unicode != '\b' && event.text.unicode < 128) {
                    // Добавление нового символа
                    m[active] += static_cast<char>(event.text.unicode);
                }
                
                inputTextFunc.setString(m[0]);
                inputTextScale.setString(m[1]);
                
                //delay = stoi(inputStr);
            }

            // Проверка нажатия
            
            if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                button.setFillColor(sf::Color(240,240,240));
                window.draw(button);
                window.draw(text);
                window.display();
                if (event.type == sf::Event::MouseButtonPressed) {
                    
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        scale = stoi(inputStrScale);
                        window.clear(sf::Color::White);
        
                        
                        window.draw(line);
                        
                        window.draw(inputBoxFunc);
                        window.draw(inputTextFunc);
                        window.draw(inputBoxScale);
                        window.draw(inputTextScale);
                        
                        // Создание кнопки
                        
                        window.draw(button);
                        
                        
                        window.draw(text);
                        
                        
                        draw_axis(window, width, height, true, length, scale, center_x, center_y, font);
                        draw_axis(window, width, height, false, length, scale, center_x, center_y, font);
                        draw_func(window, f, -6, 7, scale, center_x, center_y, sf::Color::Red, delay);
                        
                    }
                }
            } else {
                button.setFillColor(sf::Color::White);
                window.draw(button);
                window.draw(text);
            }
            
        }
        window.draw(inputBoxFunc);
        window.draw(inputTextFunc);
        window.draw(inputBoxScale);
        window.draw(inputTextScale);
        window.display();
    }

    return 0;
}

