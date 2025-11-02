#include "Game.h"
#include <cstdlib>
#include <ctime>


const int CELL_SIZE = 30;
const int GRID_W = 30;
const int GRID_H = 25;
const float START_SPEED = 0.12f;



Game::Game() : map(GRID_H, GRID_W ) {

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    headUp.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/head_up.png");
    headDown.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/head_down.png");
    headLeft.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/head_left.png");
    headRight.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/head_right.png");
    bodyVertical.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/body_vertical.png");
    bodyHorizontal.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/body_horizontal.png");
    AppleTexture.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/apple.png");
    BananaTexture.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/chuoi.png");
    WaterMelonTexture.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/duahau.jpg");
	turnDownLeft.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/body_bottomleft.png");
	turnDownRight.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/body_bottomright.png");
	turnUpLeft.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/body_topleft.png");
	turnUpRight.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/body_topright.png");
	tailDown.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/tail_down.png");
	tailUp.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/tail_up.png");
	tailLeft.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/tail_left.png");
	tailRight.loadFromFile("C:/C++/SNAKE 31 10/TESTSFML2.6.2/Graphics/tail_right.png");
	map.setWall();
    reset();
}

void Game::reset() {
    snake.clear();
    while(true){
        int x = std::rand() % GRID_W;
        int y = std::rand() % GRID_H;
        if (!map.isWall(x, y) && !map.isWall(x - 1, y) && !map.isWall(x - 2, y)&&!map.isWall(x+1, y)&&!map.isWall(x+2,y)) {
            snake.push_back({ x, y });
            snake.push_back({ x - 1, y });
            snake.push_back({ x - 2, y });
            dir = Right;
            break;
        }
	}
    alive = true;
    moveTimer = 0.f;
    moveInterval = START_SPEED;
    score = 0;
    placeFood();

}

void Game::placeFood() {
    while (true) {
        int check = rand()% 3;
        checkFood = check + 1;
        int x, y;
        if (check == 2) {
             x = std::rand() % (GRID_W-1);
            y = std::rand() % (GRID_H-1);
        }
        else {
            x = std::rand() % GRID_W;
            y = std::rand() % GRID_H;
        }
        sf::Vector2i p{ x, y };
        bool onSnake = false;
        if (check == 0 || check == 1) {
            for (auto& s : snake) if (s == p) { onSnake = true; break; }
        }
        else {
                for (int i = 0; i < 2 && !onSnake; i++) {
                    for (int j = 0; j < 2&& !onSnake; j++) {
                        for (auto& s : snake) {
                            if (s == sf::Vector2i(x + i, y + j)) {
                                onSnake = true;
                                break;
                            }
                        }
                    }
                }
            
        }
        if (!onSnake&&!map.isWall(x,y)) {
            food = { x, y};
            break;
        }
    }
}

void Game::changeDirection(Direction d) {
    if ((dir == Up && d == Down) || (dir == Down && d == Up) ||
        (dir == Left && d == Right) || (dir == Right && d == Left)) return;
    dir = d;
}

void Game::update(float dt) {
    if (!alive) return;
    moveTimer += dt;
    if (moveTimer < moveInterval) return;
    moveTimer -= moveInterval;
    sf::Vector2i head = snake.front();
    sf::Vector2i newHead = head;
    switch (dir) {
    case Up:    newHead.y -= 1; break;
    case Down:  newHead.y += 1; break;
    case Left:  newHead.x -= 1; break;
    case Right: newHead.x += 1; break;
    }
    if (newHead.x < 0 || newHead.x >= GRID_W || newHead.y < 0 || newHead.y >= GRID_H) {
        alive = false; return;
    }
    else {
        if(map.isWall(newHead.x, newHead.y)) {
            alive = false; return;
		}
    }
    for (auto& s : snake) if (s == newHead) { alive = false; return; }

    snake.push_front(newHead);

    bool eat = false;
    if (checkFood == 3) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (newHead == sf::Vector2i(food.x + i, food.y + j)) {
                    eat = true;
                }
            }
        }
    }
    else {
		eat = (newHead == food);
    }
    if(eat) {
        if (checkFood == 1) {
              
            score += 10;
            moveInterval *= 0.95f;
                    
				
        }
        if (checkFood == 2) {
         
                score += 15;
                moveInterval *= 0.99f;
        
        }
        if (checkFood == 3) {
            score += 50;
            moveInterval *= 0.95f;
  
        }
        placeFood();
    }
    else {
        snake.pop_back();
    }
}

void Game::draw(sf::RenderWindow& window, sf::Font* font) {
    sf::RectangleShape cell(sf::Vector2f((float)CELL_SIZE - 1.f, (float)CELL_SIZE - 1.f));
	
    // Draw background grid
    //for (int x = 0; x < GRID_W; ++x)
    //    for (int y = 0; y < GRID_H; ++y) {
    //        cell.setPosition((float)x * CELL_SIZE, (float)y * CELL_SIZE);
    //        cell.setFillColor(sf::Color(18, 18, 18));
    //        window.draw(cell);
    //    }
    map.drawWall(window);
    // Draw food
    sf::Sprite foodsprite;
    if (checkFood == 1) {
        foodsprite.setTexture(AppleTexture);
        float scaleX = (float)CELL_SIZE / foodsprite.getTexture()->getSize().x;
        float scaleY = (float)CELL_SIZE / foodsprite.getTexture()->getSize().y;
        foodsprite.setScale(scaleX, scaleY);
    }   
    if (checkFood == 2) {
        foodsprite.setTexture(BananaTexture);
        float scaleX = (float)CELL_SIZE / foodsprite.getTexture()->getSize().x;
        float scaleY = (float)CELL_SIZE / foodsprite.getTexture()->getSize().y;
        foodsprite.setScale(scaleX, scaleY);
    }  
    if (checkFood == 3) {
        foodsprite.setTexture(WaterMelonTexture);
        float scaleX = (float)CELL_SIZE*2 / foodsprite.getTexture()->getSize().x;
        float scaleY = (float)CELL_SIZE*2 / foodsprite.getTexture()->getSize().y;
        foodsprite.setScale(scaleX, scaleY);
    }
   
    foodsprite.setPosition((float)this->food.x * CELL_SIZE, (float)this->food.y * CELL_SIZE);
    window.draw(foodsprite);


    // Draw snake
    for (int i = 0; i < snake.size(); ++i) {
        sf::Sprite sprite;
        sf::Vector2i curr = snake[i];

        if (i == 0) {
            // ---- ĐẦU ----
            switch (dir) {
            case Up:    sprite.setTexture(headUp); break;
            case Down:  sprite.setTexture(headDown); break;
            case Left:  sprite.setTexture(headLeft); break;
            case Right: sprite.setTexture(headRight); break;
            }
        }
        else if (i == snake.size() - 1) {
            // ---- ĐUÔI ----
            sf::Vector2i prev = snake[i - 1];
            if (prev.x < curr.x) sprite.setTexture(tailRight);
            else if (prev.x > curr.x) sprite.setTexture(tailLeft);
            else if (prev.y < curr.y) sprite.setTexture(tailDown);
            else if (prev.y > curr.y) sprite.setTexture(tailUp);
        }
        else {
            // ---- THÂN ----
            sf::Vector2i prev = snake[i - 1];
            sf::Vector2i next = snake[i + 1];

            // Cùng hàng
            if (prev.y == curr.y && next.y == curr.y)
                sprite.setTexture(bodyHorizontal);
            // Cùng cột
            else if (prev.x == curr.x && next.x == curr.x)
                sprite.setTexture(bodyVertical);
            // ---- KHÚC CUA ----
            else {
                if ((prev.x < curr.x && next.y < curr.y) || (next.x < curr.x && prev.y < curr.y))
                    sprite.setTexture(turnUpLeft); // từ trái sang trên
                else if ((prev.x < curr.x && next.y > curr.y) || (next.x < curr.x && prev.y > curr.y))
                    sprite.setTexture(turnDownLeft); // từ trái sang dưới
                else if ((prev.x > curr.x && next.y < curr.y) || (next.x > curr.x && prev.y < curr.y))
                    sprite.setTexture(turnUpRight); // từ phải sang trên
                else if ((prev.x > curr.x && next.y > curr.y) || (next.x > curr.x && prev.y > curr.y))
                    sprite.setTexture(turnDownRight); // từ phải sang dưới
            }
        }

        // Cài đặt vị trí & scale
        float scaleX = (float)CELL_SIZE / sprite.getTexture()->getSize().x;
        float scaleY = (float)CELL_SIZE / sprite.getTexture()->getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition((float)curr.x * CELL_SIZE, (float)curr.y * CELL_SIZE);
        window.draw(sprite);
    }

    // Draw score text
    if (font) {
        sf::Text scoreText;
        if (alive) {
            scoreText.setFont(*font);
            scoreText.setCharacterSize(18);
            scoreText.setPosition(6.f , 6.f);
            scoreText.setString("Score: " + std::to_string(score) );
        }
        else {
            scoreText.setFont(*font);
            scoreText.setCharacterSize(50);
            scoreText.setPosition(100.f, 720.f / 2);
			scoreText.setFillColor(sf::Color::Black);
            scoreText.setString("Score Recorded: " + std::to_string(score) + "\n[GAME OVER] Press R or Space");
   
        }
        window.draw(scoreText);
    }
}
