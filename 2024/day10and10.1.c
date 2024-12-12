#include <stdio.h>
#include <stdlib.h>

#define ARR_BUF_SIZE 200

char map[ARR_BUF_SIZE][ARR_BUF_SIZE];
int height, width;

void parseMap() {
    int c, x = 0, y = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            width = x;
            x = 0;
            y++;
            continue;
        }

        map[y][x] = c;

        x++;
    }
    height = y;
}

void printMap() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            putchar(map[y][x]);
        putchar('\n');
    }
}

char mapOfTrailends[ARR_BUF_SIZE][ARR_BUF_SIZE];

void getTrailHeadScore(int y, int x, int *score) {
    /*printf("getTrailHeadScore for (%d, %d)\n", y, x);*/
    if (map[y][x] == '9') {
        /*if (mapOfTrailends[y][x] == 1)*/
        /*    return;*/
        (*score)++;
        /*mapOfTrailends[y][x] = 1;*/
        return;
    }
    char nextMark = map[y][x] + 1;
    if ((y + 1) < height && map[y + 1][x] == nextMark) {
        getTrailHeadScore(y + 1, x, score);
    }
    if ((x + 1) < width && map[y][x + 1] == nextMark) {
        getTrailHeadScore(y, x + 1, score);
    }
    if ((y - 1) >= 0 && map[y - 1][x] == nextMark) {
        getTrailHeadScore(y - 1, x, score);
    }
    if ((x - 1) >= 0 && map[y][x - 1] == nextMark) {
        getTrailHeadScore(y, x - 1, score);
    }
}

int getTotalScore() {
    int score = 0;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            if (map[y][x] == '0') {
                /*printf("Getting score for (%d, %d)", y, x);*/
                /*memset(mapOfTrailends, 0, ARR_BUF_SIZE * ARR_BUF_SIZE);*/
                getTrailHeadScore(y, x, &score);
                /*printf("  Score: %d\n", score);*/
            }
    return score;
}

int main(void) {
    parseMap();
    /*printMap();*/
    printf("Score: %d\n", getTotalScore());
    return EXIT_SUCCESS;
}
