#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"
#include <SFML/Window/Cursor.hpp>
#include "loginSystem/UserManager.h"
#include "gameMenu.h"
#include "tetris/Field.h"

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
    static bool wasClicked = false;

    if (isOverLoginField || isOverPasswordField) {
        window.setMouseCursor(textCursor);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        window.setMouseCursor(activeCursor.value());

        if (!wasClicked) {
            clickSound.play();
            wasClicked = true;
        }
    } else {
        window.setMouseCursor(cursor.value());
        wasClicked = false;
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

    // Add loginField
    textField loginField(360, 100, "Login Button","../image/LoginPasswordField_v2.png");
    loginField.setPosition(780.f, 220.f);

    // Add passwordField
    textField passwordField(360, 100, "Password Button","../image/LoginPasswordField_v2.png");
    passwordField.setPosition(780.f, 380.f);

    // Add button
    button btn(false,360, 100, "", "../image/LoginButton3d_v2.png");
    btn.setPosition(780.f, 720.f);

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


    sf::Cursor textCursor(sf::Cursor::Type::Text);

    gameMenu startGameMenu(window);

    sf::SoundBuffer buffer("../music/pzdc.wav.");
    sf::Sound clickSound(buffer);
    clickSound.setVolume(50);

    Field field(window);


while (window.isOpen()) {

    while (const std::optional<sf::Event> event = window.pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }


        //if (event->is<sf::Event::KeyPressed>()) {
        if (currentState == GameState::LoginMenu) {
            if (btn.isButtonClicked(window)) {
                if (userManager.loginUser(loginField.getUserInput(), passwordField.getUserInput())) {
                    currentState = GameState::GameMenu;
                    window.setMouseCursorVisible(false);
                    music.stop();
                }
            }

        } else if (currentState == GameState::GameMenu) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                    if (startGameMenu.showGameMenu(window) == 1) {
                        currentState = GameState::Game;
                        //music.stop();
                    } else if (startGameMenu.showGameMenu(window) == 2) {
                        currentState = GameState::Settings;
                    } else if (startGameMenu.showGameMenu(window) == 3) {
                        window.close();
                    }
                }
        } else if (currentState == GameState::Settings) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                currentState = GameState::GameMenu;
            }
        } else if (currentState == GameState::Game) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                currentState = GameState::GameMenu;
            }
        }
        //}


        loginField.handleClick(window, *event);
        passwordField.handleClick(window, *event);

        loginField.handeTextInput(*event);
        passwordField.handeTextInput(*event);
    }


    window.clear();


    if (currentState == GameState::LoginMenu) {
        musicSettings(keyPressed, music, musicPlaying);
        changeCursor(window, textCursor, loginField, passwordField, activeCursor, cursor, clickSound);
        window.draw(sprite);              // фон
        loginField.draw(window);
        passwordField.draw(window);
        btn.draw(window);
    } else if (currentState == GameState::GameMenu) {
        startGameMenu.showGameMenu(window);
    } else if (currentState == GameState::Settings) {
        startGameMenu.showSettings(window);
    } else if(currentState == GameState::Game)
    {
        field.draw(window);
        field.generateNewFigure();
    }

    window.display();
}

    return 0;
}










