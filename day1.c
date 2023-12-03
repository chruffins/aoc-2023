#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<inttypes.h>

int process_line(char *buffer) {
    int first_digit = 0;
    int last_digit = 0;
    int strlength = strlen(buffer);

    for (int i = 0; i < strlength; i++) {
        if (isdigit(buffer[i])) {
            first_digit = buffer[i] - '0';
            break;
        }
    }

    for (int i = strlength; i >= 0; i--) {
        if (isdigit(buffer[i])) {
            last_digit = buffer[i] - '0';
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
        
        fgets(buffer, 70, fp);
        int result = process_line(buffer);
        sum += result;
        if (result == 0) {
            printf("check line: %"PRIu32"\n", lines);
        }
        lines++;
    }

    printf("sum: %"PRIu32"\n", sum);

    return 0;
}