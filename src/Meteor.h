#ifndef METEOR_H
#define METEOR_H

#include <SFML/Graphics.hpp>

class Meteor {
public:
    Meteor(); // Default constructor
    Meteor(const sf::Texture& texture, const sf::Vector2f& position, float speed); // Parameterized constructor

    void update(float dt);
    sf::Sprite& getSprite();

    void setHitPoints(int hp);   // Add setter for health
    void decreaseHealth(int amount);  // Add method to decrease health
    int getHealth() const;  // Add getter for health

private:
    sf::Sprite sprite;
    float speed;
    int health; // Health variable
};

#endif
