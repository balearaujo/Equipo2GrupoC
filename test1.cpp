#include <SFML/Graphics.hpp>
#include "header.hpp"
using namespace sf;

void screen1(){
    RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");
    window.setTitle("hola");
    RectangleShape rectangle({300.f, 300.f});
    rectangle.setFillColor(sf::Color::Cyan);
    rectangle.setPosition({200.f, 100.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {   
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        window.clear();
        window.draw(rectangle);
        window.display();
    }


}