#ifndef _LIGHT_H_
#define _LIGHT_H_

typedef struct Image image;

void initializeLight();

void floorLight();
void enemyLight(int part);
void healLight();
void cubeLight();
void heartLight();
     
#endif