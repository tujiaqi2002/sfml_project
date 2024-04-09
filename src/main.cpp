#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "player.h"

void player_move(bool left, bool right, bool up, bool down, float *player_x, float *player_y)
{
    if (left && up)
    {
        *player_x -= 0.007071f * Constants::playerSpeed;
        *player_y -= 0.007071f * Constants::playerSpeed;
    }
    else if (left && down)
    {
        *player_x -= 0.007071f * Constants::playerSpeed;
        *player_y += 0.007071f * Constants::playerSpeed;
    }
    else if (right && up)
    {
        *player_x += 0.007071f * Constants::playerSpeed;
        *player_y -= 0.007071f * Constants::playerSpeed;
    }
    else if (right && down)
    {
        *player_x += 0.007071f * Constants::playerSpeed;
        *player_y += 0.007071f * Constants::playerSpeed;
    }
    else if (left)
    {
        *player_x -= 0.01f * Constants::playerSpeed;
    }
    else if (right)
    {
        *player_x += 0.01f * Constants::playerSpeed;
    }
    else if (up)
    {
        *player_y -= 0.01f * Constants::playerSpeed;
    }
    else if (down)
    {
        *player_y += 0.01f * Constants::playerSpeed;
    }
}

void player_check_move(float *player_x, float *player_y)
{
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        left = true;
        std::cout << "the Left key was pressed" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        right = true;
        std::cout << "the Right key was pressed" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        up = true;
        std::cout << "the Up key was pressed" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        down = true;
        std::cout << "the Down key was pressed" << std::endl;
    }

    player_move(left, right, up, down, player_x, player_y);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(Constants::width, Constants::height), "My window");
    window.setMouseCursorVisible(false);

    sf::CircleShape player(Constants::playerRadius);
    float player_x = float(Constants::width / 2) - Constants::playerRadius;
    float player_y = float(Constants::height / 2) - Constants::playerRadius;

    player.setPosition(player_x, player_y);
    player.setFillColor(sf::Color(0, 0, 0));

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
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                // The escape key was pressed
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                std::cout << event.key.code << std::endl;
            }
        }

        player_check_move(&player_x, &player_y);

        window.clear(sf::Color::White);

        sf::CircleShape mouseShape(Constants::mouseShapeRadius);

        player.setPosition(player_x, player_y);
        player.setFillColor(sf::Color(0, 0, 0));

        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window

        mouseShape.setPosition(localPosition.x - Constants::mouseShapeRadius, localPosition.y - Constants::mouseShapeRadius);
        mouseShape.setFillColor(sf::Color(0, 0, 0));

        window.draw(mouseShape);
        window.draw(player);

        // end the current frame
        window.display();
    }

    return 0;
}
