#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_BUF_SIZE 200

bool antinodesMap[ARR_BUF_SIZE][ARR_BUF_SIZE];
int mapWidth, mapHeight;

typedef struct {
    int x, y;
} Point;

Point substruct(Point a, Point b) {
    Point p = {.x = a.x - b.x, .y = a.y - b.y};
    return p;
}

Point add(Point a, Point b) {
    Point p = {.x = a.x + b.x, .y = a.y + b.y};
    return p;
}

bool pointInBoundsOfMap(Point p) {
    return p.x >= 0 && p.x < mapWidth && p.y >= 0 && p.y < mapHeight;
}

typedef struct {
    char frec;
    Point points[ARR_BUF_SIZE];
    int pointsLength;
} FrecPoints;

int getIndxOfFrec(char frec, FrecPoints antennas[], int antennasLength) {
    for (int i = 0; i < antennasLength; i++)
        if (antennas[i].frec == frec)
            return i;
    return -1;
}

int parseInput(FrecPoints antennas[]) {
    int c, antennasIndx = 0;
    Point p = {.x = 0, .y = 0};

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            mapWidth = p.x;
            p.x = 0;
            p.y++;
            continue;
        }

        if (c == '.') {
            p.x++;
            continue;
        }

        int currentAntennaIndx = getIndxOfFrec(c, antennas, antennasIndx);
        if (currentAntennaIndx == -1) {
            FrecPoints fp = {.pointsLength = 1, .frec = c, .points = {p}};
            antennas[antennasIndx++] = fp;
        } else {
            antennas[currentAntennaIndx]
                .points[antennas[currentAntennaIndx].pointsLength++] = p;
        }

        p.x++;
    }

    mapHeight = p.y;

    return antennasIndx;
}

void setAntinodes(FrecPoints fp, int *antinodesCount) {
    for (int i = 0; i < fp.pointsLength; i++)
        for (int j = 0; j < fp.pointsLength; j++) {
            if (j == i)
                continue;

            /*printf("  %c: (%d, %d), (%d, %d)\n", fp.frec, fp.points[i].x,*/
            /*       fp.points[i].y, fp.points[j].x, fp.points[j].y);*/

            Point a1 = add(fp.points[i], substruct(fp.points[i], fp.points[j]));
            if (pointInBoundsOfMap(a1) && !antinodesMap[a1.y][a1.x]) {
                (*antinodesCount)++;
                antinodesMap[a1.y][a1.x] = true;
            }

            Point a2 = add(fp.points[j], substruct(fp.points[j], fp.points[i]));
            if (pointInBoundsOfMap(a2) && !antinodesMap[a2.y][a2.x]) {
                (*antinodesCount)++;
                antinodesMap[a2.y][a2.x] = true;
            }

            /*printf("Letter: %c a1=(%d, %d) a2=(%d, %d)\n", fp.frec, a1.x, a1.y,*/
            /*       a2.x, a2.y);*/
        }
}

void printAntennas(FrecPoints antennas[], int len) {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            char c = '.';
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < antennas[i].pointsLength; j++)
                    if (antennas[i].points[j].x == x &&
                        antennas[i].points[j].y == y)
                        c = antennas[i].frec;
            }
            putchar(c);
        }
        putchar('\n');
    }
}

void printMap() {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++)
            if (antinodesMap[y][x]) {
                putchar('#');
            } else {
                putchar('.');
            }
        putchar('\n');
    }
}

int main(void) {
    memset(antinodesMap, false, ARR_BUF_SIZE * ARR_BUF_SIZE * sizeof(bool));

    FrecPoints antennas[ARR_BUF_SIZE];

    int length = parseInput(antennas);
    /*printf("L: %d, mapHeight: %d, mapWidth: %d\n", length, mapHeight, mapWidth);*/
    /**/
    /*printAntennas(antennas, length);*/

    int antinodesCount = 0;
    for (int i = 0; i < length; i++) {
        setAntinodes(antennas[i], &antinodesCount);
    }

    /*printMap();*/

    printf("Answer: %d\n", antinodesCount);

    return EXIT_SUCCESS;
}
