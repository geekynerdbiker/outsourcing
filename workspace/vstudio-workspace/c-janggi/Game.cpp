#include "Game.h"
#include <windows.h>

// �ܼ� ���� �Լ� ����
void gotoxy(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcolor(int color, int bgcolor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void xyprintf(int x, int y, const char* format, ...) {
    va_list args;
    va_start(args, format);
    gotoxy(x, y);
    vprintf(format, args);
    va_end(args);
}

// �ʱ� ���� ��ġ
Location Units[] = {
    // Han units
    {0, 0, CHAR_CHA, TEXT("��"), HAN}, {1, 0, CHAR_SANG, TEXT("��"), HAN}, {2, 0, CHAR_MA, TEXT("��"), HAN}, {3, 0, CHAR_SA, TEXT("��"), HAN},
    {5, 0, CHAR_SA, TEXT("��"), HAN}, {6, 0, CHAR_MA, TEXT("��"), HAN}, {7, 0, CHAR_SANG, TEXT("��"), HAN}, {8, 0, CHAR_CHA, TEXT("��"), HAN},
    {4, 1, CHAR_KING, TEXT("��"), HAN},
    {1, 2, CHAR_PO, TEXT("��"), HAN}, {7, 2, CHAR_PO, TEXT("��"), HAN},
    {0, 3, CHAR_ZOL, TEXT("��"), HAN}, {2, 3, CHAR_ZOL, TEXT("��"), HAN}, {4, 3, CHAR_ZOL, TEXT("��"), HAN}, {6, 3, CHAR_ZOL, TEXT("��"), HAN}, {8, 3, CHAR_ZOL, TEXT("��"), HAN},
    // Cho units
    {0, 6, CHAR_ZOL, TEXT("��"), CHO}, {2, 6, CHAR_ZOL, TEXT("��"), CHO}, {4, 6, CHAR_ZOL, TEXT("��"), CHO}, {6, 6, CHAR_ZOL, TEXT("��"), CHO}, {8, 6, CHAR_ZOL, TEXT("��"), CHO},
    {1, 7, CHAR_PO, TEXT("��"), CHO}, {7, 7, CHAR_PO, TEXT("��"), CHO},
    {4, 8, CHAR_KING, TEXT("��"), CHO},
    {0, 9, CHAR_CHA, TEXT("��"), CHO}, {1, 9, CHAR_SANG, TEXT("��"), CHO}, {2, 9, CHAR_MA, TEXT("��"), CHO}, {3, 9, CHAR_SA, TEXT("��"), CHO},
    {5, 9, CHAR_SA, TEXT("��"), CHO}, {6, 9, CHAR_MA, TEXT("��"), CHO}, {7, 9, CHAR_SANG, TEXT("��"), CHO}, {8, 9, CHAR_CHA, TEXT("��"), CHO}
};

Game::Game() {
    int x, y, unit_num = 0, plus = 0;
    int i;

    status = win = NODECIDED;
    turn = 0;
    curx = 0; cury = 0;
    selectx = selecty = 0;
    jang = mung = FALSE;
    validMove = TRUE;

    int country = CHO;

    for (y = 0; y < PANYSIZE; y++)
        for (x = 0; x < PANXSIZE; x++)
            pan[x][y] = NULL;

    for (i = 0; i < ONETEAMUNITS * 2; i++) {
        if (i < ONETEAMUNITS) {
            ChoDead[i] = NULL;
            HanDead[i] = NULL;
        }
        x = Units[i].x;
        y = Units[i].y;
        if (pan[x][y] == NULL) {
            switch (Units[i].engname) {
            case CHAR_CHA:
                pan[x][y] = new Cha(x, y, Units[i].country, this, Units[i].unitname); break;
            case CHAR_SANG:
                pan[x][y] = new Sang(x, y, Units[i].country, this, Units[i].unitname); break;
            case CHAR_MA:
                pan[x][y] = new Ma(x, y, Units[i].country, this, Units[i].unitname); break;
            case CHAR_SA:
                pan[x][y] = new Sa(x, y, Units[i].country, this, Units[i].unitname); break;
            case CHAR_KING:
                pan[x][y] = new King(x, y, Units[i].country, this, Units[i].unitname); break;
            case CHAR_PO:
                pan[x][y] = new Po(x, y, Units[i].country, this, Units[i].unitname); break;
            case CHAR_ZOL:
                pan[x][y] = new Zol(x, y, Units[i].country, this, Units[i].unitname); break;
            }
        }
    }
}

Game::~Game() {
    int x, y, i;
    for (y = 0; y < PANYSIZE; y++)
        for (x = 0; x < PANXSIZE; x++)
            if (pan[x][y] != NULL)
                delete pan[x][y];
    for (i = 0; i < ONETEAMUNITS; i++) {
        if (ChoDead[i] != NULL)
            delete ChoDead[i];
        if (HanDead[i] != NULL)
            delete HanDead[i];
    }
}

Unit* Game::getUnitAt(int x, int y) const {
    if (x >= 0 && x < PANXSIZE && y >= 0 && y < PANYSIZE) {
        return pan[x][y];
    }
    return nullptr;
}

void Game::handleClick(int x, int y) {
    if (status == NODECIDED) {
        selectx = x;
        selecty = y;
        if (pan[x][y] != nullptr && pan[x][y]->getCountry() == who()) {
            status = SELECTED;
            curx = x;
            cury = y;
        }
    }
    else if (status == SELECTED) {
        if (MoveUnit(selectx, selecty, x, y)) {
            if (InJang()) {
                MoveUnit(x, y, selectx, selecty);
                status = NODECIDED;
                validMove = FALSE;
                return;
            }
            status = NODECIDED;
            NextTurn();
            curx = x;
            cury = y;
            validMove = TRUE;
        }
        else {
            validMove = FALSE;
            status = NODECIDED;
        }
    }
}

BOOL Game::MoveUnit(int fromX, int fromY, int toX, int toY) {
    Unit* unit = pan[fromX][fromY];
    if (unit != nullptr) {
        MyList cango;
        unit->MoveAvailable(&cango);
        for (int i = 0; i < cango.length(); ++i) {
            Coord* one = cango.get(i);
            if (one->x == toX && one->y == toY) {
                Unit* target = pan[toX][toY];
                if (target == nullptr || target->getCountry() != unit->getCountry()) {
                    if (target != nullptr) {
                        target->setAlive(FALSE);
                        if (target->getCountry() == HAN) {
                            for (int j = 0; j < ONETEAMUNITS; ++j) {
                                if (HanDead[j] == nullptr) {
                                    HanDead[j] = target;
                                    break;
                                }
                            }
                        }
                        else {
                            for (int j = 0; j < ONETEAMUNITS; ++j) {
                                if (ChoDead[j] == nullptr) {
                                    ChoDead[j] = target;
                                    break;
                                }
                            }
                        }
                    }
                    pan[toX][toY] = unit;
                    pan[fromX][fromY] = nullptr;
                    unit->Move(toX, toY);

                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

int Game::exist(int x, int y) const {
    int ret = NONE;
    if (pan[x][y] != NULL)
        ret = pan[x][y]->getCountry();
    return ret;
}

BOOL Game::isPo(int x, int y) const {
    BOOL ret = FALSE;
    if (pan[x][y] != NULL && lstrcmp(pan[x][y]->getUnitName(), TEXT("��")) == 0)
        ret = TRUE;
    return ret;
}

void Game::CheckEndGame() {
    if (jang && mung) {
        if (who() == HAN) {
            win = HANWIN;
        }
        else {
            win = CHOWIN;
        }
    }
    else if (turn >= 100) { // ������ 100�� �̻� ����Ǹ� ���º� ó��
        win = DRAWGAME;
    }

    if (win != NODECIDED) {
        if (win == HANWIN) {
            MessageBox(NULL, TEXT("Han Win!"), TEXT("Game Over"), MB_OK);
        }
        else if (win == CHOWIN) {
            MessageBox(NULL, TEXT("Cho Win!"), TEXT("Game Over"), MB_OK);
        }
        else if (win == DRAWGAME) {
            MessageBox(NULL, TEXT("Draw Game!"), TEXT("Game Over"), MB_OK);
        }
        exit(0); // ���� ����
    }
}

BOOL Game::InJang() {
    int myKingX, myKingY;

    // ���� ���� ��ġ�� ã��
    for (int y = 0; y < PANYSIZE; ++y) {
        for (int x = 0; x < PANXSIZE; ++x) {
            Unit* unit = pan[x][y];
            if (unit != nullptr && unit->getCountry() == who() && lstrcmp(unit->getUnitName(), TEXT("��")) == 0) {
                myKingX = x;
                myKingY = y;
                break;
            }
        }
    }


    // ���� ���� ����� ��� ������ ���� ���� ������ �� �ִ��� Ȯ��
    for (int y = 0; y < PANYSIZE; ++y) {
        for (int x = 0; x < PANXSIZE; ++x) {
            Unit* unit = pan[x][y];
            if (unit != nullptr && unit->getCountry() != who()) {
                MyList cango;
                unit->MoveAvailable(&cango);
                for (int i = 0; i < cango.length(); ++i) {
                    Coord* pos = cango.get(i);
                    if (pos->x == myKingX && pos->y == myKingY) {
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

void Game::CheckJang() {
    int enemyKingX, enemyKingY;
    BOOL jang = FALSE;
    int currentTurn = who();

    

    // ����� ���� ��ġ�� ã��
    for (int y = 0; y < PANYSIZE; ++y) {
        for (int x = 0; x < PANXSIZE; ++x) {
            Unit* unit = pan[x][y];
            if (unit != nullptr && unit->getCountry() != currentTurn && lstrcmp(unit->getUnitName(), TEXT("��")) == 0) {
                enemyKingX = x;
                enemyKingY = y;
                break;
            }
        }
    }


    // ���� ���� ���� ��� ������ ����� ���� ������ �� �ִ��� Ȯ��
    for (int y = 0; y < PANYSIZE; ++y) {
        for (int x = 0; x < PANXSIZE; ++x) {
            Unit* unit = pan[x][y];
            if (unit != nullptr && unit->getCountry() == currentTurn) {
                MyList cango;
                unit->MoveAvailable(&cango);
                for (int i = 0; i < cango.length(); ++i) {
                    Coord* pos = cango.get(i);
                    if (pos->x == enemyKingX && pos->y == enemyKingY) {
                        this->jang = TRUE;
                        return;
                    }
                }
            }
        }
    }

    this->jang = FALSE;
}

void Game::CheckMung() {
    if (this->jang == FALSE)
        return;

    BOOL mung = TRUE;
    int currentTurn = who();

    // ����� ���� ������ �� �ִ� ��ġ�� �ִ��� Ȯ��
    int enemyKingX, enemyKingY;
    for (int y = 0; y < PANYSIZE; ++y) {
        for (int x = 0; x < PANXSIZE; ++x) {
            Unit* unit = pan[x][y];
            if (unit != nullptr && unit->getCountry() != currentTurn && lstrcmp(unit->getUnitName(), TEXT("��")) == 0) {
                enemyKingX = x;
                enemyKingY = y;
                break;
            }
        }
    }

    MyList cango;
    Unit* enemyKing = pan[enemyKingX][enemyKingY];
    enemyKing->MoveAvailable(&cango);
    for (int i = 0; i < cango.length(); ++i) {
        Coord* pos = cango.get(i);
        if (pan[pos->x][pos->y] == nullptr || pan[pos->x][pos->y]->getCountry() != currentTurn) {
            mung = FALSE;
            break;
        }
    }

    this->mung = mung;
}

void Game::NextTurn() {
    CheckJang();
    CheckMung();

    // ���� ���� ������ Ȯ���ϴ� �Լ� ȣ��
    CheckEndGame();
    turn++;
}
