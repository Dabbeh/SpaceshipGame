#include "Spaceship.h"

Spaceship::Spaceship() {}

Spaceship::Spaceship(const sf::Texture &texture) {
    sprite.setTexture(texture);
    // Place the spaceship at the center bottom of the window
    sprite.setPosition(1280 / 2.0f, 720 - texture.getSize().y);
}

void Spaceship::setPosition(const sf::Vector2f &pos) {
    sprite.setPosition(pos);
}

sf::Vector2f Spaceship::getPosition() const {
    return sprite.getPosition();
}

sf::Sprite& Spaceship::getSprite() {
    return sprite;
}

sf::Vector2f Spaceship::getSize() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

void Spaceship::resetPosition() {
    sprite.setPosition(1280 / 2.0f, 720 - sprite.getTexture()->getSize().y);
}
