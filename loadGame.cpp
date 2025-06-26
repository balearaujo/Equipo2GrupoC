// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "header.hpp"
using namespace std;
using namespace sf;

void screenLoadGame(){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!"); // creates the 825x800 window

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // BACKGROUND 
    // texture store the image data 
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/backg.png")) {
        cout << "Image couldnt be loaded" << endl;
        return;
    }
    
    // get data to load game as size of the board, user points, the sequence of the game, the size of the numbers of the sequence
    bool canLoad{false};
    cout << "\nGame\n";
    std::string lastGame = ""; 
    int size{0};
    int points{0};
    int sequenceSize{0};
    int *sequence = new int[50];
    canLoad = checkGame(lastGame, size, points, sequence, sequenceSize); // calls the function to check if the user has a game to load
    cout << lastGame;
    cout << "\nSize " << size << "  points " << points;

    // sprite is a image that gets drawn in the screen
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    // TITLE
    Font font("assets/BurbankBigCondensed-Black.otf"); // load the font
    Text title(font, "LOAD GAME", 100); // declare the text, its font, content and size
    title.setOrigin({170,40}); // manually set origin for positioning
    title.setPosition({790/2, 110}); 

    // YES BUTTON
    RectangleShape btnYes;
    btnYes.setSize(Vector2f(240, 100));
    btnYes.setFillColor(Color(253,114,114));
    btnYes.setOrigin({(btnYes.getSize().x)/2 , (btnYes.getSize().y)/2});
    btnYes.setPosition({260, 630}); // x,y

    RectangleShape btnYesBorder;
    btnYesBorder.setSize(Vector2f(250,110));
    btnYesBorder.setFillColor(Color::Red);
    btnYesBorder.setOrigin({(btnYesBorder.getSize().x)/2 , (btnYesBorder.getSize().y)/2});
    btnYesBorder.setPosition({260, 630}); // x,y

    Text tYes(font, "YES", 70);
    tYes.setFillColor(Color::White);
    tYes.setOrigin({75, 20});
    tYes.setPosition({285, 605});

    // NO BUTTON
    RectangleShape btnNo;
    btnNo.setSize(Vector2f(240, 100));
    btnNo.setFillColor(Color(253,114,114));
    btnNo.setOrigin({(btnNo.getSize().x)/2 , (btnNo.getSize().y)/2});
    btnNo.setPosition({570, 630}); // x,y

    RectangleShape btnNoBorder;
    btnNoBorder.setSize(Vector2f(250,110));
    btnNoBorder.setFillColor(Color::Red);
    btnNoBorder.setOrigin({(btnNoBorder.getSize().x)/2 , (btnNoBorder.getSize().y)/2});
    btnNoBorder.setPosition({570, 630}); // x,y

    Text tNo(font, "NO", 70);
    tNo.setFillColor(Color::White);
    tNo.setOrigin({75, 20});
    tNo.setPosition({610, 605});

    // load game infomation
    RectangleShape recInfo;
    recInfo.setSize(Vector2f(450, 250));
    recInfo.setFillColor(Color(0,0,0,190));
    recInfo.setOrigin({(recInfo.getSize().x)/2 , (recInfo.getSize().y)/2});
    recInfo.setPosition({825/2, 380}); // x,y

    RectangleShape recInfoBorder;
    recInfoBorder.setSize(Vector2f(460,260));
    recInfoBorder.setFillColor(Color::White);
    recInfoBorder.setOrigin({(recInfoBorder.getSize().x)/2 , (recInfoBorder.getSize().y)/2});
    recInfoBorder.setPosition({825/2, 380}); // x,y

    Text recInfoPoints(font, "SCORE: "+to_string(points), 60);
    recInfoPoints.setFillColor(Color::White);
    recInfoPoints.setOrigin({85, 23});
    recInfoPoints.setPosition({295, 285});

    Text recInfoSize(font, string("DIFFICULTY: ") + (size == 9 ? "HARD" : "EASY"), 60);
    recInfoSize.setFillColor(Color::White);
    recInfoSize.setOrigin({85, 23});
    recInfoSize.setPosition({295, 355});

    Text recInfoStatus(font, "GAME PAUSED", 60);
    recInfoStatus.setFillColor(Color::White);
    recInfoStatus.setOrigin({85, 23});
    recInfoStatus.setPosition({295, 425});
    
    // can't load text
    Text tCantLoad(font, " You don't have a game\n to load.\n\n Try starting a new one!", 70);
    tCantLoad.setLineSpacing(0.8);
    tCantLoad.setFillColor(Color::White);
    tCantLoad.setOrigin({75, 20});
    tCantLoad.setPosition({180, 230});


    // pause menu
    RectangleShape bgMenu(Vector2f{650 , 700});
    bgMenu.setFillColor(Color(20,20,40));
    bgMenu.setOrigin({bgMenu.getSize().x/2, bgMenu.getSize().y/2});
    bgMenu.setPosition({825/2, 800/2});

    RectangleShape bgMenuBorder(Vector2f{660 , 710});
    bgMenuBorder.setFillColor(Color::White);
    bgMenuBorder.setOrigin({bgMenuBorder.getSize().x/2, bgMenuBorder.getSize().y/2});
    bgMenuBorder.setPosition({825/2, 800/2});

    // home black icon
    Texture homeBTexture;
    if (!homeBTexture.loadFromFile("assets/home-icon-black.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite homeBSprite(homeBTexture); 
    homeBSprite.setPosition({675,675});
    bool homeIconHover = false; // boolean used for a change of icon if the home button is selected

    int posAux{0};
        // Main loop
    while (window.isOpen()) {
        // events loop
        while (const optional event = window.pollEvent()){ // check and handle window events
            if (event->is<sf::Event::Closed>()) // check if the event was closing the window
                window.close();

            // if escape is pressed the screen returns to the main menu
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){ 
                    window.close();
                    screenMenu();
                }
            }

            // if enter key is pressed
            if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Enter){
                    cout << posAux;
                    if (canLoad){ // if the user has a game to load 
                        switch(posAux){ 
                            case 0: // case 0, yes button, load game with the variables obtained calling screenGame() function
                                window.close();
                                screenGame(points, size, sequence, sequenceSize, true);
                                break;
                
                            case 1: // case 1, no button, close window and go back to the menu
                                window.close();
                                screenMenu();
                                break;
                        }
                    } else { // if the user can't load any games and presses enter, window closes and goes back to the menu
                        window.close(); 
                        screenMenu();
                    }
                }
            }

        }
        // draw the basic classes
        window.clear(Color::Black);
        window.draw(backgSprite);
        window.draw(bgMenuBorder);
        window.draw(bgMenu);
        window.draw(title);

        if (canLoad){ // if the user can load a game
            homeIconHover = false;
            // set a range to handle the buttons
            if (posAux>= 0 && posAux<1){
                if (Keyboard::isKeyPressed(Keyboard::Key::Right)){
                    posAux++;
                }
            }    
            if (posAux> 0 && posAux<=1){
                if (Keyboard::isKeyPressed(Keyboard::Key::Left)){
                    posAux--;
                }
            }
    
            switch(posAux){ // change colors depending on the position
                case 0:
                    btnYes.setFillColor(Color(253,114,114));
                    btnYesBorder.setFillColor(Color::Red);
                    btnNo.setFillColor(Color(130,130,130));
                    btnNoBorder.setFillColor(Color::Transparent);
                    break;
    
                case 1:
                    btnNo.setFillColor(Color(253,114,114));
                    btnNoBorder.setFillColor(Color::Red);
                    btnYes.setFillColor(Color(130,130,130));
                    btnYesBorder.setFillColor(Color::Transparent);
                    break;
            }
            
            // draw the classes needed when the user can load
            window.draw(btnYesBorder);
            window.draw(btnYes);
            window.draw(tYes);
            window.draw(btnNoBorder);
            window.draw(btnNo);
            window.draw(tNo);
            window.draw(recInfoBorder);
            window.draw(recInfo);
            window.draw(recInfoPoints);
            window.draw(recInfoSize);
            window.draw(recInfoStatus);
        } else{
            // classes needed when he can't load 
            window.draw(tCantLoad);
            window.draw(homeBSprite);
        }

        // show what was drawn
        window.display();
    }
}

// function checkGame uses only strings and files, they are opened with ifstream and ofstream for more convenient operation, the main point of this function is getting all the data needed
// to start a paused game, like the size of the board, the points of the user, the sequence of the game, with this information we can start a game from the last paused position, it functions
// first substracting the last game of the user, then it extracts information separated by commas, from the 4th to 5th comma is the game state, 3rd to 4th is the score, 2nd to 3rd is the board 
// size, and everything after the last comma is the array of illuminated positions during gameplay.
bool checkGame(std::string& lastGame, int& size, int& points, int *sequence, int& sequenceSize){
    ifstream games("games.txt"); // open games.txt in reading mode
    std::string line; // line of text
    std::string getState;
    std::string getPoints;
    std::string getSize;
    std::string getArray;
    int pos{0};
    while (getline(games, line)){ // read the file line by ine
        if (line.substr(0, line.find("/")) == to_string(currentUser.idUser)){ // check the user id, the format writed for every user in the file is ID/[idGame,date,size,points,state,(pos)]
            int opening = line.find_last_of("[");                           // so the line gets substracted until it finds a "/", and then is compared to the current global user id
            int closing = line.find_last_of("]"); // finds the position of the last [ ]
            lastGame = line.substr(opening, closing-opening+1); // sets the string from the opening to the closing bracket
            getState = lastGame; // asigns the same string
            getPoints = lastGame; // asigns the same string
            getSize = lastGame; // asigns the same string
            int aux{0};
            while (aux!=4){ // aux 4 because we are looking for the 4th comma 
                getState = getState.substr(getState.find_first_of(",")+1, getState.npos); // we substract a smaller string every iteration
                if (aux<3){ // looking for the 3rd comma
                    getPoints = getPoints.substr(getPoints.find_first_of(",")+1, getPoints.npos);                    
                }
                if (aux<2){ // 2nd comma
                    getSize = getSize.substr(getSize.find_first_of(",")+1, getSize.npos);
                }
                aux++;
            }
            int startBr = lastGame.find_first_of("(");
            int endBr = lastGame.find_first_of(")")-1;
            getArray = lastGame.substr(startBr+1, endBr-startBr); // the same process for the array, it looks for the pair of ( ) and substracts between them
            // cout << "Array: " << getArray << endl;
            int posAux{0};
            if (!getArray.empty()){ // if the array is not empty
                for (char c : getArray){ // iterate in all characters of the array
                    if (c == ',') continue; // if its a comma, continue
                    else {
                        sequence[posAux] = c - '0'; // if not, get the ascii of the number and put it on a vector
                        posAux++;
                    }
                }   
            }
            sequenceSize = posAux;
            // cout << "sequence" << endl;
            // for (int i=0; i<posAux; i++){
            //     cout << sequence[i] << " ";
            // }
            // cout << endl;
            getState = getState.substr(0, 1);
            getSize = getSize.substr(0, 1); // at the end of the substractions, we only get the information that we need without symbols 
            getPoints = getPoints.substr(0, getPoints.find_first_of(","));
            size = stoi(getSize); // convert string to int
            points = stoi(getPoints); // string to int 
            if (stoi(getState) == 3){ // if the state is 3 (state 3 means gamePaused)
                return true; // return true, this means that the user has a game to load
            }
        }
    }
    return false; // return false if the user doesn't have a game to load
}