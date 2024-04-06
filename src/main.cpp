#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <iostream>

int width = 800;
int height = 600;

float mouseShapeRadius = 10.f;
float playerRadius = 20.f;

int playerSpeed = 5;


void player_move(bool left, bool right, bool up, bool down, float* player_x, float* player_y) {
    if (left && up) {
        std::cout << "Moving player diagonally up-left" << std::endl;
        // Adjust player's position accordingly
        *player_x -= 0.007071f * playerSpeed;
        *player_y -= 0.007071f * playerSpeed;
    } else if (left && down) {
        std::cout << "Moving player diagonally down-left" << std::endl;
        // Adjust player's position accordingly
        *player_x -= 0.007071f * playerSpeed;
        *player_y += 0.007071f * playerSpeed;
    } else if (right && up) {
        std::cout << "Moving player diagonally up-right" << std::endl;
        // Adjust player's position accordingly
        *player_x += 0.007071f * playerSpeed;
        *player_y -= 0.007071f * playerSpeed;
    } else if (right && down) {
        std::cout << "Moving player diagonally down-right" << std::endl;
        // Adjust player's position accordingly
        *player_x += 0.007071f * playerSpeed;
        *player_y += 0.007071f * playerSpeed;
    } else if (left) {
        std::cout << "Moving player left" << std::endl;
        // Adjust player's position accordingly
        *player_x -= 0.01f * playerSpeed;
    } else if (right) {
        std::cout << "Moving player right" << std::endl;
        // Adjust player's position accordingly
        *player_x += 0.01f * playerSpeed;
    } else if (up) {
        std::cout << "Moving player up" << std::endl;
        // Adjust player's position accordingly
        *player_y -= 0.01f * playerSpeed;
    } else if (down) {
        std::cout << "Moving player down" << std::endl;
        // Adjust player's position accordingly
        *player_y += 0.01f * playerSpeed;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    window.setMouseCursorVisible(false);

    sf::CircleShape player(playerRadius);
    float player_x = float(width/2) - playerRadius;
    float player_y =  float(height/2) - playerRadius;
    player.setPosition(player_x , player_y);
    player.setFillColor(sf::Color(0, 0, 0));

    // run the program as long as the window is open
    while (window.isOpen())
    {
         // draw everything here...
        // window.draw(...);
        

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
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                }
            }
        }

        
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {   
            left = true;
            std::cout << "the Left key was pressed" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            right = true;
            std::cout << "the Right key was pressed" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            up = true;
            std::cout << "the Up key was pressed" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            down = true;
            std::cout << "the Down key was pressed" << std::endl;
        }

        player_move(left,right,up,down,&player_x,&player_y);

        // clear the window with black color
        window.clear(sf::Color::White);

        sf::CircleShape mouseShape(mouseShapeRadius);
       
        player.setPosition(player_x , player_y);
        player.setFillColor(sf::Color(0, 0, 0));

        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window
        // std::cout << localPosition.x << ' ' << localPosition.y << std::endl;
        mouseShape.setPosition(localPosition.x - mouseShapeRadius, localPosition.y - mouseShapeRadius);
        mouseShape.setFillColor(sf::Color(0, 0, 0));

        

        window.draw(mouseShape);
        window.draw(player);

        // end the current frame
        window.display();
    }

    return 0;
}


