// Vẽ cửa sổ "play"
#include"Single.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "select.h"
using namespace sf;
using namespace std;

void playGame() {

    RenderWindow Play(VideoMode(900, 700), "Play", Style::Default);


    Texture anh2;
    anh2.loadFromFile("Graphics/nenanh.jpg");
    Sprite nen2(anh2);
    float scaleX = (float)Play.getSize().x / anh2.getSize().x;
    float scaleY = (float)Play.getSize().y / anh2.getSize().y;
    nen2.setScale(scaleX, scaleY);

    MainMenu2 modeMenu(Play.getSize().x, Play.getSize().y);

    while (Play.isOpen()) {
        Event e;
        while (Play.pollEvent(e)) {
            if (e.type == Event::Closed)
                Play.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape)
                    Play.close();
                if (e.key.code == Keyboard::Up) {
                    modeMenu.MoveUp();
                }
                if (e.key.code == Keyboard::Down) {
                    modeMenu.MoveDown();
                }
                if (e.key.code == Keyboard::Return) {
                    int pick = modeMenu.MainMenuPressed();
                    if (pick == 0) {
						SinglePlayer();
                   }
                    Play.close();
                }
            }
        }
        Play.clear();
        Play.draw(nen2);
        modeMenu.draw(Play);
        Play.display();
    }
}
