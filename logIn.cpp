// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

void screenLogIn(){
    RenderWindow window(sf::VideoMode({825, 800}), "Fabulous Fred!");
    
    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // background
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/back2.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    // home white icon
    Texture homeWTexture;
    if (!homeWTexture.loadFromFile("assets/home-icon-white.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite homeWSprite(homeWTexture); 
    homeWSprite.setPosition({740,725});

    // home black icon
    Texture homeBTexture;
    if (!homeBTexture.loadFromFile("assets/home-icon-black.png")) {
        cout << "Image couldnt be loaded" << endl;
    }
    Sprite homeBSprite(homeBTexture); 
    homeBSprite.setPosition({740,725});

    // 0 username, 1 password, 2 button, 3 home button
    int posAux{0};

    // declarations
    Font font("assets/BurbankBigCondensed-Black.otf");
    Text tTitle(font, "LOG IN", 90);
    Text tUsername(font, "USERNAME", 30);
    Text tPass(font, "PASSWORD", 30);
    Text tWarnings(font, "SPECIAL CHARACTERS NOT ALLOWED!", 30);
    Text tWarningPass(font, "", 30);
    Text tButtonLI(font, "LOG IN", 50);
    
    sf::String concatUser(""); // concat strings are useful to simulate a text input
    sf::String concatPass("");
    Text inpUsername(font, "", 50);
    Text inpPass(font, "", 50);
    RectangleShape buttSub(Vector2f{350, 75});
    RectangleShape buttSubBorder(Vector2f{370, 90});
    
    // colors
    tTitle.setFillColor(Color::White);
    tUsername.setFillColor(Color::White);
    tPass.setFillColor(Color::White);
    tWarnings.setFillColor(Color::Transparent);
    tWarningPass.setFillColor(Color::Transparent);
    tButtonLI.setFillColor(Color::White);

    inpUsername.setFillColor(Color(155, 160, 182)); // light blue
    inpPass.setFillColor(Color(155, 160, 182));
    buttSub.setFillColor(Color(130,130,130)); 
    buttSubBorder.setFillColor(Color::Transparent);
    
    // origins
    tTitle.setOrigin({100, 40});
    tUsername.setOrigin({65, 17});
    tPass.setOrigin({65, 17});
    tWarnings.setOrigin({65, 17});
    tWarningPass.setOrigin({65, 17});
    tButtonLI.setOrigin({75, 20});

    inpUsername.setOrigin({75,20});
    inpPass.setOrigin({75,20});
    buttSub.setOrigin({(buttSub.getSize().x)/2 , (buttSub.getSize().y)/2});
    buttSubBorder.setOrigin({(buttSubBorder.getSize().x)/2 , (buttSubBorder.getSize().y)/2});

    // position
    tTitle.setPosition({410, 125});
    tUsername.setPosition({190, 240}); 
    tPass.setPosition({190, 400});
    tWarnings.setPosition({100, 720});
    tWarningPass.setPosition({100, 760});
    tButtonLI.setPosition({850/2, 560});

    inpUsername.setPosition({215, 290});
    inpPass.setPosition({215, 450});
    buttSub.setPosition({825/2, 575});
    buttSubBorder.setPosition({825/2, 575});

    // create multiple rectangles with equal properties using a vector of rectangles
    vector<RectangleShape> inpBoxes; // input boxes
    for (int i = 0; i<2; i++){
        RectangleShape inpBox;
        inpBox.setSize(Vector2f({565, 75}));
        inpBox.setFillColor(Color(19, 20, 40));
        inpBox.setOrigin({(inpBox.getSize().x) / 2, (inpBox.getSize().y) / 2});
        inpBox.setPosition({825/2, 300.f + i * 160.f});
        inpBoxes.push_back(inpBox);
    }
    
    // create multiple rectangle borders with equal properties using a vector of rectangles
    vector<RectangleShape> inpBoxesBorder; // white border 
    for (int i = 0; i<2; i++){
        RectangleShape inpBoxBor;
        inpBoxBor.setSize(Vector2f({570, 80}));
        inpBoxBor.setFillColor(Color::White);
        inpBoxBor.setOrigin({(inpBoxBor.getSize().x) / 2, (inpBoxBor.getSize().y) / 2});
        inpBoxBor.setPosition({825/2, 300.f + i * 160.f});
        inpBoxesBorder.push_back(inpBoxBor);
    }

    // flag used for showing a image that is used as a menu button
    bool homeIconHover = false;

    // main loop
    while (window.isOpen())
    {   
        // events loop
        while (const std::optional event = window.pollEvent())
        {   
            if (event->is<sf::Event::Closed>()){
                window.close(); 
            } else if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close(); // if the escape key is pressed, the actual window closes and goes one back
                    screenMainMenu();
                }
            }

            // set a range to manipulate the menu
            if (posAux >= 0 && posAux<3){
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    cout << posAux;
                }
            }
            if (posAux>0 && posAux<=3){
                if (Keyboard:: isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                    cout << posAux;
                }
            }
            
            // simulate the menu by switching classes colors
            switch(posAux){
                case 0:
                    tUsername.setFillColor(Color(102, 179, 255));
                    tPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpUsername, event.value(), concatUser, tWarnings); // function setInputValues sends the original variable, a copy of the events, a variable to concat
                    homeIconHover = false;                              // everything that it's being writed and a text used for showing warnings while inputting the username or password
                    break;
                case 1:
                    tPass.setFillColor(Color(102, 179, 255));
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpPass, event.value(), concatPass, tWarnings);
                    homeIconHover = false;
                    break;
                case 2:
                    tUsername.setFillColor(Color::White);
                    tPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Red);
                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){ // if the user press enter, evaluate if the input of the password and user are smaller than 8 characters
                            if (inpPass.getString().getSize()<8 || inpUsername.getString().getSize()<8){ 
                                tWarningPass.setString("USERNAME / PASSWORD MUST BE AT LEAST 8 CHARACTERS");
                                tWarningPass.setFillColor(Color::Yellow);
                            } else{  // if they are longer than 8 characters, the function isValidUser is called with the passord and username input to check if its a real user
                                if (isValidUser(inpUsername, inpPass)){
                                    window.close(); // if it is a real user, closes de windows and goes to the next screen
                                    screenMenu();
                                } else{
                                    tWarningPass.setString("LOGIN FAILED. VERIFY YOUR INFORMATION AND TRY AGAIN"); // not a real user, show a warning
                                    tWarningPass.setFillColor(Color::Yellow); // warning in yellow
                                }
                            }
                        }
                    }
                    homeIconHover = false; // flag for the house icon that works as a go back button
                    break;
                case 3:
                    tUsername.setFillColor(Color::White);
                    tPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    homeIconHover = true;
                    if (const auto* key = event->getIf<Event::KeyPressed>()){ // go back button
                        if (key->scancode == Keyboard::Scancode::Enter){
                            window.close(); 
                            screenMainMenu();
                        }
                    }
            }

            if (!inpUsername.getString().isEmpty() && !inpPass.getString().isEmpty()){ // if all the inputs have information, switch the button to color red
                buttSub.setFillColor(Color(253,114,114));
            } else{
                buttSub.setFillColor(Color(130,130,130)); // if not, gray
            }
        }   
        
        // show everything on screen
        window.clear();
        window.draw(backgSprite);
        window.draw(tTitle);
        for (const auto & inpBoxBor : inpBoxesBorder){
            window.draw(inpBoxBor);
        }   
        for (const auto & inpBox : inpBoxes){
            window.draw(inpBox);
        }   
        window.draw(tUsername);
        window.draw(tPass);
        window.draw(inpUsername);
        window.draw(inpPass);
        window.draw(tWarnings);
        window.draw(tWarningPass);
        window.draw(buttSubBorder);
        window.draw(buttSub);
        window.draw(tButtonLI);

        if (homeIconHover){
            window.draw(homeBSprite);
        } else {
            window.draw(homeWSprite);
        }
        
        window.display();
    }
}

// this function receives the input from the username and password, opens a users.dat file and starts comparing line by line if the user exist and it has the same input password
bool isValidUser(sf::Text inpUsername, sf::Text inpPass){
    User checkUser;
    FILE *users;
    bool found = false;
    users = fopen("users.dat", "rb");
    if (users==NULL){
        cout << "Error while opening users.dat (logIn)" << endl;
    }

    while (fread(&checkUser, sizeof(User), 1, users)){ // read file, search username and compare
        if ((strcmp(inpUsername.getString().toAnsiString().c_str(), checkUser.username)==0) && // compare username
            (strcmp(inpPass.getString().toAnsiString().c_str(), checkUser.password)==0)) // compare password
            {
                cout << "usuarios correctos" << endl;
                
                // copy the data of the user and set it as a global variable so we can access it from all the files
                // the variable is declared as extern in the header.hpp and the original declaration is on main because the program compiles all files on main
                currentUser.idUser = checkUser.idUser;
                strcpy(currentUser.username, checkUser.password);
                strcpy(currentUser.username, checkUser.password);
                currentUser.nGames = checkUser.nGames;
                
                fclose(users); // close file
                return true; // if the user exists returns true
        } 

    }
    fclose(users); // close file
    return false; // if the user doesn't exist returns false
}