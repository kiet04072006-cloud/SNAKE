//Vẽ cửa sổ setting
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

void opensetting() {

    RenderWindow Setting(VideoMode(900, 700), "Setting", Style::Default);

    Texture anh2;
    anh2.loadFromFile("Graphics/nenanh.jpg");
    Sprite nen2(anh2);
    float scaleX = (float)Setting.getSize().x / anh2.getSize().x;
    float scaleY = (float)Setting.getSize().y / anh2.getSize().y;
    nen2.setScale(scaleX, scaleY);
    while (Setting.isOpen()) {
        Event e;
        while (Setting.pollEvent(e)) {
            if (e.type == Event::Closed)
                Setting.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape)
                    Setting.close();
            }
        }
        Setting.clear();
        Setting.draw(nen2);
        Setting.display();
    }
}
