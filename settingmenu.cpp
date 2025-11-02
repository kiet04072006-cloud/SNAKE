//Vẽ 2 dòng Volume và Credit + nút bấm lên xuống
#include "settingmenu.h"

MainMenuSetting::MainMenuSetting(float width, float height) {
    if (!font.loadFromFile("fontchu/font-times-new-roman.ttf"))
        cout << "Khong tim thay font!\n";

    options[0].setFont(font);
    options[0].setFillColor(Color::Blue);
    options[0].setString("Volume");
    options[0].setCharacterSize(70);
    options[0].setPosition(Vector2f(330.f, 175.f));

    options[1].setFont(font);
    options[1].setFillColor(Color::Black);
    options[1].setString("Credit");
    options[1].setCharacterSize(70);
    options[1].setPosition(Vector2f(330.f, 350.f));

    MainMenuSettingSelected = 0;
}

MainMenuSetting::~MainMenuSetting() {}

void MainMenuSetting::draw(RenderWindow& window) {
    for (int i = 0; i < Max_main_menu; ++i) window.draw(options[i]);
}

void MainMenuSetting::MoveUp() {
    options[MainMenuSettingSelected].setFillColor(Color::Black);
    MainMenuSettingSelected--;
    if (MainMenuSettingSelected < 0) MainMenuSettingSelected = Max_main_menu - 1;
    options[MainMenuSettingSelected].setFillColor(Color::Blue);
}

void MainMenuSetting::MoveDown() {
    options[MainMenuSettingSelected].setFillColor(Color::Black);
    MainMenuSettingSelected++;
    if (MainMenuSettingSelected >= Max_main_menu) MainMenuSettingSelected = 0;
    options[MainMenuSettingSelected].setFillColor(Color::Blue);
}
