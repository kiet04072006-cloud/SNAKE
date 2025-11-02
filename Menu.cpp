//Vẽ các options và bấm nút lên xuống

#include "Menu.h"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("fontchu/font-times-new-roman.ttf"))
        cout << "Không tìm thấy font!" << endl;


    options[0].setFont(font);
    options[0].setFillColor(Color::Blue); 
    options[0].setString("Play");
    options[0].setCharacterSize(70);
    options[0].setPosition(Vector2f(300,150));


    options[1].setFont(font);
    options[1].setFillColor(Color::Black);
    options[1].setString("Setting");
    options[1].setCharacterSize(70);
    options[1].setPosition(Vector2f(300,300));

 
    options[2].setFont(font);
    options[2].setFillColor(Color::Black);
    options[2].setString("Exit");
    options[2].setCharacterSize(70);
    options[2].setPosition(Vector2f(300,450));

    MainMenuSelected = 0; 
}

MainMenu::~MainMenu() {}
void MainMenu::draw(RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(options[i]);
    }
}

void MainMenu::MoveUp() {
    options[MainMenuSelected].setFillColor(Color::Black);
    MainMenuSelected--;
    if (MainMenuSelected < 0) MainMenuSelected = Max_main_menu - 1;
    options[MainMenuSelected].setFillColor(Color::Blue);
}

void MainMenu::MoveDown() {
    options[MainMenuSelected].setFillColor(Color::Black);
    MainMenuSelected++;
    if (MainMenuSelected >= Max_main_menu) MainMenuSelected = 0;
    options[MainMenuSelected].setFillColor(Color::Blue);
}

