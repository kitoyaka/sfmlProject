//
// Created by rigry on 11.02.2025.
//

#ifndef SFMLPROJECT_FIELD_H
#define SFMLPROJECT_FIELD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>
#include <fstream>

void musicSettings(bool &isPlaying, sf::Music &music, bool &stopMusic);

class Field {
private:
    static constexpr int WIDTH = 15;
    static constexpr int HEIGHT = 15;
    static constexpr int TILE_SIZE = 72;


    sf::RectangleShape cell;
    std::vector<std::vector<int>> grid;
    sf::Vector2f offset;

    const sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackgroundSprite;

    sf::Music music;
    sf::Music musicGameOver;
    bool musicPlaying = true;
    bool keyPressed = false;



    sf::Texture textureBlueBlock;
    sf::Texture textureYellowBlock;
    sf::Texture texturePinkBlock;
    sf::Texture textureGreenBlock;
    sf::Texture textureRedBlock;

    const int figures[7][4] = {
            {1, 3, 5, 7},
            {2, 4, 5, 7},
            {3, 5, 4, 6},
            {3, 5, 4, 7},
            {2, 3, 5, 7},
            {3, 5, 7, 6},
            {2, 3, 4, 5}
    };
    struct Point {int x, y;};
    Point currentShape[4];

    bool isActiveFigure = false;
    sf::Sprite blockSprite[5];
    int randomColor;
    int Right;
    int Left;
    float moveSideTimer = 0;
    const float moveSideDelay = 0.15f;

    float baseDropDelay=0.5f;
    float fastDropDelay=0.1f;
    float dropTimer = 0;
    bool isFastFalling=0;

    bool isGameOver = false;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    sf::RectangleShape gameOverRectangle;
    bool gameOverMusicPlaying = false;
    bool squareNotReturn = false;

    int score = 0;
    sf::Font font;
    sf::Text scoreText;
    sf::Text timerText;
    sf::Clock gameClock;
    float elapsedTime = 0;
    sf::Texture textureStats;
    int tabPressed = 0;
    int tabState = 0;
    bool tabReleased = true;

    float rotateTimer = 0.0f;
    const float rotateDelay = 0.3f;

    bool resetMusic = false;

    sf::Text writeTimesPlayed;
    int timesPlayed = 0;

    int n;
    int bestScore = 0;
    bool gameDataSaved = false;

public:
    Field(sf::RenderWindow& window) : grid(HEIGHT, std::vector<int>(WIDTH, 0)), cell(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2)),
            gameBackgroundTexture(("../image/backgroundGame.png")), gameBackgroundSprite(gameBackgroundTexture),
            music("../music/bgm_2.ogg"),
            musicGameOver("../music/bgm_3.ogg"),
            textureBlueBlock(("../image/blue_squarev2.png")),
            textureYellowBlock(("../image/yellow_squarev2.png")),
            texturePinkBlock(("../image/pink_squarev2.png")),
            textureGreenBlock(("../image/green_squarev2.png")),
            textureRedBlock(("../image/red_squarev2.png")),
            gameOverTexture("../image/gameOver.png"),
            gameOverSprite(gameOverTexture),
            gameOverRectangle({1920.f,1080.f}),
            font(("../font/hermanomayor.ttf")),
            scoreText(font),
            timerText(font),
            blockSprite{
            sf::Sprite(textureBlueBlock),
            sf::Sprite(textureYellowBlock),
            sf::Sprite(texturePinkBlock),
            sf::Sprite(textureGreenBlock),
            sf::Sprite(textureRedBlock)
            },
            writeTimesPlayed(font)

    {
        music.setVolume(30);
        musicGameOver.setVolume(30);
        cell.setFillColor(sf::Color(0, 0, 0,50));
        gameOverRectangle.setFillColor(sf::Color(255, 0, 0,80));
        //gameOverSprite.setColor(sf::Color(255, 0, 0,95));
        float fieldWidth = WIDTH * TILE_SIZE;
        offset.x = (window.getSize().x - fieldWidth) / 2;
        offset.y = 0;


        writeTimesPlayed.setFont(font);
        writeTimesPlayed.setCharacterSize(145);
        writeTimesPlayed.setFillColor(sf::Color::Black);
        writeTimesPlayed.setStyle(sf::Text::Bold);
        //writeTimesPlayed.setOutlineColor(sf::Color::Black);
        //writeTimesPlayed.setOutlineThickness(4.f);
        writeTimesPlayed.setPosition(sf::Vector2f(10, 0));


        scoreText.setFont(font);
        scoreText.setCharacterSize(100);
        writeTimesPlayed.setStyle(sf::Text::Bold);
        scoreText.setFillColor(sf::Color::Black);
        //scoreText.setOutlineThickness(4.f);
        //scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setPosition(sf::Vector2f(10, 180));


        timerText.setFont(font);
        timerText.setCharacterSize(100);
        writeTimesPlayed.setStyle(sf::Text::Bold);
        timerText.setFillColor(sf::Color::Black);
        //timerText.setOutlineThickness(4.f);
        //timerText.setOutlineColor(sf::Color::Black);
        timerText.setPosition(sf::Vector2f(10, 324));

    }


    void draw(sf::RenderWindow& window);
    void generateNewFigure();
    void moveFigure(float deltaTime);
    void handleInput();
    void clearFullLine();
    void rotateFigure();
    void update(float deltaTime);
    void resetGame();
    void startGame();
    void saveGameData();
    void loadGameData();
};


#endif //SFMLPROJECT_FIELD_H
