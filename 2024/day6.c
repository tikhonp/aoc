#include <stdio.h>
#include <stdlib.h>

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
        putchar('\n');
    }
}

int guardValking(Guard guard) {
    int visited = 1;
    while (1) {
        switch (guard.direction) {
        case UP:
            if (guard.y == 0)
                return visited;
            if (map[guard.y - 1][guard.x] == OBSTRUCTION) {
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.y--;
            break;
        case DOWN:
            if (guard.y == (height - 1))
                return visited;
            if (map[guard.y + 1][guard.x] == OBSTRUCTION) {
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.y++;
            break;
        case LEFT:
            if (guard.x == 0)
                return visited;
            if (map[guard.y][guard.x - 1] == OBSTRUCTION) {
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.x--;
            break;
        case RIGHT:
            if (guard.x == (width - 1))
                return visited;
            if (map[guard.y][guard.x + 1] == OBSTRUCTION) {
                guard.direction = getNextDirection(guard.direction);
                continue;
            }
            guard.x++;
            break;
        }

        if (map[guard.y][guard.x] != VISITED) {
            visited++;
            map[guard.y][guard.x] = VISITED;
        }
    }
}

int main(void) {
    Guard guard;

    parseMap(&guard);
    /*printGuard(guard);*/
    /*printMap();*/
    printf("Answer: %d\n", guardValking(guard));
    /*printMap();*/

    return EXIT_SUCCESS;
}
