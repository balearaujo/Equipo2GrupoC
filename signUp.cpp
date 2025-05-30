#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

// static int totalUsers{0};

// ACABAR FUNCION CUANDO FUNCIONE LA SIMULACIÓN DE INPUT, TODAVIA NO SIRVE BIEN

// void addUser(FILE *users){
//     User newUser;
//     int textSize{25};
//     bool samePass = false;

//     // allocate dynamic memory
//     char *passAux = new char[textSize];
//     char *passAux2 = new char[textSize];
//     newUser.username = new char[textSize]; 
//     newUser.password = new char[textSize];
//     newUser.games = new GameHistory[3];
    
//     totalUsers++;
//     newUser.idUser = totalUsers;

//     // cin user

//     do{ // password and confirm password
//         // cin pass aux

//         fflush(stdin);

//         // cin pass aux 2

//         fflush(stdin);
//         // if (strcmp(passAux,passAux2)==0){
//         //     samePass = true;
//         //     newUser.password = strcpy(newUser.password, passAux);
//         // } else{
//         //     cout << "The password must be the same" << endl;
//         // }
//     } while (!samePass);
//     // Write dynamic memory variables separately because when using fwrite, it accesses
//     // to the memory address and not to the content.
//     fwrite(&newUser.idUser, sizeof(int), 1, users);
//     fwrite(newUser.username, sizeof(char), textSize, users);
//     fwrite(newUser.password, sizeof(char), textSize, users);
    
//     // !!!!!!! we need to verify the number of games started||concluded!!!!!!!! 
//     // the game history hasn't yet been saved
//     // fwrite(newUser.games, sizeof(GameHistory), 1, users);
//     delete [] passAux;
//     delete [] passAux2;
//     delete [] newUser.username;
//     delete [] newUser.password;
//     // delete [] newUser.games;
// }


void screenSignUp(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!");
    window.setTitle("Sign up");

    // 0 = username, 1 = password, 2 = confirm password 
    int posAux{0};
    bool button = false;
    sf::String concatUser("");
    sf::String concatPass("");
    sf::String concatConfPass("");
    
    // FALTA
    // HACER UN BOTON DE CONFIRMAR.

    // declaration
    Font font("assets/ARIAL.TTF");
    Text tTitle(font, "Sign up", 75);
    Text tUsername(font, "Username: ", 50);
    Text tPass(font, "Password: ", 50);
    Text tConfPass(font, "Confirm password:", 50);
    Text tWarnings(font, "Special characters not allowed!", 30);
    
    
    Text inpUsername(font, "->", 50);
    Text inpPass(font, "->", 50);
    Text inpConfPass(font, "->", 50);
    

    // color
    tTitle.setFillColor(Color::Red);
    tUsername.setFillColor(Color::White);
    tPass.setFillColor(Color::White);
    tConfPass.setFillColor(Color::White);
    tWarnings.setFillColor(Color::Black);
    
    inpUsername.setFillColor(Color::Green);
    inpPass.setFillColor(Color::Green);
    inpConfPass.setFillColor(Color::Green);
    

    // origin
    tTitle.setOrigin({90, 30});
    tUsername.setOrigin({75, 20});
    tPass.setOrigin({75, 20});
    tConfPass.setOrigin({75, 20});
    tWarnings.setOrigin({64, 17});
    
    inpUsername.setOrigin({75,20});
    inpPass.setOrigin({75,20});
    inpConfPass.setOrigin({75,20});


    // position
    tTitle.setPosition({350, 100});
    tUsername.setPosition({100, 250});
    tPass.setPosition({100, 350});
    tConfPass.setPosition({100, 450});
    tWarnings.setPosition({100, 600});

    inpUsername.setPosition({350, 250});
    inpPass.setPosition({350, 350});
    inpConfPass.setPosition({550, 450});
    
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
            if (posAux>=0 && posAux<2){ // posAux between 0-1
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    cout << posAux;
                }
            }

            if (posAux>0 && posAux<=2){ // posAux between 1-2
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
                    setInputValues(inpUsername, event.value(), concatUser, tWarnings);
                    break;
                case 1:
                    // optText[posAux] = 1;
                    tPass.setFillColor(Color::Magenta);
                    tUsername.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    setInputValues(inpPass, event.value(), concatPass, tWarnings);
                    break;
                case 2:
                    // optText[posAux] = 1;
                    tConfPass.setFillColor(Color::Magenta);
                    tPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    setInputValues(inpConfPass, event.value(), concatConfPass, tWarnings);
                    break;
                }


        }
        window.clear(Color::Black);
        window.draw(tTitle);
        window.draw(tUsername);
        window.draw(tPass);
        window.draw(tConfPass);
        window.draw(tWarnings);
        window.draw(inpUsername);
        window.draw(inpPass);
        window.draw(inpConfPass);
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