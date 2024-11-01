int main(void) {
    int a = 21, b = 17, c = 6;
    int result = max(a, b, c);
}

int max(int a, int b, int c) {
    if (a > b) {
        if (c > a) return c;
        else return a;
    } else {
        if (c > b) return c;
        else return b;
    }
}
