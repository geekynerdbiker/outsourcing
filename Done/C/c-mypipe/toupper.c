//
//  toupper.c
//  c-workspace
//
//  Created by Jacob An on 2023/04/13.
//

char toupper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}
