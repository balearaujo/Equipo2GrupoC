#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

void screenLogIn(){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!");
    window.setTitle("Log in");
    
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

    // 0 username, 1 password, 2 button
    int posAux{0};

    // declaration
    Font font("assets/BurbankBigCondensed-Black.otf");
    Text tTitle(font, "LOG IN", 90);
    Text tUsername(font, "USERNAME", 30);
    Text tPass(font, "PASSWORD", 30);
    Text tWarnings(font, "SPECIAL CHARACTERS NOT ALLOWED!", 30);
    Text tWarningPass(font, "", 30);
    Text tButtonLI(font, "LOG IN", 50);
    
    sf::String concatUser("");
    sf::String concatPass("");
    Text inpUsername(font, "", 50);
    Text inpPass(font, "", 50);
    RectangleShape buttSub(Vector2f{350, 75});
    RectangleShape buttSubBorder(Vector2f{370, 90});
    
    // color
    tTitle.setFillColor(Color::White);
    tUsername.setFillColor(Color::White);
    tPass.setFillColor(Color::White);
    tWarnings.setFillColor(Color::Transparent);
    tWarningPass.setFillColor(Color::Transparent);
    tButtonLI.setFillColor(Color::White);

    inpUsername.setFillColor(Color(155, 160, 182)); // light blue
    inpPass.setFillColor(Color(155, 160, 182));
    buttSub.setFillColor(Color(130,130,130)); 
    buttSubBorder.setFillColor(Color::Transparent);
    
    // origin
    tTitle.setOrigin({100, 40});
    tUsername.setOrigin({65, 17});
    tPass.setOrigin({65, 17});
    tWarnings.setOrigin({65, 17});
    tWarningPass.setOrigin({65, 17});
    tButtonLI.setOrigin({75, 20});

    inpUsername.setOrigin({75,20});
    inpPass.setOrigin({75,20});
    buttSub.setOrigin({(buttSub.getSize().x)/2 , (buttSub.getSize().y)/2});
    buttSubBorder.setOrigin({(buttSubBorder.getSize().x)/2 , (buttSubBorder.getSize().y)/2});

    // position
    tTitle.setPosition({825/2, 85});
    tUsername.setPosition({190, 240}); 
    tPass.setPosition({190, 400});
    tWarnings.setPosition({100, 720});
    tWarningPass.setPosition({100, 760});
    tButtonLI.setPosition({850/2, 610});

    inpUsername.setPosition({215, 290});
    inpPass.setPosition({215, 450});
    buttSub.setPosition({825/2, 625});
    buttSubBorder.setPosition({825/2, 625});

    // design
    vector<RectangleShape> inpBoxes; // input boxes
    for (int i = 0; i<2; i++){
        RectangleShape inpBox;
        inpBox.setSize(Vector2f({565, 75}));
        inpBox.setFillColor(Color(19, 20, 40));
        inpBox.setOrigin({(inpBox.getSize().x) / 2, (inpBox.getSize().y) / 2});
        inpBox.setPosition({825/2, 300.f + i * 160.f});
        inpBoxes.push_back(inpBox);
    }

    vector<RectangleShape> inpBoxesBorder; // white border 
    for (int i = 0; i<2; i++){
        RectangleShape inpBoxBor;
        inpBoxBor.setSize(Vector2f({570, 80}));
        inpBoxBor.setFillColor(Color::White);
        inpBoxBor.setOrigin({(inpBoxBor.getSize().x) / 2, (inpBoxBor.getSize().y) / 2});
        inpBoxBor.setPosition({825/2, 300.f + i * 160.f});
        inpBoxesBorder.push_back(inpBoxBor);
    }


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {   
            if (event->is<sf::Event::Closed>()){
                window.close();
            } else if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close();
                    mainMenuScreen();
                }
            }

            cout << "hola ";

            if (posAux >= 0 && posAux<2){
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    cout << posAux;
                }
            }
            if (posAux>0 && posAux<=2){
                if (Keyboard:: isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                    cout << posAux;
                }
            }
            switch(posAux){
                case 0:
                    tUsername.setFillColor(Color(102, 179, 255));
                    tPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpUsername, event.value(), concatUser, tWarnings);
                    break;
            
                case 1:
                    tPass.setFillColor(Color(102, 179, 255));
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpPass, event.value(), concatPass, tWarnings);
                    break;
                
                case 2:
                    tUsername.setFillColor(Color::White);
                    tPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Red);
                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){
                            if (inpPass.getString().getSize()<8 || inpUsername.getString().getSize()<8){
                                tWarningPass.setString("USERNAME / PASSWORD MUST BE AT LEAST 8 CHARACTERS");
                                tWarningPass.setFillColor(Color::Yellow);
                            } else{ // user available, same password, correct lenght
                                if (isValidUser(inpUsername, inpPass)){
                                    window.close();
                                    mainMenuScreen();
                                } else{
                                    tWarningPass.setString("LOGIN FAILED. VERIFY YOUR INFORMATION AND TRY AGAIN");
                                    tWarningPass.setFillColor(Color::Yellow);
                                }
                            }
                        }
                    }
                    break;
            }

            if (!inpUsername.getString().isEmpty() && !inpPass.getString().isEmpty()){
                buttSub.setFillColor(Color(253,114,114));
            } else{
                buttSub.setFillColor(Color(130,130,130));
            }
        }   
        
        window.clear();
        window.draw(backgSprite);
        window.draw(tTitle);
        for (const auto & inpBoxBor : inpBoxesBorder){
            window.draw(inpBoxBor);
        }   
        for (const auto & inpBox : inpBoxes){
            window.draw(inpBox);
        }   
        window.draw(tUsername);
        window.draw(tPass);
        window.draw(inpUsername);
        window.draw(inpPass);
        window.draw(tWarnings);
        window.draw(tWarningPass);
        window.draw(buttSubBorder);
        window.draw(buttSub);
        window.draw(tButtonLI);
        window.display();
    }
}

bool isValidUser(sf::Text inpUsername, sf::Text inpPass){
    User checkUser;
    FILE *users;
    bool found = false;
    users = fopen("users.dat", "rb");
    if (users==NULL){
        cout << "Error while opening users.dat (logIn)" << endl;
    }

    while (fread(&checkUser, sizeof(User), 1, users)){ // read file, search username and compare
        if ((strcmp(inpUsername.getString().toAnsiString().c_str(), checkUser.username)==0) &&
            (strcmp(inpPass.getString().toAnsiString().c_str(), checkUser.password)==0))
            {
                cout << "usuarios correctos" << endl;
                fclose(users);
                return true;
        } 

    }
    fclose(users);
    return false;
}