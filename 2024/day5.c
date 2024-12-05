#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int prev;
    int after;
} Rule;

#define ARR_BUF_SIZE 2000
#define STR_BUF_SIZE 100

typedef enum {
    PARSING_FIRST_VALUE,
    PARSING_SECOND_VALUE,
} ParseRulesState;

int parseRules(Rule rules[]) {
    int c;
    char strBuf[STR_BUF_SIZE];

    ParseRulesState state = PARSING_FIRST_VALUE;

    int rulesI = 0;
    int i = 0;
    int firstValue;

    while (!(((c = getchar()) == '\n') && state == PARSING_FIRST_VALUE)) {
        switch (state) {
        case PARSING_FIRST_VALUE:
            if (c == '|') {
                state = PARSING_SECOND_VALUE;
                strBuf[i] = '\0';
                firstValue = atoi(strBuf);
                i = 0;
            } else {
                strBuf[i++] = c;
            }
            break;
        case PARSING_SECOND_VALUE:
            if (c == '\n') {
                state = PARSING_FIRST_VALUE;
                strBuf[i] = '\0';
                Rule r = {.prev = firstValue, .after = atoi(strBuf)};
                rules[rulesI++] = r;
                i = 0;
            } else {
                strBuf[i++] = c;
            }
            break;
        }
    }
    return rulesI;
}

void printRules(Rule rules[], int length) {
    for (int i = 0; i < length; i++)
        printf("%d | %d\n", rules[i].prev, rules[i].after);
}

void printLine(int data[], int length) {
    for (int i = 0; i < length; i++)
        printf("%d ", data[i]);
    printf("\n");
}

bool parseLine(int data[], int *length) {
    int i = 0, c;

    char strBuf[STR_BUF_SIZE];
    int numI = 0;

    while ((c = getchar()) != EOF)
        if (c == ',' || c == '\n') {
            strBuf[numI] = '\n';
            data[i++] = atoi(strBuf);
            numI = 0;
            if (c == '\n')
                break;
        } else {
            strBuf[numI++] = c;
        }

    *length = i;
    return c != EOF;
}

bool checkIfLineViolatesRule(int line[], int lineLength, Rule rule) {
    bool afterWasFound = false;
    for (int i = 0; i < lineLength; i++)
        if (line[i] == rule.prev && afterWasFound)
            return false;
        else if (line[i] == rule.after)
            afterWasFound = true;
    return true;
}

bool isLineViolatesTheRules(int line[], int lineLength, Rule rules[],
                            int rulesLength) {
    for (int i = 0; i < rulesLength; i++)
        if (!checkIfLineViolatesRule(line, lineLength, rules[i]))
            return false;
    return true;
}

int main(void) {
    Rule rules[ARR_BUF_SIZE];

    int rulesCount = parseRules(rules);

    /*printf("Rules: %d\n", rulesCount);*/

    /*printRules(rules, rulesCount);*/

    int answer = 0;
    int line[ARR_BUF_SIZE], length;
    while (parseLine(line, &length)) {
        /*printLine(line, length);*/
        bool ok = isLineViolatesTheRules(line, length, rules, rulesCount);
        /*printf("Line is %d\n", (int)ok);*/
        if (ok) {
            answer += line[(int)((length - 1) / 2)];
        }
    }

    printf("Answer: %d\n", answer);

    return EXIT_SUCCESS;
}
