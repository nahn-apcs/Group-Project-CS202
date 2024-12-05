#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"

class Character {
public:
    Character(sf::Texture& idleTexture, std::vector<sf::Texture>& runTextures, int x, int y);

    void update(float deltaTime, const Map& map);
    void move(float dx, float dy, const Map& map);
    void jump();
    void draw(sf::RenderWindow& window);
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }
    void drawBounds(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    float velocityX, velocityY;
    bool onGround;
    bool isJumping;
    Animation* runAnimation;  // Pointer to the running animation
    sf::Texture idle;
    const float gravity = 600.f;
    const float jumpStrength = -600.f;
    const float moveSpeed = 200.f;

    void handleCollisions(const Map& map);
    void applyGravity(float deltaTime);
    void applyFriction(float deltaTime);
    int checkWallCollision(float dx, float dy, const Map& map);
};

#endif
