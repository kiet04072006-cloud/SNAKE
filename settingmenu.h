#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#define Max_main_menu 2

class MainMenuSetting {
public:
    MainMenuSetting(float width, float height);
    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int MainMenuSettingPressed() const { return MainMenuSettingSelected; }
    ~MainMenuSetting();

private:
    int  MainMenuSettingSelected = 0;
    Font font;
    Text options[Max_main_menu]; // 2 mục: Volume, Music
};
