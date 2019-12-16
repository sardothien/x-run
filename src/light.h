#ifndef _LIGHT_H_
#define _LIGHT_H_

void initializeLight();

void floorLight();
void enemyLight(int part);
void healLight();
void cubeLight();
void heartLight();

void initializeTextures();
unsigned backgroundTexture(Image* img);
     
#endif