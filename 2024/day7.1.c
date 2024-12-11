#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_BUF_SIZE 1000
#define STR_BUF_SIZE 20

typedef struct {
    long long result;
    unsigned int numbers[ARR_BUF_SIZE];
    int numbersLength;
} Equation;

void printEquation(Equation e) {
    printf("%lld: ", e.result);
    for (int i = 0; i < e.numbersLength; i++)
        printf("%d ", e.numbers[i]);
    puts("");
}

typedef enum {
    TEST_VALUE,
    NUMBER,
} ParseState;

int parseInput(Equation data[]) {
    int c, i = 0;

    int bufIndex = 0;
    char buf[STR_BUF_SIZE];
    ParseState state = TEST_VALUE;

    Equation curEquation = {.numbersLength = 0};

    while ((c = getchar()) != EOF) {
        switch (state) {
        case TEST_VALUE:
            if (c == ':') {
                getchar(); // whitespace

                state = NUMBER;

                buf[bufIndex] = '\0';
                curEquation.result = atoll(buf);

                bufIndex = 0;
            } else {
                buf[bufIndex++] = c;
            }
            break;
        case NUMBER:
            if (c == ' ') {
                buf[bufIndex] = '\0';
                curEquation.numbers[curEquation.numbersLength++] = atoll(buf);
                bufIndex = 0;
            } else if (c == '\n') {
                buf[bufIndex] = '\0';
                curEquation.numbers[curEquation.numbersLength++] = atoll(buf);
                bufIndex = 0;
                data[i++] = curEquation;
                state = TEST_VALUE;
                curEquation.numbersLength = 0;
            } else {
                buf[bufIndex++] = c;
            }
            break;
        }
    }
    return i;
}

void printData(Equation data[], int length) {
    for (int i = 0; i < length; i++)
        printEquation(data[i]);
}

bool nextCombination(int data[], int n, int k) {
    int i;
    for (i = 0; i < n && data[i] == (k - 1); i++)
        data[i] = 0;

    if (i >= n) {
        return false;
    } else {
        data[i]++;
        return true;
    }
}

#define K 3
#define ADD 0
#define MUL 1
#define CONCAT 2

bool isValidEquation(Equation e) {
    int i, n = e.numbersLength - 1;
    int combination[n];
    memset(combination, 0, n * sizeof(int));

    char strBuf[STR_BUF_SIZE];
    long long result;

    do {
        result = (long long)e.numbers[0];

        for (i = 0; i < n;) {
            switch (combination[i]) {
            case ADD:
                result += (long long)e.numbers[++i];
                break;
            case MUL:
                result *= (long long)e.numbers[++i];
                break;
            case CONCAT:
                sprintf(strBuf, "%lld%u", result, e.numbers[++i]);
                result = atoll(strBuf);
                break;
            }
        }

        if (result == e.result)
            return true;
    } while (nextCombination(combination, n, K));

    return false;
}

long long checkData(Equation data[], int length) {
    long long result = 0;
    for (int i = 0; i < length; i++) {
        /*printEquation(data[i]);*/
        bool ok = isValidEquation(data[i]);
        if (ok)
            result += data[i].result;
        /*printf("Is: %d\n", (int)ok);*/
    }
    return result;
}

int main(void) {
    Equation data[ARR_BUF_SIZE];
    int length = parseInput(data);
    /*printData(data, length);*/
    printf("Answer: %lld\n", checkData(data, length));
    return EXIT_SUCCESS;
}
