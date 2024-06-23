#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>
#include <ctime> // Include <ctime> for time manipulation
#include <cmath> // Include <cmath> for mathematical functions
#include "cat.h"
#include "fish.h"

float fishGenerationInterval = Constants::FishGenerationInterval; // Interval for fish generation in seconds
float catSpeed = Constants::CatSpeed;                             // Speed of the cat in pixels per second

// Function to calculate distance between two points
float distance(sf::Vector2f p1, sf::Vector2f p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

enum GameState
{
    StartMenu,
    Playing
};

int main()
{
    ////////////////////////////////////////// config //////////////////////////////////////////
    int numCats = Constants::catNum; // Assuming Constants::catNum is defined somewhere
    int numFish = Constants::fishNum;
    int capturedFishCount = 0; // Initialize the captured fish count
    bool gameStart = false;
    std::list<Cat> catList;   // Change the list type to Cat
    std::list<Fish> fishList; // Change the list type to Fish

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

    // Load cat texture from file
    sf::Texture catTexture;
    if (!catTexture.loadFromFile("src/cat1.png")) // Path to your cat image
    {
        // Error handling if the texture fails to load
        return EXIT_FAILURE;
    }

    // Load a font for the text
    sf::Font font;
    if (!font.loadFromFile("src/new_athletic.ttf")) // Path to your font file
    {
        // Error handling if the font fails to load
        return EXIT_FAILURE;
    }

    sf::Text fishCountText;
    fishCountText.setFont(font);                  // Set the font
    fishCountText.setCharacterSize(24);           // Set the character size
    fishCountText.setFillColor(sf::Color::Black); // Set the text color

    sf::Text buyCatText;
    buyCatText.setFont(font);
    buyCatText.setCharacterSize(20);
    buyCatText.setFillColor(sf::Color::Black);

    sf::Text speedUpCatText;
    speedUpCatText.setFont(font);
    speedUpCatText.setCharacterSize(20);
    speedUpCatText.setFillColor(sf::Color::Black);

    sf::Text increaseFishSpawnText;
    increaseFishSpawnText.setFont(font);
    increaseFishSpawnText.setCharacterSize(20);
    increaseFishSpawnText.setFillColor(sf::Color::Black);

    sf::Text startMenuText;
    startMenuText.setFont(font);
    startMenuText.setCharacterSize(30);
    startMenuText.setFillColor(sf::Color::Black);
    startMenuText.setString("Press SPACE to start the game");
    startMenuText.setPosition(
        (Constants::windowWidth - startMenuText.getGlobalBounds().width) / 2,
        (Constants::windowHeight - startMenuText.getGlobalBounds().height) / 2);

    GameState gameState = StartMenu;

    ////////////////////////////////////////// levels //////////////////////////////////////////
    int costCatNewLevel = 0;
    int costCatSpeedUpLevel = 0;
    int costFishSpawnRateLevel = 0;

    while (window.isOpen())
    {

        int costCatNew = 100 * std::pow(static_cast<int>(costCatNewLevel + 1), 3);
        int costCatSpeedUp = 100 * std::pow(static_cast<int>(costCatSpeedUpLevel + 1), 2);
        int costFishSpawnRate = 50 * std::pow(static_cast<int>(costFishSpawnRateLevel + 1), 2);

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
                if (event.key.code == sf::Keyboard::Space)
                {
                    capturedFishCount = 10000;
                }
                if (event.key.code == sf::Keyboard::N)
                {
                    Cat catNew(static_cast<int>(catList.size())); // Assign a unique ID to the new cat
                    catList.push_back(catNew);
                }
                // Purchase a new cat
                if (event.key.code == sf::Keyboard::Num1)
                {
                    std::cout << "new cat";
                    if (capturedFishCount >= costCatNew)
                    {
                        capturedFishCount -= costCatNew;
                        Cat catNew(static_cast<int>(catList.size())); // Assign a unique ID to the new cat
                        catList.push_back(catNew);
                        costCatNewLevel += 1;
                    }
                }

                // Speed up cats
                if (event.key.code == sf::Keyboard::Num2)
                {
                    if (capturedFishCount >= costCatSpeedUp)
                    {
                        capturedFishCount -= costCatSpeedUp;
                        catSpeed = catSpeed * 1.1f; // Adjust this value as needed
                        costCatSpeedUpLevel += 1;
                    }
                }

                // Increase fish spawn rate
                if (event.key.code == sf::Keyboard::Num3)
                {
                    if (capturedFishCount >= costFishSpawnRate)
                    {
                        capturedFishCount -= costFishSpawnRate;
                        fishGenerationInterval *= 0.8f; // Decrease interval by 10%
                        costFishSpawnRateLevel += 1;
                    }
                }
            }
        }

        // Update elapsed time
        elapsedTime += clock.restart().asSeconds();

        // If elapsed time exceeds fish generation interval, generate fish
        if (elapsedTime >= fishGenerationInterval)
        {
            Fish newFish(static_cast<int>(fishList.size())); // Assign a unique ID to the new fish
            fishList.push_back(newFish);

            // Reset elapsed time
            elapsedTime = 0.0f;
        }

        std::cout << capturedFishCount << std::endl;
        std::cout << costCatNew << std::endl;
        std::cout << costCatSpeedUp << std::endl;
        std::cout << costFishSpawnRate << std::endl;

        window.clear(sf::Color::White);

        sf::CircleShape mouseShape(Constants::mouseShapeRadius);

        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window

        mouseShape.setPosition(localPosition.x - Constants::mouseShapeRadius, localPosition.y - Constants::mouseShapeRadius);
        mouseShape.setFillColor(sf::Color(0, 0, 0));

        window.draw(mouseShape);

        // Iterate through each cat
        for (auto &cat : catList)
        {
            // Find the closest fish to the cat
            sf::Vector2f catPosition(cat.x_position, cat.y_position);
            sf::Vector2f closestFishPosition;
            float minDistance = std::numeric_limits<float>::max();

            // Iterate through each fish to find the closest one
            for (auto it = fishList.begin(); it != fishList.end();)
            {
                sf::Vector2f fishPosition(it->x_position, it->y_position);
                float dist = distance(catPosition, fishPosition);

                // Skip fish already targeted by other cats
                if (it->fishId != cat.targetFishId)
                {
                    if (dist < minDistance)
                    {
                        minDistance = dist;
                        closestFishPosition = fishPosition;
                    }
                }

                // Check if the cat is very close to the fish
                if (dist < 10.0f) // Adjust this value as needed
                {
                    // Remove the fish
                    it = fishList.erase(it);
                    // Update the target fish ID for the cat
                    cat.targetFishId = -1; // No target fish
                    // Increment the captured fish count
                    capturedFishCount++;
                }
                else
                {
                    ++it;
                }
            }

            // If cat doesn't have a target fish, set the closest one as the target
            if (cat.targetFishId == -1)
            {
                for (const auto &fish : fishList)
                {
                    sf::Vector2f fishPosition(fish.x_position, fish.y_position);
                    if (fishPosition == closestFishPosition)
                    {
                        cat.targetFishId = fish.fishId;
                        break;
                    }
                }
            }

            // Move the cat towards the closest fish
            sf::Vector2f direction = closestFishPosition - catPosition;
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= magnitude; // Normalize the direction vector

            float moveDistance = std::min(catSpeed, magnitude); // Limit movement to the distance to the fish

            cat.x_position += direction.x * moveDistance; // Move the cat
            cat.y_position += direction.y * moveDistance;

            // Set the scale of the cat sprite to change its size
            float scaleFactor = 0.1f; // Change this value to adjust the size
            sf::Sprite catSprite;
            catSprite.setTexture(catTexture); // Set the texture
            catSprite.setPosition(cat.x_position, cat.y_position);
            catSprite.setScale(scaleFactor, scaleFactor);

            window.draw(catSprite); // Draw the cat sprite
        }

        for (const auto &fish : fishList) // Iterate through fish
        {
            sf::Sprite fishSprite;              // Create a fish sprite
            fishSprite.setTexture(fishTexture); // Set the texture
            fishSprite.setPosition(fish.x_position, fish.y_position);

            window.draw(fishSprite); // Draw the fish sprite
        }

        // Update the text with the captured fish count
        fishCountText.setString("Fish: " + std::to_string(capturedFishCount));
        buyCatText.setString("Buy Cat: " + std::to_string(costCatNew));
        speedUpCatText.setString("Speed Up Cat: " + std::to_string(costCatSpeedUp));
        increaseFishSpawnText.setString("Increase Fish Spawn: " + std::to_string(costFishSpawnRate));

        // Set the position of the text to the top-right corner
        fishCountText.setPosition(Constants::windowWidth / 2 - 50, 10);

        // Draw the text
        window.draw(fishCountText);

        // Draw the upgrade texts
        buyCatText.setPosition(Constants::windowWidth - 250, fishCountText.getGlobalBounds().height + fishCountText.getGlobalBounds().height + 10);
        window.draw(buyCatText);

        speedUpCatText.setPosition(Constants::windowWidth - 250, fishCountText.getGlobalBounds().height + fishCountText.getGlobalBounds().height + buyCatText.getGlobalBounds().height + 20);
        window.draw(speedUpCatText);

        increaseFishSpawnText.setPosition(Constants::windowWidth - 250, fishCountText.getGlobalBounds().height + fishCountText.getGlobalBounds().height + buyCatText.getGlobalBounds().height + speedUpCatText.getGlobalBounds().height + 30);
        window.draw(increaseFishSpawnText);

        // end the current frame
        window.display();
    }

    return 0;
}
