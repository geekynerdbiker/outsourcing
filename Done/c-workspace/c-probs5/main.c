#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N1 10
#define N11 11
#define N2 10

void printStringArray(char strArr[][N2], int size);
void getFirstChar(char str[], char strArr[][N2], int size);
void sortCharArray(char str[], int size);
void sortStringArray(char strArr[][N2], int size);
void setFirstCharUpper(char strArr[][N2], int size);
void stringArrayLen(int arr[], char strArr[][N2], int size);
int getSum(int arr[], int size);
double getAverage(int sum, int size);

int main() {
    char fruits[][N2] = {"lime", "dates", "cherry", "honeydew", "eggfruit", "banana", "fig", "apple", "grapes", "kiwi"};

    printStringArray(fruits, N1);
    sortStringArray(fruits, N1);
    setFirstCharUpper(fruits, N1);

    int fruitsLen[N1];
    stringArrayLen(fruitsLen, fruits, N1);

    for (int i = 0; i < N1; i++)
        printf("%s(%d)\n", fruits[i],fruitsLen[i]);

    int sum = getSum(fruitsLen, N1);
    printf("\nsum: %d", sum);
    printf("\naverage: %f\n", getAverage(sum, N1));
}

void printStringArray(char strArr[][N2], int size) {
    for (int i=0; i <size; i++)
        puts(strArr[i]);
}


void getFirstChar(char str[], char strArr[][N2], int size) {
    for (int i = 0; i < size; i++)
        str[i] = strArr[i][0];
}

void sortCharArray(char str[], int size) {
    int min_index=0;
    for (int i = 0; i < size; i++) {
        char minimum = 'z';
        for(int j = i; j < size; j++) {
            if (str[j] < minimum) {
                minimum = str[j];
                min_index = j;
            }
        }
        char tmp = str[min_index];
        str[min_index] = str[i];
        str[i] = tmp;
    }
}

void sortStringArray(char strArr[][N2], int size) {
    char str[N11];
    
    getFirstChar(str, strArr, size);
    sortCharArray(str, size);
    
    int min_index=0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (str[i] == strArr[j][0]) {
                if(i == j)
                    break;
                char tmp[N2];
                strcpy(tmp, strArr[j]);
                strcpy(strArr[j], strArr[i]);
                strcpy(strArr[i], tmp);
                break;
            }
        }
    }
}

void setFirstCharUpper(char strArr[][N2], int size) {
    for (int i = 0; i < size; i++) {
        strArr[i][0] = toupper(strArr[i][0]);
    }
}

void stringArrayLen(int arr[], char strArr[][N2], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = strlen(strArr[i]);
}


int getSum(int arr[], int size) {
    int sum = 0;
    
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

double getAverage(int sum, int size) {
    return (double)sum / (double) size;
}
