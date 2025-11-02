#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <deque>
#include"Map.h"

enum Direction { Up, Down, Left, Right };

class Game {
private:
    Map map;
    sf::Texture headUp, headDown, headLeft, headRight;
    sf::Texture bodyVertical, bodyHorizontal;
    sf::Texture AppleTexture, BananaTexture, WaterMelonTexture;
    sf::Texture tailUp, tailDown, tailLeft, tailRight;
	sf::Texture turnDownLeft, turnDownRight, turnUpLeft, turnUpRight;
    void placeFood();
    std::deque<sf::Vector2i> snake;
    sf::Vector2i food;
    Direction dir;
    bool alive;
    float moveTimer;
    float moveInterval;
    unsigned int score;
    int checkFood;
public:
    Game();
    void reset();
    void update(float dt);
    void changeDirection(Direction d);
    void draw(sf::RenderWindow& window, sf::Font* font = nullptr);
    bool isAlive() const { return alive; }
    unsigned int getScore() const { return score; }
};
#endif