#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 200

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Direction;

Direction getNextDirection(Direction direction) {
    switch (direction) {
    case UP:
        return RIGHT;
    case DOWN:
        return LEFT;
    case LEFT:
        return UP;
    case RIGHT:
        return DOWN;
    }
}

typedef struct {
    int x, y;
    Direction direction;
} Guard;

void printGuard(Guard g) {
    printf("Guard (%d, %d) %d\n", g.x, g.y, g.direction);
}

typedef enum {
    EMPTY,
    OBSTRUCTION,
    VISITED,
} Square;

Square map[ARR_SIZE][ARR_SIZE];
int height, width;

Square *copyMap() {
    Square *newMap = (Square *)malloc(height * width * sizeof(Square));
    memcpy(map, newMap, height * width * sizeof(Square));
    return newMap;
}

void parseMap(Guard *guard) {
    int c, x = 0, y = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            width = x;
            x = 0;
            y++;
            continue;
        }
        switch (c) {
        case '.':
            map[y][x] = EMPTY;
            break;
        case '#':
            map[y][x] = OBSTRUCTION;
            break;
        case '^':
            map[y][x] = VISITED;
            guard->x = x;
            guard->y = y;
            guard->direction = UP;
            break;
        case '>':
            map[y][x] = VISITED;
            guard->x = x;
            guard->y = y;
            guard->direction = RIGHT;
            break;
        case 'v':
            map[y][x] = VISITED;
            guard->x = x;
            guard->y = y;
            guard->direction = DOWN;
            break;
        case '<':
            map[y][x] = VISITED;
            guard->x = x;
            guard->y = y;
            guard->direction = LEFT;
            break;
        }
        x++;
    }
    height = y;
}

void printMap() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (map[y][x]) {
            case EMPTY:
                putchar('.');
                break;
            case OBSTRUCTION:
                putchar('#');
                break;
            case VISITED:
                putchar('X');
                break;
            }
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}

typedef struct {
    int x, y;
} Point;

typedef struct {
    Direction direction;
    Point guardPosition;
} VisitedObstructionPoint;

bool vbpEqual(VisitedObstructionPoint a, Guard b) {
    return a.direction == b.direction && a.guardPosition.x == b.x &&
           a.guardPosition.y == b.y;
}

bool guardIn(VisitedObstructionPoint vPoints[], int length, Guard guard) {
    for (int i = 0; i < length; i++)
        if (vbpEqual(vPoints[i], guard))
            return true;
    return false;
}

bool isGuardValkingCycle(Guard guard, Point newObstructionPoint,
                         bool markVisit) {
    int vPointsI = 0;
    VisitedObstructionPoint vPoints[ARR_SIZE * ARR_SIZE];
    map[newObstructionPoint.y][newObstructionPoint.x] = OBSTRUCTION;

    while (1) {
        switch (guard.direction) {
        case UP:
            if (guard.y == 0) {
                map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                return false;
            }
            if (map[guard.y - 1][guard.x] == OBSTRUCTION) {
                if (guardIn(vPoints, vPointsI, guard)) {
                    map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                    return true;
                } else {
                    VisitedObstructionPoint vop = {
                        .direction = guard.direction,
                        .guardPosition = {.x = guard.x, .y = guard.y}};
                    vPoints[vPointsI++] = vop;
                }
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.y--;
            break;
        case DOWN:
            if (guard.y == (height - 1)) {
                map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                return false;
            }
            if (map[guard.y + 1][guard.x] == OBSTRUCTION) {
                if (guardIn(vPoints, vPointsI, guard)) {
                    map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                    return true;
                } else {
                    VisitedObstructionPoint vop = {
                        .direction = guard.direction,
                        .guardPosition = {.x = guard.x, .y = guard.y}};
                    vPoints[vPointsI++] = vop;
                }
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.y++;
            break;
        case LEFT:
            if (guard.x == 0) {
                map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                return false;
            }
            if (map[guard.y][guard.x - 1] == OBSTRUCTION) {
                if (guardIn(vPoints, vPointsI, guard)) {
                    map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                    return true;
                } else {
                    VisitedObstructionPoint vop = {
                        .direction = guard.direction,
                        .guardPosition = {.x = guard.x, .y = guard.y}};
                    vPoints[vPointsI++] = vop;
                }
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.x--;
            break;
        case RIGHT:
            if (guard.x == (width - 1)) {
                map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                return false;
            }
            if (map[guard.y][guard.x + 1] == OBSTRUCTION) {
                if (guardIn(vPoints, vPointsI, guard)) {
                    map[newObstructionPoint.y][newObstructionPoint.x] = EMPTY;
                    return true;
                } else {
                    VisitedObstructionPoint vop = {
                        .direction = guard.direction,
                        .guardPosition = {.x = guard.x, .y = guard.y}};
                    vPoints[vPointsI++] = vop;
                }
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.x++;
            break;
        }

        if (markVisit && map[guard.y][guard.x] != VISITED) {
            map[guard.y][guard.x] = VISITED;
        }
        if (markVisit) {
            /*printGuard(guard);*/
            /*printMap();*/
        }
    }
}

int successObstructions(Guard guard) {
    int x, y, successObstructionsCount = 0;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            /*printf("x: %d, y: %d, c: %d\n", x, y, successObstructionsCount);*/
            if (map[y][x] == OBSTRUCTION)
                continue;
            Point obstrPoint = {.x = x, .y = y};
            if (isGuardValkingCycle(guard, obstrPoint, (x == 3 && y == 6)))
                successObstructionsCount++;
        }
        /*printf("%d%%", (int)(((y + 1) / height) * 100));*/
    }
    return successObstructionsCount;
}

int main(void) {
    Guard guard;

    parseMap(&guard);
    /*printGuard(guard);*/
    /*printMap();*/

    printf("Answer: %d\n", successObstructions(guard));
    /*printMap();*/

    return EXIT_SUCCESS;
}
