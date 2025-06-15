#include <SFML/Graphics.hpp>
#include "header.hpp"
using namespace std; 
using namespace sf;

int main() {
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!", State::Windowed);
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    Font font("assets/ARIAL.TTF");
    Text title(font, "Fabulous Fred!", 100);
    Text optLogIn(font, "Log in", 50);
    Text optSignUp(font, "Sign up", 50);
    //title
    title.setFillColor(Color::Blue);
    title.setOrigin({150,40}); // set the origin in the middle
    title.setPosition({250, 150});

    //login
    optLogIn.setFillColor({Color::White});
    optLogIn.setOrigin({75,20}); // set the origin in the middle
    optLogIn.setPosition({400, 400}); 
    
    //signup
    optSignUp.setFillColor({Color::White});
    optSignUp.setOrigin({75,20}); // set the origin in the middle
    optSignUp.setPosition({400, 500});

    int options[2] = {1,0};
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                options[0] = 1;
                options[1] = 0;
                optSignUp.setFillColor({Color::White});
                optLogIn.setFillColor({Color::Blue});
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                options[0] = 0;
                options[1] = 1;
                optSignUp.setFillColor({Color::Blue});
                optLogIn.setFillColor({Color::White});
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                if (options[0] == 1){ // log in
                    window.setVisible(false);
                    screenLogIn();
                    window.setVisible(true);
                }

                if (options[1] == 1){ // sign up
                    window.setVisible(false);
                    screenSignUp();
                    window.setVisible(true);
                }
            }
        }
        
        window.clear(Color::Black);
        window.draw(title);
        window.draw(optSignUp);
        window.draw(optLogIn);
        window.display();
    }
    
    return 0;
}