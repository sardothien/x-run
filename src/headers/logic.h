#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <stdbool.h>

/* Pomocna struktura za ucitavanje nivoa */
typedef struct {
    char **levelMatrix;
    int rowNumber;
    int obstacleNumberInRow;
    int viewDistance;
    unsigned backgroundID;
} Level;

int timer_active;
float time_parameter;

/* Pamti se pozicija na kojoj se nalazimo */
int moves[2];
double x, z;
int x_pom;

/* Pomocna promenljiva za koliziju */
int hit;

/* Broj preostalih zivota */
int lives;

/* Pomocne promenljive za akciju ubijanja neprijatelja */
int sword;
int killed;

/* Pomocne promenljive koje detektuju pauzu/kraj igre */
int paused, won;

/* Inicijalizacija igre */
void initialize();

/* Funkcija za ucitavanje nivoa iz datoteke */
char** loadLevel(char *path, int *rowNumber, int *obstacleNumberInRow);

/* Funkcija za obradu kolizija */
bool hasCollision(char** lvlMatrix, int rowNumber);
     
#endif