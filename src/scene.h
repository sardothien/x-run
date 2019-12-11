#ifndef _SCENE_H_
#define _SCENE_H_

#include <stdbool.h>

typedef struct Image Image;

typedef struct {
    char **levelMatrix;
    int rowNumber;
    int obstacleNumberInRow;
    int viewDistance;
} Level;

double x, z;
int x_pom;
float time_parameter;

void drawSystem();
void drawFloor(double width);
void drawHeader();

char** loadLevel(char *path, int *rowNumber, int *obstacleNumberInRow);
void deallocLevel(char **levelMatrix, int rowNumber);

void drawObstacles(double spinningPath, char** levelMatrix, int rowNumber, int obstacleNumberInRow, int maxRows, double pathWidth);

bool hasCollision(double minPosition, char** lvlMatrix, int rowNumber);
     
#endif
