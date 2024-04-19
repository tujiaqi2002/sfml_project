#ifndef Cat_H
#define Cat_H

#include "constants.h"
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>

class Cat
{
public:
    int catId;
    float x_position;
    float y_position;

    std::string catName;
    

    Cat(int catId);
    Cat(float radius, sf::Vector2f screenSize);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_radius;
    sf::Vector2f m_screenSize;
    float m_speed = 2000.0f; // Adjust speed as needed
};

#endif // Cat_H
