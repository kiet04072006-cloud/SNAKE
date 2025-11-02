#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#define Max_main_menuu 2

class MainMenu2
{
public:
	MainMenu2(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}
	~MainMenu2();
private:
	int MainMenuSelected;
	Font font;
	Text options[2];
};

