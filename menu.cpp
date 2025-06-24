#include <SFML/Graphics.hpp>
#include <iostream>
#include "header.hpp"
using namespace std;
using namespace sf;

void screenMenu(){
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
    Text title(font, "MENU", 90); // declare the text, its font, content and size
    title.setOrigin({150,40}); // manually set origin for positioning
    title.setPosition({458, 100}); 

    // NEW GAME BUTTON
    RectangleShape nGameBtn;
    nGameBtn.setSize(Vector2f(600,75));
    nGameBtn.setFillColor(Color(253,114,114));
    nGameBtn.setOrigin({(nGameBtn.getSize().x)/2 , (nGameBtn.getSize().y)/2});
    nGameBtn.setPosition({412, 255}); // x,y

    RectangleShape nGameBtnBorder;
    nGameBtnBorder.setSize(Vector2f(620,100));
    nGameBtnBorder.setFillColor(Color::Red);
    nGameBtnBorder.setOrigin({(nGameBtnBorder.getSize().x)/2 , (nGameBtnBorder.getSize().y)/2});
    nGameBtnBorder.setPosition({412, 255}); // x,y

    Text tNGameBtn(font, "NEW GAME", 70);
    tNGameBtn.setFillColor(Color::White);
    tNGameBtn.setOrigin({75, 20});
    tNGameBtn.setPosition({360, 230});

    // LEADERBOARD BUTTON
    RectangleShape leadbBtn;
    leadbBtn.setSize(Vector2f(600,75));
    leadbBtn.setFillColor(Color(130,130,130));
    leadbBtn.setOrigin({(leadbBtn.getSize().x)/2 , (leadbBtn.getSize().y)/2});
    leadbBtn.setPosition({412, 375}); // x,y

    RectangleShape leadbBtnBorder;
    leadbBtnBorder.setSize(Vector2f(620,100));
    leadbBtnBorder.setFillColor(Color::Black);
    leadbBtnBorder.setOrigin({(leadbBtnBorder.getSize().x)/2 , (leadbBtnBorder.getSize().y)/2});
    leadbBtnBorder.setPosition({412, 375}); // x,y

    Text tLeadbBtn(font, "LEADERBOARD", 70);
    tLeadbBtn.setFillColor(Color::White);
    tLeadbBtn.setOrigin({75, 20});
    tLeadbBtn.setPosition({320, 350});

    // LOAD GAME BUTTON
    RectangleShape ldGameBtn;
    ldGameBtn.setSize(Vector2f(600,75));
    ldGameBtn.setFillColor(Color(130,130,130)); 
    ldGameBtn.setOrigin({(ldGameBtn.getSize().x)/2 , (ldGameBtn.getSize().y)/2});
    ldGameBtn.setPosition({412, 495}); // x,y

    RectangleShape ldGameBtnBorder;
    ldGameBtnBorder.setSize(Vector2f(620,100));
    ldGameBtnBorder.setFillColor(Color::Black); 
    ldGameBtnBorder.setOrigin({(ldGameBtnBorder.getSize().x)/2 , (ldGameBtnBorder.getSize().y)/2});
    ldGameBtnBorder.setPosition({412, 495}); // x,y

    Text tLdGameBtn(font, "LOAD GAME", 70);
    tLdGameBtn.setFillColor(Color::White);
    tLdGameBtn.setOrigin({75, 20});
    tLdGameBtn.setPosition({340, 470});

    // HELP BUTTON
    RectangleShape helpBtn;
    helpBtn.setSize(Vector2f(600,75));
    helpBtn.setFillColor(Color(130,130,130)); 
    helpBtn.setOrigin({(helpBtn.getSize().x)/2 , (helpBtn.getSize().y)/2});
    helpBtn.setPosition({412, 615}); 

    RectangleShape helpBtnBorder;
    helpBtnBorder.setSize(Vector2f(620,100));
    helpBtnBorder.setFillColor(Color::Black); 
    helpBtnBorder.setOrigin({(helpBtnBorder.getSize().x)/2 , (helpBtnBorder.getSize().y)/2});
    helpBtnBorder.setPosition({412, 615}); // x,y

    Text tHelpBtn(font, "HELP", 70);
    tHelpBtn.setFillColor(Color::White);
    tHelpBtn.setOrigin({75, 20});
    tHelpBtn.setPosition({415, 590});


    // LOG OUT BUTTON
    RectangleShape logOutBtn;
    logOutBtn.setSize(Vector2f(300,60));
    logOutBtn.setFillColor(Color(75,75,75));
    logOutBtn.setOrigin({(logOutBtn.getSize().x)/2 , (logOutBtn.getSize().y)/2});
    logOutBtn.setPosition({400, 725}); // x,y

    RectangleShape logOutBtnBorder;
    logOutBtnBorder.setSize(Vector2f(320,75));
    logOutBtnBorder.setFillColor(Color::Black);
    logOutBtnBorder.setOrigin({(logOutBtnBorder.getSize().x)/2 , (logOutBtnBorder.getSize().y)/2});
    logOutBtnBorder.setPosition({400, 725}); // x,y

    Text tlogOutBtn(font, "LOG OUT", 45);
    tlogOutBtn.setFillColor(Color::White);
    tlogOutBtn.setOrigin({75, 20});
    tlogOutBtn.setPosition({410, 715});

    // 0 = new game, 1 = leaderboard, 2 = load game, 3 = help, 4 = log out
    int posAux = 0;

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close();
                    screenMainMenu();
                }
            }
            if (posAux>= 0 && posAux<4){
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                }
            }

            if (posAux> 0 && posAux<=4){
                if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                }
            }

            switch(posAux){ // change colors depending on the position
                case 0:
                    // NEW GAME button selected
                    nGameBtn.setFillColor(Color(253,114,114));
                    nGameBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    leadbBtn.setFillColor(Color(130,130,130));
                    leadbBtnBorder.setFillColor(Color::Black);

                    ldGameBtn.setFillColor(Color(130,130,130));
                    ldGameBtnBorder.setFillColor(Color::Black);

                    helpBtn.setFillColor(Color(130,130,130));
                    helpBtnBorder.setFillColor(Color::Black);

                    logOutBtn.setFillColor(Color(75,75,75));
                    logOutBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        
                    }

                    break;

                case 1:
                    // LEADERBOARD button selected
                    leadbBtn.setFillColor(Color(253,114,114));
                    leadbBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    nGameBtn.setFillColor(Color(130,130,130));
                    nGameBtnBorder.setFillColor(Color::Black);

                    ldGameBtn.setFillColor(Color(130,130,130));
                    ldGameBtnBorder.setFillColor(Color::Black);

                    helpBtn.setFillColor(Color(130,130,130));
                    helpBtnBorder.setFillColor(Color::Black);

                    logOutBtn.setFillColor(Color(75,75,75));
                    logOutBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        // LEADERBOARD action
                    }
                    break;

                case 2:
                    // LOAD GAME button selected
                    ldGameBtn.setFillColor(Color(253,114,114));
                    ldGameBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    nGameBtn.setFillColor(Color(130,130,130));
                    nGameBtnBorder.setFillColor(Color::Black);

                    leadbBtn.setFillColor(Color(130,130,130));
                    leadbBtnBorder.setFillColor(Color::Black);

                    helpBtn.setFillColor(Color(130,130,130));
                    helpBtnBorder.setFillColor(Color::Black);

                    logOutBtn.setFillColor(Color(75,75,75));
                    logOutBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        // LOAD GAME action
                    }
                    break;

                case 3:
                    // HELP button selected
                    helpBtn.setFillColor(Color(253,114,114));
                    helpBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    nGameBtn.setFillColor(Color(130,130,130));
                    nGameBtnBorder.setFillColor(Color::Black);

                    leadbBtn.setFillColor(Color(130,130,130));
                    leadbBtnBorder.setFillColor(Color::Black);

                    ldGameBtn.setFillColor(Color(130,130,130));
                    ldGameBtnBorder.setFillColor(Color::Black);

                    logOutBtn.setFillColor(Color(75,75,75));
                    logOutBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        // HELP action
                    }
                    break;

                case 4:
                    // LOG OUT button selected
                    logOutBtn.setFillColor(Color(253,114,114));
                    logOutBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    nGameBtn.setFillColor(Color(130,130,130));
                    nGameBtnBorder.setFillColor(Color::Black);

                    leadbBtn.setFillColor(Color(130,130,130));
                    leadbBtnBorder.setFillColor(Color::Black);

                    ldGameBtn.setFillColor(Color(130,130,130));
                    ldGameBtnBorder.setFillColor(Color::Black);

                    helpBtn.setFillColor(Color(130,130,130));
                    helpBtnBorder.setFillColor(Color::Black);

                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        window.close();
                        screenMainMenu();
                    }
                    break;
            }
            
            if (const auto *key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Enter){
                    switch(posAux){
                        case 0:
                            window.close();
                            screenSelectDifficulty();
                            break;
                        case 1:
                            window.close();
                            screenLeaderboard();
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            window.close();
                            screenMainMenu();
                            break;
                        }
                }
            }
        }

        window.clear(Color::Black); // clear the window to draw the next frame
        window.draw(backgSprite);

        // draw stuff here
        window.draw(title);

        window.draw(nGameBtnBorder);
        window.draw(nGameBtn);
        window.draw(tNGameBtn);

        window.draw(leadbBtnBorder);
        window.draw(leadbBtn);
        window.draw(tLeadbBtn);

        window.draw(ldGameBtnBorder);
        window.draw(ldGameBtn);
        window.draw(tLdGameBtn);

        window.draw(logOutBtnBorder);
        window.draw(logOutBtn);
        window.draw(tlogOutBtn);

        window.draw(helpBtnBorder);
        window.draw(helpBtn);
        window.draw(tHelpBtn);


        // show what was drawn
        window.display();
    }
}