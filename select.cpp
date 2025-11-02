//Vẽ 2 lựa chọn "Single" và "Multiple" + lên xuống
#include "select.h"

MainMenu2::MainMenu2(float width, float height) {
    if (!font.loadFromFile("fontchu/font-times-new-roman.ttf"))
        cout << "Không tìm thấy font!" << endl;


    options[0].setFont(font);
    options[0].setFillColor(Color::Blue);
    options[0].setString("Single");
    options[0].setCharacterSize(70);
    options[0].setPosition(Vector2f(300, 150));


    options[1].setFont(font);
    options[1].setFillColor(Color::Black);
    options[1].setString("Multiple");
    options[1].setCharacterSize(70);
    options[1].setPosition(Vector2f(300, 300));

    MainMenuSelected = 0;
}

MainMenu2::~MainMenu2() {}
void MainMenu2::draw(RenderWindow& window) {
    for (int i = 0; i < 2; i++) {
        window.draw(options[i]);
    }
}

void MainMenu2::MoveUp() {
    options[MainMenuSelected].setFillColor(Color::Black);
    MainMenuSelected--;
    if (MainMenuSelected < 0) MainMenuSelected = Max_main_menuu - 1;
    options[MainMenuSelected].setFillColor(Color::Blue);
}

void MainMenu2::MoveDown() {
    options[MainMenuSelected].setFillColor(Color::Black);
    MainMenuSelected++;
    if (MainMenuSelected >= Max_main_menuu) MainMenuSelected = 0;
    options[MainMenuSelected].setFillColor(Color::Blue);
}

