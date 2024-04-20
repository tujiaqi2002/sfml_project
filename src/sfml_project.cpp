#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>
#include <ctime> // Include <ctime> for time manipulation
#include <cmath> // Include <cmath> for mathematical functions
#include "cat.h"
#include "fish.h"

const float FishGenerationInterval = 0.1f; // Interval for fish generation in seconds
const float CatSpeed = 1.0f; // Speed of the cat in pixels per second

// Function to calculate distance between two points
float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main()
{
    int numCats = Constants::catNum; // Assuming Constants::catNum is defined somewhere
    int numFish = Constants::fishNum;

    std::list<sf::CircleShape> catList;
    std::list<Cat> cats;
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


    const float ballRadius = 20.0f;
    sf::Vector2f screenSize(window.getSize().x, window.getSize().y);
    //Cat catBounce(ballRadius, screenSize);

    // Load cat texture from file
    sf::Texture catTexture;
    if (!catTexture.loadFromFile("src/cat.jpeg")) // Path to your cat image
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
                    //Cat catNew(Constants::catNum);
                    

                    //sf::CircleShape catNewShape(Constants::catShapeRadius);

                    //catNewShape.setPosition(catNew.x_position, catNew.y_position);
                    //catNewShape.setFillColor(sf::Color(0, 0, 0));

                    //catList.push_back(catNewShape);
                    Cat catBounce(ballRadius, screenSize);
                    cats.push_back(catBounce);

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
        float deltaTime = clock.restart().asSeconds();
        for (auto& cat : cats) {
            cat.update(deltaTime);
            cat.draw(window);
        }
        

        // Iterate through each cat
        for (auto &catSprite : catList)
        {
            // Find the closest fish to the cat
            sf::Vector2f catPosition = catSprite.getPosition();
            sf::Vector2f closestFishPosition;
            float minDistance = std::numeric_limits<float>::max();

            // Iterate through each fish to find the closest one
            for (auto it = fishList.begin(); it != fishList.end(); )
            {
                sf::Vector2f fishPosition = it->getPosition();
                float dist = distance(catPosition, fishPosition);

                if (dist < minDistance)
                {
                    minDistance = dist;
                    closestFishPosition = fishPosition;
                }

                // Check if the cat is very close to the fish
                if (dist < 10.0f) // Adjust this value as needed
                {
                    it = fishList.erase(it); // Remove the fish
                }
                else
                {
                    ++it;
                }
            }

            // Move the cat towards the closest fish
            sf::Vector2f direction = closestFishPosition - catPosition;
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= magnitude; // Normalize the direction vector

            float moveDistance = std::min(CatSpeed, magnitude); // Limit movement to the distance to the fish

            catSprite.move(direction * moveDistance); // Move the cat

            // Set the scale of the cat sprite to change its size
            float scaleFactor = 0.1f; // Change this value to adjust the size
            catSprite.setScale(scaleFactor, scaleFactor);

            window.draw(catSprite); // Draw the cat sprite
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
