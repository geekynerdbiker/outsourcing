//
//  main.c
//  untitled
//
//  Created by Jacob An on 2021/11/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE 0
#define CATEGORY 2
#define EXPENSE 4

#define SMALL_BUFFER_SIZE 20
#define LARGE_BUFFER_SIZE 100

int command = 0, count = 0;

int daily_expenses[30];

int categoric_counter[4];
int categoric_expenses[4];
char *categories[4];


void init() {
    for(int i=0; i < 4; i++)
        categories[i] = malloc(sizeof(char) * 20);
}

void record_daily_expenses() {
    int input;
    char line[LARGE_BUFFER_SIZE];
    
    printf("Record Daily Expenses\n");
    printf("================================\n");
    
    printf("Number of inputs : ");
    scanf("%d", &input);
    getchar();
    
    printf("DATE / CATEGORY / EXPENSE\n");
    
    for (int i = 0; i < input; i++){
        fgets(line, LARGE_BUFFER_SIZE, stdin);
        char *ptr = strtok(line, " ");
        
        char *date = ptr;
        ptr = strtok(NULL, " / ");
        char *category = ptr;
        ptr = strtok(NULL, " / ");
        char *expense = ptr;
        
        daily_expenses[atoi(date)] += atoi(expense);
        
        int isSaved = 0;
        for (int i = 0; i < 4; i++) {
            if(strcmp(categories[i], category) == 0) {
                categoric_counter[i]++;
                categoric_expenses[i] += atoi(expense);
                isSaved = 1;
                break;
            }
            else if (strcmp(categories[i], "") == 0){
                strcpy(categories[i], category);
                categoric_counter[i]++;
                categoric_expenses[i] += atoi(expense);
                break;
            }
        }
    }
}

void print_daily_expenses() {
    int start, end, total = 0;
    
    printf("Print Daily Expenses\n");
    printf("================================\n");
    
    printf("Start Date: ");
    scanf("%d", &start);
    printf("End Date: ");
    scanf("%d", &end);
    printf("================================\n");
    
    for (int i = start; i <= end; i++) {
        printf("21/11/%d: %d\n", i, daily_expenses[i]);
        total += daily_expenses[i];
    }
    printf("Total Expense: %d\n", total);
}

void spending_pattern_analysis() {
    int index = 0, max = 0;
    int total = 0;
    
    for (int i = 0; i < 4; i++) {
        total += categoric_expenses[i];
        if (max < categoric_expenses[i]) {
            max = categoric_expenses[i];
            index = i;
        }
    }
    
    double perc = (double)max / (double)total * 100;
    
    printf("Spending Pattern Analysis\n");
    printf("================================\n");
    
    printf("You spended the most on %s (%d won).\n", categories[index], max);
    printf("It accounts for %.2lf percent of total spending.\n", perc);
}

int get_input() {
    printf("Input: ");
    scanf("%d", &command);
    printf("================================\n");
    return command;
}

void print_menu() {
    printf("==============Menu==============\n");
    printf("1. Record Daily Expenses\n");
    printf("2. Print Daily Expenses\n");
    printf("3. Spending Pattern Analysis\n");
    printf("4. End\n");
    printf("================================\n");
}

int main(int argc, const char * argv[]) {
    init();
    
    while(command != 4) {
        print_menu();
        command = get_input();
        
        switch(command) {
            case 1:
                record_daily_expenses();
                break;
            case 2:
                print_daily_expenses();
                break;
            case 3:
                spending_pattern_analysis();
                break;
            default:
                break;
                
                
        }
    }
    
    return 0;
}
