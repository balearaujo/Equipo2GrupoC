#include <SFML/Graphics.hpp>

int main() 
{
    sf::RenderWindow window(sf::VideoMode({825, 800}), "SFML works!");
    int mat[3][3]={{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    sf::Color colors[]{
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

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        for (int i=0; i<3; i++){
            for(int j=0; j<3; j++) {
            sf::RectangleShape rectangle({140.f, 140.f});
            rectangle.setPosition({i*170.f+170.f, j*170.f +170.f});
            rectangle.setFillColor(colors[mat[i][j]]);

            window.draw(rectangle);
            }
        }

        window.display();
    }
}