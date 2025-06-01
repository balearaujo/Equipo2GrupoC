#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
using namespace sf;

int main() 
{
    sf::RenderWindow window(sf::VideoMode({825, 800}), "SFML works!"); //create a window 825x800 
    int mat[3][3]={{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};  //Matriz 3x3 filled with numbers form 0 to 8
    int row=0, col=0; //row and column in 0
    sf::Color colors[]{ //Array with 9 colors
        sf::Color(117, 78, 227),
        sf::Color(29, 152, 228),
        sf::Color(132, 201, 3),
        sf::Color(235, 229, 30),
        sf::Color(246, 174, 8),
        sf::Color(255, 113, 0),
        sf::Color(223, 1, 1),
        sf::Color(242, 64, 91),
        sf::Color(111, 2, 103),
    };

    Color lighterCol[]{ //Array with 9 lighter colors
        sf::Color(214, 202, 247),
        sf::Color(145, 205, 242),
        sf::Color(205, 254, 114),
        sf::Color(246, 242, 142),
        sf::Color(251, 217, 136),
        sf::Color(255, 154, 71), //
        sf::Color(254, 133, 133), //
        sf::Color(246, 121, 140), //
        sf::Color(180, 4, 168), //
    };

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) //events
        {
            //Move rows or columns based on pressed key and validate if movement is posible by checking Matrix boundaries.
            if (Keyboard::isKeyPressed(Keyboard::Key::Up) && row>0){ 
                row--;
            } else {
                
                if (Keyboard::isKeyPressed(Keyboard::Key::Down) && row<3){
                    row++;
                } else {
                    
                    if (Keyboard::isKeyPressed(Keyboard::Key::Right) && col<3){
                        col++;
                    
                    } if (Keyboard::isKeyPressed(Keyboard::Key::Left) && col>0){
                        col--;
                    }
                }
            } 
            //close window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        //Clears window before drawing
        window.clear();
        //Draw Matrix
        for (int i=0; i<3; i++){
            for(int j=0; j<3; j++) {
            sf::RectangleShape rectangle({140.f, 140.f}); //set the shape and the size of the rectangles
            rectangle.setPosition({j*170.f+170.f, i*170.f +170.f}); //set the position of rectangles with spaces
            rectangle.setFillColor(lighterCol[mat[i][j]]); //filled rectangles with the lighter versions of colors
            
            if (i==row && j==col){ //selected postion
                rectangle.setFillColor(colors[mat[i][j]]); //filled selected rectangle with the darker color version
            }

            window.draw(rectangle); //draw the rectangle in the window
            }
        }
        window.display(); //display window
    }
}
