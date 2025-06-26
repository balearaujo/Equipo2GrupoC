#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "header.hpp"
using namespace std;
using namespace sf;

void screenGameOver(int score, int size){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!"); // creates the 825x800 window
    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // BACKGROUND 
    // texture store the image data 
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }


    // sprite is a image that gets drawn in the screen
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    // TITLE
    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font
    Text title(font, "GAME OVER", 100); // declare the text, its font, content and size
    title.setOrigin({170,40}); // manually set origin for positioning
    title.setPosition({755/2, 110}); 

    Text tTry(font, "NICE TRY!", 40); // declare the text, its font, content and size
    tTry.setOrigin({20,20}); // manually set origin for positioning
    tTry.setPosition({735/2, 200}); 


    Text tScore(font, "SCORE: "+to_string(score), 85);
    tScore.setFillColor(Color::White);
    tScore.setOrigin({100, 35});
    tScore.setPosition({765/2, 325});
    
    // YES BUTTON
    RectangleShape btnTA;
    btnTA.setSize(Vector2f(500, 100));
    btnTA.setFillColor(Color(253,114,114));
    btnTA.setOrigin({(btnTA.getSize().x)/2 , (btnTA.getSize().y)/2});
    btnTA.setPosition({825/2, 470}); // x,y

    RectangleShape btnTABorder;
    btnTABorder.setSize(Vector2f(510,110));
    btnTABorder.setFillColor(Color::Red);
    btnTABorder.setOrigin({(btnTABorder.getSize().x)/2 , (btnTABorder.getSize().y)/2});
    btnTABorder.setPosition({825/2, 470}); // x,y

    Text tTA(font, "BACK TO THE MENU", 70);
    tTA.setFillColor(Color::White);
    tTA.setOrigin({75, 20});
    tTA.setPosition({265, 445});

    // NO BUTTON
    RectangleShape btnMenu;
    btnMenu.setSize(Vector2f(500, 100));
    btnMenu.setFillColor(Color(253,114,114));
    btnMenu.setOrigin({(btnMenu.getSize().x)/2 , (btnMenu.getSize().y)/2});
    btnMenu.setPosition({825/2, 620}); // x,y

    RectangleShape btnMenuBorder;
    btnMenuBorder.setSize(Vector2f(510, 110));
    btnMenuBorder.setFillColor(Color::Red);
    btnMenuBorder.setOrigin({(btnMenuBorder.getSize().x)/2 , (btnMenuBorder.getSize().y)/2});
    btnMenuBorder.setPosition({825/2, 620}); // x,y

    Text tMenu(font, "TRY AGAIN", 70);
    tMenu.setFillColor(Color::White);
    tMenu.setOrigin({75, 20});
    tMenu.setPosition({355, 595});

    // pause menu
    RectangleShape bgMenu(Vector2f{650 , 700});
    bgMenu.setFillColor(Color(20,20,40));
    bgMenu.setOrigin({bgMenu.getSize().x/2, bgMenu.getSize().y/2});
    bgMenu.setPosition({825/2, 800/2});

    RectangleShape bgMenuBorder(Vector2f{660 , 710});
    bgMenuBorder.setFillColor(Color::White);
    bgMenuBorder.setOrigin({bgMenuBorder.getSize().x/2, bgMenuBorder.getSize().y/2});
    bgMenuBorder.setPosition({825/2, 800/2});
    int posAux{0};
        // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();
            // if scape is pressed the screen returns to the main menu
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){ 
                    window.close();
                    screenMenu();
                }
            }

            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Enter){
                    sleep(milliseconds(150)); 
                    switch(posAux){ 
                        case 0:
                            window.close();
                            screenMenu();
                            break;
                        
                        case 1:
                            window.close();
                            screenGame(0, size, 0, 0, false);
                            break;
                    }
                }
            }

        }
        
        // if key down is pressed and its not the last button, move selection to the next button
        if (posAux>= 0 && posAux<1){
            if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                posAux++;
            }
        }

        // if key up is pressed and its not the first button, move selection to the prev button
        if (posAux> 0 && posAux<=1){
            if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                posAux--;
            }
        }

        switch(posAux){ // change colors depending on the position
            case 0:
                btnTA.setFillColor(Color(253,114,114));
                btnTABorder.setFillColor(Color::Red);
                btnMenu.setFillColor(Color(130,130,130));
                btnMenuBorder.setFillColor(Color::Transparent);
                break;

            case 1:
                btnMenu.setFillColor(Color(253,114,114));
                btnMenuBorder.setFillColor(Color::Red);
                btnTA.setFillColor(Color(130,130,130));
                btnTABorder.setFillColor(Color::Transparent);
                break;
        }
        
        window.clear(Color::Black); // clear the window to draw the next frame
        window.draw(backgSprite);
        window.draw(bgMenuBorder);
        window.draw(bgMenu);
        window.draw(btnTABorder);
        window.draw(btnTA);
        window.draw(btnMenuBorder);
        window.draw(btnMenu);
        window.draw(tMenu);
        window.draw(tTry);
        window.draw(title);
        window.draw(tTA);
        window.draw(tScore);

        // show what was drawn
        window.display();
    }
}

