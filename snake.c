#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
123456789
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
    printf("\n");
}

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
    }
}

int main() {
    init();
    while (!over) {
        render();
        ctrl();
        update();
        Sleep(80);
    }
    printf("END: %d\n", sc);
    getch();
    return 0;
}
