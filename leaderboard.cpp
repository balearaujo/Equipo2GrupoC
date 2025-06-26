// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include <iostream>
#include "header.hpp"
#include <algorithm>
using namespace std;
using namespace sf;

void screenLeaderboard() {
    ScoreRecord data;
    vector<ScoreRecord> allUsers;

    // Read all records from the binary file "leaderb.dat"
    FILE* leadbData = fopen("leaderb.dat", "rb");
    if (leadbData == NULL) {
        cout << "Error opening leaderb.dat" << endl;
        return;
    }
    // Read each ScoreRecord and store it in a vector
    while (fread(&data, sizeof(ScoreRecord), 1, leadbData)) {
        allUsers.push_back(data);
    }
    fclose(leadbData);

    // Sort the users descending by score
    sort(allUsers.begin(), allUsers.end(), [](const ScoreRecord& a, const ScoreRecord& b) {
        return a.score > b.score;
    });

    int totalUsers = allUsers.size();

    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!"); // Create a window

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    //BACKGROUND
    // Load background texture
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }
    // Create a sprite from the loaded texture
    Sprite backgSprite(backgTexture);
    // Calculate scale factors to make the background fit the entire window
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    // Apply the calculated scale to the sprite
    backgSprite.setScale({scaleX, scaleY});
    

    // Load font and set title
    Font font("assets/BurbankBigCondensed-Black.otf");
    Text title(font, "LEADERBOARD", 90);
    title.setOrigin({150,40});
    title.setPosition({350, 75});

    // Create white translucent background margin
    RectangleShape margin;
    margin.setSize(Vector2f(702,504));
    margin.setFillColor(Color(255,255,255,150));
    margin.setOrigin(margin.getSize() / 2.f);
    margin.setPosition({825 / 2.f, 425});

    // Header row for the leaderboard table
    RectangleShape headerRow;
    headerRow.setSize(Vector2f(700,50));
    headerRow.setFillColor(Color(10, 20, 60));
    headerRow.setOrigin(headerRow.getSize() / 2.f);
    headerRow.setPosition({825 / 2.f, 200});

    // Set header labels
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

    // Create alternating background rows
    vector<RectangleShape> rows;
    for (int i = 0; i < 10; ++i) {
        RectangleShape row;
        row.setSize(Vector2f(700, 44));
        row.setFillColor(i % 2 == 0 ? Color(30, 30, 50) : Color(20, 20, 40));
        row.setOrigin(row.getSize() / 2.f);
        row.setPosition({825 / 2.f, 248.0f + i * 45.0f});
        rows.push_back(row);
    }

    // Buttons for navigation
    // PREV button
    RectangleShape prevBtn, prevBtnBorder;
    prevBtn.setSize(Vector2f(125,40));
    prevBtn.setFillColor(Color(130,130,130));
    prevBtn.setOrigin({prevBtn.getSize().x/2 , prevBtn.getSize().y/2});
    prevBtn.setPosition({125, 730});
    prevBtnBorder.setSize(Vector2f(145,55));
    prevBtnBorder.setFillColor(Color::Black);
    prevBtnBorder.setOrigin({prevBtnBorder.getSize().x/2 , prevBtnBorder.getSize().y/2});
    prevBtnBorder.setPosition({125, 730});
    Text tPrevBtn(font, "PREV", 40);
    tPrevBtn.setFillColor(Color::White);
    tPrevBtn.setOrigin({75, 20});
    tPrevBtn.setPosition({163, 725});

    // MENU button
    RectangleShape menuBtn, menuBtnBorder;
    menuBtn.setSize(Vector2f(300,40));
    menuBtn.setFillColor(Color(253,114,114));
    menuBtn.setOrigin({menuBtn.getSize().x/2 , menuBtn.getSize().y/2});
    menuBtn.setPosition({412, 730});
    menuBtnBorder.setSize(Vector2f(320,55));
    menuBtnBorder.setFillColor(Color::Red);
    menuBtnBorder.setOrigin({menuBtnBorder.getSize().x/2 , menuBtnBorder.getSize().y/2});
    menuBtnBorder.setPosition({412, 730});
    Text tMenuBtn(font, "MENU", 40);
    tMenuBtn.setFillColor(Color::White);
    tMenuBtn.setOrigin({75, 20});
    tMenuBtn.setPosition({440, 725});

    // NEXT button
    RectangleShape nextBtn, nextBtnBorder;
    nextBtn.setSize(Vector2f(125,40));
    nextBtn.setFillColor(Color(130,130,130));
    nextBtn.setOrigin({nextBtn.getSize().x/2 , nextBtn.getSize().y/2});
    nextBtn.setPosition({702, 730});
    nextBtnBorder.setSize(Vector2f(145,55));
    nextBtnBorder.setFillColor(Color::Black);
    nextBtnBorder.setOrigin({nextBtnBorder.getSize().x/2 , nextBtnBorder.getSize().y/2});
    nextBtnBorder.setPosition({702, 730});
    Text tNextBtn(font, "NEXT", 40);
    tNextBtn.setFillColor(Color::White);
    tNextBtn.setOrigin({75, 20});
    tNextBtn.setPosition({740, 725});

    // Pagination variables
    int actualPage = 1;
    int lastPage = (totalUsers + 9) / 10;
    int actualUser = actualPage * 10 - 9;
    int lastUserPage = actualPage * 10;

    // Vectors for each column of the leaderboard
    vector<Text> ranks;
    vector<Text> usernames;
    vector<Text> scores;
    vector<Text> dates;

    // Loop through users to display on the first page 
    for (int i = actualUser - 1; i < lastUserPage && i < totalUsers; ++i) {
        ScoreRecord& data = allUsers[i]; // Access the i-th user in the vector

        // Create rank text 
        Text rank(font, to_string(i + 1), 32);
        rank.setOrigin({150, 40});
        // Position vertically based on current page and index
        rank.setPosition({230, 270.0f + (i - (actualUser - 1)) * 45.0f});
        // Highlight the first place with gold color
        if (i == 0) {
            rank.setFillColor(Color(255, 215, 0)); 
        }
        ranks.push_back(rank);

        // Create username text
        Text username(font, data.name, 32);
        username.setOrigin({150, 40});
        username.setPosition({280, 270.0f + (i - (actualUser - 1)) * 45.0f});
        if (i == 0) {
            username.setFillColor(Color(255, 215, 0));
        }
        usernames.push_back(username);

        // Create score text
        Text score(font, to_string(data.score), 32);
        score.setOrigin({150, 40});
        score.setPosition({575, 270.0f + (i - (actualUser - 1)) * 45.0f});
        if (i == 0) {
            score.setFillColor(Color(255, 215, 0));
        }
        scores.push_back(score);

        // Format date as dd-mm-yyyy
        string dateText = to_string(data.dd) + "-" + to_string(data.mm) + "-" + to_string(data.aa);
        Text date(font, dateText, 32);
        date.setOrigin({150, 40});
        date.setPosition({775, 270.0f + (i - (actualUser - 1)) * 45.0f});
        if (i == 0) {
            date.setFillColor(Color(255, 215, 0));
        }
        dates.push_back(date);
    }

    // 0 = prev, 1 = menu, 2 = next
    int posAux = 1;
    bool needsUpdate = false; // Boolean flag that indicates if the leaderboard information needs to be updated
    bool enterPressed = false; // Boolean flag that prevents doble enter

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()){
                window.close();
            }   
            if(const auto*key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close(); // Close the window if Escape key is pressed
                    screenMenu();
                }
            }

            // If Right arrow is pressed and there is more than one page
            if (Keyboard::isKeyPressed(Keyboard::Key::Right) && lastPage != 1){
                if (actualPage == 1 && posAux==1){
                    posAux++; // Move selection to the next button if on first page and current button is 1
                    cout << posAux;
                } else if (actualPage == lastPage && posAux==0){
                    posAux++; // Move selection to the menu button if on last page and current button is 0 (prev)
                    cout << posAux; 
                } else if (posAux >= 0 && posAux < 2 && actualPage!=lastPage){
                    posAux++; // Move selection right for all other valid positions if not on the last page
                    cout << posAux;
                }
            }

            // If Left arrow is pressed and there is more than one page
            if (Keyboard::isKeyPressed(Keyboard::Key::Left) && lastPage != 1){
                if (actualPage == 1 && posAux == 2){
                    posAux--; // Move selection to the previous button if on first page and current button is 2 (next)
                    cout << posAux;
                } 
                else if (actualPage == lastPage && posAux == 1){
                    posAux--; // Move selection to the previous button if on last page and current button is 1 (menu)
                    cout << posAux;
                } 
                else if (posAux > 0 && posAux <= 2 && actualPage != 1){
                    posAux--; // Move selection left for all other valid positions if not on the first page
                    cout << posAux;
                }
            }

            switch(posAux) {
                case 0:
                    // PREV button selected
                    prevBtn.setFillColor(Color(253,114,114));
                    prevBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    menuBtn.setFillColor(Color(130,130,130));
                    menuBtnBorder.setFillColor(Color::Black);
                    nextBtn.setFillColor(Color(130,130,130));
                    nextBtnBorder.setFillColor(Color::Black);

                    // If enter is pressed the page goes back and it needs update
                    if (const auto *key = event->getIf<Event::KeyPressed>()) {
                        if (key->scancode == Keyboard::Scancode::Enter){
                            if (!enterPressed && actualPage > 1) {
                                actualPage--;
                                needsUpdate = true;
                                enterPressed = true;
                            }
                        }
                    } else enterPressed = false;
                    
                    break;

                case 1:
                    // menu button selected
                    menuBtn.setFillColor(Color(253,114,114));
                    menuBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    prevBtn.setFillColor(Color(130,130,130));
                    prevBtnBorder.setFillColor(Color::Black);
                    nextBtn.setFillColor(Color(130,130,130));
                    nextBtnBorder.setFillColor(Color::Black);

                    // if enter is pressed the screen changes to the menu
                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){
                            window.close();
                            screenMenu();
                        }
                    }
                    break;

                case 2:
                    // NEXT button selected
                    nextBtn.setFillColor(Color(253,114,114));
                    nextBtnBorder.setFillColor(Color::Red);

                    // rest stay default
                    prevBtn.setFillColor(Color(130,130,130));
                    prevBtnBorder.setFillColor(Color::Black);
                    menuBtn.setFillColor(Color(130,130,130));
                    menuBtnBorder.setFillColor(Color::Black);

                    // if enter is pressed the pages goes forward and it needs update
                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){
                            if (!enterPressed && actualPage < lastPage) {
                                actualPage++;
                                needsUpdate = true;
                                enterPressed = true;
                            }
                        } 
                    } else enterPressed = false;
                    break;
            }

        }   

        // depending on the page, these calculate what is gonna be the first and last player in the leadb
        actualUser = actualPage*10-9;
        lastUserPage = actualPage*10;

        if (needsUpdate) {
            // Clear previous texts to update with new page data
            ranks.clear();
            usernames.clear();
            scores.clear();
            dates.clear();

            for (int i = actualUser - 1; i < lastUserPage && i < totalUsers; ++i) {
                ScoreRecord& data = allUsers[i]; // Get user data from vector

                // Create rank text 
                Text rank(font, to_string(i + 1), 32);
                rank.setOrigin({150, 40});
                rank.setPosition({230, 270.0f + (i - (actualUser - 1)) * 45.0f});
                // Highlight first place with gold color
                if (i == 0) {
                    rank.setFillColor(Color(255, 215, 0));
                }
                ranks.push_back(rank);

                // Create username text
                Text username(font, data.name, 32);
                username.setOrigin({150, 40});
                username.setPosition({280, 270.0f + (i - (actualUser - 1)) * 45.0f});
                if (i == 0) {
                    username.setFillColor(Color(255, 215, 0));
                }
                usernames.push_back(username);

                // Create score text
                Text score(font, to_string(data.score), 32);
                score.setOrigin({150, 40});
                score.setPosition({575, 270.0f + (i - (actualUser - 1)) * 45.0f});
                if (i == 0) {
                    score.setFillColor(Color(255, 215, 0));
                }
                scores.push_back(score);

                // Format date as dd-mm-yyyy
                string dateText = to_string(data.dd) + "-" + to_string(data.mm) + "-" + to_string(data.aa);
                Text date(font, dateText, 32);
                date.setOrigin({150, 40});
                date.setPosition({775, 270.0f + (i - (actualUser - 1)) * 45.0f});
                if (i == 0) {
                    date.setFillColor(Color(255, 215, 0));
                }
                dates.push_back(date);
            }

            needsUpdate = false;
        }


        window.clear(Color::Black); // clear the window to draw the next frame
        window.draw(backgSprite);

        // draw stuff here
        window.draw(title);
        window.draw(margin);
        window.draw(headerRow);

        // for loops that iterate through the row vector and draw them
        for (const auto& row : rows) {
            window.draw(row);
        }
        window.draw(rank);
        window.draw(user);
        window.draw(score);
        window.draw(date);

        // for loops that iterate through the text vectors and draw them
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

        // if is the first page the prev button doesnt appear
        if (actualPage != 1){
            window.draw(prevBtnBorder);
            window.draw(prevBtn);
            window.draw(tPrevBtn);
        }

        window.draw(menuBtnBorder);
        window.draw(menuBtn);
        window.draw(tMenuBtn); 

        // if is the last page the next button doesnt appear
        if (actualPage != lastPage){  
            window.draw(nextBtnBorder);
            window.draw(nextBtn);
            window.draw(tNextBtn);
        }

        // show what was drawn
        window.display();
    }
}