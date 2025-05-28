#include <SFML/Graphics.hpp>
#include "header.hpp"
using namespace sf; 

int main() {
    RenderWindow window(sf::VideoMode({1920, 1080}), "Selecciona pantalla");
    Font font("ARIAL.TTF");
    Text titulo(font, "hola", 30);
    titulo.setFillColor(Color::Red);

    while (window.isOpen()) {
        bool open = false;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // test, open screen1 windoww and close main window
        if (Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            window.setVisible(false);
            screen1(); // Asegúrate de que esta función esté definida
            window.setVisible(true);
        }
        
        // test, open screen2 windoww and close main window
        if (Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            window.setVisible(false);
            screen2(); 
            window.setVisible(true);
        }
        
        window.clear(sf::Color::Black);
        window.draw(titulo);
        window.display();
    }
    
    return 0;
}