#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "play.h"
#include "settingmenu.h"
#include "settingwindow.h"
#include "volume.h"
#include "select.h"
#include "setting.h"
using namespace sf;
int main() {
    RenderWindow MENU(VideoMode(900, 700), "Main Menu", Style::Default);
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

    SoundBuffer nhac;
    nhac.loadFromFile("music/pop.mp3");
    Sound nhacthtsu(nhac);
    nhacthtsu.setVolume(gVolume);                 // NEW: áp âm lượng ban đầu

    Music backgroundMusic;
    backgroundMusic.openFromFile("music/xoso.mp3");
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(gVolume);           // NEW: áp âm lượng ban đầu
    backgroundMusic.play();

    Texture nen;
    nen.loadFromFile("Graphics/snakegamebackground.jpg");
    Sprite bg(nen);

    float scaleX = (float)MENU.getSize().x / nen.getSize().x;
    float scaleY = (float)MENU.getSize().y / nen.getSize().y;
    bg.setScale(scaleX, scaleY);

    while (MENU.isOpen()) {

        Event sukien;
        while (MENU.pollEvent(sukien)) {
            if (sukien.type == Event::Closed)
                MENU.close();

            if (sukien.type == Event::KeyReleased) {
                if (sukien.key.code == Keyboard::Up) {
                    mainMenu.MoveUp();
                    nhacthtsu.setVolume(gVolume); // NEW: luôn sync SFX theo gVolume mới nhất
                    nhacthtsu.play();
                    break;
                }
                if (sukien.key.code == Keyboard::Down) {
                    mainMenu.MoveDown();
                    nhacthtsu.setVolume(gVolume); // NEW
                    nhacthtsu.play();
                    break;
                }
                if (sukien.key.code == Keyboard::Return) {
                    int x = mainMenu.MainMenuPressed();
                    if (x == 0) {
                        // Trước khi vào game
                        backgroundMusic.stop();     // dừng nhạc nền
                        MENU.setVisible(false);     // ẩn cửa sổ menu (không đóng)
                        // MENU.setActive(false);   // (tuỳ chọn) nhả context nếu game dùng OpenGL khác

                        playGame();                 // chạy game (hàm này return khi bạn thoát game)

                        // Sau khi thoát game, quay lại menu
                        MENU.setVisible(true);      // hiện lại cửa sổ menu
                        // MENU.setActive(true);    // (nếu bạn đã setActive(false) ở trên)
                        MENU.requestFocus();        // lấy lại focus cho cửa sổ
                        backgroundMusic.setVolume(gVolume); // NEW: áp lại volume người dùng đã chỉnh
                        backgroundMusic.play();     // phát lại nhạc nền

                        // Vẽ lại ngay để tránh khung hình đen trong 1 tick
                        MENU.clear();
                        MENU.draw(bg);
                        mainMenu.draw(MENU);
                        MENU.display();
                    }

                    if (x == 1) {
                        // --- Trước khi mở Setting ---
                        backgroundMusic.stop();       // Dừng nhạc nền
                        MENU.setVisible(false);

                        runSettings(); // Trong Setting, khi chọn Volume bạn sẽ mở volumesetting() và cập nhật gVolume

                        // --- Sau khi thoát Setting ---
                        MENU.setVisible(true);        // Hiện lại cửa sổ menu
                        MENU.requestFocus();          // Lấy lại focus
                        // Áp lại volume mới (nếu người dùng vừa chỉnh)
                        backgroundMusic.setVolume(gVolume); // NEW
                        nhacthtsu.setVolume(gVolume);       // NEW
                        backgroundMusic.play();             // Phát lại nhạc nền

                        // Vẽ lại ngay khung hình menu để tránh màn đen
                        MENU.clear();
                        MENU.draw(bg);
                        mainMenu.draw(MENU);
                        MENU.display();
                    }

                    if (x == 2) {
                        MENU.close();
                    }

                }
            }
        }

        MENU.clear();
        MENU.draw(bg);
        mainMenu.draw(MENU);
        MENU.display();
    }
    return 0;
}
