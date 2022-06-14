//
//  main.c
//  c-cau
//
//  Created by Jacob An on 2022/03/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    FILE *f = fopen("input.txt", "r");
    FILE *o = fopen("output.txt", "w");

    int n = -1;
    int arr[999];
    char buffer[10000];

    int k = 0;
    while (!feof(f)) {
        fgets(buffer, 10000, f);
        
        if (n == k) break;
        if (n == -1) n = atoi(buffer);
        else {
            char *ptr = strtok(buffer, " ");
            while (ptr != NULL) {
                arr[k++] = atoi(ptr);
                ptr = strtok(NULL, " ");
            }
        }
    }
    
    int iterator = 0;
    
    while (1) {
        if (iterator % 2 == 0) {
            for (int i = 0; i < n; i++) {
                if (i == n -1) break;
                if (i % 2 == 0 && arr[i] > arr[i+1]) {
                    int temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (i == n - 1) break;
                if (i % 2 == 1 && arr[i] > arr[i+1]) {
                    int temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }
            }
        }
        iterator++;
        
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i+1]) break;
            if (i == n - 2) {
                fprintf(o, "%d", iterator);
                fclose(o);
                fclose(f);
                
                return 0;
            }
        }
    }
    
    return 0;
}
