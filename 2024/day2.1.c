#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CHAR_BUF_SIZE 10
#define LINE_INT_BUF_SIZE 100

typedef enum { SAFE, UNSAFE } safety;
typedef enum { ASC, DESC } checkLineState;

safety checkLine(int data[], int length) {
    if (data[0] == data[1])
        return UNSAFE;
    if (abs(data[0] - data[1]) > 3)
        return UNSAFE;
    checkLineState state = data[0] < data[1] ? ASC : DESC;
    for (int i = 2; i < length; i++) {
        switch (state) {
        case ASC:
            if (data[i - 1] >= data[i])
                return UNSAFE;
            if ((data[i] - data[i - 1]) > 3)
                return UNSAFE;
            break;
        case DESC:
            if (data[i - 1] <= data[i])
                return UNSAFE;
            if ((data[i - 1] - data[i]) > 3)
                return UNSAFE;
            break;
        }
    }
    return SAFE;
}

// -1 if EOF
int parseLine(int data[], int bufferSize) {
    int c, numberIndx, dataIndx;

    numberIndx = dataIndx = 0;

    char number[CHAR_BUF_SIZE];

    while ((c = getchar()) != '\n') {
        if (c == EOF)
            return -1;
        while (c != ' ' && c != '\n') {
            number[numberIndx++] = c;
            c = getchar();
        }

        number[numberIndx] = '\0';
        numberIndx = 0;
        data[dataIndx++] = atoi(number);

        if (c == '\n')
            return dataIndx;
        if (dataIndx >= bufferSize)
            return -1;
    }

    return dataIndx;
}

void printArr(int data[], int length) {
    printf("[");
    for (int i = 0; i < length; i++)
        printf("%d ", data[i]);
    printf("]\n");
}

void copyRemovingElement(int source[], int target[], int atIndex, int length) {
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (i == atIndex)
            continue;
        target[j++] = source[i];
    }
}

safety problemDampener(int data[], int length) {
    int dampedData[length];
    printf("Trying to fix: ");
    printArr(data, length);
    for (int i = 0; i < length; i++) {
        copyRemovingElement(data, dampedData, i, length);
        printArr(dampedData, length - 1);
        if (checkLine(dampedData, length - 1) == SAFE)
            return SAFE;
    }
    return UNSAFE;
}

int main(void) {

    int safeReports = 0;

    int i = 0;

    int line[LINE_INT_BUF_SIZE];

    while (1) {
        i++;
        int len = parseLine(line, LINE_INT_BUF_SIZE);
        if (len == -1)
            break;
        safety lineResult = checkLine(line, len);
        if (lineResult == SAFE)
            safeReports++;
        else {
            printf("LINE %d is UNSAFE trying to fix\n", i);
            if (problemDampener(line, len) == SAFE) {
                safeReports++;
                printf("FINE\n");
            } else {
                printf("FAILED\n");
            }
        }
    }

    printf("Answer: %d\n", safeReports);

    return EXIT_SUCCESS;
}
