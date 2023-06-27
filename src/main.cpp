#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "My Window", sf::Style::Fullscreen);
    window.setFramerateLimit(50);
    sf::CircleShape shape(50, 6);
    shape.setOrigin(50, 50);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::White);
    shape.setPosition(500, 500);

    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        shape.rotate(5);
        window.draw(shape);
        window.display();
    }
}

// g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system                                 ─╯
