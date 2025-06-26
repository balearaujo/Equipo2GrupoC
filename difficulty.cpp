// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include <iostream>
#include "header.hpp"
using namespace std;
using namespace sf;

/*Displays a window for the player to choose the game difficulty (EASY or HARD)
or return to the main menu. Allows navigation with arrow keys and selection
with Enter. Updates button highlights based on selection*/
void screenSelectDifficulty(){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!"); // creates the 825x800 window

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    

    // BACKGROUND 
    // load background texture
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }
     // Create a sprite from the loaded texture
    Sprite backgSprite(backgTexture);
    // Calculate scale factors to make the background fit the entire window
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    // Apply the calculated scale to the sprite
    backgSprite.setScale({scaleX, scaleY});


    // home white icon
    // load texture
    Texture homeWTexture;
    if (!homeWTexture.loadFromFile("assets/home-icon-white.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    // Create a sprite from the loaded texture
    Sprite homeWSprite(homeWTexture); 
    homeWSprite.setPosition({740,725});

    // home black icon
    // load texture
    Texture homeBTexture;
    if (!homeBTexture.loadFromFile("assets/home-icon-black.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    // Create a sprite from the loaded texture
    Sprite homeBSprite(homeBTexture); 
    homeBSprite.setPosition({740,725});

    // TITLE
    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font
    Text title(font, "SELECT DIFFICULTY", 90); // declare the text, its font, content and size
    title.setOrigin({150,40}); // manually set origin for positioning
    title.setPosition({275, 150}); 

    // EASY BUTTON
    RectangleShape easyBtn;
    easyBtn.setSize(Vector2f(600,100));
    easyBtn.setFillColor(Color(253,114,114));
    easyBtn.setOrigin({(easyBtn.getSize().x)/2 , (easyBtn.getSize().y)/2});
    easyBtn.setPosition({412, 330}); // x,y

    RectangleShape easyBtnBorder;
    easyBtnBorder.setSize(Vector2f(620,115));
    easyBtnBorder.setFillColor(Color::Red);
    easyBtnBorder.setOrigin({(easyBtnBorder.getSize().x)/2 , (easyBtnBorder.getSize().y)/2});
    easyBtnBorder.setPosition({412, 330}); // x,y

    Text tEasyBtn(font, "EASY", 80);
    tEasyBtn.setFillColor(Color::White);
    tEasyBtn.setOrigin({75, 20});
    tEasyBtn.setPosition({405, 300});

    // HARD BUTTON
    RectangleShape hardBtn;
    hardBtn.setSize(Vector2f(600,100));
    hardBtn.setFillColor(Color(130,130,130));
    hardBtn.setOrigin({(hardBtn.getSize().x)/2 , (hardBtn.getSize().y)/2});
    hardBtn.setPosition({412, 480}); // x,y

    RectangleShape hardBtnBorder;
    hardBtnBorder.setSize(Vector2f(620,115));
    hardBtnBorder.setFillColor(Color::Black);
    hardBtnBorder.setOrigin({(hardBtnBorder.getSize().x)/2 , (hardBtnBorder.getSize().y)/2});
    hardBtnBorder.setPosition({412, 480}); // x,y

    Text tHardBtn(font, "HARD", 80);
    tHardBtn.setFillColor(Color::White);
    tHardBtn.setOrigin({75, 20});
    tHardBtn.setPosition({405, 450});

    // 0 = easy, 1 = hard, 2 = home button
    int posAux = 0;
    bool homeIconHover = false; // boolean used for a change of icon if the home button is selected

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();
            if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }

            // if key down is pressed and its not the last button, move selection to the next button
            if (posAux>= 0 && posAux<2){
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                }
            }

            // if key up is pressed and its not the first button, move selection to the prev button
            if (posAux> 0 && posAux<=2){
                if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                }
            }

            switch(posAux){ // change colors depending on the position
                case 0:
                    // EASY button selected
                    easyBtn.setFillColor(Color(253,114,114));
                    easyBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    hardBtn.setFillColor(Color(130,130,130));
                    hardBtnBorder.setFillColor(Color::Black);
                    homeIconHover = false;
                    break;
                case 1:
                    // HARD button selected
                    hardBtn.setFillColor(Color(253,114,114));
                    hardBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    easyBtn.setFillColor(Color(130,130,130));
                    easyBtnBorder.setFillColor(Color::Black);
                    homeIconHover = false;
                    break;

                case 2:
                    // rest stay default
                    hardBtn.setFillColor(Color(130,130,130));
                    hardBtnBorder.setFillColor(Color::Black);
                    easyBtn.setFillColor(Color(130,130,130));
                    easyBtnBorder.setFillColor(Color::Black);

                    // HOME button selected
                    homeIconHover = true;
                    break;
            } 
            
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Enter){
                    // Action based on the currently selected button (posAux)
                    if (posAux==0){
                        window.close();
                        screenGame(0, 4, 0, 0, false);
                    } 
                    else if (posAux==1){
                        window.close();
                        screenGame(0, 9, 0, 0, false);
                    } 
                    else{
                        window.close();
                        screenMenu();
                    }
                }
            }
        }

        window.clear(Color::Black); // clear the window to draw the next frame
        window.draw(backgSprite);

        // draw stuff here
        window.draw(title);

        window.draw(easyBtnBorder);
        window.draw(easyBtn);
        window.draw(tEasyBtn);

        window.draw(hardBtnBorder);
        window.draw(hardBtn);
        window.draw(tHardBtn);

        // depending in if the home icon is selected the icon changes
        if (homeIconHover){
            window.draw(homeBSprite);
        } else {
            window.draw(homeWSprite);
        }

        // show what was drawn
        window.display();
    }
}