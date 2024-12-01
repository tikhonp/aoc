#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 2048
#define MAX_NUMBER_CHAR_SIZE 15

int parseInput(int leftList[], int rightList[]) {

    int c, i, intListIndx;

    char leftNum[MAX_NUMBER_CHAR_SIZE], rightNum[MAX_NUMBER_CHAR_SIZE];

    bool scanningLeftChar = true;

    intListIndx = i = 0;

    while ((c = getchar()) != EOF) {
        if (scanningLeftChar) {
            if (c == ' ') {
                leftNum[i] = '\0';
                leftList[intListIndx] = atoi(leftNum);

                scanningLeftChar = false;
                i = 0;
            } else if (i < MAX_NUMBER_CHAR_SIZE) {
                leftNum[i++] = c;
            } else {
                return -1;
            }
        } else {
            if (c == '\n') {
                rightNum[i] = '\0';
                rightList[intListIndx] = atoi(rightNum);
                intListIndx++;

                scanningLeftChar = true;
                i = 0;
            } else if (i < MAX_NUMBER_CHAR_SIZE) {
                rightNum[i++] = c;
            } else {
                return -1;
            }
        }
    }

    return intListIndx;
}

int compare(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}

int main(void) {

    int leftList[MAX_LIST_SIZE], rightList[MAX_LIST_SIZE];

    int n = parseInput(leftList, rightList);

    if (n == -1) {
        puts("FUCK");
        return EXIT_FAILURE;
    }

    qsort(&leftList, n, sizeof(int), compare);
    qsort(&rightList, n, sizeof(int), compare);

    int diffSum = 0;
    for (int i = 0; i < n; i++) {
        printf("nums: %d %d\n", leftList[i], rightList[i]);
        diffSum += abs(leftList[i] - rightList[i]);
    }

    printf("Answer is: %d\n", diffSum);

    return EXIT_SUCCESS;
}
