#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>

class Spaceship {
public:
    Spaceship();
    Spaceship(const sf::Texture &texture);

    void setPosition(const sf::Vector2f &pos);
    sf::Vector2f getPosition() const;
    sf::Sprite& getSprite();
    sf::Vector2f getSize() const;
    void resetPosition();

private:
    sf::Sprite sprite;
};

#endif // SPACESHIP_H
