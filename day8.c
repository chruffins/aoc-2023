#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<inttypes.h>

struct directions_t {
    char name[4];
    char left[4];
    char right[4];
} typedef dirs;

int dircomparator(const void *p1, const void *p2) {
    dirs *d1 = (dirs*)p1;
    dirs *d2 = (dirs*)p2;

    return strcmp(d1->name, d2->name);
}

int nameequalsdir(const void *p1, const void *p2) {
    return strcmp((char*)p1, ((dirs*)p2)->name);
}

void part1() {
    FILE *fp = fopen("day8.txt", "r");

    dirs *nodes = malloc(sizeof(dirs)*732);
    memset(nodes, 0, sizeof(dirs)*732);
    int sresult;
    int num_nodes = 0;
    uint64_t final_steps = 0;

    char *lrstr = malloc(sizeof(char)*275);
    int dindex = 0;
    
    fscanf(fp, "%s\n", lrstr);
    int ltrstrlen = strlen(lrstr);
    printf("%d\n", ltrstrlen);

    while ((sresult = fscanf(fp, "%3[^ ] = (%3[^,], %3[^)])\n", nodes[num_nodes].name, nodes[num_nodes].left, nodes[num_nodes].right)) == 3) {
        num_nodes++;
    }

    //printf("%d\n%d\n", sresult, num_nodes);
    //printf("%s %s %s\n", current_node.name, current_node.left, current_node.right);
    //printf("%s %s %s\n", last_node.name, last_node.left, last_node.right);
    dirs *node_ptr;
    dirs *final_node_ptr;

    char firstsearch[4] = "AAA";
    char lastsearch[4] = "ZZZ";

    qsort(nodes, num_nodes, sizeof(dirs), dircomparator);
    node_ptr = (dirs*)(bsearch(firstsearch, nodes, num_nodes, sizeof(dirs), nameequalsdir));
    final_node_ptr = (dirs*)(bsearch(lastsearch, nodes, num_nodes, sizeof(dirs), nameequalsdir));
    printf("%s %s %s %c\n", node_ptr->name, node_ptr->left, node_ptr->right, lrstr[dindex]);
    printf("%s %s %s %c\n", final_node_ptr->name, final_node_ptr->left, final_node_ptr->right, lrstr[dindex]);
    
    while (node_ptr != final_node_ptr) {
        //printf("%s %s %s %c\n", node_ptr->name, node_ptr->left, node_ptr->right, lrstr[dindex]);

        switch (lrstr[dindex])
        {
        case 'L':
            //printf("L %s\n", node_ptr->left);
            node_ptr = (dirs*)(bsearch(node_ptr->left, nodes, num_nodes, sizeof(dirs), nameequalsdir));
            break;
        case 'R':
            //printf("R %s\n", node_ptr->right);
            node_ptr = (dirs*)(bsearch(node_ptr->right, nodes, num_nodes, sizeof(dirs), nameequalsdir));
            break;
        default:
            printf("what %c %d\n", lrstr[dindex], dindex);
            break;
        }
        //printf("%c", lrstr[dindex]);
        dindex = (dindex + 1) % ltrstrlen;
        final_steps++;
    }
    printf("final steps: %d\n", final_steps);
    //printf("%s %s %s\n", current_node.name, current_node.left, current_node.right);

    free(nodes);
    free(lrstr);
}

void part2() {
    FILE *fp = fopen("day8.txt", "r");

    dirs *nodes = malloc(sizeof(dirs)*732);
    memset(nodes, 0, sizeof(dirs)*732);
    int sresult;
    int num_nodes = 0;
    uint64_t final_steps = 0;

    char *lrstr = malloc(sizeof(char)*275);
    int dindex = 0;
    
    fscanf(fp, "%s\n", lrstr);
    int ltrstrlen = strlen(lrstr);
    printf("%d\n", ltrstrlen);

    while ((sresult = fscanf(fp, "%3[^ ] = (%3[^,], %3[^)])\n", nodes[num_nodes].name, nodes[num_nodes].left, nodes[num_nodes].right)) == 3) {
        num_nodes++;
    }

    //printf("%d\n%d\n", sresult, num_nodes);
    //printf("%s %s %s\n", current_node.name, current_node.left, current_node.right);
    //printf("%s %s %s\n", last_node.name, last_node.left, last_node.right);
    dirs *node_ptr;
    dirs *final_node_ptr;

    char firstsearch[4] = "AAA";
    char lastsearch[4] = "ZZZ";

    qsort(nodes, num_nodes, sizeof(dirs), dircomparator);
    node_ptr = (dirs*)(bsearch(firstsearch, nodes, num_nodes, sizeof(dirs), nameequalsdir));
    final_node_ptr = (dirs*)(bsearch(lastsearch, nodes, num_nodes, sizeof(dirs), nameequalsdir));
    printf("%s %s %s %c\n", node_ptr->name, node_ptr->left, node_ptr->right, lrstr[dindex]);
    printf("%s %s %s %c\n", final_node_ptr->name, final_node_ptr->left, final_node_ptr->right, lrstr[dindex]);
    
    while (node_ptr != final_node_ptr) {
        //printf("%s %s %s %c\n", node_ptr->name, node_ptr->left, node_ptr->right, lrstr[dindex]);

        switch (lrstr[dindex])
        {
        case 'L':
            //printf("L %s\n", node_ptr->left);
            node_ptr = (dirs*)(bsearch(node_ptr->left, nodes, num_nodes, sizeof(dirs), nameequalsdir));
            break;
        case 'R':
            //printf("R %s\n", node_ptr->right);
            node_ptr = (dirs*)(bsearch(node_ptr->right, nodes, num_nodes, sizeof(dirs), nameequalsdir));
            break;
        default:
            printf("what %c %d\n", lrstr[dindex], dindex);
            break;
        }
        //printf("%c", lrstr[dindex]);
        dindex = (dindex + 1) % ltrstrlen;
        final_steps++;
    }
    printf("final steps: %d\n", final_steps);
    //printf("%s %s %s\n", current_node.name, current_node.left, current_node.right);

    free(nodes);
    free(lrstr);
}

int main(int argc, char **argv) {
    part1();
    part2();

    return 0;
}