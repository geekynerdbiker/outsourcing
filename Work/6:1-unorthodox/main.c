#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *maze;

int width, height;
int *hWall, *vWall;
int index = 1;

FILE *fp;

int makeWall();
int makeVerticalWall();
int makeHorizontalWall();

int joinVertical();
int joinHorizontal();
int lineFirst();
int lineMids();
int lineLast();


int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    
    fp = fopen("maze.maz", "wt");
    
    printf("Width: ");
    scanf("%d", &width);
    printf("Height: ");
    scanf("%d", &height);

    hWall = (int *)malloc(sizeof(int) * width);
    vWall = (int *)malloc(sizeof(int) * (width - 1));
    maze = (int *)calloc(width, sizeof(int));

    makeWall();
    lineFirst();
    makeVerticalWall();
    lineMids();
    lineLast();
    makeWall();

    fclose(fp);

    return 0;
}

int makeWall() {
    for (int i = 0; i < width; i++)
        fprintf(fp, "+-");
    
    fprintf(fp, "+\n");
    
    return 0;
}

int makeVerticalWall() {
    fprintf(fp, "|");

    for (int i = 0; i < width - 1; i++) {
        fprintf(fp, " ");

        if (vWall[i]) fprintf(fp, "|");
        else fprintf(fp, " ");
    }

    fprintf(fp, " |\n");
    return 0;
}

int makeHorizontalWall() {
    fprintf(fp, "+");
    for (int i = 0; i < width; i++) {
        if (hWall[i]) fprintf(fp, "-+");
        else fprintf(fp, " +");
    }
    
    fprintf(fp, "\n");
    return 0;
}

int joinVertical() {
    int flag = 0;
    int prevIndex = maze[0];

    for (int i = 0; i < width; i++)
    {
        hWall[i] = rand() % 2;
        if (!hWall[i]) flag = 1;

        if ((i < width - 1) && (prevIndex != maze[i + 1])) {
            if (!flag) hWall[i] = 0;
            else flag = 0;
            prevIndex = maze[i + 1];
        }

        if ((i == width - 1) && (!flag)) hWall[i] = 0;
        if (hWall[i]) maze[i] = index++;
    }
    return 0;
}

int joinHorizontal() {
    int prevIndex;

    for (int i = 0; i < width - 1; i++) {
        if (maze[i] != maze[i + 1]) {
            vWall[i] = rand() % 2;
            if (!vWall[i]) {
                prevIndex = maze[i + 1];
                maze[i + 1] = maze[i];
                for (int j = 0; j < width; j++)
                    if (maze[j] == prevIndex) maze[j] = maze[i];
            }
        }
        else vWall[i] = 1;
    }
    return 0;
}

int lineFirst() {
    int prevWall = -1;

    for (int i = 0; i < width - 1; i++) {
        vWall[i] = rand() % 2;
        
        if (vWall[i]) {
            for (int j = prevWall + 1; j <= i; j++)
                maze[j] = index++;
            prevWall = i;
        }
    }
    
    for (int i = prevWall + 1; i < width; i++)
        maze[i] = index;
    index++;
    return 0;
}

int lineMids() {
    for (int i = 1; i < height - 1; i++) {
        joinVertical();
        makeHorizontalWall();
        joinHorizontal();
        makeVerticalWall();
    }
    return 0;
}

int lineLast() {
    int prevIndex;

    joinVertical();
    makeHorizontalWall();

    for (int i = 0; i < width - 1; i++) {
        if (maze[i] != maze[i + 1])
        {
            vWall[i] = 0;
            prevIndex = maze[i + 1];
            maze[i + 1] = maze[i];
            for (int j = 0; j < width; j++)
                if (maze[j] == prevIndex) maze[j] = maze[i];
        }
        else vWall[i] = 1;
    }

    makeVerticalWall();
    return 0;
}


