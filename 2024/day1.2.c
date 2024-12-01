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

int main(void) {

    int leftList[MAX_LIST_SIZE], rightList[MAX_LIST_SIZE];

    int n = parseInput(leftList, rightList);

    if (n == -1) {
        puts("FUCK");
        return EXIT_FAILURE;
    }

    int i, j;
    long simSum = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (leftList[i] == rightList[j])
                simSum += leftList[i];

    printf("Answer is: %ld\n", simSum);

    return EXIT_SUCCESS;
}
