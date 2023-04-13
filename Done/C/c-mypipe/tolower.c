//
//  tolower.c
//  c-workspace
//
//  Created by Jacob An on 2023/04/13.
//

char tolower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}
