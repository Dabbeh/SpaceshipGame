#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet();
    Bullet(const sf::Texture& texture, const sf::Vector2f& position, float speed);

    void update(float dt);
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    float speed;
};

#endif
