#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

// for bit mask:
//  0 - ADD
//  1 - MUL
bool isValidEquation(Equation e) {
    unsigned int combination;
    int i = 0;

    unsigned long long maxCombination = (1 << (e.numbersLength - 1)) - 1;
    if (maxCombination >= UINT_MAX)
        printf("FUCK\n");

    for (combination = 0; combination <= maxCombination; combination++) {
        long long result = (long long)e.numbers[0];
        for (i = 0; i < (e.numbersLength - 1);)
            if (combination & (1 << i)) {
                result *= (long long)e.numbers[++i];
            } else {
                result += (long long)e.numbers[++i];
            }
        if (result == e.result)
            return true;
    }
    return false;
}

long long checkData(Equation data[], int length) {
    long long result = 0;
    for (int i = 0; i < length; i++) {
        if (isValidEquation(data[i]))
            result += data[i].result;
        /*printEquation(data[i]);*/
        /*printf("Is: %d\n", (int)isValidEquation(data[i]));*/
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
