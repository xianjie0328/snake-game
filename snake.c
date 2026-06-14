#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAP_WIDTH 25
#define MAP_HEIGHT 20

int snakeHeadX, snakeHeadY, fruitX, fruitY, currentScore, isGameOver, highestScore;
int snakeTailX[200], snakeTailY[200];
int tailLength;
int gameSpeed = 120;
int isPaused = 0;
enum Direction { STOPPED = 0, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN };
enum Direction currentDirection;
HANDLE consoleHandle;

void setConsoleColor(int color) {
    SetConsoleTextAttribute(consoleHandle, color);
}

void resetConsoleColor() {
    SetConsoleTextAttribute(consoleHandle, 7);
}

void loadHighestScore() {
    FILE *file = fopen("score.dat", "r");
    if (file) {
        fscanf(file, "%d", &highestScore);
        fclose(file);
    } else {
        highestScore = 0;
    }
}

void saveHighestScore() {
    FILE *file = fopen("score.dat", "w");
    if (file) {
        fprintf(file, "%d", highestScore);
        fclose(file);
    }
}

void initializeGame() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    isGameOver = 0;
    isPaused = 0;
    currentDirection = STOPPED;
    snakeHeadX = MAP_WIDTH / 2;
    snakeHeadY = MAP_HEIGHT / 2;
    fruitX = rand() % MAP_WIDTH;
    fruitY = rand() % MAP_HEIGHT;
    currentScore = 0;
    tailLength = 0;
    gameSpeed = 120;
    loadHighestScore();
}

void drawGameBoard() {
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(consoleHandle, cursorPosition);

    setConsoleColor(11);
    printf("Score: %d  |  High Score: %d  |  Speed: %d\n", currentScore, highestScore, 130 - gameSpeed);
    resetConsoleColor();

    setConsoleColor(8);
    for (int i = 0; i < MAP_WIDTH + 2; i++) printf("#");
    printf("\n");
    resetConsoleColor();

    for (int i = 0; i < MAP_HEIGHT; i++) {
        setConsoleColor(8);
        printf("#");
        resetConsoleColor();

        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == snakeHeadY && j == snakeHeadX) {
                setConsoleColor(10);
                printf("O");
                resetConsoleColor();
            } else if (i == fruitY && j == fruitX) {
                setConsoleColor(12);
                printf("*");
                resetConsoleColor();
            } else {
                int drawn = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        setConsoleColor(14);
                        printf("o");
                        resetConsoleColor();
                        drawn = 1;
                        break;
                    }
                }
                if (!drawn) printf(" ");
            }
        }

        setConsoleColor(8);
        printf("#\n");
        resetConsoleColor();
    }

    setConsoleColor(8);
    for (int i = 0; i < MAP_WIDTH + 2; i++) printf("#");
    printf("\n");
    resetConsoleColor();

    if (isPaused) {
        setConsoleColor(13);
        printf("[PAUSED] Press P to resume\n");
        resetConsoleColor();
    } else {
        printf("W/A/S/D: Move | P: Pause | X: Quit\n");
    }
}

void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'a':
                if (currentDirection != MOVE_RIGHT) currentDirection = MOVE_LEFT;
                break;
            case 'd':
                if (currentDirection != MOVE_LEFT) currentDirection = MOVE_RIGHT;
                break;
            case 'w':
                if (currentDirection != MOVE_DOWN) currentDirection = MOVE_UP;
                break;
            case 's':
                if (currentDirection != MOVE_UP) currentDirection = MOVE_DOWN;
                break;
            case 'p':
            case 'P':
                isPaused = !isPaused;
                break;
            case 'x':
            case 'X':
                isGameOver = 1;
                break;
        }
    }
}

void updateGameLogic() {
    if (isPaused) return;

    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int tempX, tempY;
    snakeTailX[0] = snakeHeadX;
    snakeTailY[0] = snakeHeadY;

    for (int i = 1; i < tailLength; i++) {
        tempX = snakeTailX[i];
        tempY = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch (currentDirection) {
        case MOVE_LEFT:  snakeHeadX--; break;
        case MOVE_RIGHT: snakeHeadX++; break;
        case MOVE_UP:    snakeHeadY--; break;
        case MOVE_DOWN:  snakeHeadY++; break;
        default: break;
    }

    if (snakeHeadX >= MAP_WIDTH) snakeHeadX = 0;
    else if (snakeHeadX < 0) snakeHeadX = MAP_WIDTH - 1;
    if (snakeHeadY >= MAP_HEIGHT) snakeHeadY = 0;
    else if (snakeHeadY < 0) snakeHeadY = MAP_HEIGHT - 1;

    for (int i = 0; i < tailLength; i++) {
        if (snakeTailX[i] == snakeHeadX && snakeTailY[i] == snakeHeadY) {
            isGameOver = 1;
        }
    }

    if (snakeHeadX == fruitX && snakeHeadY == fruitY) {
        currentScore += 10;
        if (currentScore > highestScore) {
            highestScore = currentScore;
            saveHighestScore();
        }
        fruitX = rand() % MAP_WIDTH;
        fruitY = rand() % MAP_HEIGHT;
        tailLength++;
        if (gameSpeed > 40 && currentScore % 50 == 0) {
            gameSpeed -= 10;
        }
    }
}

void showGameOverScreen() {
    system("cls");
    setConsoleColor(12);
    printf("=========================\n");
    printf("       GAME OVER         \n");
    printf("=========================\n");
    resetConsoleColor();
    printf("Final Score: %d\n", currentScore);
    printf("High Score:  %d\n", highestScore);
    printf("\nPress any key to exit...\n");
    getch();
}

int main() {
    initializeGame();
    while (!isGameOver) {
        drawGameBoard();
        handleInput();
        updateGameLogic();
        Sleep(gameSpeed);
    }
    showGameOverScreen();
    return 0;
}
