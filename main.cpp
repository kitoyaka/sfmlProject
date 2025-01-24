#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"
#include <SFML/Window/Cursor.hpp>
#include "loginSystem/UserManager.h"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Big patric");

    // Load a sprite to display
    const sf::Texture texture("../image/main_menu.png");
    sf::Sprite sprite(texture);

    // Add button
    button btn(200, 50, "HELLO BUTTON");
    btn.setPosition(300.f, 300.f);

    // Add textField
    textField loginField(200.f, 50.f, "Login Button");
    loginField.setPosition(300.f, 100.f);

    // Add textField
    textField passwordField(200.f, 50.f, "Password Button");
    passwordField.setPosition(300.f, 200.f);

    // Load a music to play
    sf::Music music("../music/gimn_ukrainyi.ogg");
    bool musicPlaying = true;
    bool keyPressed = false;
    sf::Music newMusic("../music/gmnrss.ogg");
    bool newMusicPlaying = true;
    //bool keyPressed = false;


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

    // Load a sprite to display
    const sf::Texture newTexture("../image/bigLike.png");
    sf::Sprite newSprite(newTexture);

    //sf::RenderWindow (sf::VideoMode({800, 400}), "Small patric");

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


        // Change the cursor to text cursor when over text fields
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool isOverLoginField = loginField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        bool isOverPasswordField = passwordField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        if (isOverLoginField || isOverPasswordField) {
            window.setMouseCursor(textCursor);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            window.setMouseCursor(activeCursor.value());
        }
        else {
            window.setMouseCursor(cursor.value());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !keyPressed) {
            if (musicPlaying) {
                music.setVolume(0);
                musicPlaying = false;
            } else {
                music.setVolume(100);
                musicPlaying = true;
            }
            keyPressed = true;
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
            keyPressed = false;
        }
        if (music.getStatus() != sf::SoundSource::Status::Playing && musicPlaying) {
            music.play();
        }

        // Проверяем, нажата ли кнопка
        if (btn.isButtonClicked(window)) {
            music.stop();
            window.close();  // Закрываем старое окно
           if(userManager.loginUser(loginField.getUserInput(), passwordField.getUserInput())) {
                // New window
                sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
                sf::RenderWindow newWindow(desktop, "Small patric", sf::Style::None);

                while (newWindow.isOpen()) {
                    if (const std::optional<sf::Event> newEvent = newWindow.pollEvent()) {
                        /*
                        if (newEvent->is<sf::Event::Closed>()) {
                            newWindow.close();
                        }
                        */
                    }
                    newWindow.clear();
                    /*
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !keyPressed) {
                        if (newMusicPlaying) {
                            newMusic.setVolume(0);
                            newMusicPlaying = false;
                        } else {
                            newMusic.setVolume(100);
                            newMusicPlaying = true;
                        }
                        keyPressed = true;
                    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                        keyPressed = false;
                    }*/
                    if (newMusic.getStatus() != sf::SoundSource::Status::Playing && newMusicPlaying) {
                        newMusic.play();
                    }

                    //newMusic.play();
                    newWindow.draw(newSprite);
                    newWindow.display();
                }
            }
        }

        window.clear();



        window.draw(sprite);  // фон
        btn.draw(window);     // кнопка
        loginField.draw(window); // поле вводу login
        passwordField.draw(window); // поле вводу password
        window.display();
    }
    return 0;
}
