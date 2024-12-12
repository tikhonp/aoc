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

int findNextFile(int data[], int fromIndx, int *fileSize) {
    int fileID = -1;
    int leftFileId;
    for (int i = fromIndx; i >= 0; i--) {
        if (fileID == -1 && data[i] != -1) {
            fileID = data[i];
            leftFileId = i;
        }
        if (fileID != -1 && data[i] != fileID) {
            (*fileSize) = leftFileId - i;
            return i + 1;
        }
    }
    return -1;
}

void moveFile(int data[], int fileIndx, int fileSize, int targetIndx) {
    int distanceBetweenFT = fileIndx - targetIndx;
    for (int i = fileIndx; i < (fileIndx + fileSize); i++) {
        data[i - distanceBetweenFT] = data[i];
        data[i] = -1;
    }
}

int findIndexOfLeftmostSpanOfFreeSpace(int data[], int length, int blockSize) {
    int startOfBlockIndx = -1;
    for (int i = 0; i < length; i++) {
        if (data[i] == -1) {
            if (startOfBlockIndx == -1)
                startOfBlockIndx = i;
            if ((i - startOfBlockIndx + 1) >= blockSize)
                return startOfBlockIndx;
        } else
            startOfBlockIndx = -1;
    }
    return startOfBlockIndx;
}

void moveFileBlocks(int data[], int length, int spacesLength) {
    int fileIndx = length;
    int fileSize;
    while ((fileIndx = findNextFile(data, fileIndx - 1, &fileSize)) != -1) {
        /*printf("fileIndx: %d, size: %d  ", fileIndx, fileSize);*/
        int freespaceIndx =
            findIndexOfLeftmostSpanOfFreeSpace(data, length, fileSize);
        /*printf("FREESPACE B: %d\n", freespaceIndx);*/
        if (freespaceIndx != -1 && freespaceIndx < fileIndx)
            moveFile(data, fileIndx, fileSize, freespaceIndx);
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
