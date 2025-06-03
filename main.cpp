#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode({825, 800}), "Ranking"); // creates the 825x800 window
     
    // TITLE
    Font font("assets/leadb_font.ttf"); // load the font
    Text title(font, "LEADERBOARD", 50); // declare the text, its font, content and size
    title.setOrigin({150,40}); // manually set origin for positioning
    title.setPosition({350, 100}); 

    // MAIN RECTANGLE
    RectangleShape rect;
    rect.setSize(Vector2f(625,550)); // width, height
    rect.setFillColor(Color::Black);
    rect.setOrigin(rect.getSize() / 2.f); // center the origin
    rect.setPosition({825 / 2.f, 450});

    // MARGINS
    RectangleShape marginTop;
    marginTop.setSize(Vector2f(625,550)); // width, height
    marginTop.setFillColor(Color::Cyan);
    marginTop.setOrigin(rect.getSize() / 2.f);
    marginTop.setPosition({805 / 2.f, 440});

    RectangleShape marginBottom;
    marginBottom.setSize(Vector2f(625,550)); // width, height
    marginBottom.setFillColor(Color::Magenta);
    marginBottom.setOrigin(rect.getSize() / 2.f); 
    marginBottom.setPosition({845 / 2.f, 460});

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();
        } 

        window.clear(Color::Black); // clear the window to draw the next frame
        
        // draw stuff here
        window.draw(title);
        window.draw(marginTop);
        window.draw(marginBottom);
        window.draw(rect);

        // show what was drawn
        window.display();
    }
}