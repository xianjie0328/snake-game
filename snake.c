#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

<<<<<<< HEAD
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
=======
#define W 20
#define H 20

int px, py, fx, fy, sc, over;
int tx[100], ty[100];
int tl;
enum D { S = 0, L, R, U, Dn };
enum D d;

void init() {
    over = 0;
    d = S;
    px = W / 2;
    py = H / 2;
    fx = rand() % W;
    fy = rand() % H;
    sc = 0;
    tl = 0;
}

void render() {
    system("cls");
    printf("SCORE: %d\n", sc);
    for (int i = 0; i < W + 2; i++) printf("+");
    printf("\n");
    for (int i = 0; i < H; i++) {
        printf("+");
        for (int j = 0; j < W; j++) {
            if (i == py && j == px) printf("@");
            else if (i == fy && j == fx) printf("$");
            else printf(" ");
        }
        printf("+\n");
    }
    for (int i = 0; i < W + 2; i++) printf("+");
>>>>>>> 367a321 (123)
    printf("\n");
    printf("Controls: I/J/K/L | Poison: X | Quit: Q\n");
}

<<<<<<< HEAD
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
=======
void ctrl() {
    if (_kbhit()) {
        char c = _getch();
        if (c == 'a') d = L;
        if (c == 'd') d = R;
        if (c == 'w') d = U;
        if (c == 's') d = Dn;
    }
}

void update() {
    tx[0] = px;
    ty[0] = py;
    for (int i = tl; i > 0; i--) {
        tx[i] = tx[i-1];
        ty[i] = ty[i-1];
    }
    if (d == L) px--;
    if (d == R) px++;
    if (d == U) py--;
    if (d == Dn) py++;
    if (px < 0 || px >= W || py < 0 || py >= H) over = 1;
    if (px == fx && py == fy) {
        sc += 5;
        fx = rand() % W;
        fy = rand() % H;
        tl++;
>>>>>>> 367a321 (123)
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
<<<<<<< HEAD
    begin();
    countdown();
    while (!over) {
        show();
        command();
        tick();
        Sleep(90);
    }
    finish();
=======
    init();
    while (!over) {
        render();
        ctrl();
        update();
        Sleep(80);
    }
    printf("END: %d\n", sc);
    getch();
>>>>>>> 367a321 (123)
    return 0;
}
