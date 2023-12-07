#include<stdio.h>
#include<inttypes.h>
#include<math.h>

#define BUFFERSIZE 40

void part1() {
    FILE *fp = fopen("day6.txt", "r");
    int results;
    int times[4];
    int distances[4];
    int product = 1;

    results = fscanf(fp, "%*[^:]:%d%d%d%d\n", times, times+1, times+2, times+3);
    //printf("%d\n", results);
    //printf("%d %d %d %d\n", times[0], times[1], times[2], times[3]);

    results = fscanf(fp, "%*[^:]:%d%d%d%d\n", distances, distances+1, distances+2, distances+3);
    //printf("%d\n", results);
    //printf("%d %d %d %d\n", distances[0], distances[1], distances[2], distances[3]);

    fclose(fp);

    for (int i = 0; i < 4; i++) {
        int time = times[i];
        int distance = distances[i];
        int held_down = 0;
        int winners = 0;

        for (int j = 1; j < time; j++) {
            if ((j * (time - j)) > distance) {
                winners++;
            }
        }
        product *= winners;
    }

    printf("possible ways to win: %d\n", product);
}

void part2() {
    FILE *fp = fopen("day6.txt", "r");
    int results;
    int times[4];
    int distances[4];
    int product = 1;

    results = fscanf(fp, "%*[^:]:%d%d%d%d\n", times, times+1, times+2, times+3);
    //printf("%d\n", results);
    //printf("%d %d %d %d\n", times[0], times[1], times[2], times[3]);

    results = fscanf(fp, "%*[^:]:%d%d%d%d\n", distances, distances+1, distances+2, distances+3);
    //printf("%d\n", results);
    //printf("%d %d %d %d\n", distances[0], distances[1], distances[2], distances[3]);

    fclose(fp);

    uint64_t time = times[3] + (times[2] * 100) + (times[1] * 10000) + (times[0] * 1000000);
    uint64_t distance = (distances[0] * 1000000000000ULL) + (uint64_t)(distances[1] * (uint64_t)100000000) + distances[3] + (distances[2] * 10000); //+ (uint64_t)(distances[1] * 10000000);
    uint64_t winners = 0;

    for (uint64_t j = 1; j < time; j++) {
        if ((j * (time - j)) > distance) {
            winners++;
        }
    }

    printf("%d\n", time);
    printf("%"PRIu64"\n", distance);

    printf("possible ways to win: %"PRIu64"\n", winners);
}

int main(int argc, char **argv) {
    part1();
    part2();

    return 0;
}