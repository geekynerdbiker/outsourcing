#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "obstacles.h"
#include "display.h"


// This is a helper function that determines whether or not line segment (v1---v2) intersects line segment (v3---v4)
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
  	float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
  	float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));

  	// If uA and uB are between 0-1, there is an intersection
  	if (uA > 0 && uA < 1 && uB > 0 && uB < 1) 
		return 1;

	return 0;
}

int generateRandomNumInRange(int min, int max)
{
    int num = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    return num;
}

int isObstacleFree(int index, TreeNode* q, Obstacle* obs) {
    return q->x <= (obs[index].x + obs[index].w) && q->x >= obs[index].x && q->y <= (obs[index].y + obs[index].h) && q->y >= obs[index].y;
}

void initRRT(Environment* env) {
    srand(time(NULL));
    env->rrt = (TreeNode**)malloc((env->maximumNodes) * sizeof(TreeNode*));
    TreeNode* firstNode = (TreeNode*)malloc(sizeof(TreeNode));
    
    firstNode->x = env->startX;
    firstNode->y = env->startY;
    firstNode->parent = NULL;
    firstNode->firstChild = NULL;
    
    *(env->rrt) = firstNode;
    env->numNodes = 1;
}

TreeNode* getRandomNode(int maximumX, int maximumY) {
    TreeNode* n = (TreeNode *)malloc(sizeof(TreeNode));
    
    n->x = generateRandomNumInRange(0, maximumX);
    n->y = generateRandomNumInRange(0, maximumY);
    
    return n;
}

TreeNode* getNearestNode(int max, TreeNode** rrt, TreeNode* n) {
    TreeNode* curr = *rrt;
    float minDist = max;
    
    while (curr->firstChild != NULL) {
        float dist = sqrt((curr->x - n->x)^2 + (curr->y - n->y)^2);
        if (minDist > dist) minDist = dist;
        
        
    }
}

// Create a rrt using the growthAmount and maximumNodes parameters in the given environment.
void createRRT(Environment *env) {
	//Add code so that it allocates a dynamic array that can hold pointers of up to a maximumNodes number of tree nodes.
	//This array MUST be stored into the rrt attribute of the Environment structure.
	srand(time(NULL));
    initRRT(env);
	/*
	//Each time you create a new TreeNode,
	TreeNode* newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->x = 100;
	newNode->y = 100;
	//you should add it to the environment’s dynamically-created rrt array
	newNode->parent = firstNode;
	
	Child* child = (Child *)malloc(sizeof(Child));
	child->node = newNode;
	firstNode->firstChild = child;
	env->rrt[1] = newNode;
	*/
	
    for (int i = 0; i < env->maximumNodes; i++) {
        TreeNode* rndNode = getRandomNode(env->maximumX, env->maximumY);
        
        float max = sqrt(env->maximumX^2 + env->maximumY^2);
        TreeNode* nearestNode = getNearestNode(max, env->rrt, rndNode);
        
        for (int i = 0; i < env->numObstacles; i++){
            if (!isObstacleFree(i, q, env->obstacles)) {
                qIsObstacleFree = 1;
                break;// break the for loop and get start with another point q
            }
        }
        
		printf("q->x: %d, q->y: %d", q->x, q->y);
        
		//find point n
		float closestDistance = 0;
		int nx, ny;
		for (int i = 0; i < env->numNodes; ++i){
			//distance between two points
            float distance = sqrt( (qx - env->rrt[i]->x) * (qx - env->rrt[i]->x) + (qy - env->rrt[i]->y) * (qy - env->rrt[i]->y) );
			if(closestDistance == 0){
				closestDistance = distance;
			}else{
				if(distance < closestDistance){
					closestDistance = distance;
					nx = env->rrt[i]->x;
					ny = env->rrt[i]->y;
				}
			}
		}
		printf("qx: %d, qy: %d", qx, qy);

		
	//}
	/*
	while(env->numNodes != env->maximumNodes){
		//Each time you create a new TreeNode,
		
		newNode->x = 50;
		newNode->y = 50;
		//you should add it to the environment’s dynamically-created rrt array
		env->rrt++;//next position in the array
		*(env->rrt) = newNode;
		firstNode->firstChild = newNode;
		newNode->parent = firstNode;
	}
	*/
	
}


// Trace the path back from the node that is closest to the given (x,y) coordinate to the root
void tracePath(Environment *env, unsigned short x, unsigned short y) {	
	
}


// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {
	free(env->obstacles);
}


