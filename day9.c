#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<inttypes.h>
#include<assert.h>
#include<stdbool.h>

#define HISTORYINITSIZE 21
#define BUFSIZE 150

void part1() {
    FILE *fp = fopen("day9.txt", "r");
    char fbuffer[150];
    int pyramid[22][22];

    int64_t sum = 0;

    while (!feof(fp)) {
        char *bp = fbuffer;
        int i = 0;
        int row = 0;
        memset(pyramid, 0, sizeof(int)*22*22);
        memset(fbuffer, 0, sizeof(char)*150);
        fgets(fbuffer, 150, fp);

        int r = sscanf(bp, "%d", &pyramid[0][i]);
        i++;
        while ((bp = strchr(bp, ' ')) != NULL) {
            r = sscanf(bp, "%d", &pyramid[0][i]); // filling the 0th row
            i++;
            bp++;
        }
        /*
        for (int j = 0; j < 21; j++) {
            printf("%d ", pyramid[0][j]);
        }
        printf("\n");
        */

        while (1) {
            bool stop = true;
            /*
            for (int j = 0; j < 22; j++) {
                printf("%d ", pyramid[row][j]);
            }
            printf("\n");
            */

            row++;
            // there are 20 values in the 0th row, so the 1st row should have 19.
            for (int i = 0; i < (21-row); i++) {
                pyramid[row][i] = pyramid[row-1][i+1] - pyramid[row-1][i];
                if (pyramid[row][i]) stop = false;
            }
            
            if (stop) break;
        }

        pyramid[row][(21-row)] = 0; // justify why we can just start at row - 1... this value is pretty obvious
        for (int r = row-1; r >= 0; r--) {
            pyramid[r][21-r] = pyramid[r][20-r] + pyramid[r+1][20-r];
            /*
            for (int j = 0; j < 22; j++) {
                printf("%d ", pyramid[r][j]);
            }
            printf("\n");
            */
        }

        //printf("%d\n", pyramid[0][20]);
        sum += pyramid[0][21];
    }

    fclose(fp);

    printf("final sum for part 1: %"PRId64"\n", sum);
}

void part2() {
    FILE *fp = fopen("day9.txt", "r");
    char fbuffer[150];
    int pyramid[22][22];

    int64_t sum = 0;

    while (!feof(fp)) {
        char *bp = fbuffer;
        int i = 1;
        int row = 0;
        memset(pyramid, 0, sizeof(int)*22*22);
        memset(fbuffer, 0, sizeof(char)*150);
        fgets(fbuffer, 150, fp);

        int r = sscanf(bp, "%d", &pyramid[0][i]);
        i++;
        while ((bp = strchr(bp, ' ')) != NULL) {
            r = sscanf(bp, "%d", &pyramid[0][i]); // filling the 0th row
            i++;
            bp++;
        }
        /*
        for (int j = 0; j < 21; j++) {
            printf("%d ", pyramid[0][j]);
        }
        printf("\n");
        */

        while (1) {
            bool stop = true;
            /*
            for (int j = 0; j < 22; j++) {
                printf("%8d ", pyramid[row][j]);
            }
            printf("\n");
            */

            row++;
            // there are 21 values in the 0th row, so the 1st row should have 10.
            for (int i = 1+row; i < 22; i++) {
                pyramid[row][i] = pyramid[row-1][i] - pyramid[row-1][i-1];
                if (pyramid[row][i]) stop = false;
            }
            
            if (stop) break;
        }

        //pyramid[row-1][(row-1)] = 0; // justify why we can just start at row - 1... this value is pretty obvious
        //printf("\n");
        for (int r = row-1; r >= 0; r--) {
            //printf("%d\n",r);
            pyramid[r][r] = pyramid[r][r+1] - pyramid[r+1][r+1];
            /*
            for (int j = 0; j < 22; j++) {
                printf("%8d ", pyramid[r][j]);
            }
            printf("\n");
            */
        }
        
        sum += pyramid[0][0];
    }

    fclose(fp);

    printf("final sum for part 2: %"PRId64"\n", sum);
}

int main(int argc, char **argv) {
    part1();
    part2();

    return 0;
}