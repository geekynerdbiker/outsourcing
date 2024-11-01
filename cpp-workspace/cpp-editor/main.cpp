#include <iostream>
#include <string>

#define MAX_STACK 100//1000000

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
string eng2kor(string s);

int main() {
    Stack l, r;
    InitStack(&l);
    InitStack(&r);
    
    int n;
    cin >> n;
    
    bool lang = false; // false = ENG / true = KOR
    
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
            string s;
            cin >> s;
            
            if (!s.compare("_")) s = " ";
            if (lang) Push(&l, eng2kor(s));
            else Push(&l, s);
        } else if (!temp.compare("language")) {
            lang = !lang;
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
    
    cout << endl;
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
        exit(1); //error)) empty stack
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
        exit(1); //error)) empty stack
    --(pstack->top);
}

string eng2kor(string s) {
    if (!s.compare("r"))
        return "ㄱ";
    
    else if (!s.compare("R")) // ㄲ
        return "ㄲ";
    
    else if (!s.compare("s")) // ㄴ
        return "ㄴ";
    
    else if (!s.compare("e")) // ㄷ
        return "ㄷ";
    
    else if (!s.compare("E")) // ㄸ
        return "ㄸ";
    
    else if (!s.compare("f")) // ㄹ
        return "ㄹ";
    
    else if (!s.compare("a")) // ㅁ
        return "ㅁ";
    
    else if (!s.compare("q")) // ㅂ
        return "ㅂ";
    
    else if (!s.compare("Q")) // ㅃ
        return "ㅃ";
    
    else if (!s.compare("t")) // ㅅ
        return "ㅆ";
    
    else if (!s.compare("T")) // ㅆ
        return "ㅆ";
    
    else if (!s.compare("d")) // ㅇ
        return "ㅇ";
    
    else if (!s.compare("w")) // ㅈ
        return "ㅈ";
    
    else if (!s.compare("W")) // ㅉ
        return "ㅉ";
    
    else if (!s.compare("c")) // ㅊ
        return "ㅊ";
    
    else if (!s.compare("z")) // ㅋ
        return "ㅋ";
    
    else if (!s.compare("x")) // ㅌ
        return "ㅌ";
    
    else if (!s.compare("v")) // ㅍ
        return "ㅍ";
    
    else if (!s.compare("g")) // ㅎ
        return "ㅎ";
    
    else if (!s.compare("k")) // ㅏ
        return "ㅏ";
    
    else if (!s.compare("o")) // ㅐ
        return "ㅐ";
    
    else if (!s.compare("i")) // ㅑ
        return "ㅑ";
    
    else if (!s.compare("O")) // ㅒ
        return "ㅒ";
    
    else if (!s.compare("j")) // ㅓ
        return "ㅓ";
    
    else if (!s.compare("p")) // ㅔ
        return "ㅔ";
    
    else if (!s.compare("u")) // ㅕ
        return "ㅕ";
    
    else if (!s.compare("P")) // ㅖ
        return "ㅖ";
    
    else if (!s.compare("h")) // ㅗ
        return "ㅗ";
    
    else if (!s.compare("y")) // ㅛ
        return "ㅛ";
    
    else if (!s.compare("n")) // ㅜ
        return "ㅜ";
    
    else if (!s.compare("b")) // ㅠ
        return "ㅠ";
    
    else if (!s.compare("m")) // ㅡ
        return "ㅡ";
    
    else if (!s.compare("l")) // ㅣ
        return "ㅣ";
    else if (!s.compare(" "))
        return " ";
    else return "";
}
