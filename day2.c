#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<inttypes.h>
#include<stdbool.h>

int is_possible(int r, int g, int b) {
    return r <= 12 && g <= 13 && b <= 14;
}

int check_set(char *start, char *end) {
    char *nextcomma;
    char buffer[7];
    int quantity = 0;
    int r = 0, g = 0, b = 0;

    while (start < end) {
        nextcomma = strchr(start, ',');
        if (nextcomma == NULL) {
            nextcomma = end;
        }
        sscanf(start, "%d %s", &quantity, &buffer);
        switch (buffer[0])
        {
        case 'r':
            r = quantity;
            break;
        case 'g':
            g = quantity;
            break;
        case 'b':
            b = quantity;
            break;
        }
        start = nextcomma + 2;
    }
    // printf("%d %d %d\n", r, g, b);
    return is_possible(r, g, b);
}

void update_minimum_cubes(char *start, char *end, int *cubes) {
    char *nextcomma;
    char buffer[7];
    int quantity = 0;
    int r = 0, g = 0, b = 0;

    while (start < end) {
        nextcomma = strchr(start, ',');
        if (nextcomma == NULL) {
            nextcomma = end;
        }
        sscanf(start, "%d %s", &quantity, &buffer);
        switch (buffer[0])
        {
        case 'r':
            r = quantity;
            break;
        case 'g':
            g = quantity;
            break;
        case 'b':
            b = quantity;
            break;
        }
        start = nextcomma + 2;
    }

    cubes[0] = r > cubes[0] ? r : cubes[0];
    cubes[1] = g > cubes[1] ? g : cubes[1];
    cubes[2] = b > cubes[2] ? b : cubes[2];
}

int get_power(int *cubes) {
    return cubes[0] * cubes[1] * cubes[2];
}

int part1() {
    int gameidsum = 0;
    FILE* fp = fopen("day2.txt", "r");
    char buffer[256];

    /* variables used for problem */
    int gameid;
    char *bufferpointer = &buffer[0];

    while (!feof(fp)) {
        bufferpointer = &buffer[0];

        memset(buffer, 0, 256);
        fgets(buffer, 256, fp);
        
        sscanf(buffer, "Game %d:", &gameid);
        //if (gameid < 5) printf("game: %d\n", gameid);

        while (*bufferpointer != ':') {
            bufferpointer++;
        }
        bufferpointer += 2;

        //if (gameid < 5) printf("%s", bufferpointer);
        /*if (gameid < 5) printf("successfully moved up pointer\n");*/
        while (1) {
            char* endofset = strchr(bufferpointer, ';');
            if (endofset == NULL) {
                endofset = strchr(bufferpointer, '\n');
            }

            if (!check_set(bufferpointer, endofset)) break;
            if (*endofset == '\n') {
                gameidsum += gameid;
                break;
            }
            bufferpointer = endofset + 1;
        }
    }

    fclose(fp);

    return gameidsum;
}

int part2() {
    int powersum = 0;
    FILE* fp = fopen("day2.txt", "r");
    char buffer[256];

    /* variables used for problem */
    int cubes[3];
    int gameid;
    char *bufferpointer = &buffer[0];

    while (!feof(fp)) {
        bufferpointer = &buffer[0];

        memset(buffer, 0, sizeof(char)*256);
        memset(cubes, 0, sizeof(int)*3);
        fgets(buffer, 256, fp);
        
        sscanf(buffer, "Game %d:", &gameid);
        //if (gameid < 5) printf("game: %d\n", gameid);

        while (*bufferpointer != ':') {
            bufferpointer++;
        }
        bufferpointer += 2;

        //if (gameid < 5) printf("%s", bufferpointer);
        /*if (gameid < 5) printf("successfully moved up pointer\n");*/
        while (1) {
            char* endofset = strchr(bufferpointer, ';');
            if (endofset == NULL) {
                endofset = strchr(bufferpointer, '\n');
                if (endofset == NULL) endofset = strchr(bufferpointer, 0);
            }

            update_minimum_cubes(bufferpointer, endofset, &cubes[0]);
            //if (endofset == NULL) printf("game id where null: %d\n", gameid);
            if (*endofset == '\n' || *endofset == 0) {
                if (gameid < 5) printf("%d %d %d\n", cubes[0], cubes[1], cubes[2]);
                powersum += get_power(&cubes[0]);
                //printf("new powersum: %d\n", powersum);
                break;
            }
            bufferpointer = endofset + 1;
        }
    }

    fclose(fp);

    return powersum;
}

int main(int argc, int **argv) {
    printf("game id sum: %d\n", part1());
    printf("power sum: %d\n", part2());
}