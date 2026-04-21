#include <SFML/Graphics.hpp>
#include <iostream>

// ===== УЗЕЛ =====
struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

// ===== КЛАСС ДЕРЕВА =====
class BinaryTree
{
private:
    Node* root;

    // вставка
    Node* insert(Node* node, int value)
    {
        if (!node) return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        return node;
    }

    // РИСОВАНИЕ (рекурсивно)
    void drawNode(sf::RenderWindow& window, Node* node,
                  float x, float y, float offset, sf::Font& font)
    {
        if (!node) return;

        // --- круг ---
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setPosition(x, y);
        window.draw(circle);

        // --- текст ---
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->value));
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 5);
        window.draw(text);

        // --- левый ---
        if (node->left)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x + 20, y + 20)),
                sf::Vertex(sf::Vector2f(x - offset + 20, y + 100))
            };
            window.draw(line, 2, sf::Lines);

            drawNode(window, node->left, x - offset, y + 100, offset / 2, font);
        }

        // --- правый ---
        if (node->right)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x + 20, y + 20)),
                sf::Vertex(sf::Vector2f(x + offset + 20, y + 100))
            };
            window.draw(line, 2, sf::Lines);

            drawNode(window, node->right, x + offset, y + 100, offset / 2, font);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value)
    {
        root = insert(root, value);
    }

    void draw(sf::RenderWindow& window, sf::Font& font)
    {
        drawNode(window, root, 500, 50, 200, font);
    }
};

// ===== MAIN =====
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Binary Tree");

    sf::Font font;
    font.loadFromFile("arial.ttf");

    BinaryTree tree;

    // пример дерева
    tree.insert(25);
    tree.insert(10);
    tree.insert(40);
    tree.insert(5);
    tree.insert(15);
    tree.insert(30);
    tree.insert(50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        tree.draw(window, font);

        window.display();
    }

    return 0;
}
