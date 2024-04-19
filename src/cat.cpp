#include "cat.h"

Cat::Cat(int catId)
{
    std::cout << "Cat Created" << std::endl;
    this->catId = catId;
    this->x_position = rand() % Constants::windowWidth;
    this->y_position = rand() % Constants::windowHeight;

    std::cout << "Cat Created, locate at " << this->x_position << "," << this->y_position << std::endl;

}

Cat::Cat(float radius, sf::Vector2f screenSize) : m_radius(radius), m_screenSize(screenSize) {
    m_position.x = rand() % (static_cast<int>(m_screenSize.x) - 2 * static_cast<int>(m_radius)) + m_radius;
    m_position.y = rand() % (static_cast<int>(m_screenSize.y) - 2 * static_cast<int>(m_radius)) + m_radius;

    float angle = static_cast<float>(rand() % 360) * 3.14f / 180.f;
    m_velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * m_speed;
}

void Cat::update(float deltaTime) {
    m_position += m_velocity * deltaTime;

    if (m_position.x - m_radius < 0 || m_position.x + m_radius > m_screenSize.x) {
        m_velocity.x = -m_velocity.x; 
    }
    if (m_position.y - m_radius < 0 || m_position.y + m_radius > m_screenSize.y) {
        m_velocity.y = -m_velocity.y; 
    }
}

void Cat::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(m_radius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(m_position - sf::Vector2f(m_radius, m_radius));
    window.draw(shape);
}


