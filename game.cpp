#include <SFML/Graphics.hpp>
#include "header.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

void screenGame(int size) {
    RenderWindow window(VideoMode({825, 800}), "SFML works!"); //create a window 825x800
    // int mat[3][3] = {{0,1,2},{3,4,5},{6,7,8}};  //Matriz 3x3 filled with numbers form 0 to 8
    
    //int size{9}; // SEND SIZE WHEN CALLING FUNCTION
    int rows = (size == 4 ? 2 : 3);
    int columns = rows;
    int **mat = new int*[rows];
    for (int i=0; i<rows; i++){
        mat[i] = new int[columns];
    }
    int cont{0};
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            *(*(mat+i)+j) = cont;
            cont++;
        }
    }

    int row=0, col=0; //row and column in 0
    //arrays of positions for the game and the user
    int *gameSequence = new int[50];
    int *userInput = new int [50];
    //the position in the array
    int gsequencePos=0, userinPos=0;

    // logo
    Image icon("assets/logo.png");
    window.setIcon(icon);
    
    // background
    Texture backgTexture;
    if (!backgTexture.loadFromFile("assets/back4.png")) {
        cout << "Image could'nt be loaded" << endl;
    }
    Sprite backgSprite(backgTexture); 
    float scaleX = float(window.getSize().x) / backgTexture.getSize().x;
    float scaleY = float(window.getSize().y) / backgTexture.getSize().y;
    backgSprite.setScale({scaleX, scaleY});

    Font font("assets/BurbankBigCondensed-Black.otf");

    int countPoints{0};
    Text tPoints(font, "Points: " + to_string(countPoints), 50);
    tPoints.setFillColor(Color::White);
    tPoints.setOrigin({75,20});
    tPoints.setPosition({825/2, 70});

    Text tTurn(font, "MEMORIZE THE SEQUENCE!", 70);
    tTurn.setFillColor(Color::White);
    tTurn.setOrigin({85, 25});
    tTurn.setPosition({200, 720});

    //Shows the state of the game: player´s turn, gamesequence, and the end of the game
    States game=showingSequence;

    
    Clock clock; //Manage the time of the sequence showing 
    Clock moveClock; //Manege the time of the user moving in the matrix
    float onTime=0.6f, offTime=0.3f, moveDelay=0.2f, timePassed;
    int show=0; //the position of the sequence showing
    bool showlighterCol=false; //ask if its time to light the rectangle
    bool entered;

    //Array of colors
    Color lighterCol[] = {
        Color(255, 0, 0),     // Bright red
        Color(255, 255, 0),   // Pure yellow
        Color(0, 255, 0),     // Neon green
        Color(0, 0, 255),     // Pure blue
        Color(255, 128, 0),   // Vivid orange
        Color(255, 0, 255),   // Bright magenta
        Color(0, 255, 255),   // Electric cyan
        Color(0, 128, 255),   // Saturated blue
        Color(128, 0, 255)    // Intense violet
    };

    Color colors[] = {
        Color(255, 178, 178),   // Very light red
        Color(255, 255, 204),   // Very light yellow
        Color(204, 255, 204),   // Very soft lime green
        Color(204, 229, 255),   // Pale light blue
        Color(255, 204, 153),   // Even lighter orange
        Color(255, 204, 255),   // Very light pastel magenta
        Color(204, 255, 238),   // Bright aqua green
        Color(204, 255, 255),   // Very light cyan
        Color(229, 204, 255)    // Very light violet
    };

    srand(time(NULL));
    gameSequence[gsequencePos]=rand()%(size==4 ? 4 : 9); //Creates first position with rand
    gsequencePos++; //moves to the next position
    showlighterCol=true; //Shows lighter color
    clock.restart(); //restart clock

    int r, c;

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<Event::Closed>())
                window.close();
        }
    
        if(game==showingSequence){ //ask if it´s the game´s turn

            timePassed=clock.getElapsedTime().asSeconds(); //get how much time ha   s passed
            if(showlighterCol){ //ask is the color its going to change
                if(timePassed>onTime){ //ask if its on time to be lighter
                    showlighterCol=false; //change to false
                    clock.restart(); //restart clock
                }
            }
            else
            {
                if(timePassed>offTime){
                    show++; //increase the position its showing
                    if(show<gsequencePos){ //change into original color
                        showlighterCol = true;
                        clock.restart();
                    }
                else{
                    //change the values to zero and calls to user turn
                        game=userTurn;
                        show=0;
                        userinPos=0;
                        moveClock.restart();
                    }
                }
            }
        }
        else if(game==userTurn){
            if(moveClock.getElapsedTime().asSeconds()>moveDelay) //HERE
            {
                //Move rows or columns based on pressed key and validate if movement is posible by checking Matrix boundaries.
                    if (Keyboard::isKeyPressed(Keyboard::Key::Up) && row>0){ 
                    row--;
                    moveClock.restart();
                    } else {
                    if (Keyboard::isKeyPressed(Keyboard::Key::Down) && row<(size==4 ? 1 : 2)){
                        row++;
                        moveClock.restart();
                    } else {
                        
                        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && col<(size==4 ? 1 : 2 )){
                            col++;
                            moveClock.restart();
                        
                        } if (Keyboard::isKeyPressed(Keyboard::Key::Left) && col>0){
                            col--;
                            moveClock.restart();
                        }
                    }
                } 
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Enter)){ //ask if enter is being pressed
                if(entered==false){
                    entered=true;
                    userInput[userinPos]=row*(size == 4 ? 2: 3)+col; //saves matrix position into an array
                    if(userInput[userinPos]!=gameSequence[userinPos]){ //if the user selects a position that dosen't match the game ends
                        game=End; 
                    }  else{
                    userinPos++; //move to the next position
                    if(userinPos==gsequencePos){
                        //if it is the same position of the sequence, you move to the next one and add a new step to the sequence
                        gameSequence[gsequencePos]=rand()%(size==4 ? 4 : 9);
                        gsequencePos++;
                        game=showingSequence;
                        show=0;
                        showlighterCol=true;
                        countPoints++;
                        tPoints.setString("Points: " + to_string(countPoints));
                        clock.restart();
                    }
                }
                sleep(milliseconds(150));
                }

            } else {
                entered=false;
            }
        }
        
        // text when the sequence is showing or its player turn
        if (game==userTurn){
            tTurn.setPosition({740/2, 720});
            tTurn.setString("YOUR TURN!");
        }
        else if (game==showingSequence){
            tTurn.setPosition({200, 720});
            tTurn.setString("MEMORIZE THE SEQUENCE!");
        } 
        
        //if the game ends close the window
        if(game==End){
            // delete dynamic memory
            for (int i = 0; i < rows; ++i) {
                delete[] mat[i];
            }
            delete[] mat;
            delete[] gameSequence;
            delete[] userInput;
            // call function to save the game information
            saveGame(gameSequence, gsequencePos, game, countPoints);
            // increase by one the game number of the user
            currentUser.nGames++;
            window.close();
            screenMenu();
        }
        window.clear();
        window.draw(backgSprite);
        
        //Draw Matrix
        for(int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){
                RectangleShape rectangle; //set the shape and the size of the rectangles
                (size == 9 ? rectangle.setSize({140.f,140.f}) : rectangle.setSize({200.f,200.f}));
                (size == 9 ? rectangle.setPosition({j*185.f+233.f, i*185.f+220.f}) : rectangle.setPosition({j*250.f+285.f, i*250.f+270.f})); //set the position of rectangles with spaces
                rectangle.setOrigin({rectangle.getSize().x/2, rectangle.getSize().y/2});
                if(game==showingSequence && show< gsequencePos)
                {
                    //turns the array of positions into matrix rows and columns 
                    r=gameSequence[show]/rows;
                    c=gameSequence[show]%columns;

                    if(i==r && j==c){ //ask if our postion is the pattern
                        if(showlighterCol){  //ask if its time to light it
                            rectangle.setFillColor(lighterCol[mat[i][j]]); //Colors it Red
                            rectangle.setScale({1.3, 1.3});
                        }else{
                            rectangle.setFillColor(lighterCol[mat[i][j]]); //filled rectangles with the ligher versions of colors
                        }
                    }
                    else{
                        rectangle.setFillColor(lighterCol[mat[i][j]]); 
                    }
                }
                else if(game==userTurn){ //ask if its the user turn
                    if(i==row && j==col) //ask if its being selected
                        rectangle.setFillColor(colors[mat[i][j]]); //colors it with a darker version
                    else{
                        rectangle.setFillColor(lighterCol[mat[i][j]]); //filled rectangles with the lighter versions of colors
                    }
                }
                else{
                    rectangle.setFillColor(lighterCol[mat[i][j]]); //filled rectangles with the lighter versions of colors
                }

                window.draw(rectangle);
            }
        }
        window.draw(tPoints);
        window.draw(tTurn);
        window.display();
    }
}

void saveGame(int *gameSequence, int gsequencePos, States game, int score){
    time_t now = time(NULL); // get the current time from the computer, time() grabs days, months, years, hours, minutes, seconds
    struct tm* time_now = localtime(&now);  // convert time from "now" into a struct
    char date[11]; // char array to store the formatted date
    strftime(date, sizeof(date), "%d-%m-%Y", time_now);  // format day month year in char date;

    bool found = false; // check if idUser was found

    std::string line; // one line in the .txt
    
    // get the sequence and concatenate it in a string
    ostringstream sequence; // ostringstream (output string stream) writes in a string like if it was a file, useful to concat strings.
    int tam = gsequencePos-1; // n-1 because the last number of the sequence is not inputted by the user
    if (score==0){ // if the user scores 0
        sequence << "()"; // space
    } else{ // if the user scores >0
        sequence << "(";
        for (int i=0; i < tam; i++){ // iterate the sequence array 
            sequence << gameSequence[i]; // concat every number into a string
            if (i<tam-1) sequence << ","; // add a comma between every number
        }        
        sequence << ")";
    }

    ostringstream newGameStream; // string to concat all the information of the game 
    // [idGame, date, score, status, sequence]
    newGameStream << "[" << currentUser.nGames << "," << date << "," << score << "," << static_cast<int>(game) << "," << sequence.str() << "]";

    ifstream games("games.txt"); // ifstream is used to open a file in reading mode
    ofstream gamesTemp("gamesTemp.txt"); // ofstream is used to open a file in writing mode

    // check if they work
    if (!games.is_open()){
        cout << "Error in games.txt (read)";
    }
    if (!gamesTemp.is_open()){
        cout << "Error in games.txt (write)";
        // this one doesn't work because there is no gamesTemp file yet so the if is always true
    }

    while (getline(games, line)){ // get every line, one by one, from games and its copied into "line"
        if (line.substr(0, line.find("/")) == to_string(currentUser.idUser)){ // goes through the line until it finds a "/" and substracts every character
            // to_string converts the user id into a string and it gets compared to the substracted characters
            found = true; // if they are the same (in other words, the line has the same id as the user), "found" is set to true
            line += newGameStream.str(); // the ostringstream previously concatenated (.str() grabs the string)is now appended at the end of the line substracted
            gamesTemp << line << "\n"; // add the modified line and a newline to a temporal write only file
            continue; // continue writing the other lines
        }
        gamesTemp << line << "\n"; // if the line doesn't have the id, the line just get copied into the temporal file
    }

    if (!found){ // if the id wasn't found, it means that the user has never played
        // add the game record and the user id at the beggining, we add a "/" to distinguish between user id and game records
        gamesTemp << currentUser.idUser  << "/" << newGameStream.str() << "\n"; 
    }
    games.close(); // close files
    gamesTemp.close();

    remove("games.txt"); // remove original file and rename temporal file.
    rename("gamesTemp.txt", "games.txt");
}