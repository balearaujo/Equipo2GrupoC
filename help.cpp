// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include <iostream>
#include "header.hpp"
using namespace std;
using namespace sf;

void helpScreen(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!");

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }
    
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    // home white icon
    Texture homeWTexture;
    if (!homeWTexture.loadFromFile("assets/home-icon-white.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite homeWSprite(homeWTexture); 
    homeWSprite.setPosition({700,685});

    // home black icon
    Texture homeBTexture;
    if (!homeBTexture.loadFromFile("assets/home-icon-black.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite homeBSprite(homeBTexture); 
    homeBSprite.setPosition({700,685});


    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font

    Text title(font, "HELP", 90);
    title.setFillColor(Color::White);
    title.setPosition({325, 50});

    float x, y;

    RectangleShape rectangle;
    rectangle.setSize({712, 700});
    rectangle.setOrigin({rectangle.getSize().x/2 , rectangle.getSize().y/2});
    rectangle.setPosition({825/2, 800/2});
    rectangle.setFillColor(Color(0, 0, 0));

    RectangleShape rectangleBorder;
    rectangleBorder.setSize({722, 710});
    rectangleBorder.setOrigin({rectangleBorder.getSize().x/2 , rectangleBorder.getSize().y/2});
    rectangleBorder.setPosition({825/2, 800/2});
    rectangleBorder.setFillColor(Color::White);


    Text instructions(font);
    instructions.setCharacterSize(35);
    instructions.setFillColor(Color::White);
    x=(825-712)/2.f;
    y=(800-700)/2.f;
    instructions.setPosition({x+25, y+120});
    instructions.setString(
        " How to play faboulous fred?\n\n" "1. Memorize the color sequence. \n\n 2. Use the arrow keys to move around the board.\n\n"
    "3. Press enter to select a color.\n\n" "4. The game will end if you choose wrong.\n\n" "5. You will earn points if you get the sequence right.\n\n"
    "6. Try to score as high as you can.\n\n" "7. HAVE FUN!"
    );
    
    instructions.setOrigin({0,0});
    instructions.setPosition({x+20, y+115});

    // 0 = home icon button
    int posAux = -1;
    bool homeIconHover = false; // boolean used for a change of icon if the home button is selected

    while (window.isOpen()) {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<Event::Closed>()){
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
                screenMenu();
            }

            if (posAux==-1){
                // if home button is selected the home icon changes
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    homeIconHover = true;
                }
            }

            if (posAux==0){
                // if enter is pressed the screen returns to the menu
                if (const auto* key = event->getIf<Event::KeyPressed>()){
                    if (key->scancode == Keyboard::Scancode::Enter){
                        window.close();
                        screenMenu();
                    }
                }
                // if home button isnt selected the home icon returns to default
                if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                    homeIconHover = false;
                }
            }
        }
    
        window.clear();
        window.draw(backgSprite);
        window.draw(rectangleBorder);
        window.draw(rectangle);
        window.draw(title);
        window.draw(instructions);

        // depending in if the home icon is selected the icon changes
        if (homeIconHover){
            window.draw(homeBSprite);
        } else {
            window.draw(homeWSprite);
        }

        window.display();
    }
}