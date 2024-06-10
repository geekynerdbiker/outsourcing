#ifndef JANGGI_H
#define JANGGI_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <tchar.h>

// 콘솔 관련 전역 함수
#define clrscr() system("cls")
void gotoxy(int x, int y);
void setcolor(int color, int bgcolor);
void xyprintf(int x, int y, const char* format, ...);

// 게임 국가와 게임판에서 빈 곳 정의
#define NONE    0
#define HAN     1
#define CHO     2

// 게임을 초기화하기 위한 자료
typedef struct _Location {
    int x;
    int y;
    TCHAR engname;
    TCHAR unitname[3];
    int country;
} Location;

#define CHAR_CHA    'C'
#define CHAR_SANG   'S'
#define CHAR_MA     'M'
#define CHAR_SA     's'
#define CHAR_KING   'K'
#define CHAR_PO     'P'
#define CHAR_ZOL    'Z'

// 동적할당 배열을 위한 자료 구조
typedef struct _Coord {
    int x;
    int y;
    int who;
} Coord;

class MyList {
private:
    int size;
    Coord* elements;
public:
    MyList() : size(0) { elements = NULL; }
    ~MyList() { if (elements != NULL) free(elements); }
    void add(int x, int y, int who);
    Coord* get(int i) const;
    int length() const { return size; }
};

// 유닛 관련 클래스
class Game;
class Unit {
protected:
    int country;
    BOOL alive;
    Game* pan;
    int x;
    int y;
    LPCTSTR unitname;
    BOOL AddList(int x, int y, MyList* current);
public:
    Unit() {}
    void Move(int x, int y) { this->x = x; this->y = y; }
    void setAlive(BOOL alive) { this->alive = alive; }
    virtual void MoveAvailable(MyList* current);
    int getX() const { return x; }
    int getY() const { return y; }
    int getCountry() const { return country; }
    LPCTSTR getUnitName() const { return unitname; }
};

#define THESAME this->x = x; this->y = y; this->alive = TRUE; this->country = country; this->pan = game; this->unitname = unitname;

class Movable : public Unit {
public:
    Movable() {}
    Movable(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
};

class Cha : public Unit {
public:
    Cha() {}
    Cha(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current);
};

class Sang : public Unit {
public:
    Sang() {}
    Sang(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current);
};

class Ma : public Unit {
public:
    Ma() {}
    Ma(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current);
};

class Sa : public Unit {
public:
    Sa() {}
    Sa(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current) { Unit::MoveAvailable(current); }
};

class King : public Unit {
public:
    King() {}
    King(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current) { Unit::MoveAvailable(current); }
};

class Po : public Unit {
public:
    Po() {}
    Po(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current);
};

class Zol : public Unit {
public:
    Zol() {}
    Zol(int x, int y, int country, Game* game, LPCTSTR unitname) { THESAME; }
    virtual void MoveAvailable(MyList* current);
};

// 게임 관련 자료 구조
#define ONETEAMUNITS   16
#define PANXSIZE       9
#define PANYSIZE       10

#define NODECIDED      0
#define SELECTED       1
#define MOVESUCCESS    2

#define HANWIN         1
#define CHOWIN         2
#define DRAWGAME       3

typedef struct _RollBack {
    int fromx, fromy;
    int tox, toy;
    unsigned turn;
    BOOL eat;
} RollBack;

extern Location Units[];

class Game {
private:
    Unit* pan[PANXSIZE][PANYSIZE];
    Unit* ChoDead[ONETEAMUNITS];
    Unit* HanDead[ONETEAMUNITS];
    unsigned int turn;

    BOOL jang;
    BOOL mung;
    int win;
    RollBack rb;

public:
    int curx;
    int cury;

    int status;
    int selectx;
    int selecty;

    BOOL validMove;

    Game();
    ~Game();
    int exist(int x, int y) const;
    BOOL isPo(int x, int y) const;
    int who() const {return (turn) % 2 + 1; }
    int Win() const { return win; }

    void AskStartUnits();
    void SelectUnit(BOOL enter);
    void PrintMovable(int x, int y);
    void RemoveMovable();
    BOOL MoveUnit(int fromX, int fromY, int toX, int toY);
    BOOL InJang();
    void CheckMung();
    void CheckJang();
    void NextTurn();
    void Undo();
    void CheckEndGame(); // CheckEndGame 함수 선언 추가

    BOOL IsJang() { return jang; }
    BOOL IsMung() { return mung; }
    void PrintConsole() const;
    void StatusConsole() const;
    void CursorMove(int direction);

    Unit* getUnitAt(int x, int y) const;
    void handleClick(int x, int y);
};

#endif // JANGGI_H
