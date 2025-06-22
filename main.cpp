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

    RenderWindow window(sf::VideoMode({825, 800}), "Leaderboard"); // creates the 825x800 window

    // BACKGROUND
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return 1;
    }

    sf::Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

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
    rank.setFillColor(Color(255, 255, 255, 150));
    Text user(font, "Player", 30); 
    user.setOrigin({150,40}); 
    user.setPosition({280, 220}); 
    user.setFillColor(Color(255, 255, 255, 150));
    Text score(font, "Score", 30); 
    score.setOrigin({150,40}); 
    score.setPosition({575, 220}); 
    score.setFillColor(Color(255, 255, 255, 150));
    Text date(font, "Date", 30); 
    date.setOrigin({150,40}); 
    date.setPosition({775, 220}); 
    date.setFillColor(Color(255, 255, 255, 150));

    vector<RectangleShape> rows;
    for (int i = 0; i < 10; ++i) {
        RectangleShape row;
        row.setSize(Vector2f(700, 44));
        row.setFillColor(i % 2 == 0 ? Color(30, 30, 50) : Color(20, 20, 40)); // colores alternos
        row.setOrigin(row.getSize() / 2.f);
        row.setPosition({825 / 2.f, 248.0f + i * 45.0f}); // posición vertical
        rows.push_back(row);
    }

    // NEXT BUTTON
    RectangleShape prevBtn;
    prevBtn.setSize(Vector2f(125,40));
    prevBtn.setFillColor(Color(130,130,130));
    prevBtn.setOrigin({(prevBtn.getSize().x)/2 , (prevBtn.getSize().y)/2});
    prevBtn.setPosition({125, 730}); // x,y

    RectangleShape prevBtnBorder;
    prevBtnBorder.setSize(Vector2f(145,55));
    prevBtnBorder.setFillColor(Color::Black);
    prevBtnBorder.setOrigin({(prevBtnBorder.getSize().x)/2 , (prevBtnBorder.getSize().y)/2});
    prevBtnBorder.setPosition({125, 730}); // x,y

    Text tPrevBtn(font, "PREV", 40);
    tPrevBtn.setFillColor(Color::White);
    tPrevBtn.setOrigin({75, 20});
    tPrevBtn.setPosition({163, 725});


    // HOME BUTTON
    RectangleShape homeBtn;
    homeBtn.setSize(Vector2f(300,40));
    homeBtn.setFillColor(Color(253,114,114));
    homeBtn.setOrigin({(homeBtn.getSize().x)/2 , (homeBtn.getSize().y)/2});
    homeBtn.setPosition({412, 730}); // x,y

    RectangleShape homeBtnBorder;
    homeBtnBorder.setSize(Vector2f(320,55));
    homeBtnBorder.setFillColor(Color::Red);
    homeBtnBorder.setOrigin({(homeBtnBorder.getSize().x)/2 , (homeBtnBorder.getSize().y)/2});
    homeBtnBorder.setPosition({412, 730}); // x,y

    Text tHomeBtn(font, "HOME", 40);
    tHomeBtn.setFillColor(Color::White);
    tHomeBtn.setOrigin({75, 20});
    tHomeBtn.setPosition({440, 725});


    // NEXT BUTTON
    RectangleShape nextBtn;
    nextBtn.setSize(Vector2f(125,40));
    nextBtn.setFillColor(Color(130,130,130));
    nextBtn.setOrigin({(nextBtn.getSize().x)/2 , (nextBtn.getSize().y)/2});
    nextBtn.setPosition({702, 730}); // x,y

    RectangleShape nextBtnBorder;
    nextBtnBorder.setSize(Vector2f(145,55));
    nextBtnBorder.setFillColor(Color::Black);
    nextBtnBorder.setOrigin({(nextBtnBorder.getSize().x)/2 , (nextBtnBorder.getSize().y)/2});
    nextBtnBorder.setPosition({702, 730}); // x,y

    Text tNextBtn(font, "NEXT", 40);
    tNextBtn.setFillColor(Color::White);
    tNextBtn.setOrigin({75, 20});
    tNextBtn.setPosition({740, 725});

    int totalUsers = 0;
    while (fread(&data,sizeof(User),1,users)){
        totalUsers++;
    }
    fclose(users);

    int actualPage = 1;
    int lastPage = totalUsers/11 + 1;
    int actualUser = actualPage*10-9;
    int lastUserPage = actualPage*10;
    vector<Text> ranks;
    vector<Text> usernames;
    vector<Text> scores;
    vector<Text> dates;

    users = fopen("users.dat","rb");

    if(users==NULL){
        cout << "Error";
        return 1;
    }

    int index=0;
    while (fread(&data,sizeof(User),1,users) && actualUser <= lastUserPage && actualUser<=totalUsers){
        Text rank(font, to_string(actualUser), 32);
        rank.setOrigin({150,40});
        rank.setPosition({230, 270.0f + index * 45.0f});
        if (actualUser == 1){
            rank.setFillColor(Color(255, 215, 0)); // golden
        }
        ranks.push_back(rank);

        Text username(font, data.name, 32);
        username.setOrigin({150,40});
        username.setPosition({280, 270.0f + index * 45.0f});
        if (actualUser == 1){
            username.setFillColor(Color(255, 215, 0));
        }
        usernames.push_back(username);

        Text score(font, to_string(data.score), 32);
        score.setOrigin({150,40});
        score.setPosition({575, 270.0f + index * 45.0f});
        if (actualUser == 1){
            score.setFillColor(Color(255, 215, 0));
        }
        scores.push_back(score);

        string dateText = to_string(data.dd) + "-" + to_string(data.mm) + "-" + to_string(data.aa);
        Text date(font, dateText, 32);
        date.setOrigin({150,40});
        date.setPosition({775, 270.0f + index * 45.0f});
        if (actualUser == 1){
            date.setFillColor(Color(255, 215, 0));
        }
        dates.push_back(date);

        actualUser++;
        index++;
    }
    fclose(users);

    // 0 = prev, 1 = menu, 2 = next
    int posAux = 1;
    bool needsUpdate = false;

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()){
                window.close();
            }   
            if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Right) && lastPage != 1){
                if (actualPage == 1 && posAux==1){
                    posAux++;
                    cout << posAux;
                } else if (actualPage == lastPage && posAux==0){
                    posAux++;
                    cout << posAux;
                } else if (posAux >= 0 && posAux < 2 && actualPage!=lastPage){
                    posAux++;
                    cout << posAux;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Left) && lastPage != 1){
                if (actualPage == 1 && posAux==2){
                    posAux--;
                    cout << posAux;
                } else if (actualPage == lastPage && posAux==1){
                    posAux--;
                    cout << posAux;
                } else if (posAux > 0 && posAux <= 2 && actualPage!=1){
                    posAux--;
                    cout << posAux;
                }
            }

            switch(posAux) {
                case 0:
                    // PREV button selected
                    prevBtn.setFillColor(Color(253,114,114));
                    prevBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    homeBtn.setFillColor(Color(130,130,130));
                    homeBtnBorder.setFillColor(Color::Black);
                    nextBtn.setFillColor(Color(130,130,130));
                    nextBtnBorder.setFillColor(Color::Black);

                    if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                        if (actualPage > 1){
                            actualPage--;
                            needsUpdate = true;
                            window.close();
                        }
                    }
                    break;

                case 1:
                    // HOME button selected
                    homeBtn.setFillColor(Color(253,114,114));
                    homeBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    prevBtn.setFillColor(Color(130,130,130));
                    prevBtnBorder.setFillColor(Color::Black);
                    nextBtn.setFillColor(Color(130,130,130));
                    nextBtnBorder.setFillColor(Color::Black);

                    if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                        // HOME action
                    }
                    break;

                case 2:
                    // NEXT button selected
                    nextBtn.setFillColor(Color(253,114,114));
                    nextBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    prevBtn.setFillColor(Color(130,130,130));
                    prevBtnBorder.setFillColor(Color::Black);
                    homeBtn.setFillColor(Color(130,130,130));
                    homeBtnBorder.setFillColor(Color::Black);
                    if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                        if (actualPage < lastPage){
                            actualPage++;
                            needsUpdate = true;
                            window.close();
                        }
                    }
                    break;
            }
        }

        actualUser = actualPage*10-9;
        lastUserPage = actualPage*10;

        if(needsUpdate){
            ranks.clear();
            usernames.clear();
            scores.clear();
            dates.clear();

            users = fopen("users.dat","rb");

            if(users==NULL){
                cout << "Error";
                return 1;
            }

            fseek(users, (actualUser - 1) * sizeof(User), SEEK_SET);

            index = 0;

            while (fread(&data,sizeof(User),1,users) && actualUser <= lastUserPage && actualUser<=totalUsers){
                Text rank(font, to_string(actualUser), 32);
                rank.setOrigin({150,40});
                rank.setPosition({230, 270.0f + index * 45.0f});
                if (actualUser == 1){
                    rank.setFillColor(Color(255, 215, 0)); // golden
                }
                ranks.push_back(rank);

                Text username(font, data.name, 32);
                username.setOrigin({150,40});
                username.setPosition({280, 270.0f + index * 45.0f});
                if (actualUser == 1){
                    username.setFillColor(Color(255, 215, 0));
                }
                usernames.push_back(username);

                Text score(font, to_string(data.score), 32);
                score.setOrigin({150,40});
                score.setPosition({575, 270.0f + index * 45.0f});
                if (actualUser == 1){
                    score.setFillColor(Color(255, 215, 0));
                }
                scores.push_back(score);

                string dateText = to_string(data.dd) + "-" + to_string(data.mm) + "-" + to_string(data.aa);
                Text date(font, dateText, 32);
                date.setOrigin({150,40});
                date.setPosition({775, 270.0f + index * 45.0f});
                if (actualUser == 1){
                    date.setFillColor(Color(255, 215, 0));
                }
                dates.push_back(date);

                actualUser++;
                index++;
            }
            fclose(users);

            needsUpdate = false;
        }

        window.clear(Color::Black); // clear the window to draw the next frame
        window.draw(backgSprite);

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

        if (actualPage != 1){
            window.draw(prevBtnBorder);
            window.draw(prevBtn);
            window.draw(tPrevBtn);
        }

        window.draw(homeBtnBorder);
        window.draw(homeBtn);
        window.draw(tHomeBtn); 

        if (actualPage != lastPage){  
            window.draw(nextBtnBorder);
            window.draw(nextBtn);
            window.draw(tNextBtn);
        }

        // show what was drawn
        window.display();
    }
}