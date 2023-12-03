#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<inttypes.h>
#include<stdbool.h>

int tonumber(char *start) {
    switch (start[0])
    {
    case 'z':
        if (start[1] == 'e' && start[2] == 'r' && start[3] == 'o') {
            return 0;
        }
        break;
    case 'o':
        if (start[1] == 'n' && start[2] == 'e') return 1;
        break;
    case 't':
        if (start[1] == 'w' && start[2] == 'o') {
            return 2;
        } else if (start[1] == 'h' && start[2] == 'r' && start[3] == 'e' && start[4] == 'e') {
            return 3;
        }
        break;
    case 'f':
        if (start[1] == 'o' && start[2] == 'u' && start[3] == 'r') {
            return 4;
        } else if (start[1] == 'i' && start[2] == 'v' && start[3] == 'e') {
            return 5;
        }
        break;
    case 's':
        if (start[1] == 'i' && start[2] == 'x') {
            return 6;
        } else if (start[1] == 'e' && start[2] == 'v' && start[3] == 'e' && start[4] == 'n') {
            return 7;
        }
        break;
    case 'e':
        if (start[1] == 'i' && start[2] == 'g' && start[3] == 'h' && start[4] == 't') {
            return 8;
        }
        break;
    case 'n':
        if (start[1] == 'i' && start[2] == 'n' && start[3] == 'e') {
            return 9;
        }
        break;
    default:
        if (isdigit(start[0])) {
            return start[0] - '0';
        }
    }
    return -1;
}

int process_line_p1(char *buffer) {
    int first_digit = 0;
    int last_digit = 0;
    int strlength = strlen(buffer);

    for (int i = 0; i < strlength; i++) {
        if (isdigit(&buffer[i])) {
            first_digit = &buffer[i] - '0';
            break;
        }
    }

    for (int i = strlength; i >= 0; i--) {
        if (isdigit(&buffer[i])) {
            last_digit = &buffer[i] - '0';
            break;
        }
    }

    return (first_digit * 10) + last_digit;
}

int process_line_p2(char *buffer, bool debug) {
    int first_digit = 0;
    int last_digit = 0;
    int strlength = strlen(buffer);
    int temp;

    for (int i = 0; i < strlength; i++) {
        if ((temp = tonumber(&buffer[i])) != -1) {
            if (debug) printf("first digit found: %d, string: %s", temp, &buffer[i]);
            first_digit = temp;
            break;
        }
    }

    for (int i = strlength; i >= 0; i--) {
        if ((temp = tonumber(&buffer[i])) != -1) {
            if (debug) printf("last digit found: %d, string: %s", temp, &buffer[i]);
            last_digit = temp;
            break;
        }
    }

    return (first_digit * 10) + last_digit;
}

int main(int argc, char **argv) {
    uint32_t sum = 0;
    uint32_t lines = 0;
    FILE* fp = fopen("day1.txt", "r");
    char buffer[70];

    while (!feof(fp)) {
        memset(buffer, 0, 70);
        fgets(buffer, 70, fp);
        int result = process_line_p2(buffer, lines < 5);
        sum += result;
        if (result == 0) {
            printf("check line: %"PRIu32"\n", lines);
        }
        if (lines < 5) {
            printf("result for line %"PRIu32": %"PRIu32"\n", lines, result);
        }
        lines++;
    }

    printf("sum: %"PRIu32"\n", sum);

    return 0;
}