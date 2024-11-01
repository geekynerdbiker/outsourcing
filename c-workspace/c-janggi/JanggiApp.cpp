#include "pclaf.h"
#include "Game.h"

class JanggiApp : public Application {
private:
    Game* game;
    int cellSize;
    int offsetX;
    int offsetY;
public:
    JanggiApp(const TCHAR* apName, int width, int height, int x, int y)
        : Application(apName, width, height, x, y) {
        game = new Game();
        cellSize = 60;
        offsetX = 30;
        offsetY = 30;
    }

    ~JanggiApp() {
        delete game;
    }

    void paint() {
        drawBoard();
        drawUnits();
        if (game->status == SELECTED) {
            MyList cango;
            Unit* selectedUnit = game->getUnitAt(game->selectx, game->selecty);
            if (selectedUnit != nullptr) {
                selectedUnit->MoveAvailable(&cango);
                for (int i = 0; i < cango.length(); ++i) {
                    Coord* pos = cango.get(i);
                    drawHighlight(pos->x, pos->y);
                }
            }
        }
        drawStatus();
    }

    void drawHighlight(int x, int y) {
        setPen(green, solidLine, 2);
        rectangle(offsetX + x * cellSize, offsetY + y * cellSize, offsetX + (x + 1) * cellSize, offsetY + (y + 1) * cellSize);
    }
    void drawBoard() {
        setPen(black, solidLine, 1);
        for (int i = 0; i <= PANXSIZE; ++i) {
            line(offsetX + i * cellSize, offsetY, offsetX + i * cellSize, offsetY + PANYSIZE * cellSize);
        }
        for (int j = 0; j <= PANYSIZE; ++j) {
            line(offsetX, offsetY + j * cellSize, offsetX + PANXSIZE * cellSize, offsetY + j * cellSize);
        }
    }

    void drawUnits() {
        for (int y = 0; y < PANYSIZE; ++y) {
            for (int x = 0; x < PANXSIZE; ++x) {
                Unit* unit = game->getUnitAt(x, y);
                if (unit != nullptr) {
                    drawUnit(x, y, unit);
                }
            }
        }
    }

    void drawUnit(int x, int y, Unit* unit) {
        TCHAR name[3];
        _stprintf_s(name, 3, TEXT("%s"), unit->getUnitName());
        int drawX = offsetX + x * cellSize + cellSize / 4;
        int drawY = offsetY + y * cellSize + cellSize / 4;
        setTextColor(unit->getCountry() == HAN ? red : blue);
        wout << setpos(drawX, drawY) << name;
    }

    void drawStatus() {
        int turn = game->who();
        int cursorX = game->curx;
        int cursorY = game->cury;
        TCHAR status[100];
        _stprintf_s(status, 100, TEXT("Turn: %d Cursor: (%d, %d)"), turn, cursorX, cursorY);
        setTextColor(black);
        wout << setpos(offsetX, offsetY + (PANYSIZE + 1) * cellSize) << status;
    }

    void mouseDown(int x, int y) {
        int boardX = (x - offsetX) / cellSize;
        int boardY = (y - offsetY) / cellSize;
        if (boardX >= 0 && boardX < PANXSIZE && boardY >= 0 && boardY < PANYSIZE) {
            game->handleClick(boardX, boardY);
            clearAndUpdate();
        }
    }
};

