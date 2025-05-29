#ifndef HEADER_HPP
#define HEADER_HPP

// signUp.cpp
union GameStatus{
    bool inProgress;
    bool finished;
};

struct GameHistory{
    int gameNumber;
    char date[50];
    int score;
    int gameSequence[50];
    GameStatus status;
};

struct User{
    int idUser;
    char *username;
    char *password;
    GameHistory *games;
};

// signUp.cpp
void screenSignUp();

// logIn.cpp
void screenLogIn();



#endif
