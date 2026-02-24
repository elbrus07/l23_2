#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;

void draw_scale(sf::RenderWindow &window, int width, int height, int isVertical, int scale, int center_x, int center_y, int length){
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
        
        /*
        sf::Text text(font);
        text.setString("0");
        text.setFont(sf::Font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setPosition(center_x + 12, center_y + 12);
        window.draw(text);
        */
        for(int i=0; i < n; i++) { 
            
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x + i * scale, center_y - 5);
            line[0].color = sf::Color::Red;
            line[1].position = sf::Vector2f(center_x + i * scale, center_y + 5);
            line[1].color = sf::Color::Red;
            window.draw(line);
            /*
            if (i != 0) {
                
                sf::Text text;
                text.setString(to_string(i));
                text.setPosition(center_x + i * scale, center_y + 12);
                window.draw(text);
            }
            */
            
        }
        for (int i=0; i < m; i++) {
            
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x - i * scale, center_y - 5); 
            line[0].color = sf::Color::Red;
            line[1].position = sf::Vector2f(center_x - i * scale, center_y + 5);
            line[1].color = sf::Color::Red;
            window.draw(line);
            /*
            if (i != 0) {
                sf::Text text;
                text.setString(to_string(i*-1));
                text.setPosition(center_x - i * scale, center_y + 12);
                window.draw(text);
                
            }
            */
        }
    } else {  // отсечки на вертикальной оси
        int y_shift = (height - length) / 2;
        int start = center_y - y_shift;
        int n = (length - start) / scale;  // количество отсечек на отрицательной части оси y
        int m = (start) / scale;  // количество отсечек на  положительной части оси y
        for (int i=0; i < n; i++) {
            
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x + 5, center_y + i * scale); 
            line[0].color = sf::Color::Red;
            line[1].position = sf::Vector2f(center_x - 5, center_y + i * scale);
            line[1].color = sf::Color::Red;
            window.draw(line);
        }   
        for (int i=0; i < m; i++) {
    
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(center_x + 5, center_y - i * scale); 
            line[0].color = sf::Color::Red;
            line[1].position = sf::Vector2f(center_x - 5, center_y - i * scale);
            line[1].color = sf::Color::Red;
            window.draw(line);
        }    
    }
}

void draw_axis(sf::RenderWindow &window, int width, int height, bool vertical, int length, int scale, int center_x, int center_y) {
    if (vertical){
        int y_shift = (width - length) / 2;
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(center_x, y_shift); 
        line[0].color = sf::Color::Red;
        line[1].position = sf::Vector2f(center_x, y_shift + length); 
        line[1].color = sf::Color::Red;
        window.draw(line);
        draw_scale(window, 800, 800, 1, scale, center_x, center_y, length);
    } else {
        int x_shift = (width - length) / 2;
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x_shift, center_y); 
        line[0].color = sf::Color::Red;
        line[1].position = sf::Vector2f(x_shift + length, center_y);
        line[1].color = sf::Color::Red;
        window.draw(line);
        draw_scale(window, 800, 800, 0, scale, center_x, center_y, length);
    }
}

double f(double x){
    //Функция

    return cos(x);
}

void draw_func(sf::RenderWindow &window, double (*func)(double), int a, int b, int scale, int center_x, int center_y){
    
    int length = b - a;  // длина отрезка
    double h = 0.1;  // шаг для рисования графика функции
    int n = (length / h);
    for (int i=0; i < n-1; i++) {
        double x0 = (a + i * h) * scale;
        double y0 = func(a + i * h) * scale;
        double x1 = (a + (i + 1) * h) * scale;
        double y1 = func(a + (i + 1) * h) * scale;
        
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(center_x + x0, center_y - y0); 
        line[0].color = sf::Color::Blue;
        line[1].position = sf::Vector2f(center_x + x1, center_y - y1);
        line[1].color = sf::Color::Blue;
        window.draw(line);
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

        window.clear(sf::Color::White);
        
        draw_axis(window, 800, 800, true, 500, 50, 400, 400);
        draw_axis(window, 800, 800, false, 500, 50, 400, 400);
        draw_func(window, f, -4, 4, 100, 400, 400);
        window.display();
    }

    return 0;
}

