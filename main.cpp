#include <SFML/Graphics.hpp>
#include "header.hpp"
#include <iostream>
using namespace std; 
using namespace sf;

int main() {
    mainMenuScreen();

    return 0;
}

void mainMenuScreen(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!", State::Windowed);
    
    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // background
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/back2.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    Font font("assets/BurbankBigCondensed-Black.otf");
    Text title(font, "FabulousFred!", 100);
    Text optLogIn(font, "Log in", 50);
    Text optSignUp(font, "Sign up", 50);
    
    //title
    title.setFillColor(Color::Blue);
    title.setOrigin({title.getGlobalBounds().getCenter()}); // set the origin in the middle
    title.setPosition({825/2, 200});

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
            if (event->is<sf::Event::Closed>()){
                window.close();
            } else if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close();
                }
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
            
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Enter){
                    if (options[0] == 1){ // log in
                        window.close();
                        screenLogIn();
                    }
                    if (options[1] == 1){ // sign up
                        window.close();
                        screenSignUp();
                    }
                }
            }
        }
        
        window.clear(Color::Black);
        window.draw(backgSprite);
        window.draw(title);
        window.draw(optSignUp);
        window.draw(optLogIn);
        window.display();
    }    
}