
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>  
#include <ctime> 
#include <vector>


//Структура пушки
struct Cannon
{
    sf::CircleShape shape;
    bool isAlive;       //Жива пушка или нет
    int playerID;       //1(красный слева) или 2(синий справа) 
};

//Структура снаряда
struct Shell {
    sf::CircleShape shape;
    float vx, vy;   // скорости по осям Оx и Оy
    bool isActive;  //Летит ли снаряд сейчас
    float mass;     //масса снаряда, от нее зависит размер снаряда и урон
    float explosionRadius; //радиус поражения
};


int main() {
    // Создаем окно 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), L"Игра Пушки - SFML 2.6");

    window.setFramerateLimit(60);//Ограничение кадров

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }
    else {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    //Тексты
    sf::Text angleText;

    angleText.setFont(font);
    angleText.setCharacterSize(20);
    angleText.setFillColor(sf::Color::White);
    
    //Скорость
    sf::Text velocityText;
    velocityText.setFont(font);
    velocityText.setCharacterSize(20);
    velocityText.setFillColor(sf::Color::Yellow);

    //Масса
    sf::Text massText;
    massText.setFont(font);
    massText.setCharacterSize(20);
    massText.setFillColor(sf::Color::Cyan);

    srand(time(0));  // Перемешивает генератор, чтобы числа были разными каждый запуск


    //Создание пушек
    int cannonsPerPlayer = rand() % 2 + 3;  // Дает число 3 или 4
    int TOTAL_CANNONS = cannonsPerPlayer * 2; // Умножаем на 2 (два игрока)

    // ЛИНИЯ ПРИЦЕЛА 
    sf::RectangleShape aimLine;
    aimLine.setSize(sf::Vector2f(60.f, 5.f)); // Длина 60, толщина 5
    aimLine.setFillColor(sf::Color::Yellow);
    aimLine.setOrigin(0.f, 2.5f); // Вращать от начала линии, а не от центра

    //создание снаряда
    Shell shell;
    shell.shape.setFillColor(sf::Color::White);
    shell.shape.setOutlineColor(sf::Color::Black);
    shell.shape.setOutlineThickness(2.f);
    shell.isActive = false; // в начале снаряд не летит
    shell.mass = 1.f;   //начальная масса

    // Визуализация снаряда(как он будет выглядить)
    sf::CircleShape shellPreview;
    shellPreview.setFillColor(sf::Color::White);
    shellPreview.setOutlineColor(sf::Color::Black);
    shellPreview.setOutlineThickness(2.f);

    std::vector<Cannon> cannons(TOTAL_CANNONS);

    //ПЕРЕМЕННЫЕ ИГРЫ 
    int currentPlayer = 1;          // Сейчас ходит Игрок 1
    int activeCannonIndex = 0;      //индекс активной пушки в массиве
    float currentAngle = 45.f;      // Начальный угол (в градусах)
    float currentVelocity = 15.f;   //начальная скорость (от 10 до 100)
    float currentMass = 1.0f;       //масса снаряда (от 1.0 до 3.0)

    bool canShoot = true;       // Можно ли сейчас стрелять 
    bool gameOver = false;      // Закончилась ли игра
    int winnerID = 0;           // какой игрок победител (1 или 2)

    int selectedCannonIndex = 0;  // Какую пушку игрок выбрал
    

    // Функция поиска первой живой пушки игрока
    auto findActiveCannon = [&]() {
        for (int i = 0; i < TOTAL_CANNONS; i++) {
            if (cannons[i].isAlive && cannons[i].playerID == currentPlayer) {
                activeCannonIndex = i;
                selectedCannonIndex = i;
                return;
            }
        }
    };


    int half = TOTAL_CANNONS / 2;       // Половина (для разделения на команды)

    float groundY = 500.f;          // Где начинается земля (верхний край)
    float cannonRadius = 20.f;      // Радиус пушки
    float cannonY = groundY - cannonRadius;
    float startX_P1 = 80.f;   // Игрок 1: начало отступа слева
    float startX_P2 = 500.f;  // Игрок 2: начало отступа справа
    float stepX = 70.f;       // Расстояние между пушками



    //заполнение масива
    for (int i = 0; i < TOTAL_CANNONS; i++) {
        cannons[i].shape.setRadius(cannonRadius);
        cannons[i].isAlive = true;  //все пушки в начале живы


        if (i < half) {
            // первый игрок
            cannons[i].playerID = 1;
            cannons[i].shape.setFillColor(sf::Color::Red);
            // Позиция: от 50 до 250 по X
            cannons[i].shape.setPosition(startX_P1 + i * stepX, cannonY);
        }
        else {
            //второй игрок
            cannons[i].playerID = 2;
            cannons[i].shape.setFillColor(sf::Color::Blue);
            // Позиция: от 550 до 750 по X (сдвиг вправо)
            cannons[i].shape.setPosition(startX_P2 + (i - half) * stepX, cannonY);
        }


    }
    findActiveCannon(); // Вызываем сразу при старте
    std::cout << "Okno sozdano! Nashinaem igru..." << std::endl;

    //настройка земли
    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(800.f, 100.f)); //ширина 800, высота 100
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0.f, 500.f);



    // Главный цикл игры
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {

                //Управление углом
                // Стрелка ВЛЕВО - уменьшить угол
                if (event.key.code == sf::Keyboard::Left) {
                    currentAngle -= 2.f;
                }
                // Стрелка ВПРАВО - увеличить угол
                if (event.key.code == sf::Keyboard::Right) {
                    currentAngle += 2.f;
                }
                // Ограничим угол от 0 до 90 градусов
                if (currentAngle < 0.f) currentAngle = 0.f;
                if (currentAngle > 90.f) currentAngle = 90.f;



                // управление Скоростью
                if (event.key.code == sf::Keyboard::Up) {
                    currentVelocity += 1.f;  // Увеличить силу
                }
                if (event.key.code == sf::Keyboard::Down) {
                    currentVelocity -= 1.f;  // Уменьшить силу
                }
                // Ограничения скорости (чтобы не улетал в космос или не падал)
                if (currentVelocity < 5.f) {
                    currentVelocity = 5.f;
                }
                if (currentVelocity > 30.f) {
                    currentVelocity = 30.f;
                }


                //управление массой снаряда
                // Нажатие W  эьо увеличить массу
                if (event.key.code == sf::Keyboard::W) {
                    currentMass += 0.25f;
                }
                // Нажатие S  это уменьшить массу
                if (event.key.code == sf::Keyboard::S) {
                    currentMass -= 0.25f;
                }
                // Ограничения массы (от 1.0 до 3.0)
                if (currentMass < 1.0f) currentMass = 1.0f;
                if (currentMass > 3.0f) currentMass = 3.0f;



                // Только если снаряд не летит и игра не закончена
                if (!shell.isActive && canShoot && !gameOver) {

                    // Q - предыдущая пушка
                    if (event.key.code == sf::Keyboard::Q) {
                        // Ищем предыдущую живую пушку текущего игрока
                        for (int i = selectedCannonIndex - 1; i >= 0; i--) {
                            if (cannons[i].isAlive && cannons[i].playerID == currentPlayer) {
                                selectedCannonIndex = i;
                                break;
                            }
                        }
                    }

                    // E - следующая пушка
                    if (event.key.code == sf::Keyboard::E) {
                        // Ищем следующую живую пушку текущего игрока
                        for (int i = selectedCannonIndex + 1; i < TOTAL_CANNONS; i++) {
                            if (cannons[i].isAlive && cannons[i].playerID == currentPlayer) {
                                selectedCannonIndex = i;
                                break;
                            }
                        }
                    }

                    // Обновляем активную пушку
                    activeCannonIndex = selectedCannonIndex;
                }



                //запуск снаряда через пробел
                if (event.key.code == sf::Keyboard::Space && !shell.isActive && canShoot && !gameOver){
                    shell.mass = currentMass; //сохранеие массы
                    shell.explosionRadius = shell.mass * 15.f;  // расчет радиуса поражения

                    //задается размер снаряда
                    float shellRadius = shell.mass * 8.f;   // получается 8 пикселей на единицу массы
                    shell.shape.setRadius(shellRadius);
                    shell.shape.setOrigin(shellRadius, shellRadius);//центр находится по центру круга


                    //начальная позиция это центр активной пушки
                    sf::Vector2f cannonPos = cannons[activeCannonIndex].shape.getPosition();
                    float cannonCenterX = cannonPos.x + cannonRadius;
                    float cannonCenterY = cannonPos.y + cannonRadius;
                    

                    //расчет начальной скорости
                    //перевод угла в радианы
                    float angleRad = currentAngle * 3.14159f / 180.f;

                    // Вычисление позиции "дула" 
                    float muzzleDist = 25.f;  // Расстояние от центра пушки 
                    // Игрок 1 стреляет вправо (+1), Игрок 2 влево (-1)
                    float direction = (cannons[activeCannonIndex].playerID == 1) ? 1.f : -1.f;

                    // Позиция вылета по направлению прицела
                    float muzzleX = cannonCenterX + cos(angleRad) * muzzleDist * direction;
                    float muzzleY = cannonCenterY - sin(angleRad) * muzzleDist;  

                    shell.shape.setPosition(muzzleX, muzzleY);

                    // Разлагаем скорость на компоненты
                    if (cannons[activeCannonIndex].playerID == 1) {
                        // Красные стреляют ВПРАВО
                        shell.vx = currentVelocity * cos(angleRad);
                    }
                    else {
                        //Синие стреляют ВЛЕВО 
                        shell.vx = -currentVelocity * cos(angleRad);
                    }
                    shell.vy = -currentVelocity * sin(angleRad);  // Минус потому что летим вверх

                    shell.isActive = true; //запуск
                    canShoot = false; //запрещает стрелять пока снаряд летит
                }
            }

        }
        // Физика полета 
        if (shell.isActive) {
            // обновление позиции
            shell.shape.move(shell.vx, shell.vy);

            // Применяем гравитацию 
            shell.vy += 0.15f * shell.mass; ;  // Сила гравитации 


            //Проверка попадания во вражеские пушки
            for (int i = 0; i < TOTAL_CANNONS; i++) {
                // Проверяем только вражеские живые пушки
                if (cannons[i].isAlive && cannons[i].playerID != currentPlayer) {

                    // Получаем центр вражеской пушки
                    sf::Vector2f enemyPos = cannons[i].shape.getPosition();
                    float enemyCenterX = enemyPos.x + cannonRadius;
                    float enemyCenterY = enemyPos.y + cannonRadius;

                    // Получаем центр снаряда
                    sf::Vector2f shellPos = shell.shape.getPosition();

                    // Считаем расстояние между снарядом и пушкой
                    float dx = shellPos.x - enemyCenterX;
                    float dy = shellPos.y - enemyCenterY;
                    float distance = sqrt(dx * dx + dy * dy);

                    //  расстояние меньше радиуса взрыва?
                    if (distance < shell.explosionRadius + cannonRadius) {
                        cannons[i].isAlive = false;  // Уничтожаем пушку
                        std::cout << "Popadanie! Vrag unichtozhen!" << std::endl;
                    }
                }
            }




            //  Проверка столкновений с землёй (Y >= 500)
            if (shell.shape.getPosition().y + shell.shape.getRadius() >= groundY) {
                shell.isActive = false;  // Снаряд упал
                canShoot = true; //разрешаем следующему игроку стрелять
                std::cout << "Snaaryd upal" << std::endl;
                
                //  СМЕНА ХОДА 
                if (!gameOver) {
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;  // Переключаем 1 на 2
                    findActiveCannon();  // Находим новую активную пушку
                    std::cout << "Hod igroka: " << currentPlayer << std::endl;
                }
            }

            //  Проверка выхода за границы экрана 
            if (shell.shape.getPosition().x > 900.f || shell.shape.getPosition().x < -100.f ||
                shell.shape.getPosition().y < -100.f) {
                shell.isActive = false;  // Снаряд улетел за экран
                canShoot = true;  // Разрешаем следующий ход

                if (!gameOver) {
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    findActiveCannon();
                }
            }

            // ПРОВЕРКА ПОБЕДЫ 
            int enemyAlive = 0;
            for (int i = 0; i < TOTAL_CANNONS; i++) {
                if (cannons[i].isAlive && cannons[i].playerID != currentPlayer) {
                    enemyAlive++;
                }
            }
            if (enemyAlive == 0 && !gameOver) {
                gameOver = true;
                winnerID = currentPlayer;
              
            }

        }

        window.clear(sf::Color::Black); // Очистка экрана
        window.draw(ground);            // Рисуем землю

        // Рисуем живые пушки
        for (int i = 0; i < TOTAL_CANNONS; i++) {
            if (cannons[i].isAlive) {
                if (i == activeCannonIndex && !gameOver && canShoot) {
                    cannons[i].shape.setOutlineColor(sf::Color::White);
                    cannons[i].shape.setOutlineThickness(4.f);
                }
                else {
                    cannons[i].shape.setOutlineColor(sf::Color::Transparent);
                    cannons[i].shape.setOutlineThickness(0.f);
                }
                window.draw(cannons[i].shape);
            }
        }

        // Обновляем позицию и поворот прицела для активной пушки 
        if (activeCannonIndex >= 0 && activeCannonIndex < TOTAL_CANNONS && cannons[activeCannonIndex].isAlive) {
            // Вычисляем центр круга (левая верхняя точка + радиус)
            sf::Vector2f cannonPos = cannons[activeCannonIndex].shape.getPosition();
            sf::Vector2f cannonCenter(cannonPos.x + cannonRadius, cannonPos.y + cannonRadius);

            aimLine.setPosition(cannonCenter);  // Устанавливаем прицел в центр пушки


           
            if (cannons[activeCannonIndex].playerID == 1) {
                aimLine.setRotation(-currentAngle);        // Игрок 1: вправо
            }
            else {
                aimLine.setRotation(-180.f + currentAngle); // Игрок 2: влево
            }

            window.draw(aimLine); // Рисуем прицел поверх пушек
        }

        // ОТРИСОВКА СНАРЯДА 
        if (shell.isActive) {
            window.draw(shell.shape);
        }

        if (activeCannonIndex >= 0 && activeCannonIndex < TOTAL_CANNONS && cannons[activeCannonIndex].isAlive) {
            // Позиция: чуть дальше конца прицела
            sf::Vector2f cannonCenter = cannons[activeCannonIndex].shape.getPosition();
            cannonCenter.x += cannonRadius;
            cannonCenter.y += cannonRadius;

            // Вычисляем точку для превью (по направлению прицела)
            float rad = -currentAngle * 3.14159f / 180.f;
            float previewDist = 70.f; // Дистанция от центра пушки

            float direction = (cannons[activeCannonIndex].playerID == 1) ? 1.f : -1.f; //направление для игрока 1 или 2

            float previewX = cannonCenter.x + cos(rad) * previewDist * direction;
            float previewY = cannonCenter.y + sin(rad) * previewDist;

            // Размер превью зависит от массы! (коэффициент 10 пикселей на единицу массы)
            float previewRadius = currentMass * 10.f;

            shellPreview.setRadius(previewRadius);
            shellPreview.setOrigin(previewRadius, previewRadius); // Центр в центре круга
            shellPreview.setPosition(previewX, previewY);

            window.draw(shellPreview); // Рисуем превью
        }

        // Обновление текста (внутри цикла)
        angleText.setString("Angle: " + std::to_string((int)currentAngle));
        angleText.setPosition(10.f, 10.f); // Угол экрана
        window.draw(angleText); // Нарисовать текст


        //Обновление текста скорости
        velocityText.setString("Power: " + std::to_string((int)currentVelocity));
        velocityText.setPosition(10.f, 40.f);  // Чуть ниже угла (по Y)
        window.draw(velocityText);             // Нарисовать текст

        //Обновление текста МАССЫ
        massText.setString("Mass: " + std::to_string(currentMass));
        massText.setPosition(10.f, 70.f);  // Ещё ниже (по Y)
        window.draw(massText);             // Нарисовать текст

        //  ОТРИСОВКА ПОБЕДЫ
        if (gameOver) {
            sf::Text winText;
            winText.setFont(font);
            winText.setCharacterSize(40);
            winText.setFillColor(sf::Color::Red);
            winText.setString("GAME OVER" );
            winText.setPosition(210.f, 220.f);  // По центру экрана
            window.draw(winText);

            sf::Text winText2;
            winText2.setFont(font);
            winText2.setCharacterSize(40);
            winText2.setFillColor(sf::Color::Red);
            winText2.setString("Igrok " + std::to_string(winnerID) + " POBEDIL!");
            winText2.setPosition(200.f, 270.f);  // По центру экрана
            window.draw(winText2);
        }


        window.display();               // Показываем кадр
    }

    return 0;
}
