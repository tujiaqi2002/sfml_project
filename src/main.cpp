#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>
#include "cat.h"
#include "fish.h"



int main()
{
    int numCats = Constants::catNum; // Assuming Constants::catNum is defined somewhere
    int numFish = Constants::fishNum;

    std::list<sf::CircleShape> catList;
    std::list<sf::CircleShape> fishList;

    sf::RenderWindow window(sf::VideoMode(Constants::windowWidth, Constants::windowHeight), "My window");
    window.setMouseCursorVisible(false);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // The escape key was pressed
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::N)
                {
                    Cat catNew(Constants::catNum);

                    sf::CircleShape catNewShape(Constants::catShapeRadius);

                    catNewShape.setPosition(catNew.x_position, catNew.y_position);
                    catNewShape.setFillColor(sf::Color(0, 0, 0));

                    catList.push_back(catNewShape);
                    
                }
            }
        }

        window.clear(sf::Color::White);

        sf::CircleShape mouseShape(Constants::mouseShapeRadius);

        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window

        mouseShape.setPosition(localPosition.x - Constants::mouseShapeRadius, localPosition.y - Constants::mouseShapeRadius);
        mouseShape.setFillColor(sf::Color(0, 0, 0));

        window.draw(mouseShape);

        for (const auto &catShape : catList)
        {
            window.draw(catShape);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
