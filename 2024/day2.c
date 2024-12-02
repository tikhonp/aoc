#include <stdio.h>
#include <stdlib.h>

typedef enum { ASC, DESC, FIRST_NUM, SECOND_NUM } linestate;

#define CHAR_BUF_SIZE 10

typedef enum { SAFE, UNSAFE, EOFFED } readline_result;

#define RET_UNSAFE(c)                                                          \
    while (c != '\n')                                                          \
        c = getchar();                                                         \
    return UNSAFE

readline_result readline() {
    /*printf("Started r\n");*/
    int c, prevNum, i;

    linestate state = FIRST_NUM;

    char cNum[CHAR_BUF_SIZE];
    i = 0;

    c = getchar();
    while (1) {
        if (c == EOF)
            return EOFFED;

        while (c != ' ' && c != '\n') {
            /*printf("Parcing num %c\n", c);*/
            cNum[i++] = c;
            c = getchar();
        }

        cNum[i] = '\0';
        i = 0;
        int num = atoi(cNum);

        /*printf("Parsed num=%d state=%d, prevNum=%d\n", num, state, prevNum);*/

        switch (state) {
        case ASC:
            if (prevNum >= num) {
                RET_UNSAFE(c);
            }
            if ((num - prevNum) > 3) {
                RET_UNSAFE(c);
            }
            break;
        case DESC:
            if (prevNum <= num) {
                RET_UNSAFE(c);
            }
            if ((prevNum - num) > 3) {
                RET_UNSAFE(c);
            }
            break;
        case FIRST_NUM:
            state = SECOND_NUM;
            break;
        case SECOND_NUM:
            if (prevNum == num) {
                RET_UNSAFE(c);
            }
            if (abs(prevNum - num) > 3) {
                RET_UNSAFE(c);
            }
            state = num > prevNum ? ASC : DESC;
            break;
        }

        prevNum = num;

        if (c == '\n')
            return SAFE;

        c = getchar();
    }
}

int main(void) {

    int safeReports = 0;
    readline_result res;

    int i = 1;
    while ((res = readline()) != EOFFED)
        /*printf("%d: is %d\n", i++, (int)res);*/
        if (res == SAFE)
            safeReports++;

    printf("Answer: %d\n", safeReports);

    return EXIT_SUCCESS;
}
