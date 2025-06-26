// Erick Fernando Perez Cruz ID: 549923
// Valeria Alejandra Araujo Martinez ID: 340195
// Angel Ricardo Gonzalez Soto ID: 551990

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "header.hpp"
using namespace sf;
using namespace std;

void screenSignUp(){
    RenderWindow window(VideoMode({825, 800}), "Fabulous Fred!");

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // background
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/back.png")) {
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


    // 0 = username, 1 = password, 2 = confirm password, 3 = sign up button, 4 home button
    int posAux{0};  
    bool homeIconHover = false;
    
    // declaration
    Font font("assets/BurbankBigCondensed-Black.otf");
    Text tTitle(font, "SIGN UP", 90);
    Text tUsername(font, "USERNAME", 30);
    Text tPass(font, "PASSWORD", 30);
    Text tConfPass(font, "CONFIRM PASSWORD", 30);
    Text tWarnings(font, "SPECIAL CHARACTERS NOT ALLOWED!", 30);
    Text tWarningPass(font, "", 30);
    Text tButtonSU(font, "SIGN UP", 50);
    
    sf::String concatUser(""); // strings used for concatenate keyboard inputs
    sf::String concatPass("");
    sf::String concatConfPass("");
    Text inpUsername(font, "", 50);
    Text inpPass(font, "", 50);
    Text inpConfPass(font, "", 50);
    
    RectangleShape buttSub(Vector2f{350, 75});
    RectangleShape buttSubBorder(Vector2f{370, 90});

    // colors
    tTitle.setFillColor(Color::White);
    tUsername.setFillColor(Color::White);
    tPass.setFillColor(Color::White);
    tConfPass.setFillColor(Color::White);
    tWarnings.setFillColor(Color::Transparent);
    tWarningPass.setFillColor(Color::Transparent);
    tButtonSU.setFillColor(Color::White);

    inpUsername.setFillColor(Color(155, 160, 182)); // light blue
    inpPass.setFillColor(Color(155, 160, 182));
    inpConfPass.setFillColor(Color(155, 160, 182));
    buttSub.setFillColor(Color(89, 111, 173)); 
    buttSubBorder.setFillColor(Color::Transparent);
    

    // origins
    tTitle.setOrigin({100, 40});
    tUsername.setOrigin({65, 17});
    tPass.setOrigin({65, 17});
    tConfPass.setOrigin({65, 17});
    tWarnings.setOrigin({65, 17});
    tWarningPass.setOrigin({65, 17});
    tButtonSU.setOrigin({75, 20});
    
    inpUsername.setOrigin({75,20});
    inpPass.setOrigin({75,20});
    inpConfPass.setOrigin({75,20});
    buttSub.setOrigin({(buttSub.getSize().x)/2 , (buttSub.getSize().y)/2});
    buttSubBorder.setOrigin({(buttSubBorder.getSize().x)/2 , (buttSubBorder.getSize().y)/2});
    

    // positions
    tTitle.setPosition({380, 110});
    tUsername.setPosition({190, 205}); 
    tPass.setPosition({190, 340});
    tConfPass.setPosition({190, 475});
    tWarnings.setPosition({100, 720});
    tWarningPass.setPosition({100, 760});
    tButtonSU.setPosition({825/2, 635});

    inpUsername.setPosition({215, 255});
    inpPass.setPosition({215, 390});
    inpConfPass.setPosition({215, 525});
    buttSub.setPosition({825/2, 650});
    buttSubBorder.setPosition({825/2, 650});

    // create multiple rectangles with equal properties using a vector of rectangles
    vector<RectangleShape> inpBoxes; // boxes
    for (int i = 0; i<3; i++){
        RectangleShape inpBox;
        inpBox.setSize(Vector2f({565, 75}));
        inpBox.setFillColor(Color(19, 20, 40));
        inpBox.setOrigin({(inpBox.getSize().x) / 2, (inpBox.getSize().y) / 2});
        inpBox.setPosition({825/2, 265.f + i * 135.f});
        inpBoxes.push_back(inpBox);
    }

    // create multiple rectangles with equal properties using a vector of rectangles
    vector<RectangleShape> inpBoxesBorder; // border
    for (int i = 0; i<3; i++){
        RectangleShape inpBoxBor;
        inpBoxBor.setSize(Vector2f({570, 80}));
        inpBoxBor.setFillColor(Color::White);
        inpBoxBor.setOrigin({(inpBoxBor.getSize().x) / 2, (inpBoxBor.getSize().y) / 2});
        inpBoxBor.setPosition({825/2, 265.f + i * 135.f});
        inpBoxesBorder.push_back(inpBoxBor);
    }


    // MAIN WINDOW
    while (window.isOpen()){
        // events loop
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close(); // close window
            } else if (const auto* key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close(); // escape pressed, go back to the lst screen
                    screenMainMenu();
                }
            }
            // adjust posAux to handle "input" textbox
            if (posAux>=0 && posAux<4){ // posAux between 0-3
                if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                    posAux++;
                    cout << posAux;
                }
            }

            if (posAux>0 && posAux<=4){ // posAux between 1-4
                if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                    posAux--;
                    cout << posAux;
                }
            }
            
            switch(posAux){ // change colors depending on the position, call function setInputValue to grab typed characters
                case 0:
                    // posAux = 0, username 
                    tUsername.setFillColor(Color(102, 179, 255));
                    tPass.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpUsername, event.value(), concatUser, tWarnings);
                    homeIconHover = false;
                    break;
        
                case 1:
                    // posAux = 1, password
                    tPass.setFillColor(Color(102, 179, 255)); // dark blue
                    tUsername.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpPass, event.value(), concatPass, tWarnings);
                    homeIconHover = false;
                    break;
            
                case 2:
                    // posAux = 2, confirm password
                    tConfPass.setFillColor(Color(102, 179, 255));
                    tPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    setInputValues(inpConfPass, event.value(), concatConfPass, tWarnings);
                    homeIconHover = false;
                    break;
                
                case 3:
                    // posAux = 3, button
                    tConfPass.setFillColor(Color::White);
                    tPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Red);

                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){ // if enter is pressed
                            if (checkUsername(inpUsername)){ // check if the username is available calling checkUsername()
                                if (checkPassword(inpPass, inpConfPass)){ // convert sf strings to std string and compare
                                    tWarningPass.setString("PASSWORDS MUST MATCH!");  // warning if they are diferent
                                    tWarningPass.setFillColor(Color::Yellow);
                                } else{
                                    if (inpPass.getString().getSize()<8 || inpUsername.getString().getSize()<8){ // check if the input is larger than 8 characters
                                        tWarningPass.setString("USERNAME / PASSWORD MUST BE AT LEAST 8 CHARACTERS");
                                        tWarningPass.setFillColor(Color::Yellow);
                                    } else{ 
                                        tWarningPass.setFillColor(Color::Transparent); // if the user is available and both of the passwords are the same
                                        writeUser(inpUsername, inpPass); // write user into a binary file
                                        cout << "User " << inpUsername.getString().toAnsiString() << " writed "; // debug
                                        window.close(); // close window
                                        screenMainMenu(); // go to the next window
                                    }
                                }   
                            } else{ // username not available
                                tWarningPass.setString("USERNAME NOT AVAILABLE!"); // warning
                                tWarningPass.setFillColor(Color::Yellow);
                            }
                        }
                    }
                    homeIconHover = false;
                    break;

                case 4:
                    tPass.setFillColor(Color::White);
                    tConfPass.setFillColor(Color::White);
                    tUsername.setFillColor(Color::White);
                    buttSubBorder.setFillColor(Color::Transparent);
                    if (const auto* key = event->getIf<Event::KeyPressed>()){
                        if (key->scancode == Keyboard::Scancode::Enter){ // house icon that works as a go back button
                            window.close();
                            screenMainMenu();
                        }
                    }
                    homeIconHover = true;
                    break;
            }
    
            if (!(inpUsername.getString().isEmpty()) && !(inpPass.getString().isEmpty()) && !(inpConfPass.getString().isEmpty())){ 
                buttSub.setFillColor(Color(253,114,114)); // if all the inputs have information, switch the button to color red
            } else {
                buttSub.setFillColor(Color(130,130,130)); // if not, gray
            }

        }
        
        // show everything on screen
        window.clear(Color::Black);
        window.draw(backgSprite);
        window.draw(tTitle);
        for (const auto& inpBoxBor : inpBoxesBorder){
            window.draw(inpBoxBor);
        }
        for (const auto& inpBox : inpBoxes){
            window.draw(inpBox);
        }
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

        if (homeIconHover){
            window.draw(homeBSprite);
        } else {
            window.draw(homeWSprite);
        }

        window.display();
    }
}

// setInputValues function receives the original variable to input, the event queue, a string used for concatenation and a text to show warnings
void setInputValues(sf::Text &variable, const sf::Event &event, sf::String &concatAux, sf::Text &tWarnings){
    // getIf returns a pointer to a constant because the content from the TextEntered event is read-only
    // That is, getIf passes the text in "read" mode to typedText and it gets concatenated into concatAux
    // Then, the concatenated string is assigned to the input variable
    if (const sf::Event::TextEntered *typedText = event.getIf<Event::TextEntered>()){
        if (typedText->unicode < 128){ // checks if the typed text is lower than 128 in unicode, that means, special characters, letters, symbols and numbers
            if (typedText->unicode == 32 || typedText->unicode > 127 || (typedText->unicode < 32 && typedText->unicode != 8)){ 
                cout << "special character "; // check if its a special character, the cout is just for debugging
                tWarnings.setFillColor(Color::Yellow);  // show the warning on screen 
            } else{
                if (variable.getString().getSize()<16){ // if the variable is smaller than 16 characters
                    if (typedText->unicode!=8){ // if the typed character isn't backspace (8 = backspace)
                        concatAux += typedText->unicode; // concatenate the input character into the concat variable
                    }
                }
                // verify if the key pressed is backspace and check if the string has one or more characters
                if (concatAux.getSize()>0 && Keyboard::isKeyPressed(Keyboard::Key::Backspace)){ 
                    // deletes the position n-1
                    concatAux.erase(concatAux.getSize()-1, 1);
                }
                variable.setString(concatAux); // concatenate the original variable with the input character
                cout << variable.getString().toAnsiString(); // debug
                tWarnings.setFillColor(Color::Transparent);  // if nothing is wrong, set the warnings color transparent
            }
        }
    }
}

// the function checkUsername receives the input username then it opens a file and compares each line to check whether the username already exists
bool checkUsername(sf::Text inpUsername){ 
    FILE *users = fopen("users.dat", "ab+"); // open file
    User userRecord;
    if (users == NULL){ 
        cout << "Error while opening users.dat";
        return false;
    }
    while (fread(&userRecord, sizeof(User), 1, users)){ // search username in the file
        if (strcmp(inpUsername.getString().toAnsiString().c_str(), userRecord.username)==0){
            fclose(users);
            return false; // if the user is found, close the file and return false
        }
    }
    fclose(users); // if the user is not found, the username is available and returns true
    return true;
}

// checkPassword converts a sf::Text into a std::string and compares if they are the same.
bool checkPassword(sf::Text inpPass, sf::Text inpConfPass){
    return (inpPass.getString().toAnsiString().compare(inpConfPass.getString().toAnsiString()));
}

// when all the inputs are validated, writeUser is called, it writes in a file the username, password, number of games played and assigns one id.
void writeUser(sf::Text inpUsername, sf::Text inpPass){
    User newUser;
    int id;
    FILE *users = fopen("users.dat", "ab+"); // open file
    if (users==NULL){
        cout << "Error while opening users.dat";
        return;
    }
    id = assignID(users); // call assignID function
    newUser.idUser = id; // copy all the inputs in a struct
    strcpy(newUser.username , inpUsername.getString().toAnsiString().c_str());
    strcpy(newUser.password, inpPass.getString().toAnsiString().c_str());
    newUser.nGames = 0;
    fwrite(&newUser, sizeof(User), 1, users); // write the struct in the file 
    fclose(users); // close file
}

// assignID function is a simple operation, first it sends the cursor of the file all the way to the bottom with fseek SEEK_END, then in a unsigned int variable (unsigned int means
// it doesn't use negative numbers) with ftell return the size of the file (because the cursor is at the end) in bytes, then it divides the number of bytes by the size of the User struct
// so it gives the number of users in the file, then it rewinds the cursor to the start of the file.
int assignID(FILE *users){ 
    unsigned int fileSize; 
    int idUs;
    fseek(users, 0, SEEK_END); // go to the end of the file
    fileSize = ftell(users); // return size in bytes
    idUs = fileSize / sizeof(User); // total users
    rewind(users);
    return ++idUs; // returns id n+1
}
