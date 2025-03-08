#include "Enemy.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position, float speed)
    : health(1), speed(speed), direction(0.f, 0.f) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Enemy::update(float dt, const sf::Vector2f& spaceshipPos) {
    // Simple movement towards spaceship
    sf::Vector2f moveDirection = spaceshipPos - sprite.getPosition();
    float length = std::sqrt(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
    if (length > 0.f) {
        moveDirection /= length;  // Normalize direction vector
        sprite.move(moveDirection * speed * dt);  // Move in direction towards spaceship
    }
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Enemy::setHitPoints(int hp) {
    health = hp;  // Set health
}

void Enemy::decreaseHealth(int amount) {
    health -= amount;  // Decrease health
}

int Enemy::getHealth() const {
    return health;  // Return current health
}

void Enemy::setDirection(const sf::Vector2f& direction) {
    this->direction = direction;  // Set direction
}

sf::Sprite& Enemy::getSprite() {
    return sprite;
}
