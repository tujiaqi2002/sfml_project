#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>
#include <ctime> // Include <ctime> for time manipulation
#include "cat.h"
#include "fish.h"

const float FishGenerationInterval = 0.5f; // Interval for fish generation in seconds

int main()
{
    int numCats = Constants::catNum; // Assuming Constants::catNum is defined somewhere
    int numFish = Constants::fishNum;

    std::list<sf::CircleShape> catList;
    std::list<sf::Sprite> fishList; // Use sf::Sprite instead of sf::CircleShape

    sf::RenderWindow window(sf::VideoMode(Constants::windowWidth, Constants::windowHeight), "My window");
    window.setMouseCursorVisible(false);

    sf::Clock clock; // Create a clock to measure time

    float elapsedTime = 0.0f; // Initialize elapsed time

    // Load fish texture from file
    sf::Texture fishTexture;
    if (!fishTexture.loadFromFile("src/fish.png")) // Path to your fish image
    {
        // Error handling if the texture fails to load
        return EXIT_FAILURE;
    }

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

        // Update elapsed time
        elapsedTime += clock.restart().asSeconds();

        // If elapsed time exceeds fish generation interval, generate fish
        if (elapsedTime >= FishGenerationInterval)
        {
            Fish newFish(Constants::fishNum); // Assuming Fish class has a constructor
            sf::Sprite fishSprite; // Use sf::Sprite instead of sf::CircleShape

            // Set fish position, texture, and add to the list
            fishSprite.setPosition(newFish.x_position, newFish.y_position);
            fishSprite.setTexture(fishTexture); // Set the texture

            fishList.push_back(fishSprite);

            // Reset elapsed time
            elapsedTime = 0.0f;
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

        for (const auto &fishSprite : fishList) // Iterate through fish sprites
        {
            window.draw(fishSprite); // Draw fish sprites instead of shapes
        }

        // end the current frame
        window.display();
    }

    return 0;
}
