#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "obstacles.h"
#include "display.h"

#define TRUE 1
#define FALSE 0

// This is a helper function that determines whether or not line segment (v1---v2) intersects line segment (v3---v4)
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
    float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
    float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
    
    // If uA and uB are between 0-1, there is an intersection
    if (uA > 0 && uA < 1 && uB > 0 && uB < 1)
        return TRUE;
    
    return FALSE;
}

int generateRandomNumInRange(int min, int max)
{
    int num = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    return num;
}

int isObstacleFree(int index, TreeNode* n1, TreeNode* n2, Obstacle* obs) {
    
    int result = FALSE;
    
    result += linesIntersect(n1->x, n1->y, n2->x, n2->y, obs[index].x, obs[index].y, obs[index].x, obs[index].y - obs[index].h);
    result += linesIntersect(n1->x, n1->y, n2->x, n2->y, obs[index].x, obs[index].y, obs[index].x + obs[index].w, obs[index].y);
    result += linesIntersect(n1->x, n1->y, n2->x, n2->y, obs[index].x + obs[index].w, obs[index].y - obs[index].h, obs[index].x, obs[index].y - obs[index].h);
    result += linesIntersect(n1->x, n1->y, n2->x, n2->y, obs[index].x + obs[index].w, obs[index].y - obs[index].h, obs[index].x + obs[index].w, obs[index].y);

    return result;
}

void initRRT(Environment* env) {
    srand((unsigned int)time(NULL));
    env->rrt = (TreeNode**)malloc((env->maximumNodes) * sizeof(TreeNode*));
    env->numNodes = (unsigned short)malloc(sizeof(unsigned short));
    TreeNode* firstNode = (TreeNode*)malloc(sizeof(TreeNode));
    
    firstNode->x = env->startX;
    firstNode->y = env->startY;
    firstNode->parent = NULL;
    firstNode->firstChild = NULL;
    
    *(env->rrt) = firstNode;
    env->numNodes = 1;
}

TreeNode* getRandomNode(Environment* env) {
    TreeNode* n = (TreeNode *)malloc(sizeof(TreeNode));
    
    n->x = generateRandomNumInRange(0, env->maximumX);
    n->y = generateRandomNumInRange(0, env->maximumY);
    
    return n;
}

TreeNode* getNearestNode(Environment* env, TreeNode* q) {
    TreeNode* curr = *(env->rrt);
    TreeNode* min = NULL;
    float minDist = sqrt(env->maximumX^2 + env->maximumY^2);;
    
    while (curr->firstChild != NULL) {
        float dist = sqrt((curr->x - q->x)^2 + (curr->y - q->y)^2);
        if (minDist > dist) {
            minDist = dist;
            min = curr;
        }
        // traversal
        curr = curr->firstChild->node;
    }
    
    return min;
}

TreeNode* getGrowthNode(Environment* env, TreeNode* n, TreeNode* q) {
    TreeNode* c = (TreeNode *)malloc(sizeof(TreeNode));
    double angle = atan2(q->y - n->y, q->x - n->x);
    
    c->x = n->x + cos(angle) * env->growthAmount;
    c->y = n->y + cos(angle) * env->growthAmount;
    
    return c;
}

void addNewNode(Environment* env, TreeNode* n, TreeNode* c) {
    
    
    if (n->firstChild == NULL) {
        n->firstChild = (Child*)malloc(sizeof(Child));
        n->firstChild->node = c;
        c->parent = n;
    }
    else {
        Child* curr = n->firstChild;
        while(curr->nextSibling != NULL) {
            curr = curr->nextSibling;
        }
        curr->nextSibling = (Child*)malloc(sizeof(Child));
        curr->nextSibling->node = c;
        c->parent = curr->node;
    }
    env->numNodes++;
}


void createRRT(Environment *env) {
    srand((unsigned int)time(NULL));
    initRRT(env);
    
    while (env->numNodes < env->maximumNodes) {
        TreeNode* q = getRandomNode(env);
        TreeNode* n = getNearestNode(env, q);
        TreeNode* c = getGrowthNode(env, n, q);
        
        int isObsFree = TRUE;
        for (int i = 0; i < env->numObstacles; i++) {
            if (!isObstacleFree(i, n, c, env->obstacles))
                isObsFree = FALSE;
        }
        
        if (isObsFree) addNewNode(env, n, c);
    }
}


// Trace the path back from the node that is closest to the given (x,y) coordinate to the root
void tracePath(Environment *env, unsigned short x, unsigned short y) {
    TreeNode* end = (TreeNode*)malloc(sizeof(TreeNode));
    end->x = x; end->y = y;
    
    TreeNode* curr = getNearestNode(env, end);
    
    int i = 0;
    while (curr->parent != NULL) {
        *(env->path + i) = curr;
        curr = curr->parent;
    }
}


// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {
    free(env->obstacles);
    free(env->path);
    free(env->rrt);
    free(env);
}


