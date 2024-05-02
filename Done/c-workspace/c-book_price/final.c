#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define LENGTH_OF_FILE_NAME 32
#define MAX_NUM_OF_BOOKS 20
#define	LENGTH_OF_BOOK 20
#define MAX_BUFFER_SIZE 30

typedef struct book {
    char name[LENGTH_OF_BOOK];
    int price;
    struct book *next;
} BOOK;

int CountNumberOfBook(char *filename) {
    FILE *fp = fopen(filename, "r");
    int count = 0;
    
    char buffer[MAX_BUFFER_SIZE];
    while(!feof(fp)) {
        fgets(buffer, sizeof(buffer), fp);
        count++;
    }
    fclose(fp);
    return count;
}

int ReadPriceTable(char *filename, BOOK books[MAX_NUM_OF_BOOKS]) {
    FILE *fp = fopen(filename, "r");
    int index = 0;
    
    char buffer[MAX_BUFFER_SIZE];
    while(!feof(fp)) {
        BOOK *book = (BOOK *)malloc(sizeof(BOOK));
        fgets(buffer, sizeof(buffer), fp);
        char *token = strtok(buffer, " ");
        strcpy(book->name, token);
        token = strtok(NULL, "\n");
        book->price = atoi(token);
        book->next = NULL;
        books[index++] = *book;
    }
    fclose(fp);
    return index;
}

void PrintPriceTable(BOOK books[MAX_NUM_OF_BOOKS], int numOfBooks) {
    printf("Inserted Book Name and Price.\n");
    for (int i = 0; i < numOfBooks; i++)
        printf("Name:%s, Price: %d\n", books[i].name, books[i].price);
}


void ReadBookList(char *filename, char BookList[MAX_NUM_OF_BOOKS][LENGTH_OF_BOOK]) {
    FILE *fp = fopen(filename, "r");
    int index = 0;
    
    char buffer[MAX_BUFFER_SIZE];
    while(!feof(fp)) {
        fgets(buffer, sizeof(buffer), fp);
        char *token = strtok(buffer, ",");
        while (token) {
            strcpy(BookList[index++], token);
            token = strtok(NULL, ",");
        }
    }
    fclose(fp);
}

void PrintBookList(char BookList[MAX_NUM_OF_BOOKS][LENGTH_OF_BOOK]) {
    int index = 0;
    while (strcmp(BookList[index], ""))
        printf("No.%d %s\n", index+1,BookList[index++]);
    
}

int ComputePrice(BOOK books[MAX_NUM_OF_BOOKS], int numOfBooks, char BookList[MAX_NUM_OF_BOOKS][LENGTH_OF_BOOK]) {
    int total = 0;
    for (int i = 0; i < numOfBooks; i++) {
        for (int j = 0; j < numOfBooks; j++) {
            if (!strcmp(BookList[i], books[j].name)) {
                total += books[j].price;
                break;
            }
        }
    }
    return total;
}

int SearchPrice(BOOK books[MAX_NUM_OF_BOOKS], int numOfBooks, char *nameOfBook) {
    int price = 0;
    for (int i = 0; i < numOfBooks; i++) {
        if (!strcmp(books[i].name, nameOfBook)) {
            return books[i].price;
        }
    }
    return -1;
}

bool InsertBookList(char BookList[MAX_NUM_OF_BOOKS][LENGTH_OF_BOOK], char *nameOfBook, BOOK books[MAX_NUM_OF_BOOKS], int numOfBooks) {
    
    bool result = false;
    for (int i = 0; i < numOfBooks; i++) {
        if (!strcmp(books[i].name, nameOfBook)) {
            result = true;
            break;
        }
    }
    
    if (!result) {
        printf("The book does not exist.\n");
        return false;
    } else {
        int index = 0;
        while (strcmp(BookList[index], ""))
            index++;
        strcpy(BookList[index], nameOfBook);
    }
    return true;
}

bool DeleteBookList(char BookList[MAX_NUM_OF_BOOKS][LENGTH_OF_BOOK], char *nameOfBook) {
    int index = 0;
    bool result = true;
    
    while (true) {
        if (!strcmp(BookList[index], "")) {
            result = false;
            break;
        } if (!strcmp(BookList[index], nameOfBook))
            break;
        index++;
    }
    
    if (!result) {
        printf("The book to remove does not exist.\n");
        return false;
    } else {
        while (true) {
            strcpy(BookList[index], BookList[index+1]);
            index++;
            if (!strcmp(BookList[index], ""))
                break;
        }
    }
    return true;
}

int main(void)
{
    char bookPriceFileName[LENGTH_OF_FILE_NAME] = {0,};
    char ListFileName[LENGTH_OF_FILE_NAME] = {0,};
    char BookList[MAX_NUM_OF_BOOKS][LENGTH_OF_BOOK] = {0,};
    int totalPrice = 0;
    int numOfBooks = 0;
    // Implement Main Program
    char buffer[MAX_BUFFER_SIZE];
    int command;
    
    BOOK books[MAX_NUM_OF_BOOKS];
    printf("Insert File name including book name and price.(*.dat)format:");
    scanf("%s", buffer);
    
    numOfBooks = CountNumberOfBook(buffer);
    numOfBooks = ReadPriceTable(buffer, books);
    PrintPriceTable(books, numOfBooks);
    
    printf("\nInsert File name including the list of books to read.:(*.dat)format:");
    scanf("%s", buffer);
    
    ReadBookList(buffer, BookList);
    PrintBookList(BookList);
    
    totalPrice = ComputePrice(books, numOfBooks, BookList);
    printf("\n1Total Price is %d won.\n\n", totalPrice);
    
    
    while (true) {
        printf("Is there any book you want to insert or delete? 1.Insert, 2.Delete, 3.None:");
        scanf("%d", &command);
        
        if (command == 1) {
            printf("Enter the name of the book you want to insert:");
            scanf("%s", buffer);
            
            InsertBookList(BookList, buffer, books, numOfBooks);
            PrintBookList(BookList);
            totalPrice = ComputePrice(books, numOfBooks, BookList);
            printf("\nUpdated Total Price is %d won.\n", totalPrice);
        } else if (command == 2) {
            printf("Enter the name of the book you want to delete:");
            scanf("%s", buffer);
            
            DeleteBookList(BookList, buffer);
            PrintBookList(BookList);
            totalPrice = ComputePrice(books, numOfBooks, BookList);
            printf("\nUpdated Total Price is %d won.\n", totalPrice);
        } else if (command == 3) {
            printf("\nCalculate the price without inserting or deleting.\n");
            totalPrice = ComputePrice(books, numOfBooks, BookList);
            
            printf("Final Total Price is %d won.\n", totalPrice);
            return 0;
        } else {
            printf("Invalid Input, Re-enter the option.\n");
        }
    }
    return 0;
}
