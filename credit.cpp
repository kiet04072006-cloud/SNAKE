// Vẽ cửa sổ credit
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

void openCredit() {

    RenderWindow Credit(VideoMode(900, 700), "Credit", Style::Default);

    // ===== Ảnh nền =====
    Texture anh2;
    anh2.loadFromFile("Graphics/nenanh.jpg");
        
    Sprite nen2(anh2);
    float scaleX = (float)Credit.getSize().x / anh2.getSize().x;
    float scaleY = (float)Credit.getSize().y / anh2.getSize().y;
    nen2.setScale(scaleX, scaleY);

    // ===== Font =====
    Font font;
    font.loadFromFile("fontchu/font-times-new-roman.ttf");
       

    // ===== Danh sách các dòng credit =====
    vector<string> creditLines = {
        "Produced by: Group 5",
        "Directed by: Group 5",
        "Music: ThanhfLong",
        "Visual Design: ThanhfLong and Chatgpt",
        "Special thanks to Mr.The and all who listened.",
        "THE END"
    };

    // ===== Tạo các Text từ danh sách =====
    vector<Text> creditTexts;
    for (const auto& line : creditLines) {
        Text t(line, font, 36);
        t.setFillColor(Color::Black);
        creditTexts.push_back(t);
    }

    // ===== Biến điều khiển hiển thị từng dòng =====
    Clock clock;
    float delayPerLine = 1.0f; // 1 giây giữa các dòng
    int currentLine = 0;
    bool creditsDone = false;
    float startY = 200.f; // vị trí dòng đầu tiên

    // ===== Vòng lặp chính của cửa sổ credit =====
    while (Credit.isOpen()) {
        Event e;
        while (Credit.pollEvent(e)) {
            if (e.type == Event::Closed)
                Credit.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape)
                    Credit.close();
            }
        }

        // ===== Cập nhật thời gian hiển thị dòng mới =====
        if (!creditsDone && clock.getElapsedTime().asSeconds() > delayPerLine) {
            clock.restart();
            if (currentLine < (int)creditTexts.size())
                currentLine++;
            else
                creditsDone = true;
        }

        // ===== Vẽ lên cửa sổ =====
        Credit.clear();
        Credit.draw(nen2); // vẽ nền

        // Vẽ các dòng đã xuất hiện
        for (int i = 0; i < currentLine; ++i) {
            FloatRect bounds = creditTexts[i].getLocalBounds();
            creditTexts[i].setPosition(
                (Credit.getSize().x - bounds.width) / 2.f,
                startY + i * 60.f
            );
            Credit.draw(creditTexts[i]);
        }
        Credit.display();
    }
}
