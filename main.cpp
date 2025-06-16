#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

struct User{
    char name[16];
    int score;
    int dd;
    int mm;
    int aa;
};

int main() {
    User data;
    FILE *users;

    users = fopen("users.dat","rb");

    if(users==NULL){
        cout << "Error";
        return 1;
    }


    RenderWindow window(sf::VideoMode({825, 800}), "Ranking"); // creates the 825x800 window

    // TITLE
    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font
    Text title(font, "LEADERBOARD", 90); // declare the text, its font, content and size
    title.setOrigin({150,40}); // manually set origin for positioning
    title.setPosition({350, 75}); 

    // MARGIN
    RectangleShape margin;
    margin.setSize(Vector2f(702,504)); // width, height
    margin.setFillColor(Color(255,255,255,150));
    margin.setOrigin(margin.getSize() / 2.f); // center the origin
    margin.setPosition({825 / 2.f, 425}); // x,y

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
    score.setPosition({575, 220}); 
    score.setFillColor(sf::Color(255, 255, 255, 150));
    Text date(font, "Date", 30); 
    date.setOrigin({150,40}); 
    date.setPosition({775, 220}); 
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

    int page = 1;
    int actualUser = page*10-9;
    int userEnd = page*10;
    vector<Text> ranks;
    vector<Text> usernames;
    vector<Text> scores;
    vector<Text> dates;

    while (fread(&data,sizeof(User),1,users) && actualUser <= userEnd){
        Text rank(font, to_string(actualUser), 32);
        rank.setOrigin({150,40});
        rank.setPosition({230, 270.0f + (actualUser-1) * 45.0f});
        if (actualUser == 1){
            rank.setFillColor(Color(255, 215, 0)); // golden
        }
        ranks.push_back(rank);

        Text username(font, data.name, 32);
        username.setOrigin({150,40});
        username.setPosition({280, 270.0f + (actualUser-1) * 45.0f});
        if (actualUser == 1){
            username.setFillColor(Color(255, 215, 0));
        }
        usernames.push_back(username);

        Text score(font, to_string(data.score), 32);
        score.setOrigin({150,40});
        score.setPosition({575, 270.0f + (actualUser-1) * 45.0f});
        if (actualUser == 1){
            score.setFillColor(Color(255, 215, 0));
        }
        scores.push_back(score);

        string dateText = to_string(data.dd) + "-" + to_string(data.mm) + "-" + to_string(data.aa);
        Text date(font, dateText, 32);
        date.setOrigin({150,40});
        date.setPosition({775, 270.0f + (actualUser-1) * 45.0f});
        if (actualUser == 1){
            date.setFillColor(Color(255, 215, 0));
        }
        dates.push_back(date);

        actualUser++;
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
        for (const auto& rank : ranks) {
            window.draw(rank);
        }
        for (const auto& username : usernames) {
            window.draw(username);
        }
        for (const auto& score : scores) {
            window.draw(score);
        }
        for (const auto& date : dates) {
            window.draw(date);
        }

        // show what was drawn
        window.display();
    }
}