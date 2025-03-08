#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Spaceship.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Enemy.h"
#include <vector>
#include <string>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnBullet();
    void spawnMeteor();
    void spawnEnemy();
    bool checkCollisions();
    sf::Texture loadTexture(const std::string &path);

    sf::RenderWindow window;
    sf::Clock clock;

    // UI elements
    sf::Font font;
    sf::Text scoreText;
    sf::Text healthText;
    sf::Text gameOverText;
    sf::Text restartText;
    sf::Text exitText;

    int score;
    int health;
    bool isGameOver;

    // Game objects
    Spaceship spaceship;
    std::vector<Bullet> bullets;
    std::vector<Meteor> meteors;
    std::vector<Enemy> enemies;

    // Persistent textures
    sf::Texture spaceshipTexture;
    sf::Texture bulletTexture;
    sf::Texture meteorTexture;
    sf::Texture enemyTexture;
    sf::Texture backgroundTexture;

    sf::Sprite backgroundSprite;
};

#endif // GAME_H
