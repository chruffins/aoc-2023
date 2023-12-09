#include<stdio.h>
#include<memory.h>
#include<stdbool.h>
#include<stdlib.h>
#include<inttypes.h>

enum HANDTYPE {
    FIVES=6,
    FOURS=5,
    FULLHOUSE=4,
    THREE=3,
    TWOPAIR=2,
    ONEPAIR=1,
    HIGH=0,
};

struct hand_t {
    char cards[6];
    int bid;
    enum HANDTYPE _value;
} typedef hand;

void hand_calculate_value(hand *this) {
    char uniques[6];
    char appears[6];
    int num_uniques = 0;
    memset(uniques, 0, sizeof(char)*6);
    memset(appears, 0, sizeof(char)*6);

    for (int i = 0; i < 5; i++) {
        bool unique = true;
        for (int j = 0; j < num_uniques; j++) {
            if (uniques[j] == this->cards[i]) {
                unique = false;
                appears[j] += 1;
                break;
            }
        }

        if (unique) {
            uniques[num_uniques] = this->cards[i];
            appears[num_uniques] = 1;
            num_uniques++;
            //printf("added %c as unique\n", this->cards[i]);
        }
    }

    int max_appears = 0;
    int twins = 0;
    //printf("max appears: %d\n", max_appears);
    for (int i = 0; i < strlen(appears); i++) {
        //printf("appears %d: %d\n", i, appears[i]);
        max_appears = appears[i] > max_appears ? appears[i] : max_appears;
    }
    //printf("max appears: %d\n", max_appears);

    bool flag = false;

    switch (max_appears)
    {
    case 5:
        this->_value = FIVES;
        break;
    case 4:
        this->_value = FOURS;
        break;
    case 1:
        this->_value = HIGH;
        break;
    case 3:
        this->_value = THREE;
        for (int i = 0; i < strlen(appears); i++) {
            if (appears[i] == 2) {
                this->_value = FULLHOUSE;
            }
        }
        break;
    case 2:
        this->_value = ONEPAIR;
        for (int i = 0; i < strlen(appears); i++) {
            if (appears[i] == 2) {
                twins++;
            }
        }
        if (twins == 2) this->_value = TWOPAIR;
        break;
    default:
        break;
    }
}

void hand_calculate_value_with_jokers(hand *this) {
    char uniques[6];
    char appears[6];
    int num_uniques = 0;
    int jokers = 0;
    memset(uniques, 0, sizeof(char)*6);
    memset(appears, 0, sizeof(char)*6);

    for (int i = 0; i < 5; i++) {
        bool unique = true;
        if (this->cards[i] == 'J') jokers++;
        for (int j = 0; j < num_uniques; j++) {
            if (uniques[j] == this->cards[i]) {
                unique = false;
                appears[j] += 1;
                break;
            }
        }

        if (unique) {
            uniques[num_uniques] = this->cards[i];
            appears[num_uniques] = 1;
            num_uniques++;
            //printf("added %c as unique\n", this->cards[i]);
        }
    }

    int max_appears = 0;
    int max_index = 0;

    //printf("max appears: %d\n", max_appears);
    for (int i = 0; i < strlen(appears); i++) {
        //printf("appears %d: %d\n", i, appears[i]);
        if (appears[i] > max_appears) {
            max_appears = appears[i];
            max_index = i;
        }
    }
    //printf("max appears: %d\n", max_appears);

    bool flag = false;
    int twins = 0;
    this->_value = -1;
    switch (num_uniques)
    {
    case 1:
        //printf("FIVES: %s\n", this->cards);
        this->_value = FIVES;
        break;
    case 2:
        if ((max_appears == 4 && jokers == 1) || jokers == 4) {
            //printf("FIVES: %s\n", this->cards);
            this->_value = FIVES;
        } else if ((max_appears == 3 && jokers == 2 ) || (max_appears == 2 && jokers == 3)) {
            //printf("FIVES: %s\n", this->cards);
            this->_value = FIVES;
        } else if (max_appears == 4) {
            //printf("FOURS: %s\n", this->cards);
            this->_value = FOURS;
        } else if (max_appears == 3) {
            //printf("FULLHOUSE: %s\n", this->cards);
            for (int j = 0; j < strlen(appears); j++) {
                if (appears[j] == 2) this->_value = FULLHOUSE;
            }
        }
        break;
    case 3:
        if ((max_appears == 3 && jokers == 1) || (max_appears == 2 && jokers == 2)) {
            //printf("FOURS: %s\n", this->cards);
            this->_value = FOURS;
        } else if (jokers == 3) {
            //printf("FOURS: %s\n", this->cards);
            this->_value = FOURS;
        } else if (max_appears == 3 && jokers == 0) {
            //printf("THREE: %s\n", this->cards);
            this->_value = THREE;
        } else if (max_appears == 2) {
                if (jokers == 1) {
                    this->_value = FULLHOUSE;
                } else {
                    //printf("TWOP: %s\n", this->cards);
                    this->_value = TWOPAIR;
                }
        }
        break;
    case 4:
        if (jokers > 0) {
            
            this->_value = THREE;
        } else {
            printf("ONEP: %s\n", this->cards);
            this->_value = ONEPAIR;
        }
        break;
    case 5:
        if (jokers == 1) {
            this->_value = ONEPAIR;
        } else {
            this->_value = HIGH;
        }
        break;
    default:
        printf("You fucked up!! %s\n", this->cards);
        break;
    }
}

int card_to_value(char card) {
    switch (card)
    {
        //A, K, Q, J, T
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return 11;
    case 'T':
        return 10;
    default:
        return card - '0';
    }
}

int card_to_value2(char card) {
    switch (card)
    {
        //A, K, Q, J, T
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return -1;
    case 'T':
        return 10;
    default:
        return card - '0';
    }
}

int card_comparator(char c1, char c2, int (*valorizer)(char)) {
    if (c1 == c2) return 0;

    int v1 = valorizer(c1);
    int v2 = valorizer(c2);

    return v1 < v2 ? -1 : 1;    
}

int hand_comparator(const void *p1, const void *p2) {
    hand h1 = *(hand*)(p1);
    hand h2 = *(hand*)(p2);

    if (h1._value < h2._value) {
        return -1;
    } else if (h1._value > h2._value) {
        return 1;
    } else {
        // indicates their value is the same so we need to do the second comparator function
        int result;
        for (int i = 0; i < 5; i++) {
            if ((result = card_comparator(h1.cards[i], h2.cards[i], card_to_value)) != 0) {
                return result;
            }
        }
    }
}

int hand_comparator2(const void *p1, const void *p2) {
    hand h1 = *(hand*)(p1);
    hand h2 = *(hand*)(p2);

    if (h1._value < h2._value) {
        return -1;
    } else if (h1._value > h2._value) {
        return 1;
    } else {
        // indicates their value is the same so we need to do the second comparator function
        int result;
        for (int i = 0; i < 5; i++) {
            if ((result = card_comparator(h1.cards[i], h2.cards[i], card_to_value2)) != 0) {
                return result;
            }
        }
    }
}

void part1() {
    FILE *fp = fopen("day7.txt", "r");

    char cards[6];
    int result;
    int bid;
    uint64_t total_winnings = 0;

    hand hands[1000];
    int i = 0;

    while ((result = fscanf(fp, "%s %d\n", cards, &bid)) == 2) {
        memcpy(hands[i].cards, cards, 6*sizeof(char));
        hands[i].bid = bid;
        hand_calculate_value(&hands[i]);
        i++;
    }
    fclose(fp);

    qsort(hands, i, sizeof(hand), hand_comparator);
    printf("%s %d\n", hands[0].cards, hands[1].bid);

    for (int j = 0; j < i; j++) {
        total_winnings += (j+1)*hands[j].bid;
    }

    printf("total winnings for part 1: %"PRIu64"\n", total_winnings);
}

void part2() {
    FILE *fp = fopen("day7.txt", "r");

    char cards[6];
    int result;
    int bid;
    uint64_t total_winnings = 0;

    hand hands[1000];
    int i = 0;

    while ((result = fscanf(fp, "%s %d\n", cards, &bid)) == 2) {
        memcpy(hands[i].cards, cards, 6*sizeof(char));
        hands[i].bid = bid;
        hand_calculate_value_with_jokers(&hands[i]);
        i++;
    }
    fclose(fp);

    qsort(hands, i, sizeof(hand), hand_comparator2);
    printf("%s %d\n", hands[0].cards, hands[0].bid);

    for (int j = 0; j < i; j++) {
        //printf("%s %d\n", hands[j].cards, hands[j]._value);
        /*
        for (int k = 0; k < 5; k++) {
            
            if (hands[j].cards[k] == 'J') {
                printf("%s %d\n", hands[j].cards, hands[j]._value);
                break;
            }
            
        }
        */
        
        total_winnings += (j+1)*hands[j].bid;
    }

    printf("total winnings for part 2: %"PRIu64"\n", total_winnings);
}

int main(int argc, char **argv) {
    part1();
    part2();

    return 0;
}