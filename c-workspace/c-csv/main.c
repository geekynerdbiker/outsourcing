//
//  main.c
//  covid
//
//  Created by Jacob An on 2021/12/08.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct {
    char country[20];
    char country_code[3];
    int totalCases;
    int totalDeaths;
    struct node* NextPtr;
} node;

int Length(node* chain)
{
    node* curr = chain;
    int len = 0;
    
    if(curr == NULL) return 0;
    while (curr) {
        len++;
        curr = curr->NextPtr;
    }

    return len;
}

void PrintALL(node* chain)
{
    node* curr = chain;

    while (pCur) {
        printf("Country: %s Country Code: %s\n", curr->country, curr->country_code);
        printf("TotalCases: %d\n", curr->totalCases);
        printf("TotalDepths: %d\n", curr->totalDeaths);
        
        curr = curr->NextPtr;
    }
}

node* FindCountryCode(node* chain, char* input)
{
    node* curr = chain;

    if(curr == NULL) return NULL;
    while (curr) {
        if (strcmp(curr->country_code, input) == 0) {
            break;
        }
        curr = curr->NextPtr;
    }

    return curr;
}

node* FindMaxCases(node* chain)
{
    int max = 0;
    node* cases = NULL;
    node* curr = chain;

    if(curr == NULL) return NULL;
    while (curr) {
        if (curr->totalCases > max) {
            max = curr->totalCases;
            cases = curr;
        }
        curr = curr->NextPtr;
    }

    return cases;
}

node* FindMaxDeaths(node * chain)
{
    int max = 0;
    node* deaths = NULL;
    node* curr = chain;

    while (curr) {
        if (curr->totalDeaths > max) {
            max = curr->totalDeaths;
            deaths = curr;
        }
        pCur = pCur->NextPtr;
    }

    return deaths;
}

int main(void)
{
    FILE* fPtr = fopen("covid-19.csv", "r");
    char currentCountry[80] = "";
    int counter = 0;
    node chain[235] = { 0 };
    node* maxTotalCases = 0;
    node* maxTotalDeaths = 0;
    node* head = &chain[0];

    if(fPtr == NULL) {
        printf("No file exist.\n");
        return 0;
    }
    /* Fill in your code here.
    Your code should:
        - Read data from the data file ("covid-19.csv").
        - Calculate the total infection cases and total death cases for each country.
        - Construct a linked list based on the calculated results.
    */

    // 1) Read data from the data file("covid-19.csv").
    int total_cases = 0;
    int total_deaths = 0;
    char country[80] = "";
    char date[80] = { 0 };
    char country_code[3] = { 0 };
    int cases = 0;
    int deaths = 0;
    int day = 0;
    int tmp = 0;

    // 1-1) find day info in first data.
    fscanf(fPtr, "%s %s %s %d %d\n", date, country_code, country, &cases, &deaths);
    day++;

    while (feof(fPtr) == 0){
        fscanf(fPtr, "%s %s %s %d %d\n", date, country_code, currentCountry, &cases, &deaths);
        if (!strcmp(currentCountry, country)) day++;
        else break;
    }

//    fseek(fPtr, 0, SEEK_SET);

    while (feof(fPtr) == 0) {
        total_cases = 0;
        total_deaths = 0;
        tmp = day;

        // 1-2) Calculate the total infection cases and total death cases for each country
        for (int k = 0; k < tmp; k++) {
            fscanf(fPtr, "%s %s %s %d %d\n", date, country_code, currentCountry, &cases, &deaths);
            total_cases += cases;
            total_deaths += deaths;
        }

    // 1-3) Construct a linked list based on the calculated results.
        strcpy(chain[counter].country, currentCountry);
        strcpy(chain[counter].country_code, country_code);
        
        chain[counter].totalCases = total_cases;
        chain[counter].totalDeaths = total_deaths;
        
        counter++;
    }

    for (int k = 1; k < counter; k++)
        chain[k - 1].NextPtr = &chain[k];

    maxTotalCases = FindMaxCases(chain);
    maxTotalDeaths = FindMaxDeaths(chain);

    printf("There are %d countries in the data.\n", Length(chain));
    printf("Max Total Cases: %s %d\n", maxTotalCases->country, maxTotalCases->totalCases);
    printf("Max Total Deaths: %s %d\n", maxTotalDeaths->country, maxTotalDeaths->totalDeaths);

    char Input[4];
    while (strcmp(Input, "q"))
    {
        printf("===============================\n");
        printf("Enter the country code to display the total number of cases and total number of death of the country.\n");
        printf("Enter \"ALL\" to display all data.\n");
        printf("Enter (q to quit): ");
        scanf("%s", Input);

        if (!strcmp(Input, "ALL"))
            PrintALL(chain);
        else if (!strcmp(Input, "q"))
            break;
        else
        {
            node * ResultPtr = FindCountryCode(chain, Input);
            if (ResultPtr == 0)
                printf("Country Code not found!\n");
            else
                printf("Country: %s; Country code: %s\nTotal Cases: %d\nTotal Deaths: %d\n", ResultPtr->country, ResultPtr->country_code, ResultPtr->totalCases, ResultPtr->totalDeaths);
        }
    }

    return 0;
}
