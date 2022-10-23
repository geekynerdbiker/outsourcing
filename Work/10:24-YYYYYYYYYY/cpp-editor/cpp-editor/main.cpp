#include <iostream>
#include <string>

#define MAX_STACK 1000000

using namespace std;

typedef struct {
    string items[MAX_STACK];
    int top;
} Stack;

// Make stack empty.
void InitStack(Stack *pstack);
// Check whether stack is full.
bool IsFull(Stack *pstack);
// check whether stack is empty.
bool IsEmpty(Stack *pstack);
// Read the item at the top.
string Peek(Stack *pstack);
// Insert an item at the top.
void Push(Stack *pstack, string item);
// Remove the item at the top.
void Pop(Stack *pstack);

int main() {
    Stack l, r;
    InitStack(&l);
    InitStack(&r);
    
    int n;
    cin >> n;
    
    while (n--) {
        string temp;
        cin >> temp;
        
        if (!temp.compare("move")) {
            char dir;
            cin >> dir;
            
            if (dir == 'l') {
                if (!IsEmpty(&l)) {
                    Push(&r, Peek(&l));
                    Pop(&l);
                }
            } else if (dir == 'r') {
                if (!IsEmpty(&r)) {
                    Push(&l, Peek(&r));
                    Pop(&r);
                }
            }
        } else if (!temp.compare("add")) {
            string c;
            cin >> c;
            
            if (c.compare("_"))
                c = " ";
            Push(&l, c);
        } else if (!temp.compare("language")) {
            
        } else if (!temp.compare("erase")) {
            if (!IsEmpty(&l)) Pop(&l);
        }
    }
    
    while (!IsEmpty(&l)) {
        Push(&r, Peek(&l));
        Pop(&l);
    }
    
    while (!IsEmpty(&r)) {
        cout << Peek(&r);
        Pop(&r);
    }
    
    return 0;
}

// Make stack empty.
void InitStack(Stack *pstack)
{
    pstack->top = -1;
}

// Check whether stack is full.
bool IsFull(Stack *pstack)
{
    return pstack->top == MAX_STACK - 1;
}

// check whether stack is empty
bool IsEmpty(Stack *pstack)
{
    return pstack->top == -1;
}

// Read the item at the top.
string Peek(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1); //error: empty stack
    return pstack->items[pstack->top];
}


void Push(Stack *pstack, string item) {
    if (IsEmpty(pstack))
        pstack->top = 0;
    else pstack->top++;
    pstack->items[pstack->top] = item;
}

// Remove the item at the top.
void Pop(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1); //error: empty stack
    --(pstack->top);
}

string eng2kor(char c) {
    switch (c) {
        case 'r': // ㄱ
            return "ㄱ";
            break;
        case 'R': // ㄲ
            return "ㄲ";
            break;
        case 's': // ㄴ
            return "ㄴ";
            break;
        case 'e': // ㄷ
            return "ㄷ";
            break;
        case 'E': // ㄸ
            return "ㄸ";
            break;
        case 'f': // ㄹ
            return "ㄹ";
            break;
        case 'a': // ㅁ
            return "ㅁ";
            break;
        case 'q': // ㅂ
            return "ㅂ";
            break;
        case 'Q': // ㅃ
            return "ㅃ";
            break;
        case 't': // ㅅ
            return "ㅆ";
            break;
        case 'T': // ㅆ
            return "ㅆ";
            break;
        case 'd': // ㅇ
            return "ㅇ";
            break;
        case 'w': // ㅈ
            return "ㅈ";
            break;
        case 'W': // ㅉ
            return "ㅉ";
            break;
        case 'c': // ㅊ
            return "ㅊ";
            break;
        case 'z': // ㅋ
            return "ㅋ";
            break;
        case 'x': // ㅌ
            return "ㅌ";
            break;
        case 'v': // ㅍ
            return "ㅍ";
            break;
        case 'g': // ㅎ
            return "ㅎ";
            break;
        case 'k': // ㅏ
            return "ㅏ";
            break;
        case 'o': // ㅐ
            return "ㅐ";
            break;
        case 'i': // ㅑ
            return "ㅑ";
            break;
        case 'O': // ㅒ
            return "ㅒ";
            break;
        case 'j': // ㅓ
            return "ㅓ";
            break;
        case 'p': // ㅔ
            return "ㅔ";
            break;
        case 'u': // ㅕ
            return "ㅕ";
            break;
        case 'P': // ㅖ
            return "ㅖ";
            break;
        case 'h': // ㅗ
            return "ㅗ";
            break;
        case 'y': // ㅛ
            return "ㅛ";
            break;
        case 'n': // ㅜ
            return "ㅜ";
            break;
        case 'b': // ㅠ
            return "ㅠ";
            break;
        case 'm': // ㅡ
            return "ㅡ";
            break;
        case 'l': // ㅣ
            return "ㅣ";
            break;
    }
    return "";
}
