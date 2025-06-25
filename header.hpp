#ifndef HEADER_HPP
#define HEADER_HPP

struct User{
    int idUser;
    char username[16];
    char password[16];
    int nGames;
};

extern User currentUser; // struct with extern because its declared in main.cpp

// signUp.cpp funciones
void screenSignUp();
void setInputValues(sf::Text &, const sf::Event &, sf::String &, sf::Text &);
bool checkUsername(sf::Text);
bool checkPassword(sf::Text, sf::Text);
void writeUser(sf::Text, sf::Text);
int assignID(FILE *);



// logIn.cpp
void screenLogIn();
bool isValidUser(sf::Text, sf::Text);


// menu.cpp
void screenMenu();


// leaderboard.cpp
void screenLeaderboard();


// difficulty.cpp
void screenSelectDifficulty();

            
// main.cpp
void screenMainMenu();



// game.cpp
enum States{showingSequence, userTurn, End}; // global enum 
void screenGame(int);
void saveGame(int *, int, States, int);

#endif
