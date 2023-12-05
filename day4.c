#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#define TEMPLATE_STRING "Card   1: 24 76 32 40 51 61 89  6 30 60 | 30 69 24 86  6  8 92 61 51 88 63 67 32 62 15 49 22 77 40 27 89 60 76 58 79"

void part1() {
    FILE *fp = fopen("day4.txt", "r");

    int sum = 0;
    int line = 0;
    char buffer[120];

    int map[100];
    int temp;
    int power;
    //memset(map, 0, 100*sizeof(char));

    char *bp = &buffer[0];
    while (fgets(buffer, 120, fp)) {
        // i guess l doesn't need to be reset if the entire array is overwritten every time
        // map needs to be reset though.
        memset(map, 0, sizeof(int)*100);
        power = -1;

        sscanf(buffer, "Card %d: ", &line);
        //printf("line %d\n", line);
        bp = &buffer[10];
        char *token = strtok(bp, " ");
        //printf("winning numbers: ");
        for (int i = 0; i < 10; i++) {
            sscanf(token, "%d", &temp);
            //printf("%d ", temp);
            map[temp] = 1;
            token = strtok(NULL, " ");
        }
        //printf("\n");
        /*
        memset(map, 0, sizeof(char)*100);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                printf("%d ", map[(i*10)+j]);
            }
            printf("\n");
        }
        */

        bp = &buffer[42];
        token = strtok(bp, " ");
        for (int i = 0; i < 25; i++) {
            sscanf(token, "%d", &temp);
            if (map[temp] == 1) {
                power += 1;
            }
            token = strtok(NULL, " ");
        }
        //printf("\n");

        // finished putting them into the variables, now let's do some work
        if (power > -1) {
            //printf("matches: %d -- added %d\n", power + 1, (1 << (power)));
            sum += (1 << (power));
        } else {
            //printf("no matches\n");
        }
    }

    fclose(fp);
    printf("final sum: %d\n", sum);
}

void part2() {
    FILE *fp = fopen("day4.txt", "r");

    int sum = 0;
    int line = 0;
    char buffer[120];

    int map[100];
    int cards_collected[197];
    int temp;
    int power;
    //memset(map, 0, 100*sizeof(char));

    for (int i = 0; i < 197; i++) {
        cards_collected[i] = 1;
    }

    char *bp = &buffer[0];
    while (fgets(buffer, 120, fp)) {
        // i guess l doesn't need to be reset if the entire array is overwritten every time
        // map needs to be reset though.
        memset(map, 0, sizeof(int)*100);
        power = 0;

        sscanf(buffer, "Card %d: ", &line);
        //printf("line %d\n", line);

        line -= 1; // need this because line starts 1-indexed

        // this logic collects the number of winning numbers
        bp = &buffer[10];
        char *token = strtok(bp, " ");

        for (int i = 0; i < 10; i++) {
            sscanf(token, "%d", &temp);
            //printf("%d ", temp);
            map[temp] = 1;
            token = strtok(NULL, " ");
        }

        bp = &buffer[42];
        token = strtok(bp, " ");
        for (int i = 0; i < 25; i++) {
            sscanf(token, "%d", &temp);
            if (map[temp] == 1) {
                power += 1;
            }
            token = strtok(NULL, " ");
        }

        // this takes the number of current cards and adds it to the next blah blah blah
        int num_cards = cards_collected[line];
        for (int i = 1; i <= power; i++) {
            if (line + i <= 197) cards_collected[line+i] += num_cards; 
        }
    }

    for (int i = 0; i < 197; i++) {
        sum += cards_collected[i];
        printf("cards collected for %d: %d\n", i+1, cards_collected[i]);
    }

    fclose(fp);
    printf("final sum: %d\n", sum);
}

int main(int argc, char **argv) {
    part1();
    part2();

    return 0;
}