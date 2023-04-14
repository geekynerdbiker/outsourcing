//
//  toupper.c
//  c-workspace
//
//  Created by Jacob An on 2023/04/13.
//

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        char c;
        
        while ((c = getchar()) != EOF )
            printf("%c", toupper(c));

        return 0;
    } else if (argc == 3) {
        printf("%c", toupper(argv[2][0]));
        return toupper(argv[2][0]);
    }
    
}
