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

bool findXvariant(int x, int y) {

    // MM
    // SS
    if (data[y + 1][x - 1] == 'M' && data[y + 1][x + 1] == 'M' &&
        data[y - 1][x - 1] == 'S' && data[y - 1][x + 1] == 'S')
        return true;

    // SS
    // MM
    if (data[y + 1][x - 1] == 'S' && data[y + 1][x + 1] == 'S' &&
        data[y - 1][x - 1] == 'M' && data[y - 1][x + 1] == 'M')
        return true;

    // SM
    // SM
    if (data[y + 1][x - 1] == 'S' && data[y + 1][x + 1] == 'M' &&
        data[y - 1][x - 1] == 'S' && data[y - 1][x + 1] == 'M')
        return true;

    // MS
    // MS
    if (data[y + 1][x - 1] == 'M' && data[y + 1][x + 1] == 'S' &&
        data[y - 1][x - 1] == 'M' && data[y - 1][x + 1] == 'S')
        return true;

    return false;
}

int main(void) {

    parseInput();
    printf("dims: (%d, %d)\n", width, height);
    printArr();

    int found = 0;

    int x, y;
    for (y = 1; y < (height - 1); y++)
        for (x = 1; x < (width - 1); x++)
            if (data[y][x] == 'A' && findXvariant(x, y)) {
                /*printf("In (%d, %d) found\n", x, y);*/
                found++;
            } else {
                /*printf("In (%d, %d) none (%c)\n", x, y, data[y][x]);*/
            }

    printf("FOUND: %d\n", found);

    return EXIT_SUCCESS;
}
