#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

void screenSignUp(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!");
    window.setTitle("Sign up");

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // background
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/back.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    // 0 = username, 1 = password, 2 = confirm password, 3 = sign up button
    int posAux{0};  
    
    // declaration
    Font font("assets/BurbankBigCondensed-Black.otf");
    Text tTitle(font, "SIGN UP", 90);
    Text tUsername(font, "USERNAME", 30);
    Text tPass(font, "PASSWORD", 30);
    Text tConfPass(font, "CONFIRM PASSWORD", 30);
    Text tWarnings(font, "SPECIAL CHARACTERS NOT ALLOWED!", 30);
    Text tWarningPass(font, "", 30);
    Text tButtonSU(font, "SIGN UP", 50);
    
    sf::String concatUser("");
    sf::String concatPass("");
    sf::String concatConfPass("");
    Text inpUsername(font, "", 50);
    Text inpPass(font, "", 50);
    Text inpConfPass(font, "", 50);
    
    RectangleShape buttSub(Vector2f{350, 75});
    RectangleShape buttSubBorder(Vector2f{370, 90});

    // color
    tTitle.setFillColor(Color::White);
    tUsername.setFillColor(Color::White);
    tPass.setFillColor(Color::White);
    tConfPass.setFillColor(Color::White);
    tWarnings.setFillColor(Color::Transparent);
    tWarningPass.setFillColor(Color::Transparent);
    tButtonSU.setFillColor(Color::White);

    inpUsername.setFillColor(Color(155, 160, 182)); // light blue
    inpPass.setFillColor(Color(155, 160, 182));
    inpConfPass.setFillColor(Color(155, 160, 182));
    buttSub.setFillColor(Color(89, 111, 173)); 
    buttSubBorder.setFillColor(Color::Transparent);
    

    // origin
    tTitle.setOrigin({100, 40});
    tUsername.setOrigin({65, 17});
    tPass.setOrigin({65, 17});
    tConfPass.setOrigin({65, 17});
    tWarnings.setOrigin({65, 17});
    tWarningPass.setOrigin({65, 17});
    tButtonSU.setOrigin({75, 20});
    
    inpUsername.setOrigin({75,20});
    inpPass.setOrigin({75,20});
    inpConfPass.setOrigin({75,20});
    buttSub.setOrigin({(buttSub.getSize().x)/2 , (buttSub.getSize().y)/2});
    buttSubBorder.setOrigin({(buttSubBorder.getSize().x)/2 , (buttSubBorder.getSize().y)/2});
    

    // position
    tTitle.setPosition({825/2, 85});
    tUsername.setPosition({190, 205}); 
    tPass.setPosition({190, 340});
    tConfPass.setPosition({190, 475});
    tWarnings.setPosition({100, 720});
    tWarningPass.setPosition({100, 760});
    tButtonSU.setPosition({825/2, 635});

    inpUsername.setPosition({215, 255});
    inpPass.setPosition({215, 390});
    inpConfPass.setPosition({215, 525});
    buttSub.setPosition({825/2, 650});
    buttSubBorder.setPosition({825/2, 650});

    // design 
    vector<RectangleShape> inpBoxes; // boxes
    for (int i = 0; i<3; i++){
        RectangleShape inpBox;
        inpBox.setSize(Vector2f({565, 75}));
        inpBox.setFillColor(Color(19, 20, 40));
        inpBox.setOrigin({(inpBox.getSize().x) / 2, (inpBox.getSize().y) / 2});
        inpBox.setPosition({825/2, 265.f + i * 135.f});
        inpBoxes.push_back(inpBox);
    }
    vector<RectangleShape> inpBoxesBorder; // border
    for (int i = 0; i<3; i++){
        RectangleShape inpBoxBor;
        inpBoxBor.setSize(Vector2f({570, 80}));
        inpBoxBor.setFillColor(Color::White);
        inpBoxBor.setOrigin({(inpBoxBor.getSize().x) / 2, (inpBoxBor.getSize().y) / 2});
        inpBoxBor.setPosition({825/2, 265.f + i * 135.f});
        inpBoxesBorder.push_back(inpBoxBor);
    }


    // MAIN WINDOW
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            
            if (event->is<sf::Event::Closed>()){
                window.close();
            } else if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close();
                    screenMainMenu();
                }
            }
            // adjust posAux to handle "input" textbox
            if (posAux>=0 && posAux<3){ // posAux between 0-2
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    cout << posAux;
                }
            }

            if (posAux>0 && posAux<=3){ // posAux between 1-3
                if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                    cout << posAux;
                }
            }
            
            switch(posAux){ // change colors depending on the position, call function setInputValue to grab typed characters
                case 0:
                    // posAux = 0, username 
                    tUsername.setFillColor(Color(102, 179, 255));
                    tPass.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpUsername, event.value(), concatUser, tWarnings);
                    break;
        
                case 1:
                    // posAux = 1, password
                    tPass.setFillColor(Color(102, 179, 255)); // dark blue
                    tUsername.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpPass, event.value(), concatPass, tWarnings);
                    break;
            
                case 2:
                    // posAux = 2, confirm password
                    tConfPass.setFillColor(Color(102, 179, 255));
                    tPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpConfPass, event.value(), concatConfPass, tWarnings);
                    break;
                
                case 3:
                    // posAux = 3, button
                    tConfPass.setFillColor(Color::White);
                    tPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Red);

                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){
                            if (checkUsername(inpUsername)){ // check if the username is available
                                if (checkPassword(inpPass, inpConfPass)){ // convert sf strings to std string and compare
                                    tWarningPass.setString("PASSWORDS MUST MATCH!"); 
                                    tWarningPass.setFillColor(Color::Yellow);
                                } else{
                                    if (inpPass.getString().getSize()<8 || inpUsername.getString().getSize()<8){
                                        tWarningPass.setString("USERNAME / PASSWORD MUST BE AT LEAST 8 CHARACTERS");
                                        tWarningPass.setFillColor(Color::Yellow);
                                    } else{ // user available, same password, correct lenght
                                        tWarningPass.setFillColor(Color::Transparent);
                                        writeUser(inpUsername, inpPass);
                                        cout << "User " << inpUsername.getString().toAnsiString() << " writed ";
                                        window.close();
                                        screenMainMenu();
                                    }
                                }   
                            } else{ // username not available
                                tWarningPass.setString("USERNAME NOT AVAILABLE!");
                                tWarningPass.setFillColor(Color::Yellow);
                            }
                        }
                    }
            }
    
            if (!(inpUsername.getString().isEmpty()) && !(inpPass.getString().isEmpty()) && !(inpConfPass.getString().isEmpty())){
                buttSub.setFillColor(Color(253,114,114)); // light red
            } else {
                buttSub.setFillColor(Color(130,130,130)); // gray
            }

        }
        
        window.clear(Color::Black);
        window.draw(backgSprite);
        window.draw(tTitle);
        for (const auto& inpBoxBor : inpBoxesBorder){
            window.draw(inpBoxBor);
        }
        for (const auto& inpBox : inpBoxes){
            window.draw(inpBox);
        }
        window.draw(tUsername);
        window.draw(tPass);
        window.draw(tConfPass); 
        window.draw(tWarnings);
        window.draw(tWarningPass);
        window.draw(inpUsername);
        window.draw(inpPass);
        window.draw(inpConfPass);
        window.draw(buttSubBorder);
        window.draw(buttSub);
        window.draw(tButtonSU);
        window.display();
    }
}

// al estar fuera de la window, se le tiene que pasar el evento, el evento se declara al crear la window. (event = window.pollEvent())
void setInputValues(sf::Text &variable, const sf::Event &event, sf::String &concatAux, sf::Text &tWarnings){
    // getIf devuelve puntero a constante, es un puntero porque no se puede modificar el contenido que recibe del evento
    // TextEntered, es decir, getIf devuelve el contenido de modo "lectura" a typedText y se concatena en concatAux, después se
    // va asignando el texto concatenado a la variable ingresada.
    if (const sf::Event::TextEntered *typedText = event.getIf<Event::TextEntered>()){
        if (typedText->unicode < 128){
            if (typedText->unicode == 32 || typedText->unicode > 127 || (typedText->unicode < 32 && typedText->unicode != 8)){
                cout << "special character ";
                tWarnings.setFillColor(Color::Yellow);    
            } else{
                if (variable.getString().getSize()<16){
                    if (typedText->unicode!=8){
                        concatAux += typedText->unicode;
                    }
                }
                // verificar si es tecla borrar y que tenga uno o mas caracteres
                if (concatAux.getSize()>0 && Keyboard::isKeyPressed(Keyboard::Key::Backspace)){
                    // elimina en la posicion n-1
                    concatAux.erase(concatAux.getSize()-1, 1);
                }
                variable.setString(concatAux);
                cout << variable.getString().toAnsiString();
                tWarnings.setFillColor(Color::Transparent);    
            }
        }
    }
}

bool checkUsername(sf::Text inpUsername){
    FILE *users = fopen("users.dat", "ab+"); // open file
    User userRecord;
    if (users == NULL){ 
        cout << "Error while opening users.dat";
        return false;
    }
    while (fread(&userRecord, sizeof(User), 1, users)){ // search username
        if (strcmp(inpUsername.getString().toAnsiString().c_str(), userRecord.username)==0){
            fclose(users);
            return false;
        }
    }
    fclose(users);
    return true;
}

bool checkPassword(sf::Text inpPass, sf::Text inpConfPass){
    return (inpPass.getString().toAnsiString().compare(inpConfPass.getString().toAnsiString()));
}

void writeUser(sf::Text inpUsername, sf::Text inpPass){
    User newUser;
    int id;
    FILE *users = fopen("users.dat", "ab+");
    if (users==NULL){
        cout << "Error while opening users.dat";
        return;
    }
    id = assignID(users);
    newUser.idUser = id;
    strcpy(newUser.username , inpUsername.getString().toAnsiString().c_str());
    strcpy(newUser.password, inpPass.getString().toAnsiString().c_str());
    newUser.nGames = 0;
    fwrite(&newUser, sizeof(User), 1, users);
    fclose(users);
}


int assignID(FILE *users){
    unsigned int fileSize;
    int idUs;
    fseek(users, 0, SEEK_END); // go to the end of the file
    fileSize = ftell(users); // return size in bytes
    idUs = fileSize / sizeof(User); // total users
    rewind(users);
    return ++idUs;
}
