#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace sf;

int main() 
{
    RenderWindow window(VideoMode({825, 800}), "SFML works!"); //create a window 825x800 
    int mat[3][3] = {{0,1,2},{3,4,5},{6,7,8}};  //Matriz 3x3 filled with numbers form 0 to 8
    int row=0, col=0; //row and column in 0
    //arrays of positions for the game and the user
    int gameSecuence[50];
    int userInput[50];
    //the position in the array
    int gsecuencePos=0, userinPos=0;

    //Shows the state of the game: player´s turn, gamesecuence, and the end of the game
    enum States{showingSecuence, userTurn, End};
    States game=showingSecuence;

    
    Clock clock; //Manage the time of the secuence showing 
    Clock moveClock; //Manege the time of the user moving in the matrix
    float onTime=0.6f, offTime=0.3f, moveDelay=0.2f, timePassed;
    int show=0; //the position of the secuence showing
    bool showlighterCol=false; //ask if its time to light the rectangle

    //Array of colors
    Color colors[]={
        Color(117, 78, 227),
        Color(29, 152, 228),
        Color(132, 201, 3),
        Color(235, 229, 30),
        Color(246, 174, 8),
        Color(255, 113, 0),
        Color(223, 1, 1),
        Color(242, 64, 91),
        Color(111, 2, 103),
    };
    //Array with the lighter version of colors
    Color lighterCol[]={
        Color(214, 202, 247),
        Color(145, 205, 242),
        Color(205, 254, 114),
        Color(246, 242, 142),
        Color(251, 217, 136),
        Color(255, 154, 71),
        Color(254, 133, 133),
        Color(246, 121, 140),
        Color(180, 4, 168),
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

            timePassed=clock.getElapsedTime().asSeconds(); //get how much time has passed
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
                        clock.restart();
                    }
                }
                sleep(milliseconds(150));
            }
        }

        //if the game ends close the window
        if(game==End){
            window.close();
        }
        window.clear();

        //Draw Matrix
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                sf::RectangleShape rectangle({140.f,140.f}); //set the shape and the size of the rectangles
                rectangle.setPosition({j*170.f+170.f, i*170.f+170.f}); //set the position of rectangles with spaces
                if(game==showingSecuence && show< gsecuencePos)
                {
                    //turns the array of positions into matrix rows and columns 
                    r=gameSecuence[show]/3;
                    c=gameSecuence[show]%3;

                    if(i==r && j==c){ //ask if our postion is the pattern
                        if(showlighterCol){  //ask if its time to light it
                            rectangle.setFillColor(Color::Red); //Colors it Red
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

        window.display();
    }
}
