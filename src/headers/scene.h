#ifndef _SCENE_H_
#define _SCENE_H_

void drawSystem();

void drawSky(unsigned textureID);
void drawFloor(double width);

void drawObstacles(double spinningPath, char** levelMatrix, int rowNumber, int obstacleNumberInRow, int maxRows, double pathWidth);
void drawHearts();
     
#endif