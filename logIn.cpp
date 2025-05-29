#include <SFML/Graphics.hpp>
#include "header.hpp"
using namespace sf;

void screenLogIn(){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!");
    window.setTitle("Log in");
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {   
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }
        }   
        
        window.clear();
        window.display();
    }
}