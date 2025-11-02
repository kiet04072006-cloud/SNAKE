#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Game.h"
using namespace sf;
using namespace std;

const int	CELL_SIZE = 30;
const int   MAP_W = 30;
const int   MAP_H = 25;

void Map::setWall() {
    for (int i = 0; i < MAP_H; i++) {
        for (int j = 0; j < MAP_W; j++) {
            if (i == 0 || j == 0 || i == MAP_H - 1 || j == MAP_W - 1) {
				    Onwall[i][j] = true;
            }
        }
    }

    int doorWidth = 3;
    int midX = MAP_W / 2;
    int midY = MAP_H / 2;

    for (int j = midX - doorWidth / 2; j <= midX + doorWidth / 2; j++) {
        Onwall[0][j] = false;
        Onwall[MAP_H - 1][j] = false;
    }

    for (int i = midY - doorWidth / 2; i <= midY + doorWidth / 2; i++) {
        Onwall[i][0] = false;
        Onwall[i][MAP_W - 1] = false;
    }

    int mid = MAP_W / 2;
    int startY = (MAP_H - 14) / 2;
    for (int i = startY; i < startY + 14; i++) {
        Onwall[i][mid] = true;
    }

    int centerY = MAP_H / 2;
    for (int j = mid - 6; j <= mid + 6; j++) {
        if ((j - mid) % 2 == 0)
            Onwall[centerY][j] = true;
    }

    for (int i = 3; i < 6; i++) {
        for (int j = 3; j < 6; j++) Onwall[i][j] = true;
        for (int j = MAP_W - 6; j < MAP_W - 3; j++) Onwall[i][j] = true;
        for (int j = 3; j < 6; j++) Onwall[MAP_H - i - 1][j] = true;
        for (int j = MAP_W - 6; j < MAP_W - 3; j++) Onwall[MAP_H - i - 1][j] = true;
    }

}

bool Map:: isWall(int x, int y) const {
    if (x >= 0 && x < MAP_W && y >= 0 && y < MAP_H)
        return Onwall[y][x];
    return false;
  }


void Map::drawWall(RenderWindow& window) {
    sf::RectangleShape cell(sf::Vector2f((float)CELL_SIZE - 1.f, (float)CELL_SIZE - 1.f));

        for (int i = 0; i < MAP_H; i++) {
            for (int j = 0; j < MAP_W; j++) {
				cell.setPosition((float)j * CELL_SIZE, (float)i * CELL_SIZE);
                if ((i + j) % 2 == 0)
                    cell.setFillColor(Color(164, 229, 109));
                else
                    cell.setFillColor(Color(154, 215, 97));

                window.draw(cell);
            }
        }

        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                if (Onwall[y][x]) {
                    cell.setPosition((float)x * CELL_SIZE, (float)y * CELL_SIZE);
                    cell.setFillColor(Color::Red);
                    window.draw(cell);
                }
            }
        }
}


