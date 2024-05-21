#include <stdio.h>
#include <string.h>

int hash(char name[5]) {
    int h = 0;
    for (int i = 0; i < strlen(name);i++)
        h += name[i] - 'a'+1;
    return h % 5;
}

int main() {
    char names[][10] = {"kim", "jeon", "shin", "baek", "lee", "koh", "park", "jeong", "yoon", "choi", "kang"};
    for (int i = 0; i < sizeof(names); i++)
        printf("%s %d\n", names[i], hash(names[i]));
}
