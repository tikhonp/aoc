#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_BUF_SIZE 100000

int parseInput(int data[], int *spacesLength) {
    int c, i, dataIndx = 0;
    int fileID = 0;
    bool freeSpace = false;
    while ((c = getchar()) != EOF) {
        char buf[2];
        buf[0] = c;
        buf[1] = '\n';
        int blockLen = atoi(buf);
        if (freeSpace) {
            (*spacesLength) += blockLen;
            for (i = 0; i < blockLen; i++)
                data[dataIndx++] = -1;
        } else {
            for (i = 0; i < blockLen; i++)
                data[dataIndx++] = fileID;
            fileID++;
        }
        freeSpace = !freeSpace;
    }
    return dataIndx;
}

void printData(int data[], int length) {
    for (int i = 0; i < length; i++)
        if (data[i] == -1)
            putchar('.');
        else
            printf("%d", data[i]);
    putchar('\n');
}

void printDataFrom(int data[], int length, int from) {
    for (int i = from; i < length; i++)
        if (data[i] == -1)
            putchar('.');
        else
            printf("%d", data[i]);
    putchar('\n');
}

void moveFileBlocks(int data[], int length, int spacesLength) {
    int i, emptyCellIndex = 0, swapped = 0;
    for (i = (length - 1); i >= 0; i--) {
        if (swapped++ >= spacesLength) {
            return;
        }
        if (data[i] == -1)
            continue;
        while (data[emptyCellIndex] != -1 && emptyCellIndex < length)
            emptyCellIndex++;
        data[emptyCellIndex] = data[i];
        data[i] = -1;
    }
}

long checksum(int data[], int length) {
    long checksum = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] != -1)
            checksum += (long)(i * data[i]);
    }
    return checksum;
}

int main(void) {
    int data[ARR_BUF_SIZE];

    int spacesLength = 0;
    int length = parseInput(data, &spacesLength);
    /*printData(data, length);*/
    moveFileBlocks(data, length, spacesLength);
    long sum = checksum(data, length);
    /*printData(data, length);*/
    printf("checksum: %ld\n", sum);

    return EXIT_SUCCESS;
}
