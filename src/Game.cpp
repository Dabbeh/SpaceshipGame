#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <filesystem>

Game::Game()
    : window(sf::VideoMode(1280, 720), "SpaceShip Game"),
      score(0),
      health(3),
      isGameOver(false)
{
    // Load persistent textures
    spaceshipTexture = loadTexture("assets/images/spaceship.png");
    bulletTexture = loadTexture("assets/images/laserRed01.png");
    meteorTexture = loadTexture("assets/images/meteorBrown_big1.png");
    enemyTexture = loadTexture("assets/images/enemyBlack1.png");
    backgroundTexture = loadTexture("assets/images/background.png");

    // Setup background sprite
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Create spaceship using the persistent spaceshipTexture
    spaceship = Spaceship(spaceshipTexture);

    // Load font
    if (!font.loadFromFile("assets/font/ARIAL.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Setup UI texts
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10.f, 40.f);
    scoreText.setString("Score: " + std::to_string(score));

    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(10.f, 10.f);
    healthText.setString("Health: " + std::to_string(health));

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(400, 200);

    restartText.setFont(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(400, 300);

    exitText.setFont(font);
    exitText.setString("Press ESC to Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(400, 350);
}

sf::Texture Game::loadTexture(const std::string &path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading texture: " << path << std::endl;
    }
    return texture;
}

void Game::spawnBullet() {
    // Position the bullet at the center top of the spaceship
    sf::Vector2f bulletPos = spaceship.getPosition();
    bulletPos.x += spaceship.getSize().x / 2;  // Position it in the center of the spaceship

    Bullet bullet(bulletTexture, bulletPos, 500.f);  // Create bullet object
    bullets.push_back(bullet);  // Add it to the bullets list
}

void Game::run() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    while (window.isOpen()) {
        processEvents();
        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (isGameOver && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                // Reset game state on restart
                score = 0;
                health = 3;
                isGameOver = false;
                bullets.clear();
                meteors.clear();
                enemies.clear();
                spaceship.resetPosition();
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void Game::update(float dt) {
    if (isGameOver)
        return;

    // Handle spaceship movement
    sf::Vector2f pos = spaceship.getPosition();
    float spaceshipSpeed = 300.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pos.x -= spaceshipSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pos.x += spaceshipSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pos.y -= spaceshipSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pos.y += spaceshipSpeed * dt;

    // Bound checks to keep the spaceship within the window
    if (pos.x < 0.f) pos.x = 0.f;
    if (pos.x + spaceship.getSize().x > window.getSize().x)
        pos.x = window.getSize().x - spaceship.getSize().x;
    if (pos.y < 0.f) pos.y = 0.f;
    if (pos.y + spaceship.getSize().y > window.getSize().y)
        pos.y = window.getSize().y - spaceship.getSize().y;

    spaceship.setPosition(pos);

    // Spawn bullets
    static float bulletSpawnTimer = 0.f;
    bulletSpawnTimer += dt;
    float bulletSpawnInterval = 0.2f;  // Fire a bullet every 0.2 seconds
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletSpawnTimer >= bulletSpawnInterval) {
        spawnBullet();  // Spawn the bullet
        bulletSpawnTimer = 0.f;  // Reset the timer after firing a bullet
    }

    // Spawn meteors at intervals
    static float meteorSpawnTimer = 0.f;
    meteorSpawnTimer += dt;
    float meteorSpawnInterval = 3.f;
    if (meteorSpawnTimer >= meteorSpawnInterval) {
        spawnMeteor();
        meteorSpawnTimer = 0.f;
    }

    // Spawn enemies at intervals
    static float enemySpawnTimer = 0.f;
    enemySpawnTimer += dt;
    float enemySpawnInterval = 5.f;
    if (enemySpawnTimer >= enemySpawnInterval) {
        spawnEnemy();
        enemySpawnTimer = 0.f;
    }

    // Update game objects
    for (auto &bullet : bullets) {
        bullet.update(dt);
    }
    for (auto &meteor : meteors) {
        meteor.update(dt);
    }
    for (auto &enemy : enemies) {
        enemy.update(dt, spaceship.getPosition());
    }

    // Handle collisions and update score/health
    checkCollisions();

    // Update UI texts
    scoreText.setString("Score: " + std::to_string(score));
    healthText.setString("Health: " + std::to_string(health));
}

void Game::render() {
    window.clear();
    // Draw background first
    window.draw(backgroundSprite);
    window.draw(spaceship.getSprite());
    for (auto &bullet : bullets)
        window.draw(bullet.getSprite());
    for (auto &meteor : meteors)
        window.draw(meteor.getSprite());
    for (auto &enemy : enemies)
        window.draw(enemy.getSprite());

    window.draw(scoreText);
    window.draw(healthText);
    if (isGameOver) {
        window.draw(gameOverText);
        window.draw(restartText);
        window.draw(exitText);
    }
    window.display();
}

void Game::spawnMeteor() {
    float randomX = static_cast<float>(rand() % window.getSize().x);
    sf::Vector2f meteorPos(randomX, 0.f);
    // Use the persistent meteorTexture
    Meteor meteor(meteorTexture, meteorPos, 200.f);
    meteor.setHitPoints(4);
    meteors.push_back(meteor);
}

void Game::spawnEnemy() {
    float randomX = static_cast<float>(rand() % window.getSize().x);
    sf::Vector2f enemyPos(randomX, -50.f);
    // Use the persistent enemyTexture
    Enemy enemy(enemyTexture, enemyPos, 300.f);
    enemy.setHitPoints(5);
    sf::Vector2f direction = spaceship.getPosition() - enemyPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance != 0)
        direction /= distance;
    enemy.setDirection(direction);
    enemies.push_back(enemy);
}

bool Game::checkCollisions() {
    // Bullet vs. meteor collisions
    for (size_t i = 0; i < bullets.size(); ++i) {
        for (size_t j = 0; j < meteors.size(); ++j) {
            if (bullets[i].getSprite().getGlobalBounds().intersects(meteors[j].getSprite().getGlobalBounds())) {
                meteors[j].decreaseHealth(1);  // Decrease meteor health
                if (meteors[j].getHealth() <= 0) {
                    score += 5;  // Score increase when meteor is destroyed
                    meteors.erase(meteors.begin() + j);  // Remove meteor if destroyed
                }
                bullets.erase(bullets.begin() + i);  // Remove bullet after hit
                return true;
            }
        }
    }

    // Bullet vs. enemy collisions
    for (size_t i = 0; i < bullets.size(); ++i) {
        for (size_t j = 0; j < enemies.size(); ++j) {
            if (bullets[i].getSprite().getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds())) {
                enemies[j].decreaseHealth(1);  // Decrease enemy health
                if (enemies[j].getHealth() <= 0) {
                    score += 10;  // Score increase when enemy is destroyed
                    enemies.erase(enemies.begin() + j);  // Remove enemy if destroyed
                }
                bullets.erase(bullets.begin() + i);  // Remove bullet after hit
                return true;
            }
        }
    }

    // Check for collisions with spaceship
    for (size_t i = 0; i < meteors.size(); ++i) {
        if (spaceship.getSprite().getGlobalBounds().intersects(meteors[i].getSprite().getGlobalBounds())) {
            health--;  // Decrease health when spaceship hits meteor
            meteors.erase(meteors.begin() + i);  // Remove meteor after collision
            if (health <= 0) {
                isGameOver = true;
            }
        }
    }

    for (size_t i = 0; i < enemies.size(); ++i) {
        if (spaceship.getSprite().getGlobalBounds().intersects(enemies[i].getSprite().getGlobalBounds())) {
            health--;  // Decrease health when spaceship hits enemy
            enemies.erase(enemies.begin() + i);  // Remove enemy after collision
            if (health <= 0) {
                isGameOver = true;
            }
        }
    }

    return false;
}
