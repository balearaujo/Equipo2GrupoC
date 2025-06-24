#include <SFML/Graphics.hpp>
#include <iostream>
#include "header.hpp"
using namespace std;
using namespace sf;

void screenSelectDificulty(){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred"); // creates the 825x800 window

    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }

    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

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

     // MENU BUTTON
    RectangleShape menuBtn;
    menuBtn.setSize(Vector2f(300,75));
    menuBtn.setFillColor(Color(75,75,75));
    menuBtn.setOrigin({(menuBtn.getSize().x)/2 , (menuBtn.getSize().y)/2});
    menuBtn.setPosition({412, 630}); // x,y

    RectangleShape menuBtnBorder;
    menuBtnBorder.setSize(Vector2f(320,90));
    menuBtnBorder.setFillColor(Color::Black);
    menuBtnBorder.setOrigin({(menuBtnBorder.getSize().x)/2 , (menuBtnBorder.getSize().y)/2});
    menuBtnBorder.setPosition({412, 630}); // x,y

    Text tMenuBtn(font, "MENU", 60);
    tMenuBtn.setFillColor(Color::White);
    tMenuBtn.setOrigin({75, 20});
    tMenuBtn.setPosition({420, 610});

    // 0 = easy, 1 = hard, 2 = menu
    int posAux = 0;

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();
            if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }

            if (posAux>= 0 && posAux<2){
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                }
            }

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
                    menuBtn.setFillColor(Color(75,75,75));
                    menuBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        // EASY action
                    }

                    break;
                case 1:
                    // HARD button selected
                    hardBtn.setFillColor(Color(253,114,114));
                    hardBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    easyBtn.setFillColor(Color(130,130,130));
                    easyBtnBorder.setFillColor(Color::Black);
                    menuBtn.setFillColor(Color(75,75,75));
                    menuBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        // HARD action
                    }

                    break;
                case 2:
                    // MENU button selected
                    menuBtn.setFillColor(Color(253,114,114));
                    menuBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    easyBtn.setFillColor(Color(130,130,130));
                    easyBtnBorder.setFillColor(Color::Black);
                    hardBtn.setFillColor(Color(130,130,130));
                    hardBtnBorder.setFillColor(Color::Black);
 
                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        // EASY action
                    }
                    break;
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

        window.draw(menuBtnBorder);
        window.draw(menuBtn);
        window.draw(tMenuBtn);

        // show what was drawn
        window.display();
    }
}