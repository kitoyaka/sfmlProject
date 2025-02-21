#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"
#include <SFML/Window/Cursor.hpp>
#include "loginSystem/UserManager.h"
#include "gameMenu.h"
#include "tetris/Field.h"

void changeTexture(sf::RectangleShape &rect, sf::Texture &m_texture, const std::string& texturePath) {
    m_texture.loadFromFile(texturePath);
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

void musicSettings(sf::Music &music) {
    static bool isMuted = false;
    static float previousVolume = music.getVolume();
    static bool mKeyPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
        if (!mKeyPressed) {
            if (!isMuted) {
                previousVolume = music.getVolume();
                music.setVolume(0);
                isMuted = true;
            } else {
                music.setVolume(previousVolume);
                isMuted = false;
            }
            mKeyPressed = true;
        }
    } else {
        mKeyPressed = false;
    }

    if (music.getStatus() != sf::SoundSource::Status::Playing) {
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
    const sf::Texture texture("../image/background.png");
    sf::Sprite sprite(texture);

    // Add loginField
    textField loginField(356, 145, "Login Button","../image/LoginPasswordField_v2.png");
    loginField.setPosition(783.f, 217.f);

    // Add passwordField
    textField passwordField(356, 145, "Password Button","../image/LoginPasswordField_v2.png");
    passwordField.setPosition(783.f, 430.f);

    // Add button
    button btn(false,360, 144, "", "../image/LoginButton3d_v2.png");
    btn.setPosition(780.f, 720.f);

    // Load a music to play
    sf::Music music;
    std::string currentMusicFile = "";
    music.setVolume(30);

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
    sf::Clock clockInGame;

    sf::Font fontWrongLogPass("../font/hermanomayor.ttf");
    sf::Text wrongLogPass(fontWrongLogPass);

    wrongLogPass.setString("WRONG LOGIN OR PASSWORD");
    wrongLogPass.setFont(fontWrongLogPass);
    wrongLogPass.setCharacterSize(25);
    wrongLogPass.setFillColor(sf::Color::Black);
    wrongLogPass.setStyle(sf::Text::Bold);
    wrongLogPass.setOutlineThickness(1.0f);
    wrongLogPass.setOutlineColor(sf::Color::Red);
    wrongLogPass.setPosition(sf::Vector2f(807, 864));

    button createAccount(false,216,72, "", "../image/CreateAccount.png");
    createAccount.setPosition(852,936);

while (window.isOpen()) {

    while (const std::optional<sf::Event> event = window.pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (currentState == GameState::LoginMenu) {
            // Обработка нажатия кнопки входа
            if (btn.isButtonClicked(window,"../image/LoginButton3d_v2.png","../image/LoginButton3dPressed_v2.png")) {
                showWrongLogPass = false;
                if (userManager.loginUser(loginField.getUserInput(), passwordField.getUserInput())) {
                    currentState = GameState::GameMenu;
                    window.setMouseCursorVisible(false);
                } else {
                    showWrongLogPass = true;
                    wrongLogPass.setOutlineColor(sf::Color::Red);
                    wrongLogPass.setString("WRONG LOGIN OR PASSWORD");
                }
            }

            // Обработка регистрации по нажатию клавиши R
            if (createAccount.isButtonClicked(window,"../image/CreateAccount.png","../image/CreateAccountPressed.png")) {
                showWrongLogPass = false;
                std::string login = loginField.getUserInput();
                std::string password = passwordField.getUserInput();

                if (!login.empty() && !password.empty()) {
                    userManager.registerUser(login, password);
                    loginField.clear();
                    passwordField.clear();
                    showWrongLogPass = true;
                    wrongLogPass.setOutlineColor(sf::Color::Green);
                    wrongLogPass.setString("REGISTRATION SUCCESSFUL");
                }
            }
        } else if (currentState == GameState::GameMenu) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                    if (startGameMenu.showGameMenu(window) == 1) {
                        currentState = GameState::Game;
                        field.startGame();
                    }
                    else if (startGameMenu.showGameMenu(window) == 2) {
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

        loginField.handleClick(window, *event);
        passwordField.handleClick(window, *event);

        loginField.handeTextInput(*event);
        passwordField.handeTextInput(*event);
    }

    std::string targetMusicFile;
    if (currentState == GameState::LoginMenu || currentState == GameState::GameMenu || currentState == GameState::Settings) {
        targetMusicFile = "menu_music";
        if (currentMusicFile != targetMusicFile) {
            music.stop();
            if (!music.openFromFile("../music/Classical-Vol3-Aether-Cut-60.ogg")) {
                std::cerr << "Ошибка загрузки меню музыки\n";
            }
            music.play();
            currentMusicFile = targetMusicFile;
        }
    } else if (currentState == GameState::Game) {
        if (field.getIsGameOver()) {
            targetMusicFile = "game_over_music";
            if (currentMusicFile != targetMusicFile) {
                music.stop();
                if (!music.openFromFile("../music/bgm_3.ogg")) {
                    std::cerr << "Ошибка загрузки GameOver музыки\n";
                }
                music.play();
                currentMusicFile = targetMusicFile;
            }
        } else {
            targetMusicFile = "game_music";
            if (currentMusicFile != targetMusicFile) {
                music.stop();
                if (!music.openFromFile("../music/Classical-Vol3-Matchmaker-Intensity-2.ogg")) {
                    std::cerr << "Ошибка загрузки игровой музыки\n";
                }
                music.play();
                currentMusicFile = targetMusicFile;
            }
        }
    }


    window.clear();

    if (currentState == GameState::LoginMenu || currentState==GameState::GameMenu || currentState==GameState::Settings || currentState==GameState::Game) {
        musicSettings(music);
    }

    if (currentState == GameState::LoginMenu) {
        changeCursor(window, textCursor, loginField, passwordField, activeCursor, cursor, clickSound);
        window.draw(sprite);              // фон
        loginField.draw(window);
        passwordField.draw(window);
        btn.draw(window);
        createAccount.draw(window);
        if (showWrongLogPass ) {
            window.draw(wrongLogPass);
        }
    } else if (currentState == GameState::GameMenu) {
        startGameMenu.showGameMenu(window);
    } else if (currentState == GameState::Settings) {
        startGameMenu.showSettings(window,music);
    } else if (currentState == GameState::Game) {
        float deltaTime = clockInGame.restart().asSeconds();
        field.generateNewFigure();
        field.update(deltaTime);
        field.moveFigure(deltaTime);
        field.draw(window);
        field.resetGame();
    }
    window.display();
}

    return 0;
}










