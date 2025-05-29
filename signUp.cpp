#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

void screenSignUp(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!");
    window.setTitle("Sign up");

    int textOpt[3] = {0,0,0};

    // declaration
    Font font("assets/ARIAL.TTF");
    Text tTitle(font, "Sign up", 75);
    Text tUsername(font, "Username: ", 50);
    Text tPass(font, "Password: ", 50);
    Text tConfPass(font, "Confirm password:", 50);
    Text inpUsername(font, "aaaa", 50);

    // color
    tTitle.setFillColor(Color::Red);
    tUsername.setFillColor(Color::White);
    inpUsername.setFillColor(Color::Green);
    tPass.setFillColor(Color::White);
    tConfPass.setFillColor(Color::White);

    // origin
    tTitle.setOrigin({90, 30});
    tUsername.setOrigin({75, 20});
    inpUsername.setOrigin({75,20});
    tPass.setOrigin({75, 20});
    tConfPass.setOrigin({75, 20});

    // position
    tTitle.setPosition({350, 100});
    tUsername.setPosition({200, 250});
    inpUsername.setPosition({600, 250});
    tPass.setPosition({200, 350});
    tConfPass.setPosition({200, 450});

    char *aux;
    aux = new char[200];
    sf::String hola("");
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // const auto es porque no cambia el texto que recibe TextEntered, el auto es para que deduzca el tipo (puntero a constante)
            // getIf devuelve puntero a constante, es un puntero porque no se puede modificar el contenido que recibe
            // TextEntered, es decir, getIf devuelve el contenido de modo "lectura" a enteredUsername.

            if (const auto *enteredUsername = event->getIf<Event::TextEntered>()){
                if (enteredUsername->unicode < 128){
                    hola += enteredUsername->unicode;
                    inpUsername.setString(hola);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }
            if (event->is<sf::Event::Closed>())
                window.close();
            
        }
        window.clear(Color::Black);
        window.draw(tTitle);
        window.draw(tUsername);
        window.draw(tPass);
        window.draw(tConfPass);
        window.draw(inpUsername);
        window.display();
    }
}