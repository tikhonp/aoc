#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_BUFFER_SIZE 4

typedef enum {
    WAITF_M_OR_D_CHAR,
    WAITF_U_CHAR,
    WAITF_L_CHAR,
    WAITF_OPEN_PR,
    SCANNING_FIRST_NUM,
    SCANNING_SECOND_NUM,

    WAITF_O_CHAR,
    WAITF_COMM_OPEN_PR,
    WAITF_COMM_CLOSE_PR,
    WAITF_N_CHAR,
    WAITF_ASTR_CHAR, // '
    WAITF_T_CHAR,
} scannState;

typedef struct {
    scannState state;
    int firstNum;
    int secondNum;
    int scanI;
    char numBuffer[NUM_BUFFER_SIZE];
    bool mulEnabled;
} scannData;

void resetScannData(scannData *data) {
    data->state = WAITF_M_OR_D_CHAR;
    data->scanI = 0;
}

typedef enum {
    WAITING_FOR_NEXT_CHAR,
    DONE,
    FAILED,
} processCharResult;

processCharResult processChar(scannData *data, char c) {
    switch (data->state) {
    case WAITF_M_OR_D_CHAR:
        if (c == 'm' && data->mulEnabled) {
            data->state = WAITF_U_CHAR;
            return WAITING_FOR_NEXT_CHAR;
        }
        if (c == 'd') {
            data->state = WAITF_O_CHAR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_U_CHAR:
        if (c == 'u') {
            data->state = WAITF_L_CHAR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_L_CHAR:
        if (c == 'l') {
            data->state = WAITF_OPEN_PR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_OPEN_PR:
        if (c == '(') {
            data->state = SCANNING_FIRST_NUM;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case SCANNING_FIRST_NUM:
        if (c == ',') {
            data->numBuffer[data->scanI] = '\0';
            data->firstNum = atoi(data->numBuffer);
            data->scanI = 0;
            data->state = SCANNING_SECOND_NUM;
            return WAITING_FOR_NEXT_CHAR;
        } else if (isdigit(c) && data->scanI <= 3) {
            data->numBuffer[data->scanI++] = c;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case SCANNING_SECOND_NUM:
        if (c == ')') {
            data->numBuffer[data->scanI] = '\0';
            data->secondNum = atoi(data->numBuffer);
            return DONE;
        } else if (isdigit(c) && data->scanI <= 3) {
            data->numBuffer[data->scanI++] = c;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_O_CHAR:
        if (c == 'o') {
            data->state = data->mulEnabled ? WAITF_N_CHAR : WAITF_COMM_OPEN_PR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_COMM_OPEN_PR:
        if (c == '(') {
            data->state = WAITF_COMM_CLOSE_PR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_COMM_CLOSE_PR:
        if (c == ')') {
            data->mulEnabled = !data->mulEnabled;
            data->state = WAITF_M_OR_D_CHAR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_N_CHAR:
        if (c == 'n') {
            data->state = WAITF_ASTR_CHAR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_ASTR_CHAR:
        if (c == '\'') {
            data->state = WAITF_T_CHAR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
    case WAITF_T_CHAR:
        if (c == 't') {
            data->state = WAITF_COMM_OPEN_PR;
            return WAITING_FOR_NEXT_CHAR;
        }
        return FAILED;
        break;
    }
}

int mulResult(scannData *data) { return data->firstNum * data->secondNum; }

int main(void) {

    int c;
    int answer = 0;

    scannData data;

    resetScannData(&data);

    data.mulEnabled = true;

    while ((c = getchar()) != EOF) {
        switch (processChar(&data, c)) {
        case WAITING_FOR_NEXT_CHAR:
            continue;
        case DONE:
            answer += mulResult(&data);
            resetScannData(&data);
            continue;
        case FAILED:
            resetScannData(&data);
            processChar(&data, c);
            continue;
        }
    }

    printf("Answer: %d\n", answer);

    return EXIT_SUCCESS;
}
