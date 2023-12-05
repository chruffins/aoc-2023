#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdint.h>
#include<stdbool.h>

int part1() {
    char *grid = malloc(140*140*sizeof(char));
    memset(grid, 0, 140*140*sizeof(char));
    int sum = 0;
    char buffer[141];

    FILE *fp = fopen("day3.txt", "r");
    int line = 0;
    printf("opened file\n");
    while (line < 140) {
        fgets(buffer, 141, fp);
        memcpy(grid+(line*140), buffer, 140*sizeof(char));
        fgets(buffer, 141, fp);
        line++;
    }
    fclose(fp);

    int value = 0;
    for (int i = 0; i < 140*140; i++) {
        if (grid[i] == '\n') printf("newline detected at %d\n", i);
        if (!isdigit(grid[i])) continue;
        int valid_part = 0;
        value = grid[i] - '0';

        // left checks
        if (i % 140 != 0) {
            if (i - 141 > 0) valid_part += grid[i-141] != '.';
            valid_part += grid[i-1] != '.';
            if (i + 139 < 140*140) valid_part += grid[i+139] != '.';
            //if (i / 140 < 1) printf("%c\n", grid[i+139]);
        }
        //if (i / 140 < 1) printf("after left checks on %c (%d): %d\n", grid[i], i, valid_part);

        // top bottom checks
        if (i - 140 > 0) valid_part += grid[i-140] != '.';
        if (i + 140 < 140*140) valid_part += grid[i+140] != '.';

        //if (i / 140 < 1) printf("after topbottom checks on %c: %d\n", grid[i], valid_part);
        // right check
        if (i % 140 != 139) {
            if (!isdigit(grid[i+1])) {
                valid_part += grid[i+1] != '.';
                if (i - 139 > 0) valid_part += grid[i-139] != '.';
                if (i + 141 < 140*140) valid_part += grid[i+141] != '.';
            } else {
                while (isdigit(grid[i+1]) && ((i+1) % 140) != 0) {
                    i++;

                    value *= 10;
                    value += grid[i] - '0';
                    if (i - 140 > 0) valid_part |= grid[i-140] != '.';
                    if (i + 140 < 140*140) valid_part |= grid[i+140] != '.';
                    //if (i / 140 < 1) printf("after topbottom checks on %c: %d\n", grid[i], valid_part);
                }
                if (i % 140 != 139) {
                    valid_part |= grid[i+1] != '.';
                    if (i - 139 > 0) valid_part |= grid[i-139] != '.';
                    if (i + 141 < 140*140) valid_part |= grid[i+141] != '.';
                }
            }
            
        }
        //if (i / 140 < 1) printf("after right checks on %c: %d\n", grid[i], valid_part);

        if (valid_part) {
            //printf("adding %d on line %d\n", value, i / 140);
            sum += value;
        } else {
            //printf("not adding %d on line %d\n", value, i / 140);
        }
    }
    /*
    for (int i = 0; i < 140; i++) {
        printf("%d ", grid[i]);
    }
    printf("\n");
    */

    free(grid);

    return sum;
}

struct engine_object {
    int value;
    int row;
    int start; // inclusive
    int end; // also inclusive
} typedef engine_obj;

int part2() {
    FILE *fp = fopen("day3.txt", "r");
    printf("opened file\n");
    int line = 0;
    int current_pos = 0;
    int object_counter = 0;
    int current_number = 0;
    int gear_ratio = 0;
    
    bool is_number = false;

    engine_obj *objects = malloc(140*50*sizeof(engine_obj));
    memset(objects, 0, 140*50*sizeof(engine_obj));
    char temp;

    printf("starting loop\n");
    while (!feof(fp)) {
        temp = (char)fgetc(fp);

        // this logic is the same no matter what
        if (temp == '\n') {
            if (is_number) {
                objects[object_counter].end = current_pos;
                object_counter++;
            }
            current_pos = 0;
            line++;
            is_number = false;
            continue;
        }

        if (!is_number) {
            switch (temp)
            {
            case '*':
                objects[object_counter] = (engine_obj){ -1, line, current_pos, current_pos };
                object_counter++;
                break;
            case '.':
                break;
            default:
                if (isdigit(temp)) {
                    objects[object_counter] = (engine_obj){ temp - '0', line, current_pos, current_pos };
                    is_number = true;
                }
                break;
            }
        } else {
            // last character was a number
            if (isdigit(temp)) {
                objects[object_counter].value = (objects[object_counter].value * 10) + (temp - '0');
                objects[object_counter].end = current_pos;
            } else if (temp == '*') {
                object_counter++;
                objects[object_counter] = (engine_obj){ -1, line, current_pos, current_pos };
                object_counter++;
                is_number = false;
            } else {
                object_counter++;
                is_number = false;
            }
        }

        current_pos += 1;
    }
    fclose(fp);
    printf("finished loop\n");
    
    int i = 0;
    printf("object 0: %d\n", objects[0].value);
    while (objects[i].value != 0) {
        //printf("object: %d\n", i);
        if (objects[i].value == -1) {
            printf("object %d: %d %d\n", i, objects[i].row, objects[i].start);
            int j = i - 1;
            int num_adjacents = 0;
            int adjacents[3] = { 0, 0, 0 };
            while (j > 0 && objects[j].row > objects[i].row - 2) {
                if (objects[j].value == -1) {
                    j--;
                    continue;
                }
                if (objects[j].row == objects[i].row) {
                    if (objects[j].end + 1 == objects[i].start) {
                        adjacents[num_adjacents] = objects[j].value;
                        num_adjacents += 1;
                    }
                } else {
                    if (objects[j].start - 1 == objects[i].start || objects[j].end + 1 == objects[i].start || (objects[j].start <= objects[i].start && objects[j].end >= objects[i].start)) {
                        adjacents[num_adjacents] = objects[j].value;
                        num_adjacents += 1;
                    }
                }
                j--;
            }
            //printf("finished backwards loop\n");
            if (num_adjacents == 3) continue;
            //printf("starting forwards loop\n");
            j = i + 1;
            while (objects[j].row < objects[i].row + 2) {
                //printf("%d ", j);
                if (objects[j].value == -1) {
                    j++;
                    continue;
                }
                if (objects[j].row == objects[i].row) {
                    if (objects[j].start - 1 == objects[i].start) {
                        adjacents[num_adjacents] = objects[j].value;
                        num_adjacents += 1;
                    }
                } else {
                    if (objects[j].start - 1 == objects[i].start || objects[j].end + 1 == objects[i].start || (objects[j].start <= objects[i].start && objects[j].end >= objects[i].start)) {
                        adjacents[num_adjacents] = objects[j].value;
                        num_adjacents += 1;
                    }
                }
                j++;
                if (num_adjacents == 3) break;
            }
            if (num_adjacents == 2) {
                printf("%d %d\n", adjacents[0], adjacents[1]);
                gear_ratio += adjacents[0] * adjacents[1];
            }
        }

        i++;
    }
    /*
    for (int i = 0; i < 10; i++) {
        printf("object %d: %d %d %d %d\n", i, objects[i].value, objects[i].row, objects[i].start, objects[i].end);
    }
    */

    free(objects);

    return gear_ratio;
}

int main(int argc, char **argv) {
    printf("parts sum: %d\n", part1());
    printf("gear ratio sum: %d\n", part2());

    return 0;
}