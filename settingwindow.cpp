//vẽ nền khi chọn giữa volume và credit
#include "settingwindow.h"
#include "settingmenu.h"            // class MainMenuSetting của bạn
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "volume.h"
#include "credit.h"
using namespace sf;
using namespace std;

void runSettings() {
    // Tạo cửa sổ Setting riêng
    RenderWindow Setting(VideoMode(900, 700), "Setting", Style::Default);

    //Load nhạc
    SoundBuffer nhac;
    nhac.loadFromFile("music/pop.mp3");
    Sound nhacthtsu(nhac);
    // --- Nền (nếu có) ---
    Texture bgTex;
    Sprite  bg;
    if (bgTex.loadFromFile("Graphics/nenanh.jpg")) {
        bg.setTexture(bgTex);
        float sx = static_cast<float>(Setting.getSize().x) / bgTex.getSize().x;
        float sy = static_cast<float>(Setting.getSize().y) / bgTex.getSize().y;
        bg.setScale(sx, sy);
    }

    // --- Menu Setting 2 mục: Volume / Music ---
    MainMenuSetting settingMenu(Setting.getSize().x, Setting.getSize().y);

    while (Setting.isOpen()) {
        Event e;
        while (Setting.pollEvent(e)) {
            if (e.type == Event::Closed) Setting.close();

            if (e.type == Event::KeyReleased) {
                if (e.key.code == Keyboard::Escape) {
                    Setting.close(); // thoát Setting
                }
                else if (e.key.code == Keyboard::Up) {
                    settingMenu.MoveUp();
                    nhacthtsu.play();
                    break;
                }
                else if (e.key.code == Keyboard::Down) {
                    settingMenu.MoveDown();
                    nhacthtsu.play();
                    break;
                }
                else if (e.key.code == Keyboard::Return) {
                    int opt = settingMenu.MainMenuSettingPressed();
                    if (opt == 0) {
                        volumesetting();
                    }
                    else if (opt == 1) {
                        openCredit();
                    }
                }
            }
        }

        Setting.clear(Color(20, 20, 30));
        Setting.draw(bg);
        settingMenu.draw(Setting);
        Setting.display();
    }
}
