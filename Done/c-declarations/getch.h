#ifndef getch_h
#define getch_h

#define BUFSIZE 100


char buf[BUFSIZE];

int bufp = 0;

//int getch(void) {
//    return ((bufp > 0) ? buf[--bufp] : getchar());
//}
//
//void UNGETCH(int c) {
//    if(bufp    >= BUFSIZE) printf("UNGETCH: too many character\n");
//    else buf[bufp++] = c;
//}

#endif /* Header_h */
