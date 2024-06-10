#include "Game.h"
#include "pclaf.h"

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
        drawStatus();
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
        
        if (game->IsJang())
            _stprintf_s(status, 100, TEXT("Turn: %d Cursor: (%d, %d) >> Jang !"), turn, cursorX, cursorY);
        else if (game->IsMung())
            _stprintf_s(status, 100, TEXT("Turn: %d Cursor: (%d, %d) >> Mung !"), turn, cursorX, cursorY);
        else if (!game->validMove) 
            _stprintf_s(status, 100, TEXT("Turn: %d Cursor: (%d, %d) >> Invalid Move !"), turn, cursorX, cursorY);
        else 
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

int mainLAF() {
    JanggiApp theApp(TEXT("Janggi"), 700, 800, 100, 100);
    theApp.run();
    return 0;
}
