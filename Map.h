#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;
class Map {
private:
	int   MAP_W = 30;
	int   MAP_H = 25;
	vector <Vector2i> wall;
	vector <vector<bool>> Onwall;
public:
	Map(int r, int c) : MAP_H(r), MAP_W(c), Onwall(r, vector<bool>(c, false)) {}
	void drawWall(RenderWindow& window);
	void setWall();
	bool isWall(int i, int j) const;
};