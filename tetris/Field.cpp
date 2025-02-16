//
// Created by rigry on 11.02.2025.
//

#include "Field.h"

#include <iostream>

void Field::loadBestGameData() {
    std::ifstream inFile("game_data.txt");
    if (inFile.is_open()) {
        std::string line;
        int bestScore = 0;
        int bestTry = 0;
        int bestTime = 0;

        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            int tryNumber;
            int score;
            int time;

            if (iss >> tryNumber >> score >> time) {
                // Проверяем, если это лучший результат
                if (score > bestScore) {
                    bestScore = score;
                    bestTry = tryNumber;
                    bestTime = time;
                }
            }
        }
        inFile.close();

        // Отображаем лучший результат
        writeBestResult.setString("BEST RESULT");
        writeBestTry.setString("TRY-" + std::to_string(bestTry));
        writeBestScore.setString("SCORE-" + std::to_string(bestScore));
        writeBestTime.setString("TIME-" + std::to_string(bestTime) + "s");
    }
}


void Field::saveGameData() {
    std::ofstream outFile("game_data.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << timesPlayed << " " << score <<" "<< elapsedTime << "\n";
        outFile.close();
    }
}

void Field::loadGameData() {
    std::ifstream inFile("game_data.txt");
    if (inFile.is_open()) {
        std::string line, lastLine;
        while (std::getline(inFile, line)) {
            if (!line.empty()) lastLine = line;
        }
        inFile.close();
        if (!lastLine.empty()) {
            std::istringstream iss(lastLine);
            iss >> timesPlayed >> score;
        } else {
            timesPlayed = 0;
            score = 0;
        }
    } else {
        timesPlayed = 0;
        score = 0;
    }
    timesPlayed++;
}

void Field::startGame() {
    loadGameData();
    gameClock.restart();
    elapsedTime = 0;
    score = 0;
}

void Field::draw(sf::RenderWindow& window) {
    if (!gameOverMusicPlaying || resetMusic) {
        resetMusic = false;
        musicSettings(keyPressed, music, musicPlaying);
    } else if (gameOverMusicPlaying && !resetMusic) {
        musicSettings(keyPressed, musicGameOver, musicPlaying);
    }

    window.draw(gameBackgroundSprite);

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            cell.setPosition(sf::Vector2f(offset.x + col * TILE_SIZE, offset.y + row * TILE_SIZE));
            window.draw(cell);
        }
    }

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (grid[row][col] != 0) {
                int colorIndex = grid[row][col] - 1;
                if (colorIndex >= 0 && colorIndex < 5) {
                    blockSprite[colorIndex].setPosition(sf::Vector2f(
                        offset.x + col * TILE_SIZE,
                        offset.y + row * TILE_SIZE
                    ));
                    window.draw(blockSprite[colorIndex]);
                }
            }
        }
    }

    if (isActiveFigure) {
        for (int i = 0; i < 4; i++) {
            blockSprite[randomColor].setPosition(sf::Vector2f(
                offset.x + currentShape[i].x * TILE_SIZE,
                offset.y + currentShape[i].y * TILE_SIZE
            ));
            window.draw(blockSprite[randomColor]);
        }
    }

    if (isGameOver) {
        if (!gameOverMusicPlaying) {
            music.stop();
            gameOverMusicPlaying = true;
        }

        if (!gameDataSaved) {
            saveGameData();
            gameDataSaved = true;
        }

        window.draw(gameOverRectangle);
        window.draw(gameOverSprite);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        music.stop();
        musicGameOver.stop();
    }

    if (tabState == 0) {
        window.draw(scoreText);
        window.draw(timerText);
        window.draw(writeTimesPlayed);
        window.draw(writeBestResult);
        window.draw(writeBestTry);
        window.draw(writeBestScore);
        window.draw(writeBestTime);
        window.draw(writeThisTry);
    }
}


void Field::generateNewFigure() {
    if (isActiveFigure) return;
    if (!isGameOver) {
        n = rand() % 7;
    }

    if (n==6)
        squareNotReturn = true;
    else
        squareNotReturn = false;

    randomColor = rand() % 5;

    for (int i = 0; i < 4; ++i) {
         currentShape[i].x = figures[n][i] % 2 + WIDTH / 2 - 1;
         currentShape[i].y = figures[n][i] / 2;

         // Проверка на столкновение с существующими блоками
         if (grid[currentShape[i].y][currentShape[i].x] != 0) {
             // Игра завершена (можно добавить обработку)
             isActiveFigure = false;
             isGameOver = true;
             return;
            }
    }
    isActiveFigure = true;
}


void Field::handleInput() {
    if (!isActiveFigure) return;
    // Обработка ускоренного падения
    isFastFalling = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        bool canMove = true;
        for (int i = 0; i < 4; ++i) {
            int newX = currentShape[i].x - 1;
            if (newX < 0 || grid[currentShape[i].y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            for (int i = 0; i < 4; ++i)
                currentShape[i].x -= 1;
        }
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        bool canMove = true;
        for (int i = 0; i < 4; ++i) {
            int newX = currentShape[i].x + 1;
            if (newX >= WIDTH || grid[currentShape[i].y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            for (int i = 0; i < 4; ++i)
                currentShape[i].x += 1;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) {
        if (tabReleased) {
            tabState = (tabState+1) % 2;
            tabReleased = false;
        }
    } else {
        tabReleased = true;
    }



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (rotateTimer <= 0) {
            rotateFigure();
            rotateTimer = rotateDelay; // Устанавливаем задержку после поворота
        }
    }
}

void Field::moveFigure(float deltaTime) {
    if (!isActiveFigure) return;

    // Выбираем задержку в зависимости от состояния клавиши
    float currentDropDelay = isFastFalling ? fastDropDelay : baseDropDelay;

    dropTimer += deltaTime;

    if (dropTimer >= currentDropDelay) {
        dropTimer = 0;

        bool canMoveDown = true;
        for (int i = 0; i < 4; ++i) {
            int newY = currentShape[i].y + 1;
            if (newY >= HEIGHT || grid[newY][currentShape[i].x] != 0) {
                canMoveDown = false;
                break;
            }
        }

        if (!canMoveDown) {
            // Фиксация фигуры
            for (int i = 0; i < 4; ++i) {
                int x = currentShape[i].x;
                int y = currentShape[i].y;
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                    grid[y][x] = randomColor + 1;
                }
            }
            isActiveFigure = false;
            clearFullLine();
            return;
        }

        // Перемещение вниз
        for (int i = 0; i < 4; ++i) {
            currentShape[i].y += 1;
        }
    }

    // Обработка бокового движения с задержкой
    moveSideTimer += deltaTime;
    if (moveSideTimer >= moveSideDelay) {
        handleInput();
        moveSideTimer = 0;
    }
}


void Field::clearFullLine() {
    int linesCleared = 0;
    int row = HEIGHT - 1;
    while (row >= 0) {
        bool isFull = true;
        for (int col = 0; col < WIDTH; ++col) {
            if (grid[row][col] == 0) {
                isFull = false;
                break;
            }
        }
        if (isFull) {
            destroySound.play();
            linesCleared++;
            for (int i = row; i > 0; --i) {
                for (int j = 0; j < WIDTH; ++j) {
                    grid[i][j] = grid[i - 1][j];
                }
            }
            for (int j = 0; j < WIDTH; ++j) {
                grid[0][j] = 0;
            }

        } else {
            row--;
        }
    }
    score += linesCleared * 100;

}

void Field::rotateFigure() {
    if (!isActiveFigure) return;
    if (squareNotReturn) return;

    Point center = currentShape[1]; // точна на якій буде обертатись фігура

    Point rotatedShape[4]; // Нові координати

    for (int i = 0; i < 4; ++i) {
        int newX = center.x - (currentShape[i].y - center.y);
        int newY = center.y + (currentShape[i].x - center.x);

        // Перевіряємо, чи не виходимо за межі поля
        if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT || grid[newY][newX] != 0)
            return; // Якщо виходимо або зайняте місце — не обертаємо
        rotatedShape[i] = {newX, newY};
    }

    // Якщо все нормально — оновлюємо позиції
    for (int i = 0; i < 4; ++i) {
        currentShape[i] = rotatedShape[i];
    }
}

void Field::update(float deltaTime) {
    if (!isGameOver) {
        elapsedTime = gameClock.getElapsedTime().asSeconds();
    }

    if (rotateTimer > 0) {
        rotateTimer -= deltaTime;
    }

    writeThisTry.setString("THIS GAME:");
    scoreText.setString("SCORE-" + std::to_string(score));
    timerText.setString("TIME-" + std::to_string(static_cast<int>(elapsedTime))+ "s");
    writeTimesPlayed.setString(std::to_string(timesPlayed) + "-TRY");


    // Обновляем лучший результат
    loadBestGameData();

    // Проверка выхода через Escape
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        if (!gameDataSaved) {
            saveGameData();
            gameDataSaved = true;
        }
        exit(0);
    }
}

void Field::resetGame() {
    if (isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        for (int row = 0; row < HEIGHT; ++row)
            for (int col = 0; col < WIDTH; ++col)
                grid[row][col] = 0;

        isActiveFigure = false;
        dropTimer = 0;
        moveSideTimer = 0;
        score = 0;
        gameClock.restart();
        isGameOver = false;
        musicGameOver.stop();
        gameOverMusicPlaying = false;
        resetMusic = false;

        gameDataSaved = false;
        timesPlayed++;
    }
}




