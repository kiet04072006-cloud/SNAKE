#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Single.h"
#include"Game.h"
#include"Map.h"

using namespace sf;
using namespace std;

void SinglePlayer() {
    const int WINDOW_W = 30 * 30;
    const int WINDOW_H = 30 * 25;
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SĂN RẮN - SFML");
    sf::Font font;
    if (!font.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/fontchu/font-times-new-roman.ttf")) {
        printf(" font arial.ttf\\n");
    }

    Game game;

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) game.changeDirection(Up);
                if (e.key.code == sf::Keyboard::Down) game.changeDirection(Down);
                if (e.key.code == sf::Keyboard::Left) game.changeDirection(Left);
                if (e.key.code == sf::Keyboard::Right) game.changeDirection(Right);
                if (e.key.code == sf::Keyboard::R || e.key.code == sf::Keyboard::Space) {
                    if (!game.isAlive()) game.reset();
                }
            }
        } 
        game.update(dt);
        window.clear(sf::Color(22, 22, 22));
        game.draw(window, &font);
        window.display();
    }
}