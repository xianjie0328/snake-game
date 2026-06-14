#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define COLS 30
#define ROWS 15

int headX, headY, foodX, foodY, badX, badY, points, over, length;
int bodyX[300], bodyY[300];
enum Move { HALT = 0, GO_LEFT, GO_RIGHT, GO_UP, GO_DOWN };
enum Move way;

void spawnItems() {
    foodX = rand() % COLS;
    foodY = rand() % ROWS;
    badX = rand() % COLS;
    badY = rand() % ROWS;
}

void begin() {
    over = 0;
    way = HALT;
    headX = COLS / 2;
    headY = ROWS / 2;
    points = 0;
    length = 0;
    spawnItems();
}

void show() {
    system("cls");
    printf("Points: %d   Length: %d\n", points, length);
    for (int i = 0; i < COLS + 2; i++) printf("=");
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            if (i == headY && j == headX) {
                printf("@");
            } else if (i == foodY && j == foodX) {
                printf("+");
            } else if (i == badY && j == badX) {
                printf("X");
            } else {
                int ok = 0;
                for (int k = 0; k < length; k++) {
                    if (bodyX[k] == j && bodyY[k] == i) {
                        printf("*");
                        ok = 1;
                        break;
                    }
                }
                if (!ok) printf(" ");
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < COLS + 2; i++) printf("=");
    printf("\n");
    printf("Controls: I/J/K/L | Poison: X | Quit: Q\n");
}

void command() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'j': if (way != GO_RIGHT) way = GO_LEFT; break;
            case 'l': if (way != GO_LEFT) way = GO_RIGHT; break;
            case 'i': if (way != GO_DOWN) way = GO_UP; break;
            case 'k': if (way != GO_UP) way = GO_DOWN; break;
            case 'q': over = 1; break;
        }
    }
}

void tick() {
    int oldX = bodyX[0];
    int oldY = bodyY[0];
    int swapX, swapY;
    bodyX[0] = headX;
    bodyY[0] = headY;
    for (int i = 1; i < length; i++) {
        swapX = bodyX[i];
        swapY = bodyY[i];
        bodyX[i] = oldX;
        bodyY[i] = oldY;
        oldX = swapX;
        oldY = swapY;
    }

    if (way == GO_LEFT) headX--;
    if (way == GO_RIGHT) headX++;
    if (way == GO_UP) headY--;
    if (way == GO_DOWN) headY++;

    if (headX < 0) headX = COLS - 1;
    if (headX >= COLS) headX = 0;
    if (headY < 0) headY = ROWS - 1;
    if (headY >= ROWS) headY = 0;

    for (int i = 0; i < length; i++) {
        if (bodyX[i] == headX && bodyY[i] == headY) {
            over = 1;
            return;
        }
    }

    if (headX == foodX && headY == foodY) {
        points += 10;
        length++;
        foodX = rand() % COLS;
        foodY = rand() % ROWS;
        if (rand() % 3 == 0) {
            badX = rand() % COLS;
            badY = rand() % ROWS;
        }
    }

    if (headX == badX && headY == badY) {
        over = 1;
    }
}

void countdown() {
    for (int i = 3; i > 0; i--) {
        system("cls");
        printf("\n\n      Starting in %d...\n", i);
        Sleep(500);
    }
    system("cls");
    printf("\n\n         GO!\n");
    Sleep(300);
}

void finish() {
    system("cls");
    printf("\n*** GAME OVER ***\n");
    printf("Points: %d\n", points);
    printf("Length: %d\n", length);
    if (points >= 100)
        printf("Great job!\n");
    else
        printf("Keep trying!\n");
    printf("\nPress any key...\n");
    getch();
}

int main() {
    begin();
    countdown();
    while (!over) {
        show();
        command();
        tick();
        Sleep(90);
    }
    finish();
    return 0;
}
