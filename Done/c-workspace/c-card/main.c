#include <stdio.h>

typedef struct {
    char suit;
    int rank;
} CARD;

int main(int argc, const char * argv[]) {
    char line[30];
    scanf("%[^\n]s", line);
    
    CARD cards[7];
    int index = 0;

    for (int i = 0; line[i] != '\0';) {
        cards[index].suit = line[i];
        
        if (line[i+3] == ',' || (line[i+3] == '\0')) {
            cards[index].rank = line[i+2] - '0';
            i += 4;
        } else {
            cards[index].rank = line[i+3] - '0' + 10;
            i += 5;
        }
        index++;
    }

    int suits[4] = { 0 };
    int ranks[13] = { 0 };
    
    for (int i = 0; i < 7; i++) {
        switch (cards[i].suit) {
            case 's':
                suits[0]++;
                break;
            case 'd':
                suits[1]++;
                break;
            case 'h':
                suits[2]++;
                break;
            case 'c':
                suits[3]++;
                break;
        }
        ranks[cards[i].rank-1]++;
//        printf("%c %d\n", cards[i].suit, cards[i].rank);
    }
    
    int straight = 0;
    int flush = 0;
    int four_card = 0;
    int three_card = 0;
    int pair = 0;
    
    int straight_counter = 0;
    for (int i = 0; i < 13; i++) {
        if (i < 12 && ranks[i] && ranks[i+1])
            straight_counter++;
        else
            straight_counter = 0;
        
        if (ranks[i] == 2)
            pair++;
        if (ranks[i] == 3)
            three_card++;
        if (ranks[i] == 4)
            four_card++;
        if (straight_counter == 4)
            straight++;
        if (i < 4 && suits[i] == 5)
            flush++;
    }
    
    if (straight && flush)
        printf("straight flush\n");
    else if (four_card)
        printf("four of a kind\n");
    else if (three_card && pair)
        printf("full house\n");
    else if (flush)
        printf("flush\n");
    else if (straight)
        printf("straight\n");
    else if (three_card)
        printf("three of a kind");
    else if (pair > 1)
        printf("two pair\n");
    else if (pair == 1)
        printf("one pair\n");
    else
        printf("high card\n");
    
    
    return 0;
}
