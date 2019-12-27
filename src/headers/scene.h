#ifndef _SCENE_H_
#define _SCENE_H_

/* Iscrtavanje koordinata */
void drawSystem();

/* Iscrtavanje pozadine */
void drawBackground(unsigned textureID);
/* Iscrtavanje staze */
void drawFloor(double width);

/* Iscrtavanje prepreka */
void drawObstacles(double spinningPath, char** levelMatrix, int rowNumber, int obstacleNumberInRow, int maxRows, double pathWidth);

/* Iscrtavanje srca za zivote */
void drawHearts();
/* Iscrtavanje maca */
void drawSword();

/* Ispisivanje teksta prilikom gubitka */
void gameOver();
/* Ispisivanje teksta prilikom pauziranja igre */
void gamePaused();
/* Ispisivanje teksta prilikom pobede */
void gameWon();
     
#endif