#include <SFML/Graphics.hpp>
#include "header.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace sf;
using namespace std;

void gameScreen() {
    RenderWindow window(VideoMode({825, 800}), "SFML works!"); //create a window 825x800 
    int mat[3][3] = {{0,1,2},{3,4,5},{6,7,8}};  //Matriz 3x3 filled with numbers form 0 to 8
    int row=0, col=0; //row and column in 0
    //arrays of positions for the game and the user
    int gameSecuence[50];
    int userInput[50];
    //the position in the array
    int gsecuencePos=0, userinPos=0;

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

    //Shows the state of the game: player´s turn, gamesecuence, and the end of the game
    enum States{showingSecuence, userTurn, End};
    States game=showingSecuence;

    
    Clock clock; //Manage the time of the secuence showing 
    Clock moveClock; //Manege the time of the user moving in the matrix
    float onTime=0.6f, offTime=0.3f, moveDelay=0.2f, timePassed;
    int show=0; //the position of the secuence showing
    bool showlighterCol=false; //ask if its time to light the rectangle

    //Array of colors
Color lighterCol[] = {
    Color(255, 0, 0),     // Rojo brillante
    Color(255, 128, 0),   // Naranja fuerte
    Color(255, 0, 255),   // Magenta brillante
    Color(0, 255, 0),     // Verde neón
    Color(0, 255, 255),   // Cian eléctrico
    Color(0, 128, 255),   // Azul saturado
    Color(0, 0, 255),     // Azul puro
    Color(128, 0, 255),   // Violeta intenso
    Color(255, 255, 0)   // Amarillo puro
};

Color colors[] = {
    Color(255, 178, 178),   // Rojo aún más claro
    Color(255, 204, 153),   // Naranja más claro aún
    Color(255, 204, 255),   // Magenta pastel muy claro
    Color(204, 255, 204),   // Verde lima muy suave
    Color(204, 255, 238),   // Verde agua luminoso
    Color(204, 255, 255),   // Cian muy claro
    Color(204, 229, 255),   // Azul claro más tenue
    Color(229, 204, 255),   // Violeta clarísimo
    Color(255, 255, 204)    // Amarillo muy claro
};
    srand(time(NULL));
    gameSecuence[gsecuencePos]=rand()%9; //Creates first position with rand
    gsecuencePos++; //moves to the next position
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
    
        if(game==showingSecuence){ //ask if it´s the game´s turn

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
                    if(show<gsecuencePos){ //change into original color
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
                    if (Keyboard::isKeyPressed(Keyboard::Key::Down) && row<2){
                        row++;
                        moveClock.restart();
                    } else {
                        
                        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && col<2){
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
                userInput[userinPos]=row*3+col; //saves matrix position into an array
                if(userInput[userinPos]!=gameSecuence[userinPos]){ //if the user selects a position that dosen't match the game ends
                    game=End; 
                }  else{
                    userinPos++; //move to the next position
                    if(userinPos==gsecuencePos){
                        //if it is the same position of the secuence, you move to the next one and add a new step to the secuence
                        gameSecuence[gsecuencePos]=rand()%9;
                        gsecuencePos++;
                        game=showingSecuence;
                        show=0;
                        showlighterCol=true;
                        countPoints++;
                        tPoints.setString("Points: " + to_string(countPoints));
                        clock.restart();
                    }
                }
                sleep(milliseconds(150));
            }
        }
        
        //if the game ends close the window
        if(game==End){
            window.close();
            mainMenuScreen();
        }
        window.clear();
        window.draw(backgSprite);
        
        //Draw Matrix
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                sf::RectangleShape rectangle({140.f,140.f}); //set the shape and the size of the rectangles
                rectangle.setPosition({j*185.f+233.f, i*185.f+240.f}); //set the position of rectangles with spaces
                rectangle.setOrigin({rectangle.getSize().x/2, rectangle.getSize().y/2});
                if(game==showingSecuence && show< gsecuencePos)
                {
                    //turns the array of positions into matrix rows and columns 
                    r=gameSecuence[show]/3;
                    c=gameSecuence[show]%3;

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
        window.display();
    }
}
