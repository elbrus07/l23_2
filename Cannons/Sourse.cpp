#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <cmath>
#include <SFML/Audio.hpp>
#include <random>


// КЛАСС ПУШКИ (сохраняем все твои комментарии)

class Cannon {
public:
    sf::CircleShape shape;
    bool isAlive;       //Жива пушка или нет
    int playerID;       //1(красный слева) или 2(синий справа)

    // Индивидуальные настройки пушки
    float angle;            // угол наклона от 0 до 90
    float velocity;         // сила выстрела от 5 до 30
    float mass;             // масса снаряда от 1.0 до 3.0

    // Конструктор
    Cannon() : isAlive(true), playerID(1), angle(45.f), velocity(15.f), mass(1.0f) {
        shape.setOrigin(20.f, 20.f); // Центр круга = его позиция (по умолчанию)
    }

    // Инициализация пушки с параметрами
    void setup(float x, float y, float radius, int pid) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius); // Центр круга = его позиция
        shape.setPosition(x, y);
        shape.setFillColor(pid == 1 ? sf::Color::Red : sf::Color::Blue);
        playerID = pid;
        isAlive = true;
        angle = 45.f;
        velocity = 15.f;
        mass = 1.0f;
    }

    // Отрисовка пушки
    void draw(sf::RenderWindow& window) const {
        if (isAlive) window.draw(shape);
    }

    // Выделение активной пушки белой обводкой
    void setSelected(bool selected) {
        if (selected && isAlive) {
            shape.setOutlineColor(sf::Color::White);
            shape.setOutlineThickness(4.f);
        }
        else {
            shape.setOutlineColor(sf::Color::Transparent);
            shape.setOutlineThickness(0.f);
        }
    }

    // Получить центр пушки 
    sf::Vector2f getCenter() const {
        return shape.getPosition();
    }

    // Установить позицию пушки
    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }
};


// КЛАСС СНАРЯДА

class Shell {
public:
    sf::CircleShape shape;
    float vx, vy;   // скорости по осям Оx и Оy
    bool isActive;  //Летит ли снаряд сейчас
    float mass;     //масса снаряда, от нее зависит размер снаряда и урон
    float explosionRadius; //радиус поражения

    Shell() : vx(0), vy(0), isActive(false), mass(1.f), explosionRadius(15.f) {
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2.f);
    }

    // Запуск снаряда из пушки
    void launch(float centerX, float centerY, float angleDeg, float velocity, float shellMass, int playerID) {
        mass = shellMass;
        explosionRadius = mass * 15.f;  // расчет радиуса поражения

        // задается размер снаряда
        float shellRadius = mass * 8.f;   // получается 8 пикселей на единицу массы
        shape.setRadius(shellRadius);
        shape.setOrigin(shellRadius, shellRadius); //центр находится по центру круга

        // расчет начальной скорости
        // перевод угла в радианы
        float angleRad = angleDeg * 3.14159f / 180.f;

        // Вычисление позиции "дула"
        float muzzleDist = 40.f;  // Расстояние от центра пушки
        // Игрок 1 стреляет вправо (+1), Игрок 2 влево (-1)
        float direction = (playerID == 1) ? 1.f : -1.f;

        // Позиция вылета по направлению прицела
        float muzzleX = centerX + cos(angleRad) * muzzleDist * direction;
        float muzzleY = centerY - sin(angleRad) * muzzleDist;
        shape.setPosition(muzzleX, muzzleY);

        // Разлагаем скорость на компоненты
        if (playerID == 1) {
            // Красные стреляют ВПРАВО
            vx = velocity * cos(angleRad);
        }
        else {
            // Синие стреляют ВЛЕВО
            vx = -velocity * cos(angleRad);
        }
        vy = -velocity * sin(angleRad);  // Минус потому что летим вверх

        isActive = true;
    }

    // Обновление физики полёта
    void update(float gravityFactor) {
        if (!isActive) return;

        // обновление позиции
        shape.move(vx, vy);

        // Применяем гравитацию (с учётом массы)
        vy += gravityFactor * mass;
    }

    // Отрисовка снаряда
    void draw(sf::RenderWindow& window) const {
        if (isActive) window.draw(shape);
    }

    // Получить центр снаряда
    sf::Vector2f getCenter() const {
        return shape.getPosition();
    }

    // Получить радиус снаряда
    float getRadius() const {
        return shape.getRadius();
    }

    // Проверка: упал ли снаряд на землю
    bool checkGroundCollision(int x, float terrainY) const {
        if (x < 0 || x >= 1200) return false;
        return shape.getPosition().y + shape.getRadius() >= terrainY;
    }

    // Проверка: вылетел ли снаряд за границы экрана
    bool checkBoundsCollision() const {
        return shape.getPosition().x > 1200.f ||
            shape.getPosition().x < -100.f ||
            shape.getPosition().y < -500.f;
    }
};


// КЛАСС ВЗРЫВА

class Explosion {
public:
    sf::CircleShape core;      // Ядро взрыва
    std::vector<sf::CircleShape> particles; // Осколки
    float lifetime;            // Время жизни (секунды)
    bool isActive;

    Explosion() : lifetime(0.f), isActive(false) {
        core.setFillColor(sf::Color(255, 165, 0));
        core.setOrigin(5.f, 5.f);
        // Создаем 8 осколков
        for (int i = 0; i < 8; ++i) {
            sf::CircleShape p(3.f);
            p.setFillColor(sf::Color::Red);
            p.setOrigin(3.f, 3.f);
            particles.push_back(p);
        }
    }

    // Запуск эффекта взрыва в точке (x, y)
    void trigger(float x, float y, float radius, sf::Sound& explosionSound) {
        core.setPosition(x, y);
        core.setRadius(radius * 0.5f);
        core.setFillColor(sf::Color(255, 200, 50, 255));

        for (auto& p : particles) {
            p.setPosition(x, y);
            p.setRadius(2.f + std::rand() % 4);
            p.setFillColor(sf::Color(255, 100, 0, 255));
        }

        lifetime = 0.5f; // Длительность полсекунды
        isActive = true;

        explosionSound.play(); // Звук
        explosionSound.setPitch(0.8f + std::rand() % 3 * 0.1f); // Немного меняем тон
    }

    // Обновление анимации взрыва
    void update(float dt) {
        if (!isActive) return;

        lifetime -= dt;
        float progress = 1.0f - (lifetime / 0.5f); // От 0 до 1

        // Расширяем ядро
        core.setRadius(core.getRadius() + 2.f);
        sf::Color coreColor = core.getFillColor();
        coreColor.a = static_cast<sf::Uint8>(255 * (1.0f - progress)); // Исчезает
        core.setFillColor(coreColor);

        // Разлетаем осколки
        for (size_t i = 0; i < particles.size(); ++i) {
            float angle = (360.f / particles.size()) * i + progress * 20;
            float dist = progress * 60.f;
            float px = core.getPosition().x + cos(angle * 3.14159f / 180.f) * dist;
            float py = core.getPosition().y + sin(angle * 3.14159f / 180.f) * dist;

            particles[i].setPosition(px, py);
            sf::Color pColor = particles[i].getFillColor();
            pColor.a = static_cast<sf::Uint8>(255 * (1.0f - progress));
            particles[i].setFillColor(pColor);
        }

        if (lifetime <= 0.f) {
            isActive = false;
        }
    }

    // Отрисовка взрыва
    void draw(sf::RenderWindow& window) const {
        if (!isActive) return;
        window.draw(core);
        for (const auto& p : particles) {
            window.draw(p);
        }
    }

    bool isFinished() const { return !isActive; }
};


// КЛАСС ЛАНДШАФТА

class Terrain {
private:
    std::vector<float> heights; // Карта высот: heights[x] = Y земли в точке X
    int width;
    sf::VertexArray terrainVA;

public:
    Terrain(int w, int baseY = 480) : width(w), terrainVA(sf::TriangleStrip, w * 2) {
        heights.resize(w);
        generate(baseY);
    }

    // Генерация случайного ландшафта
    void generate(int baseY) {
        // Базовый уровень
        for (int i = 0; i < width; ++i) heights[i] = static_cast<float>(baseY);

        // Добавляем случайные холмы и ямы
        for (int h = 0; h < 12; ++h) {
            int center = rand() % width;
            int w = 40 + rand() % 80;      // Ширина холма
            float height = (rand() % 100) - 50; // Высота (+ вверх, - вниз)

            for (int x = center - w; x <= center + w; ++x) {
                if (x >= 0 && x < width) {
                    float dist = std::abs(x - center);
                    float factor = 1.0f - (dist / static_cast<float>(w));
                    factor = factor * factor; // Сглаживание краев
                    heights[x] += height * factor;
                }
            }
        }

        // Финальное сглаживание
        for (int pass = 0; pass < 3; ++pass) {
            std::vector<float> temp = heights;
            for (int i = 1; i < width - 1; ++i) {
                temp[i] = (heights[i - 1] + heights[i] + heights[i + 1]) / 3.0f;
            }
            heights = temp;
        }

        updateVertexArray();
    }

    // Обновление массива вершин для отрисовки
    void updateVertexArray() {
        for (int i = 0; i < width; ++i) {
            terrainVA[2 * i].position = sf::Vector2f(static_cast<float>(i), heights[i]);
            terrainVA[2 * i].color = sf::Color(50, 180, 50);       // Верх травы
            terrainVA[2 * i + 1].position = sf::Vector2f(static_cast<float>(i), 600.f);
            terrainVA[2 * i + 1].color = sf::Color(20, 80, 20);    // Низ земли
        }
    }

    // Получить Y земли в точке X
    float getHeight(int x) const {
        if (x < 0) x = 0;
        if (x >= width) x = width - 1;
        return heights[x];
    }

    // Отрисовка ландшафта
    void draw(sf::RenderWindow& window) const {
        window.draw(terrainVA);
    }

    int getWidth() const { return width; }
};


// ГЕНЕРАТОР ЗВУКОВ 

sf::SoundBuffer createExplosionSound() {
    std::vector<sf::Int16> samples(44100 * 0.5); // 0.5 секунды
    for (size_t i = 0; i < samples.size(); ++i) {
        samples[i] = (std::rand() % 65536 - 32768) * (1.0f - i / (float)samples.size());
    }
    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), 1, 44100);
    return buffer;
}

// ГЛАВНАЯ ФУНКЦИЯ

int main() {
    // Создаем окно 1200x600
    sf::RenderWindow window(sf::VideoMode(1200, 600), L"Игра Пушки - SFML 2.6");
    window.setFramerateLimit(60); // Ограничение кадров

    // Звуки
    sf::SoundBuffer shootBuffer;
    if (!shootBuffer.loadFromFile("cannon_shot.wav")) {
        std::cerr << "[AUDIO] Не удалось загрузить cannon_shot.wav. Проверьте путь и формат." << std::endl;
    }
    sf::SoundBuffer explosionBuffer = createExplosionSound();
    sf::Sound shootSound(shootBuffer);
    sf::Sound explosionSound(explosionBuffer);

    // Шрифт для текстов
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    }
    else {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    // Тексты интерфейса
    sf::Text angleText, velocityText, massText;
    angleText.setFont(font); angleText.setCharacterSize(20); angleText.setFillColor(sf::Color::White);
    velocityText.setFont(font); velocityText.setCharacterSize(20); velocityText.setFillColor(sf::Color::Yellow);
    massText.setFont(font); massText.setCharacterSize(20); massText.setFillColor(sf::Color::Cyan);

    srand(time(0));  // Перемешивает генератор, чтобы числа были разными каждый запуск

    // Генерация ландшафта
    Terrain terrain(1200, 480);

    // Создание пушек
    int cannonsPerPlayer = rand() % 2 + 3;  // Дает число 3 или 4
    int TOTAL_CANNONS = cannonsPerPlayer * 2; // Умножаем на 2 (два игрока)

    // ЛИНИЯ ПРИЦЕЛА
    sf::RectangleShape aimLine;
    aimLine.setSize(sf::Vector2f(60.f, 5.f)); // Длина 60, толщина 5
    aimLine.setFillColor(sf::Color::Yellow);
    aimLine.setOrigin(0.f, 2.5f); // Вращать от начала линии, а не от центра

    // Создание снаряда
    Shell shell;

    // Визуализация снаряда (как он будет выглядеть)
    sf::CircleShape shellPreview;
    shellPreview.setFillColor(sf::Color::White);
    shellPreview.setOutlineColor(sf::Color::Black);
    shellPreview.setOutlineThickness(2.f);

    // Массив пушек
    std::vector<Cannon> cannons(TOTAL_CANNONS);

    // ПЕРЕМЕННЫЕ ИГРЫ
    int currentPlayer = 1;          // Сейчас ходит Игрок 1
    int activeCannonIndex = 0;      // индекс активной пушки в массиве
    bool canShoot = true;           // Можно ли сейчас стрелять
    bool gameOver = false;          // Закончилась ли игра
    int winnerID = 0;               // какой игрок победитель (1 или 2)
    bool isPlacementPhase = true;   // true - режим расстановки, false - бой начался
    int draggedCannonIndex = -1;    // индекс пушки которую тащим мышкой
    int selectedCannonIndex = 0;    // Какую пушку игрок выбрал

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
    float cannonRadius = 20.f;          // Радиус пушки
    float startX_P1 = 150.f;            // Игрок 1: начало отступа слева
    float startX_P2 = 750.f;            // Игрок 2: начало отступа справа
    float stepX = 130.f;                // Расстояние между пушками

    // Заполнение массива пушек
    for (int i = 0; i < TOTAL_CANNONS; i++) {
        float startX = (i < half) ? (startX_P1 + i * stepX) : (startX_P2 + (i - half) * stepX);
        float groundY_at_X = terrain.getHeight(static_cast<int>(startX));
        cannons[i].setup(startX, groundY_at_X - cannonRadius, cannonRadius, (i < half) ? 1 : 2);
    }

    findActiveCannon(); // Вызываем сразу при старте

    // Взрыв
    Explosion explosion;

    // Главный цикл игры
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Проверка на запуск боя
            if (isPlacementPhase && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    isPlacementPhase = false; // Переключение в режим боя
                    currentPlayer = 1;
                    findActiveCannon();
                    canShoot = true;
                    gameOver = false;
                    winnerID = 0;
                    shell.isActive = false;
                }
            }

            if (!isPlacementPhase && event.type == sf::Event::KeyPressed) {
                // Перезапуск игры через кнопку R
                if (event.key.code == sf::Keyboard::R && gameOver) {
                    gameOver = false; winnerID = 0; currentPlayer = 1;
                    canShoot = true; shell.isActive = false;
                    isPlacementPhase = true; // включение режима расстановки
                    for (int i = 0; i < TOTAL_CANNONS; i++) cannons[i].isAlive = true;
                    findActiveCannon();
                }

                // Управление углом
                if (event.key.code == sf::Keyboard::Left) {
                    cannons[activeCannonIndex].angle -= 1.f;
                    if (cannons[activeCannonIndex].angle < 0.f) cannons[activeCannonIndex].angle = 0.f;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    cannons[activeCannonIndex].angle += 1.f;
                    if (cannons[activeCannonIndex].angle > 90.f) cannons[activeCannonIndex].angle = 90.f;
                }

                // Управление скоростью
                if (event.key.code == sf::Keyboard::Up) {
                    cannons[activeCannonIndex].velocity += 1.f;
                    if (cannons[activeCannonIndex].velocity > 30.f) cannons[activeCannonIndex].velocity = 30.f;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    cannons[activeCannonIndex].velocity -= 1.f;
                    if (cannons[activeCannonIndex].velocity < 5.f) cannons[activeCannonIndex].velocity = 5.f;
                }

                // Управление массой снаряда
                if (event.key.code == sf::Keyboard::W) {
                    cannons[activeCannonIndex].mass += 0.25f;
                    if (cannons[activeCannonIndex].mass > 3.0f) cannons[activeCannonIndex].mass = 3.0f;
                }
                if (event.key.code == sf::Keyboard::S) {
                    cannons[activeCannonIndex].mass -= 0.25f;
                    if (cannons[activeCannonIndex].mass < 1.0f) cannons[activeCannonIndex].mass = 1.0f;
                }

                // Переключение между пушками (Q/E)
                if (!shell.isActive && canShoot && !gameOver) {
                    if (event.key.code == sf::Keyboard::Q) {
                        for (int i = selectedCannonIndex - 1; i >= 0; i--) {
                            if (cannons[i].isAlive && cannons[i].playerID == currentPlayer) {
                                selectedCannonIndex = i; break;
                            }
                        }
                    }
                    if (event.key.code == sf::Keyboard::E) {
                        for (int i = selectedCannonIndex + 1; i < TOTAL_CANNONS; i++) {
                            if (cannons[i].isAlive && cannons[i].playerID == currentPlayer) {
                                selectedCannonIndex = i; break;
                            }
                        }
                    }
                    activeCannonIndex = selectedCannonIndex;
                }

                // Запуск снаряда через пробел
                if (event.key.code == sf::Keyboard::Space && !shell.isActive && canShoot && !gameOver) {
                    float angle = cannons[activeCannonIndex].angle;
                    float velocity = cannons[activeCannonIndex].velocity;
                    float mass = cannons[activeCannonIndex].mass;

                    shell.launch(cannons[activeCannonIndex].getCenter().x,
                        cannons[activeCannonIndex].getCenter().y,
                        angle, velocity, mass,
                        cannons[activeCannonIndex].playerID);

                    shootSound.play();
                    shootSound.setVolume(100.f);
                    shootSound.setPitch(0.98f + std::rand() % 5 * 0.01f);
                    canShoot = false;
                }
            }
        }

        // Логика расстановки мышкой
        if (isPlacementPhase) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && draggedCannonIndex == -1) {
                for (int i = 0; i < TOTAL_CANNONS; i++) {
                    float cx = cannons[i].getCenter().x;
                    float cy = cannons[i].getCenter().y;
                    float dist = sqrt(pow(mousePos.x - cx, 2) + pow(mousePos.y - cy, 2));
                    if (dist < cannonRadius + 5.f) {
                        draggedCannonIndex = i; break;
                    }
                }
            }
            if (draggedCannonIndex != -1) { // Тащим пушку
                float newX = (float)mousePos.x - cannonRadius;
                //  ограничение по растановке а именно нельзя заходить дальше центра
                if (cannons[draggedCannonIndex].playerID == 1) {    // Игрок 1: только левая половина (от 50 до 590)
                    if (newX < 50.f) newX = 50.f;
                    if (newX > 590.f) newX = 590.f;
                }
                else {  // Игрок 2: только правая половина (от 610 до 1150)
                    if (newX < 610.f) newX = 610.f;
                    if (newX > 1150.f) newX = 1150.f;
                }
                float terrainY = terrain.getHeight(static_cast<int>(newX));
                cannons[draggedCannonIndex].setPosition(newX, terrainY - cannonRadius);
            }
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Отпустили кнопку мыши?
                draggedCannonIndex = -1;
            }
        }

        // Физика полёта снаряда
        if (shell.isActive) {
            shell.update(0.15f); // Гравитация

            // Проверка попадания во вражеские пушки
            for (int i = 0; i < TOTAL_CANNONS; i++) {
                if (cannons[i].isAlive && cannons[i].playerID != currentPlayer) {
                    sf::Vector2f enemyCenter = cannons[i].getCenter();
                    sf::Vector2f shellCenter = shell.getCenter();
                    float dx = shellCenter.x - enemyCenter.x;   // Считаем расстояние между снарядом и пушкой
                    float dy = shellCenter.y - enemyCenter.y;
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance < shell.explosionRadius + cannonRadius) {
                        cannons[i].isAlive = false; // Уничтожаем пушку
                        explosion.trigger(enemyCenter.x, enemyCenter.y, shell.explosionRadius, explosionSound); //создаем взрыв в центре пушки
                    }
                }
            }

            // Проверка столкновений с землёй
            int shellX = static_cast<int>(shell.getCenter().x);
            if (shellX >= 0 && shellX < 1200) {
                if (shell.checkGroundCollision(shellX, terrain.getHeight(shellX))) {
                    shell.isActive = false; // Снаряд упал
                    canShoot = true;    //разрешаем следующему игроку стрелять
                    if (!gameOver) {
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                        findActiveCannon(); // Находим новую активную пушку
                    }
                }
            }

            // Проверка выхода за границы экрана
            if (shell.checkBoundsCollision()) {
                shell.isActive = false;     // Снаряд улетел за экран
                canShoot = true;    // Разрешаем следующий ход
                if (!gameOver) {
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    findActiveCannon();
                }
            }

            // Проверка победы
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

        // Обновление анимации взрыва
        explosion.update(1.0f / 60.f);

        // ОТРИСОВКА
        window.clear(sf::Color::Black);

        terrain.draw(window); // Рисуем рельеф

        // Рисуем живые пушки
        for (int i = 0; i < TOTAL_CANNONS; i++) {
            cannons[i].setSelected(i == activeCannonIndex && !gameOver && canShoot);
            cannons[i].draw(window);
        }

        // Прицел для активной пушки
        if (activeCannonIndex >= 0 && activeCannonIndex < TOTAL_CANNONS && cannons[activeCannonIndex].isAlive) {
            aimLine.setPosition(cannons[activeCannonIndex].getCenter());
            float cannonAngle = cannons[activeCannonIndex].angle;
            if (cannons[activeCannonIndex].playerID == 1) {
                aimLine.setRotation(-cannonAngle);  // Игрок 1: вправо
            }
            else {
                aimLine.setRotation(-180.f + cannonAngle);  // Игрок 2: влево
            }
            window.draw(aimLine);
        }

        // Отрисовка снаряда
        shell.draw(window);

        // Превью снаряда
        if (activeCannonIndex >= 0 && activeCannonIndex < TOTAL_CANNONS && cannons[activeCannonIndex].isAlive) {
            sf::Vector2f cannonCenter = cannons[activeCannonIndex].getCenter();     // Позиция: чуть дальше конца прицела
            float rad = -cannons[activeCannonIndex].angle * 3.14159f / 180.f;
            float previewDist = 70.f;
            float direction = (cannons[activeCannonIndex].playerID == 1) ? 1.f : -1.f;  //направление для игрока 1 или 2
            float previewX = cannonCenter.x + cos(rad) * previewDist * direction;
            float previewY = cannonCenter.y + sin(rad) * previewDist;
            float previewRadius = cannons[activeCannonIndex].mass * 10.f;   // Размер превью зависит от массы! (коэффициент 10 пикселей на единицу массы)
            shellPreview.setRadius(previewRadius);
            shellPreview.setOrigin(previewRadius, previewRadius);
            shellPreview.setPosition(previewX, previewY);
            window.draw(shellPreview);
        }

        // Отрисовка взрыва
        explosion.draw(window);

        // Обновление текстов интерфейса
        angleText.setString(L"Угол наклона: " + std::to_wstring((int)cannons[activeCannonIndex].angle));
        angleText.setPosition(10.f, 10.f);
        velocityText.setString(L"Сила выстрела: " + std::to_wstring((int)cannons[activeCannonIndex].velocity));
        velocityText.setPosition(10.f, 40.f);
        massText.setString(L"Масса снаряда: " + std::to_wstring(cannons[activeCannonIndex].mass));
        massText.setPosition(10.f, 70.f);
        window.draw(angleText);
        window.draw(velocityText);
        window.draw(massText);

        // Отрисовка победы
        if (gameOver) {
            sf::Text winText, winText2, restartText;
            winText.setFont(font); winText.setCharacterSize(40); winText.setFillColor(sf::Color::Red);
            winText.setString("GAME OVER"); winText.setPosition(410.f, 220.f);
            winText2.setFont(font); winText2.setCharacterSize(40); winText2.setFillColor(sf::Color::Red);
            winText2.setString(L"Игрок " + std::to_wstring(winnerID) + L" Победил!"); winText2.setPosition(400.f, 270.f);
            restartText.setFont(font); restartText.setCharacterSize(20); restartText.setFillColor(sf::Color::Red);
            restartText.setString(L"Нажми R для рестарта"); restartText.setPosition(410.f, 320.f);
            window.draw(winText); window.draw(winText2); window.draw(restartText);
        }

        // Статус игры
        sf::Text statusText;
        statusText.setFont(font); statusText.setCharacterSize(20); statusText.setFillColor(sf::Color::Yellow);
        if (isPlacementPhase) {
            statusText.setString(L" Идет Расстановка: Перетащите пушки мышью. Нажмите ENTER для старта.");
            statusText.setPosition(190.f, 10.f);
        }
        else if (!gameOver) {
            statusText.setString(L" Ход Игрока " + std::to_wstring(currentPlayer));
            statusText.setPosition(400.f, 10.f);
        }
        window.draw(statusText);

        window.display();
    }

    return 0;
}
