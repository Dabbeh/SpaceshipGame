#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Texture& texture, const sf::Vector2f& position, float speed);

    void update(float dt, const sf::Vector2f& spaceshipPos);
    void render(sf::RenderWindow& window);

    void setHitPoints(int hp);   // Add setter for health
    void decreaseHealth(int amount);  // Add method to decrease health
    int getHealth() const;  // Add getter for health
    void setDirection(const sf::Vector2f& direction);  // Add setter for direction
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    int health;
    float speed;
    sf::Vector2f direction;  // Direction for movement
};

#endif
