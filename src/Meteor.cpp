#include "Meteor.h"
#include <SFML/Graphics.hpp>

Meteor::Meteor() : speed(0.f), health(1) {}

Meteor::Meteor(const sf::Texture& texture, const sf::Vector2f& position, float speed)
    : speed(speed), health(1) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Meteor::update(float dt) {
    sprite.move(0.f, speed * dt); // Adjust movement by speed and delta time
}

sf::Sprite& Meteor::getSprite() {
    return sprite;
}

void Meteor::setHitPoints(int hp) {
    health = hp;  // Set health
}

void Meteor::decreaseHealth(int amount) {
    health -= amount;  // Decrease health
}

int Meteor::getHealth() const {
    return health;  // Return current health
}
