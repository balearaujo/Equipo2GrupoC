#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

void screenSignUp(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!");
    window.setTitle("Sign up");
    Image icon("assets/logo.png");
    window.setIcon(icon);

    // 0 = username, 1 = password, 2 = confirm password, 3 = sign up button
    int posAux{0};
    bool button = false;
    sf::String concatUser("");
    sf::String concatPass("");
    sf::String concatConfPass("");
    
    // declaration
    Font font("assets/ARIAL.TTF");
    Text tTitle(font, "Sign up", 75);
    Text tUsername(font, "Username: ", 50);
    Text tPass(font, "Password: ", 50);
    Text tConfPass(font, "Confirm password:", 50);
    Text tWarnings(font, "Special characters not allowed!", 30);
    Text tWarningPass(font, "", 30);
    Text tButtonSU(font, "Sign Up", 50);
    RectangleShape buttSub(Vector2f{350, 75});
    RectangleShape buttSubBorder(Vector2f{370, 90});
    
    
    Text inpUsername(font, "", 50);
    Text inpPass(font, "", 50);
    Text inpConfPass(font, "", 50);
    

    // color
    tTitle.setFillColor(Color::Red);
    tUsername.setFillColor(Color::White);
    tPass.setFillColor(Color::White);
    tConfPass.setFillColor(Color::White);
    tWarnings.setFillColor(Color::Black);
    tWarningPass.setFillColor(Color::Black);
    tButtonSU.setFillColor(Color::White);

    inpUsername.setFillColor(Color::Green);
    inpPass.setFillColor(Color::Green);
    inpConfPass.setFillColor(Color::Green);
    buttSub.setFillColor(Color(130,130,130));
    buttSubBorder.setFillColor(Color::Black);
    

    // origin
    tTitle.setOrigin({90, 30});
    tUsername.setOrigin({75, 20});
    tPass.setOrigin({75, 20});
    tConfPass.setOrigin({75, 20});
    tWarnings.setOrigin({64, 17});
    tWarningPass.setOrigin({64, 17});
    tButtonSU.setOrigin({75, 20});
    
    inpUsername.setOrigin({75,20});
    inpPass.setOrigin({75,20});
    inpConfPass.setOrigin({75,20});
    buttSub.setOrigin({(buttSub.getSize().x)/2 , (buttSub.getSize().y)/2});
    buttSubBorder.setOrigin({(buttSubBorder.getSize().x)/2 , (buttSubBorder.getSize().y)/2});
    

    // position
    tTitle.setPosition({350, 100});
    tUsername.setPosition({100, 250});
    tPass.setPosition({100, 350});
    tConfPass.setPosition({100, 450});
    tWarnings.setPosition({100, 700});
    tWarningPass.setPosition({100, 750});
    tButtonSU.setPosition({410, 585});

    inpUsername.setPosition({350, 250});
    inpPass.setPosition({350, 350});
    inpConfPass.setPosition({550, 450});
    buttSub.setPosition({415, 600});
    buttSubBorder.setPosition({415, 600});
    
    //extra
    // sf::String test("");

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
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
                    // optText[posAux] = 1; 
                    tUsername.setFillColor(Color::Magenta);
                    tPass.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Black);
                    setInputValues(inpUsername, event.value(), concatUser, tWarnings);
                    break;
                case 1:
                    // optText[posAux] = 1;
                    tPass.setFillColor(Color::Magenta);
                    tUsername.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Black);
                    setInputValues(inpPass, event.value(), concatPass, tWarnings);
                    break;
                case 2:
                    // optText[posAux] = 1;
                    tConfPass.setFillColor(Color::Magenta);
                    tPass.setFillColor(Color::White);
                        tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Black);
                    setInputValues(inpConfPass, event.value(), concatConfPass, tWarnings);
                    break;
                case 3:
                    tConfPass.setFillColor(Color::White);
                    tPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Red);
                    if (Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                        if (checkUsername(inpUsername)){ // check if the username is available
                            if (inpPass.getString().toAnsiString().compare(inpConfPass.getString().toAnsiString())){ // convert sf strings to std string and compare
                                tWarningPass.setString("Passwords must match!"); 
                                tWarningPass.setFillColor(Color::Yellow);
                                cout << "a";
                            } else{ // user available and same password
                                tWarningPass.setFillColor(Color::Black);
                                cout << "b";
                            }
                        } else{ // username not available
                            tWarningPass.setString("Username not available");
                            tWarningPass.setFillColor(Color::Yellow);
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
        window.draw(tTitle);
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
                if (typedText->unicode!=8){
                    concatAux += typedText->unicode;
                }
                // verificar si es tecla borrar y que tenga uno o mas caracteres
                if (concatAux.getSize()>0 && Keyboard::isKeyPressed(Keyboard::Key::Backspace)){
                    // elimina en la posicion n-1
                    concatAux.erase(concatAux.getSize()-1, 1);
                }
                variable.setString(concatAux);
                cout << variable.getString().toAnsiString();
                tWarnings.setFillColor(Color::Black);    
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

// void writeUser(sf::Text inpUsername, sf::Text inpPass, sf::Text inpConfPass){
//     FILE *users = fopen("users.bin", "ab+");
//     User userRecord;
//     strcpy(userRecord.username, inpUsername.getString().toAnsiString().c_str());
//     strcpy(userRecord.username, inpPass.getString().toAnsiString().c_str());
// }