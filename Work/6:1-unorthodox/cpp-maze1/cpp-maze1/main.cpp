#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Block {
private:
    int route;
    int wall;
    
public:
    void setRoute(int r) { route = r; }
    void setWall(int w) { wall = w;}
    int getRoute() { return route; }
    int getWall() { return wall; }
};

class Maze {
private:
    Block** maze;
    int width, height;
    
public:
    Maze(int w, int h) {
        width = w;
        height = h;
        
        maze = (Block**)malloc(sizeof(Block*) * 2);
        for (int i = 0; i < 2; i++)
            maze[i] = (Block*)malloc(sizeof(Block) * width);
    }
    
    int getWidth() { return width; }
    int getHeight() { return height; }
    Block** getMaze() { return maze; }
    
};

void fill(Maze maze, int w) {
    for (int i = 0; i < maze.getWidth(); i++) {
        maze.getMaze()[0][i].setRoute(maze.getMaze()[1][i].getRoute());
        maze.getMaze()[0][i].setWall(maze.getMaze()[1][i].getWall());
        
        maze.getMaze()[1][i].setRoute(0);
        maze.getMaze()[1][i].setWall(0);
    }

    for (int i = 0; i < w - 1; i++)
        if (maze.getMaze()[1][i].getWall() >= maze.getMaze()[0][i+1].getWall())
            for (int j = i + 1; j < maze.getWidth(); j++) {
                int wall = maze.getMaze()[0][j].getWall();
                maze.getMaze()[0][j].setWall(wall + maze.getMaze()[0][i].getWall());
            }
}


void makeMaze(Maze maze, int check) {
    int i, j, k;
    int temp, flag, count, vertical, checker, numCount, newRoute;

    if (check > 0) fill(maze, maze.getWidth());

    for (i = 0; i < maze.getWidth() - 1; i++) {
        if (maze.getMaze()[0][i].getRoute() != maze.getMaze()[0][i + 1].getRoute()) {
            flag = rand() % 5;
            if (flag < 3) {
                temp = maze.getMaze()[0][i + 1].getRoute();
                
                maze.getMaze()[0][i + 1].setRoute(maze.getMaze()[0][i].getRoute());
                maze.getMaze()[0][i + 1].setWall(maze.getMaze()[0][i].getRoute());

                for (j = 0; j < maze.getWidth(); j++)
                    if (maze.getMaze()[0][j].getRoute() == temp && j != i)
                        maze.getMaze()[0][j].setRoute(maze.getMaze()[0][i].getRoute());
            }
        }
    }

    temp = i = vertical = 0;
    while (i < maze.getWidth()) {
        flag = rand() % 28;

        if (flag < 1) {
            maze.getMaze()[1][i] = maze.getMaze()[0][i];    // 수직 내리기
            if (i > 0 && maze.getMaze()[1][i].getRoute() == maze.getMaze()[1][i - 1].getRoute() && maze.getMaze()[1][i].getWall() == maze.getMaze()[1][i - 1].getWall()) {
                if (maze.getMaze()[0][i].getWall() == maze.getMaze()[0][i - 1].getWall() && maze.getMaze()[0][i].getRoute() == maze.getMaze()[0][i - 1].getRoute()) {
                    while (1) {
                        newRoute = (i + 1) * (i + maze.getWidth()) + maze.getMaze()[0][i].getWall() + rand() % 100;
                        numCount = 0;
                        for (j = 0; j < 2; j++)
                            for (k = 0; k < maze.getWidth(); k++)
                                if (newRoute == maze.getMaze()[j][k].getRoute()) numCount++;
                        if (numCount == 0) break;
                    }
                    maze.getMaze()[1][i].setRoute(newRoute);
                }
            }
            vertical++;
        }

        if (i == 0 && maze.getMaze()[0][i].getRoute() != maze.getMaze()[0][i + 1].getRoute() && vertical == 0) {
            maze.getMaze()[1][i].setRoute(maze.getMaze()[0][i].getRoute());
            maze.getMaze()[1][i].setWall(maze.getMaze()[0][i].getWall());
            vertical++;
        }

        if (i < maze.getWidth() - 1 && maze.getMaze()[0][i].getRoute() == maze.getMaze()[0][i + 1].getRoute()) i++;
        else {    // 그 다음 인덱스와 다른 경우 -> vertical이 0이면 돌아가고 1보다 크면 진행한다.
            if (vertical == 0) {
                for (j = temp; j <= i; j++) {
                    maze.getMaze()[1][j].setRoute(0);
                    maze.getMaze()[1][j].setWall(0);
                }
                i = temp;
            }
            else {
                vertical = 0;
                temp = i++;
            }
        }

        if (i == maze.getWidth() - 1 && maze.getMaze()[0][i].getRoute() != maze.getMaze()[0][i - 1].getRoute() && vertical == 0) {
            maze.getMaze()[1][j].setRoute(maze.getMaze()[0][i].getRoute());
            maze.getMaze()[1][j].setWall(maze.getMaze()[0][i].getWall());
            i++;
        }
    }

    for (i = 0; i < maze.getWidth(); i++)
        if (maze.getMaze()[1][i].getRoute() == 0) {

            while (1) {
                newRoute = (i + 1) * (i + maze.getWidth()) + maze.getMaze()[0][i].getWall() + rand() % 10;
                maze.getMaze()[1][i].setWall((i + 1) * (i + maze.getWidth()) + maze.getMaze()[0][i].getWall() + rand() % 10);
                numCount = 0;
                for (j = 0; j < 2; j++)
                    for (k = 0; k < maze.getWidth(); k++)
                        if (newRoute == maze.getMaze()[j][k].getRoute()) numCount++;
                if (numCount == 0) break;
            }
            maze.getMaze()[1][i].setRoute(newRoute);
        }
}



int main() {
    Block** maze;
    
    int w, h, temp;
    char c;

    srand(time(NULL));
    cout << "Width Height: ";
    cin >> w >> h;

    Maze maze(w, h);
    
    FILE* fp = fopen("maze0.txt", "w");

    for (int i = 0; i < maze.getWidth(); i++) {
        maze.getMaze()[0][i].setRoute(i + 1);
        maze.getMaze()[0][i].setWall(i + 1);
        
        maze.getMaze()[1][i].setRoute(0);
        maze.getMaze()[1][i].setWall(0);
    }

    for (int i = 0; i < 2 * w + 1; i++) {
        if (i % 2) {
            fprintf(fp, "-");
            cout << "-";
        } else {
            fprintf(fp, "+");
            cout << "+";
        }
    } fprintf(fp, "\n");
    cout << "\n";


    for (int i = 0; i < h; i++) {
        makeMaze(maze, i);

        if (i == h - 1) {

            fprintf(fp, "|");
            cout << "|";
            for (int j = 0; j < w - 1; j++) {
                fprintf(fp, " ");
                cout << " ";
                if (maze.getMaze()[0][j].getRoute() != maze.getMaze()[0][j + 1].getRoute()) {
                    fprintf(fp, " ");
                    cout << " ";
                    temp = maze.getMaze()[0][j + 1].getRoute();
                    maze.getMaze()[0][j + 1].setRoute(maze.getMaze()[0][j].getRoute());
                    for (int k = j + 2; k < maze.getWidth(); k++)
                        if (temp == maze.getMaze()[0][k].getRoute())
                            maze.getMaze()[0][k].setRoute(maze.getMaze()[0][j].getRoute());
                }
                else
                    if (maze.getMaze()[0][j].getWall() == maze.getMaze()[0][j + 1].getWall()) {
                        fprintf(fp, " ");
                        cout << " ";
                    } else {
                        fprintf(fp, "|");
                        cout << "|";
                    }
            } fprintf(fp, " |\n");
            cout << "|\n";
            continue;
        }

        fprintf(fp, "|");
        cout << "|";
        for (int j = 0; j < w - 1; j++) {
            fprintf(fp, " ");
            cout << " ";

            if (maze.getMaze()[0][j].getWall() == maze.getMaze()[0][j + 1].getWall()) {
                fprintf(fp, " ");
                cout << " ";
            } else {
                fprintf(fp, "|");
                cout << "|";
            }
        } fprintf(fp, " |\n");
        cout << "|\n";

        for (int j = 0; j < maze.getWidth(); j++) {
            fprintf(fp, "+");
            cout << "+";
            if (maze.getMaze()[0][j].getRoute() != maze.getMaze()[1][j].getRoute()) {
                fprintf(fp, "-");
                cout << "-";
            } else {
                fprintf(fp, " ");
                cout << " ";
            }
        } fprintf(fp, "+\n");
        cout << "+\n";
    }

    for (int i = 0; i < 2 * w + 1; i++) {
        if (i % 2) {
            fprintf(fp, "-");
            cout << "-";
        } else {
            fprintf(fp, "+");
            cout << "+";
        }
    }

    fclose(fp);
    return 0;
}
