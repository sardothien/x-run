#ifndef _LIGHT_H_
#define _LIGHT_H_

/* Inicijalizacija osvetljenja */
void initializeLight();

/* Osvetljenje i boje kod objekta enemy */
void enemyLight(int part);

/* Inicijalizacija osvetljenja */
void elementsLight(int part);

/* Inicijalizacija tekstura */
void initializeTextures();

unsigned backgroundTexture(Image* img);
     
#endif