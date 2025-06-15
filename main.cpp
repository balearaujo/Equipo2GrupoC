#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode({825, 800}), "Ranking"); // creates the 825x800 window

    // TITLE
    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font
    Text title(font, "LEADERBOARD", 90); // declare the text, its font, content and size
    title.setOrigin({150,40}); // manually set origin for positioning
    title.setPosition({350, 75}); 

    // MARGIN
    RectangleShape margin;
    margin.setSize(Vector2f(702,550)); // width, height
    margin.setFillColor(Color(255,255,255,150));
    margin.setOrigin(margin.getSize() / 2.f); // center the origin
    margin.setPosition({825 / 2.f, 449}); // x,y

    // HEADER ROW
    RectangleShape headerRow;
    headerRow.setSize(Vector2f(700,50)); // width, height
    headerRow.setFillColor(Color(10, 20, 60));
    headerRow.setOrigin(headerRow.getSize() / 2.f); // center the origin
    headerRow.setPosition({825 / 2.f, 200}); // x,y
    
    // HEADER TEXT
    Text rank(font, "#", 30); 
    rank.setOrigin({150,40}); 
    rank.setPosition({230, 225}); 
    rank.setFillColor(sf::Color(255, 255, 255, 150));
    Text user(font, "Player", 30); 
    user.setOrigin({150,40}); 
    user.setPosition({280, 220}); 
    user.setFillColor(sf::Color(255, 255, 255, 150));
    Text score(font, "Score", 30); 
    score.setOrigin({150,40}); 
    score.setPosition({600, 220}); 
    score.setFillColor(sf::Color(255, 255, 255, 150));
    Text date(font, "Date", 30); 
    date.setOrigin({150,40}); 
    date.setPosition({815, 220}); 
    date.setFillColor(sf::Color(255, 255, 255, 150));

    vector<RectangleShape> rows;
    for (int i = 0; i < 10; ++i) {
        RectangleShape row;
        row.setSize(Vector2f(700, 44));
        row.setFillColor(i % 2 == 0 ? Color(30, 30, 50) : Color(20, 20, 40)); // colores alternos
        row.setOrigin(row.getSize() / 2.f);
        row.setPosition({825 / 2.f, 248.0f + i * 45.0f}); // posición vertical
        rows.push_back(row);
    }

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();
        } 

        window.clear(Color::Black); // clear the window to draw the next frame

        // draw stuff here
        window.draw(title);
        window.draw(margin);
        window.draw(headerRow);
        for (const auto& row : rows) {
            window.draw(row);
        }
        window.draw(rank);
        window.draw(user);
        window.draw(score);
        window.draw(date);

        // show what was drawn
        window.display();
    }
}