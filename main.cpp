#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"
#include <SFML/Window/Cursor.hpp>
#include "loginSystem/UserManager.h"
#include "gameMenu.h"

void changeTexture(sf::RectangleShape &rect, sf::Texture &m_texture, const std::string& newTexturePath) {
    m_texture.loadFromFile(newTexturePath);
    rect.setTexture(&m_texture);
}

void changeCursor(sf::RenderWindow &window,sf::Cursor &textCursor,textField &loginField,
                 textField &passwordField,const auto &activeCursor,const auto &cursor,
                 sf::Sound &clickSound) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isOverLoginField = loginField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    bool isOverPasswordField = passwordField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    static bool wasClicked = false;  // Переменная для отслеживания нажатия

    if (isOverLoginField || isOverPasswordField) {
        window.setMouseCursor(textCursor);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        window.setMouseCursor(activeCursor.value());
        // Если кнопка мыши была только что нажата (не удерживается), проигрываем звук
        if (!wasClicked) {
            clickSound.play();
            wasClicked = true;
        }
    } else {
        window.setMouseCursor(cursor.value());
        wasClicked = false;  // Сбрасываем флаг, когда кнопка отпущена
    }
}
void musicSettings(bool &keyPressed, sf::Music &music, bool &musicPlaying) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !keyPressed) {
        if (musicPlaying) {
            music.setVolume(0);
            musicPlaying = false;
        } else {
            music.setVolume(30);
            musicPlaying = true;
        }
        keyPressed = true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
        keyPressed = false;
    }
    if (music.getStatus() != sf::SoundSource::Status::Playing && musicPlaying) {
        music.play();
    }
}

enum class GameState {
    LoginMenu,
    GameMenu,
    Settings,
    Game
};

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Big patric", sf::Style::None);
    GameState currentState = GameState::LoginMenu;

    // Load a sprite to display
    const sf::Texture texture("../image/startWindow.png");
    sf::Sprite sprite(texture);

    // Add button
    button btn(false,360, 100, "", "../image/LoginButton3d_v2.png");

    btn.setPosition(780.f, 560.f);

    // Add textField
    textField loginField(360, 100, "Login Button","../image/LoginPasswordField_v2.png");
    loginField.setPosition(780.f, 240.f);

    // Add textField
    textField passwordField(360, 100, "Password Button","../image/LoginPasswordField_v2.png");
    passwordField.setPosition(780.f, 410.f);

    // Load a music to play
    sf::Music music("../music/bgm_6.ogg");
    music.setVolume(30);
    bool musicPlaying = true;
    bool keyPressed = false;

    // Load image for cursor
    sf::Image cursorImage("../image/notActiveCursor.png");
    sf::Image activeCursorImage("../image/activeCursor.png");

    // UserManager
    UserManager userManager("../loginSystem/loginData.txt");

    // Cursor
    const auto cursor = sf::Cursor::createFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
    const auto activeCursor = sf::Cursor::createFromPixels(activeCursorImage.getPixelsPtr(), activeCursorImage.getSize(), sf::Vector2u(0, 0));

    // Create a text cursor for text fields
    sf::Cursor textCursor(sf::Cursor::Type::Text);  // Create a Text cursor

    gameMenu startGameMenu(window);

    sf::SoundBuffer buffer("../music/pzdc.wav.");
    sf::Sound clickSound(buffer);
    clickSound.setVolume(50);

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Pass event to textField
            loginField.handleClick(window, *event);
            passwordField.handleClick(window, *event);

            loginField.handeTextInput(*event);
            passwordField.handeTextInput(*event);
        }
        window.clear();

        if (currentState == GameState::LoginMenu) {
            musicSettings(keyPressed,music,musicPlaying);
            changeCursor(window,textCursor,loginField,passwordField,activeCursor,cursor,clickSound);
            // Проверка логина при клике
            if (btn.isButtonClicked(window)) {
                if (userManager.loginUser(loginField.getUserInput(), passwordField.getUserInput())) {
                    currentState = GameState::GameMenu; // Переход к игровому меню
                    window.setMouseCursorVisible(false);
                    music.stop();
                }
            }
            window.draw(sprite);  // фон
            loginField.draw(window); // поле вводу login
            passwordField.draw(window); // поле вводу password
            btn.draw(window);     // кнопка
        } else if (currentState == GameState::GameMenu) {
            startGameMenu.showGameMenu(window);
            if (startGameMenu.showGameMenu(window) == 1) {
                currentState = GameState::Game;
            } else if (startGameMenu.showGameMenu(window) == 2) {
                currentState = GameState::Settings;
            } else if (startGameMenu.showGameMenu(window) == 3) {
                window.close();
            }
        }
        window.display();
    }
    return 0;
}
