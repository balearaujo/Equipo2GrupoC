#ifndef HEADER_HPP
#define HEADER_HPP

// signUp.cpp estructura
// union GameStatus{
//     bool inProgress;
//     bool finished;
// };

// struct GameHistory{
//     int gameNumber;
//     char date[50];
//     int score;
//     int gameSequence[50];
//     GameStatus status;
// };

struct User{
    int idUser;
    char username[16];
    char password[16];
    int nGames;
    // GameHistory *games;
};

// signUp.cpp funciones
void screenSignUp();
void setInputValues(sf::Text &, const sf::Event &, sf::String &, sf::Text &);
bool checkUsername(sf::Text);
void writeUser(sf::Text, sf::Text, sf::Text);




// logIn.cpp
void screenLogIn();



#endif
