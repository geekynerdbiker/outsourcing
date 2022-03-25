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

    int n = 0;
    char arr[10000][10];
    char buffer[10];

    int i = 0;
    while (!feof(f)) {
        fgets(buffer, 10, f);
        
        if (n == 0) n = atoi(buffer);
        else strcpy(arr[i++], buffer);
    }
    
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = 0; arr[i][k] != '\n'; k++) {
                if (arr[i][k] != arr[j][k]) break;
                if (arr[i][k+1] == '\n') {
                    fprintf(o, "0");
                    return 0;
                }
            }
            
    fprintf(o, "1");
    fclose(o);
    fclose(f);
    
    return 0;
}
