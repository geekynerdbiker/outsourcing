#include "projects/automated_warehouse/node.h"
#include "projects/automated_warehouse/aw_manager.h"

#define MAX_QUEUE_SIZE ((ROW_MAX + 1) * (COL_MAX + 1))

typedef struct Point
{
    int row;
    int col;
} Point;

typedef struct Queue
{
    Point data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *queue)
{
    queue->front = 0;
    queue->rear = 0;
}

bool isQueueEmpty(Queue *queue)
{
    return queue->front == queue->rear;
}

bool isQueueFull(Queue *queue)
{
    return (queue->rear + 1) % MAX_QUEUE_SIZE == queue->front;
}

void enqueue(Queue *queue, Point point)
{
    if (isQueueFull(queue))
    {
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->data[queue->rear] = point;
}

Point dequeue(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        Point emptyPoint = {-1, -1};
        return emptyPoint;
    }
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    Point point = queue->data[queue->front];
    return point;
}

bool isOutOfBound(int row, int col)
{
    return row < ROW_MIN || row > ROW_MAX || col < COL_MIN || col > COL_MAX;
}

bool isWall(int row, int col)
{
    return map[row][col] == 'X';
}

bool isAnotherCurrentPayload(int row, int col, int current)
{
    return map[row][col] >= '0' && map[row][col] <= '9' &&
           map[row][col] != current;
}

bool isAnotherRequiredPayload(int row, int col, int current)
{
    return map[row][col] >= 'A' && map[row][col] <= 'Z' &&
           map[row][col] != 'W' && map[row][col] != 'S' &&
           map[row][col] != current;
}

bool msg_is_loaded(Message *msg)
{
    return msg->current > msg->required;
}

int find_path(Message *msg)
{
    INFO("cnt", "find_path row: %d, col: %d, current: %c, required: %c", msg->row, msg->col, msg->current, msg->required);
    int row = msg->row;
    int col = msg->col;

    if (msg_is_loaded(msg) && map[row][col] == msg->current)
    {
        return CMD_NOP;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    Queue queue;
    initQueue(&queue);

    bool visited[ROW_MAX + 1][COL_MAX + 1] = {false};
    Point prev[ROW_MAX + 1][COL_MAX + 1] = {0};

    Point start = {row, col};
    enqueue(&queue, start);
    visited[start.row][start.col] = true;

    while (!isQueueEmpty(&queue))
    {
        Point current = dequeue(&queue);
        for (int i = 0; i < 4; i++)
        {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];

            if (isOutOfBound(nr, nc))
            {
                INFO("cnt", "skip(isOutOfBound) row: %d, col: %d", nr, nc);
                continue;
            }

            if (isWall(nr, nc))
            {
                INFO("cnt", "skip(isWall) row: %d, col: %d", nr, nc);
                continue;
            }

            if (visited[nr][nc])
            {
                INFO("cnt", "skip(visited) row: %d, col: %d", nr, nc);
                continue;
            }

            if (isAnotherCurrentPayload(nr, nc, msg->current))
            {
                INFO("cnt", "skip(isAnotherCurrentPayload) row: %d, col: %d", nr, nc);
                continue;
            }

            if (isAnotherRequiredPayload(nr, nc, msg->current))
            {
                INFO("cnt", "skip(isAnotherRequiredPayload) row: %d, col: %d", nr, nc);
                continue;
            }

            Point next = {nr, nc};
            enqueue(&queue, next);
            INFO("cnt", "enqueue row: %d, col: %d", nr, nc);
            visited[nr][nc] = true;
            prev[nr][nc] = current;
        }
    }

    Point target;
    bool found = false;
    for (int i = 0; i < ROW_MAX + 1; i++)
    {
        for (int j = 0; j < COL_MAX + 1; j++)
        {
            if (visited[i][j] && map[i][j] == msg->current)
            {
                target.row = i;
                target.col = j;
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }
    }

    if (!found)
    {
        return CMD_NOP;
    }

    while (prev[target.row][target.col].row != row ||
           prev[target.row][target.col].col != col)
    {
        target = prev[target.row][target.col];
    }

    if (target.row == row - 1)
    {
        return CMD_UP;
    }
    else if (target.row == row + 1)
    {
        return CMD_DOWN;
    }
    else if (target.col == col - 1)
    {
        return CMD_LEFT;
    }
    else if (target.col == col + 1)
    {
        return CMD_RIGHT;
    }
    return CMD_NOP;
}