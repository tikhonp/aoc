#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 200

char data[BUF_SIZE][BUF_SIZE], width, height;

void parseInput() {
    int c, i = 0, j = 0;

    while ((c = getchar()) != EOF)
        if (c == '\n') {
            width = j;
            j = 0;
            i++;
        } else {
            data[i][j++] = c;
        }

    height = i;
}

void printArr() {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            printf("%c", data[i][j]);
        printf("\n");
    }
}

typedef enum {
    WAITF_M,
    WAITF_A,
    WAITF_S,
    SUCCESS,
} ScanStatus;

ScanStatus getNext(ScanStatus status) {
    switch (status) {
    case WAITF_M:
        return WAITF_A;
    case WAITF_A:
        return WAITF_S;
    case WAITF_S:
        return SUCCESS;
    case SUCCESS:
        return SUCCESS;
    }
}

bool isRightCharFor(ScanStatus status, int x, int y) {
    switch (status) {
    case WAITF_M:
        return data[y][x] == 'M';
    case WAITF_A:
        return data[y][x] == 'A';
    case WAITF_S:
        return data[y][x] == 'S';
    case SUCCESS:
        return false;
    }
}

typedef enum {
    // horizontal
    H_RIGHT,
    H_LEFT,
    // vertical
    V_UP,
    V_DOWN,
    // diagonal
    D_LEFT_UP,
    D_RIGHT_UP,
    D_LEFT_DOWN,
    D_RIGHT_DOWN,
} Direction;

void checkAroundPoint(ScanStatus status, Direction direction, int x, int y,
                      int *found) {
    if (status == SUCCESS) {
        (*found)++;
        return;
    }

    bool unknownDirectionStep = status == WAITF_M;

    // x-1, y-1 D_LEFT_DOWN
    if (unknownDirectionStep || direction == D_LEFT_DOWN)
        if (x > 0 && y > 0 && isRightCharFor(status, x - 1, y - 1))
            checkAroundPoint(getNext(status), D_LEFT_DOWN, x - 1, y - 1, found);

    // x, y-1 V_DOWN
    if (unknownDirectionStep || direction == V_DOWN)
        if (y > 0 && isRightCharFor(status, x, y - 1))
            checkAroundPoint(getNext(status), V_DOWN, x, y - 1, found);

    // x+1, y-1 D_RIGHT_DOWN
    if (unknownDirectionStep || direction == D_RIGHT_DOWN)
        if (x < (width - 1) && y > 0 && isRightCharFor(status, x + 1, y - 1))
            checkAroundPoint(getNext(status), D_RIGHT_DOWN, x + 1, y - 1,
                             found);

    // x-1, y H_LEFT
    if (unknownDirectionStep || direction == H_LEFT)
        if (x > 0 && isRightCharFor(status, x - 1, y))
            checkAroundPoint(getNext(status), H_LEFT, x - 1, y, found);

    // NO x, y

    // x+1, y H_RIGHT
    if (unknownDirectionStep || direction == H_RIGHT)
        if (x < (width - 1) && isRightCharFor(status, x + 1, y))
            checkAroundPoint(getNext(status), H_RIGHT, x + 1, y, found);

    // x-1, y+1 D_LEFT_UP
    if (unknownDirectionStep || direction == D_LEFT_UP)
        if (x > 0 && y < (height - 1) && isRightCharFor(status, x - 1, y + 1))
            checkAroundPoint(getNext(status), D_LEFT_UP, x - 1, y + 1, found);

    // x, y+1 V_UP
    if (unknownDirectionStep || direction == V_UP)
        if (y < (height - 1) && isRightCharFor(status, x, y + 1))
            checkAroundPoint(getNext(status), V_UP, x, y + 1, found);

    // x+1, y+1 D_RIGHT_UP
    if (unknownDirectionStep || direction == D_RIGHT_UP)
        if (x < (width - 1) && y < (height - 1) &&
            isRightCharFor(status, x + 1, y + 1))
            checkAroundPoint(getNext(status), D_RIGHT_UP, x + 1, y + 1, found);
}

int main(void) {

    parseInput();
    printf("dims: (%d, %d)\n", width, height);
    printArr();

    int found = 0;

    int x, y;
    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++)
            if (data[y][x] == 'X')
                checkAroundPoint(WAITF_M, V_UP, x, y, &found);

    printf("FOUND: %d\n", found);

    return EXIT_SUCCESS;
}
