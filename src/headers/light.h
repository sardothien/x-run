#ifndef _LIGHT_H_
#define _LIGHT_H_

void initializeLight();

void floorLight();
void enemyLight(int part);
void elementsLight(int part);

void initializeTextures();
unsigned backgroundTexture(Image* img);
     
#endif