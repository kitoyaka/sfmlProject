//
// Created by rigry on 11.02.2025.
//

#ifndef SFMLPROJECT_FIELD_H
#define SFMLPROJECT_FIELD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>

void musicSettings(sf::Music &music);

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
    bool isFastFalling;

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
    int elapsedTime = 0;
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
    //int bestScore = 0;
    bool gameDataSaved = false;

    sf::Text writeThisTry;
    sf::Text writeBestResult;
    sf::Text writeBestTry;
    sf::Text writeBestScore;
    sf::Text writeBestTime;

    sf::SoundBuffer buffer;
    sf::Sound destroySound;

    sf::SoundBuffer rotateBuffer;
    sf::Sound rotateSound;

    sf::SoundBuffer blockBuffer;
    sf::Sound blockSound;

    bool upSpeed = true;
    float fallSpeed = 1;
    sf::Text fallSpeedText;

public:
    Field(sf::RenderWindow& window) : grid(HEIGHT, std::vector<int>(WIDTH, 0)), cell(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2)),
            gameBackgroundTexture(("../image/backgroundGame.png")), gameBackgroundSprite(gameBackgroundTexture),
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
            writeTimesPlayed(font),
            writeBestResult(font),
            writeBestTry(font),
            writeBestScore(font),
            writeBestTime(font),
            writeThisTry(font),
            buffer("../music/Pickup_coin 9.wav"),
            destroySound(buffer),
            rotateBuffer("../music/Small_Tear_D.wav"),
            rotateSound(rotateBuffer),
            blockBuffer("../music/Wall_Break_Stone_C.wav"),
            blockSound(blockBuffer),
            fallSpeedText(font)
    {
        destroySound.setVolume(20);
        rotateSound.setVolume(20);
        blockSound.setVolume(20);
        cell.setFillColor(sf::Color(0, 0, 0,50));
        gameOverRectangle.setFillColor(sf::Color(255, 0, 0,80));

        float fieldWidth = WIDTH * TILE_SIZE;
        offset.x = (window.getSize().x - fieldWidth) / 2;
        offset.y = 0;


        writeThisTry.setCharacterSize(90);
        writeThisTry.setFillColor(sf::Color::Black);
        writeThisTry.setStyle(sf::Text::Bold);
        writeThisTry.setOutlineThickness(1.0f);
        writeThisTry.setOutlineColor(sf::Color::Yellow);
        writeThisTry.setPosition(sf::Vector2f(2, 54));

        writeTimesPlayed.setCharacterSize(72);
        writeTimesPlayed.setFillColor(sf::Color::Black);
        writeTimesPlayed.setStyle(sf::Text::Bold);
        writeTimesPlayed.setOutlineThickness(1.0f);
        writeTimesPlayed.setOutlineColor(sf::Color::Yellow);
        writeTimesPlayed.setPosition(sf::Vector2f(2, 141));

        scoreText.setCharacterSize(72);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setOutlineThickness(1.0f);
        scoreText.setOutlineColor(sf::Color::Yellow);
        scoreText.setPosition(sf::Vector2f(2, 213));

        timerText.setCharacterSize(72);
        timerText.setStyle(sf::Text::Bold);
        timerText.setFillColor(sf::Color::Black);
        timerText.setOutlineThickness(1.0f);
        timerText.setOutlineColor(sf::Color::Yellow);
        timerText.setPosition(sf::Vector2f(2, 285));

        fallSpeedText.setCharacterSize(72);
        fallSpeedText.setStyle(sf::Text::Bold);
        fallSpeedText.setFillColor(sf::Color::Black);
        fallSpeedText.setOutlineThickness(1.0f);
        fallSpeedText.setOutlineColor(sf::Color::Yellow);
        fallSpeedText.setPosition(sf::Vector2f(2, 357));

        writeBestResult.setCharacterSize(90);
        writeBestResult.setStyle(sf::Text::Bold);
        writeBestResult.setFillColor(sf::Color::Black);
        writeBestResult.setOutlineThickness(1.0f);
        writeBestResult.setOutlineColor(sf::Color::Yellow);
        writeBestResult.setPosition(sf::Vector2f(1502, 54));

        writeBestTry.setCharacterSize(72);
        writeBestTry.setStyle(sf::Text::Bold);
        writeBestTry.setFillColor(sf::Color::Black);
        writeBestTry.setOutlineThickness(1.0f);
        writeBestTry.setOutlineColor(sf::Color::Yellow);
        writeBestTry.setPosition(sf::Vector2f(1502, 141));

        writeBestScore.setCharacterSize(72);
        writeBestScore.setStyle(sf::Text::Bold);
        writeBestScore.setFillColor(sf::Color::Black);
        writeBestScore.setOutlineThickness(1.0f);
        writeBestScore.setOutlineColor(sf::Color::Yellow);
        writeBestScore.setPosition(sf::Vector2f(1502, 213));

        writeBestTime.setCharacterSize(72);
        writeBestTime.setStyle(sf::Text::Bold);
        writeBestTime.setFillColor(sf::Color::Black);
        writeBestTime.setOutlineThickness(1.0f);
        writeBestTime.setOutlineColor(sf::Color::Yellow);
        writeBestTime.setPosition(sf::Vector2f(1502, 285));

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
    void loadBestGameData();

    bool getIsGameOver() const { return isGameOver; }

};


#endif //SFMLPROJECT_FIELD_H
