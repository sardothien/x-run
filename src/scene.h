#ifndef _SCENE_H_
#define _SCENE_H_

// 1 - kocka, 2 - heal, 3 - enemy (krug za sada)
typedef struct {
    float x, y, z;
    int type;
} Obstacle;

void drawSystem();
void drawFloor(double width);
// void drawObjects();

void drawObstacle(float x, float y, float z, int type);
     
#endif
