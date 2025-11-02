//Chỉnh âm thanh khi chọn "Volume" ở settingwindow
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
using namespace sf;
float gVolume = 50;
// --- Slider đơn giản: track + progress + knob tròn ---
class VolumeSlider {
public:
    VolumeSlider(Vector2f pos, Vector2f size, float init = 50.f)
        : position(pos), size(size), value(init) {

        track.setPosition(position);
        track.setSize(size);
        track.setFillColor(Color(220, 220, 220));
        track.setOutlineThickness(2.f);
        track.setOutlineColor(Color(100, 100, 100));

        knob.setRadius(size.y * 0.7f / 2.f);
        knob.setOrigin(knob.getRadius(), knob.getRadius());
        knob.setFillColor(Color(70, 130, 180));
        knob.setOutlineThickness(2.f);
        knob.setOutlineColor(Color::Black);

        updateKnobFromValue();
    }

    void handleEvent(const Event& e, const RenderWindow& win) {
        if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
            Vector2f mp = (Vector2f)Mouse::getPosition(win);
            if (knob.getGlobalBounds().contains(mp) || track.getGlobalBounds().contains(mp)) {
                dragging = true;
                setValueFromMouseX(mp.x);
            }
        }
        else if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left) {
            dragging = false;
        }
        else if (e.type == Event::MouseMoved && dragging) {
            Vector2f mp = (Vector2f)Mouse::getPosition(win);
            setValueFromMouseX(mp.x);
        }
    }

    void draw(RenderWindow& win) {
        // progress
        RectangleShape progress;
        progress.setPosition(position);
        float filled = knob.getPosition().x - position.x;
        if (filled < 0) filled = 0;
        progress.setSize({ filled, size.y });
        progress.setFillColor(Color(100, 180, 220));

        win.draw(track);
        win.draw(progress);
        win.draw(knob);
    }

    float get() const { return value; }          // 0..100
    void  set(float v) { value = std::clamp(v, 0.f, 100.f); updateKnobFromValue(); }

private:
    Vector2f position, size;
    float value;
    bool dragging = false;
    RectangleShape track;
    CircleShape    knob;

    void updateKnobFromValue() {
        float t = value / 100.f;                 // 0..1
        float x = position.x + t * size.x;
        float y = position.y + size.y * 0.5f;
        knob.setPosition({ x, y });
    }
    void setValueFromMouseX(float mouseX) {
        float x = std::clamp(mouseX, position.x, position.x + size.x);
        float t = (x - position.x) / size.x;
        value = 100.f * t;
        updateKnobFromValue();
    }
};

void volumesetting() {
    RenderWindow VolumeSetting(VideoMode(900, 700), "Volume", Style::Default);
    VolumeSetting.setFramerateLimit(120);

    // --- Nền ---
    Texture anh2;
    Sprite nen2;
    if (anh2.loadFromFile("Graphics/nenanh.jpg")) {
        nen2.setTexture(anh2);
        float scaleX = (float)VolumeSetting.getSize().x / anh2.getSize().x;
        float scaleY = (float)VolumeSetting.getSize().y / anh2.getSize().y;
        nen2.setScale(scaleX, scaleY);
    }

    // --- Slider ---
    VolumeSlider slider({ 150.f, 330.f }, { 600.f, 24.f }, 50.f);

    // --- Font + Text (tùy chọn) ---
    Font font;
    bool hasFont = font.loadFromFile("fontchu/font-times-new-roman.ttf");
    Text title, hint, percent;
    if (hasFont) {
        title.setFont(font);
        title.setString("Chinh am luong");
        title.setCharacterSize(42);
        title.setFillColor(Color::White);
        title.setPosition(150.f, 250.f);

        hint.setFont(font);
        hint.setString("Keo thanh bang chuot | ESC de quay lai");
        hint.setCharacterSize(22);
        hint.setFillColor(Color(230, 230, 230));
        hint.setPosition(150.f, 380.f);

        percent.setFont(font);
        percent.setCharacterSize(28);
        percent.setFillColor(Color::White);
    }

    // --- Nhac demo (co cung duoc, khong co van chay) ---
    Music music;
    bool musicLoaded = false;
    if (music.openFromFile("music/xoso.mp3")) {
        musicLoaded = true;
        music.setLoop(true);
        music.setVolume(slider.get());  // đồng bộ volume ban đầu
        music.play();
    }
    else {
        std::cout << "Khong tim thay music.ogg (demo). Slider van hoat dong, chi khong co am thanh.\n";
    }

    while (VolumeSetting.isOpen()) {
        Event e;
        while (VolumeSetting.pollEvent(e)) {
            if (e.type == Event::Closed) VolumeSetting.close();
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) VolumeSetting.close();

            // Chuột điều khiển slider
            slider.handleEvent(e, VolumeSetting);
        }

        // Cập nhật nhạc theo slider
        if (musicLoaded) music.setVolume(slider.get());

        // Cập nhật text %
        if (hasFont) {
            char buf[16];
            std::snprintf(buf, sizeof(buf), "%.0f%%", std::round(slider.get()));
            percent.setString(buf);
            percent.setPosition(150.f + 600.f + 20.f, 320.f);
        }

        VolumeSetting.clear();
        if (anh2.getSize().x) VolumeSetting.draw(nen2);
        if (hasFont) { VolumeSetting.draw(title); VolumeSetting.draw(hint); }
        slider.draw(VolumeSetting);
        if (hasFont) VolumeSetting.draw(percent);
        VolumeSetting.display();
    }
    gVolume = slider.get();
}
