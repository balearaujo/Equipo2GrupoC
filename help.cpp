#include <SFML/Graphics.hpp>
#include <iostream>
#include "header.hpp"
using namespace std;
using namespace sf;

void helpScreen(){
    RenderWindow window(VideoMode({825, 800}), "Help");
    
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }
    
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font

    Text title(font, "HELP", 90);
    title.setFillColor(Color::White);
    title.setPosition({325, 50});

    float x, y;

    RectangleShape rectangle;
    rectangle.setSize({712, 700});
    x=(825-712)/2.f;
    y=(800-700)/2.f;
    rectangle.setPosition({x, y});
    rectangle.setFillColor(Color(0, 0, 0, 190));

    Text instructions(font);
    instructions.setCharacterSize(35);
    instructions.setFillColor(Color::White);
    instructions.setPosition({x+25, y+100});
    instructions.setString(
        " How to play faboulous fred?\n\n" "1. Memorize the color sequence. \n\n 2. Use the arrow keys to move around the board.\n\n"
    "3. Press enter to select a color.\n\n" "4. The game will end if you choose wrong.\n\n" "5. You will earn points if you get the sequence right.\n\n"
    "6. Try to score as high as you can.\n\n" "7. HAVE FUN!"
    );
    
    instructions.setOrigin({0,0});
    instructions.setPosition({x+20, y+115});
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
        }
    
        window.clear();
        window.draw(backgSprite);
        window.draw(rectangle);
        window.draw(title);
        window.draw(instructions);
        window.display();
    }
}