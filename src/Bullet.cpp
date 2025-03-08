#include "Bullet.h"
#include <SFML/Graphics.hpp>

Bullet::Bullet() : speed(0.f) {}

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& position, float speed)
    : speed(speed) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Bullet::update(float dt) {
    sprite.move(0.f, -speed * dt);  // Move the bullet upward
}

sf::Sprite& Bullet::getSprite() {
    return sprite;
}
