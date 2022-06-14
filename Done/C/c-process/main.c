//
//  main.c
//  crebugs
//
//  Created by Jacob An on 2022/03/03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t getpid(void);

#define TEAM 0
#define LEAGUE 1

/* prototypes */
void debugMode(char *[]);
void estimationMode(int, int, char *[]);


/* Terminal input should be:
 Debmode: ./a.out XX XX XX XX XX
 Simmode ./a.out <child no.> [<no. of sim> <seed> <Pattern>] ... */
int main(int argc, char *argv[]) {
    int myid = getpid();
    
    if(strcmp(argv[2], "D") == 0) {
        printf("Parent, pid %d: ", myid);
        printf("debug mode\n");
        debugMode(argv+3);
    } else if(strcmp(argv[2], "E") == 0) {
        int numChild = atoi(argv[3]);
        int tasks = 0;
        
        int i = 3;
        while(i++) {
            if(argv[i][0] >= 48 && argv[i][0] <= 57)
                tasks++;
            else break;
        }
        printf("Parent, pid %d: %d children, ", myid, numChild);
        printf("%d tasks, estimation mode\n", tasks/2);
        estimationMode(numChild, tasks/2, argv+3);
    }
    return 0;
}

/* Debug mode */
void debugMode(char *argv[]) {
    int pid;
    int i, j = 0, k = 0;
    char group = 'A';
    
    char teams[16][2][20];
    char groups[8][2][20];
    
    for (int i = 0; i < 16; i++) {
        strcpy(teams[i][TEAM], argv[k]);
        if(i % 2 == 0) strcpy(groups[j][0], argv[k++]);
        else {
            strcpy(groups[j][1], argv[k++]);
            j++;
        }
        strcpy(teams[i][LEAGUE], argv[k++]);
        
    }
    
    
    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    }
    
    else{
        bool isLegal = true;
        for(int i=0; i < 16; i+=2)
            printf("Child %d, pid %d: Group %c: %s(%s) and %s(%s)\n", 1,getpid(), group++ ,teams[i][0], teams[i][1], teams[i+1][0], teams[i+1][1]);
        
        for(int i=0; i < 16; i+=2) {
            char league1[20], league2[20];
            char team1[20], team2[20];
            
            if(argv[k] != NULL) {
                strcpy(team1, argv[k]);
                strcpy(team2, argv[k+1]);
                
                
                for (int j=0;j<16;j++) {
                    if (strcmp(argv[k], teams[j][TEAM]) == 0)
                        strcpy(league1, teams[j][LEAGUE]);
                }
                for (int j=0;j<16;j++) {
                    if (strcmp(argv[k+1], teams[j][TEAM]) == 0)
                        strcpy(league2, teams[j][LEAGUE]);
                }
                
                for(int j=0; j <8; j++) {
                    if(strcmp(groups[j][0], argv[k]) == 0){
                        if (strcmp(groups[j][1], argv[k+1]) == 0){
                            isLegal = false;
                            break;
                        }
                    }
                    else if(strcmp(groups[j][1], argv[k]) == 0){
                        if (strcmp(groups[j][0], argv[k+1]) == 0){
                            isLegal = false;
                            break;
                        }
                    }
                }
                k+=2;
                printf("Child %d, pid %d: %s(%s) vs %s(%s)\n", 1, getpid(),team1, league1, team2, league2);
            }
        }
        
        if(!isLegal) printf("Child %d, pid %d: Illegal Fixture\n", 1,getpid());
        else printf("Child %d, pid %d: Legal Fixture\n", 1,getpid());
        exit(0);
    }
}


/* Estimation mode */
void estimationMode(int children, int task, char *argv[]) {
    int pid;
    int i, j = 0, k = 1;
    
    int tasks[20][2];
    char teams[16][2][20];
    char groups[8][2][20];
    
    for(int i=0; i<task; i++) {
        tasks[i][0] = atoi(argv[k]);
        k++;
        tasks[i][1] = atoi(argv[k]);
        k++;
    }
    
    for (int i = 0; i < 16; i++) {
        strcpy(teams[i][TEAM], argv[k]);
        if(i % 2 == 0) strcpy(groups[j][0], argv[k++]);
        else {
            strcpy(groups[j][1], argv[k++]);
            j++;
        }
        strcpy(teams[i][LEAGUE], argv[k++]);
        
    }
    
    
    for(int c=0; c< children; c++) {
        pid = fork();
        if(pid < 0) {
            printf("Error");
            exit(1);
        }
        
        else{
            bool isLegal = true;
            
            char group = 'A';
            for(int i=0; i < 16; i+=2)
                printf("Child %d, pid %d: Group %c: %s(%s) and %s(%s)\n", c+1, getpid(), group++ ,teams[i][0], teams[i][1], teams[i+1][0], teams[i+1][1]);
        }
        
        for(int i=0;i<task;i++) {
            int fixture = tasks[i][0];
            int seed = tasks[i][1];
            
            srand(seed);
            
            int success = 0;
            for(int i=0; i < fixture; i++) {
                int r = rand() % 100 + 1;
                if (r <= 12) success++;
            }
            printf("Child %d, pid %d: Seed %d with %d legal fixture out of %d (%.3f)\n", c+1, getpid(), seed, success, fixture, (double)fixture / (double)success);
        }
    }
    printf("Parent, pid %d: %d children completed execution\n", getpid(), children);
    exit(0);
}
