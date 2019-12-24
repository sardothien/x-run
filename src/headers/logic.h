#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <stdbool.h>

typedef struct {
    char **levelMatrix;
    int rowNumber;
    int obstacleNumberInRow;
    int viewDistance;
    unsigned backgroundID;
} Level;

int moves[2];

double x, z;
int x_pom;
int hit;
int timer_active;
float time_parameter;
int lives;
int sword;
int notKilled;

void initialize();

char** loadLevel(char *path, int *rowNumber, int *obstacleNumberInRow);
void deallocLevel(char **levelMatrix, int rowNumber);

bool hasCollision(char** lvlMatrix, int rowNumber);
     
#endif