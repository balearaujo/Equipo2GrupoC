// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include "header.hpp"
#include <iostream>
using namespace std; 
using namespace sf;

User currentUser; //declare a global variable of type struct for one user, the current user that is using the program

int main() {
    screenMainMenu();

    return 0;
}

// this screen is the main one, it has log in and sign up options 
void screenMainMenu(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!", State::Windowed);
    
    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // background
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/back4.png")) {
        cout << "Image could'nt be loaded" << endl;
    }
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    // declaration
    Font font("assets/BurbankBigCondensed-Black.otf");
    Text tTitle(font, "FABULOUS\n    FRED!", 150);
    Text tLogIn(font, "LOG IN", 60);
    Text tSignUp(font, "SIGN UP", 60);
    RectangleShape buttLI(Vector2f{370, 90});
    RectangleShape buttBorderLI(Vector2f{390, 105});
    RectangleShape buttSU(Vector2f{370, 90});
    RectangleShape buttBorderSU(Vector2f{390, 105});

    // color
    tTitle.setFillColor(Color::White);
    tLogIn.setFillColor({Color::White});
    tSignUp.setFillColor({Color::White});
    buttSU.setFillColor(Color(130,130,130)); 
    buttBorderSU.setFillColor(Color::Transparent);
    buttLI.setFillColor(Color(130,130,130)); 
    buttBorderLI.setFillColor(Color::Transparent);

    // origin
    tTitle.setOrigin({tTitle.getGlobalBounds().getCenter()}); // set the origin in the middle
    tLogIn.setOrigin({75,20}); // set the origin in the middle
    tSignUp.setOrigin({75,20}); // set the origin in the middle
    buttSU.setOrigin({(buttSU.getSize().x)/2 , (buttSU.getSize().y)/2});
    buttBorderSU.setOrigin({(buttBorderSU.getSize().x)/2 , (buttBorderSU.getSize().y)/2});
    buttLI.setOrigin({(buttLI.getSize().x)/2 , (buttLI.getSize().y)/2});
    buttBorderLI.setOrigin({(buttBorderLI.getSize().x)/2 , (buttBorderLI.getSize().y)/2});
    
    // position
    tTitle.setLineSpacing(0.8);
    tTitle.setPosition({825/2, 225});
    tLogIn.setPosition({420, 427}); 
    tSignUp.setPosition({405, 552});
    buttLI.setPosition({825/2, 445});
    buttBorderLI.setPosition({825/2, 445});
    buttSU.setPosition({825/2, 570});
    buttBorderSU.setPosition({825/2, 570});
    
    // animation variables
    bool animate = true;
    float scale = 1.f;
    float scaleSpeed = 0.05f;
    Clock clock;

    int posAux{0}; // counter to use the menu options 
    
    // main loop
    while (window.isOpen()) {
        // title animation with a clock
        float timeElapsed = clock.restart().asSeconds();
        if (animate){ // if animate is set to true, the scale of the title starts growing
            scale += scaleSpeed * timeElapsed; 
            if (scale >= 1.1f) animate = false; // if the scale hits 1.1, it turns animate to false
        } else{
            scale -= scaleSpeed * timeElapsed;  // animate false decreaases the size of the title
            if (scale <= 1.0f) animate = true; // if the scale hits 1, turns animate into true
        }
        tTitle.setScale({scale, scale}); // scale

        // events loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                window.close(); // close window
            } else if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){ // if escape is pressed, the window close
                    window.close();
                }
            }
            
            // set a range for posAux 0<=posAux>=1 when pressing up or down key
            if (posAux>0 && posAux<=1) 
                if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                    cout << posAux;
                }
            if (posAux>=0 && posAux<1){
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    cout << posAux;
                }
            }

            // simulates an options menu, it switches colors depending of the posAux value
            switch(posAux){
                case 0:
                    buttBorderLI.setFillColor(Color::Red);
                    buttLI.setFillColor(Color(253,114,114));
                    buttBorderSU.setFillColor(Color::Transparent);
                    buttSU.setFillColor(Color(130,130,130));
                    break;
                
                case 1:
                    buttBorderSU.setFillColor(Color::Red);
                    buttSU.setFillColor(Color(253,114,114));
                    buttBorderLI.setFillColor(Color::Transparent);
                    buttLI.setFillColor(Color(130,130,130));
                    break;
            }

            // menu options when pressing enter, they use posAux too
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Enter){
                    if (posAux==0){ // log in
                        window.close();
                        screenLogIn();
                    }
                    if (posAux==1){ // sign up
                        window.close();
                        screenSignUp();
                    }
                }
            }
        }
        
        // draw everything
        window.clear(Color::Black);
        window.draw(backgSprite);
        window.draw(buttBorderSU);
        window.draw(buttBorderLI);
        window.draw(buttSU);
        window.draw(buttLI);
        window.draw(tTitle);
        window.draw(tSignUp);
        window.draw(tLogIn);

        window.display();
    }    
}