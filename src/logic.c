#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "logic.h"
#include "scene.h"
#include "image.h"
#include "light.h"

#define MAX (1700)

extern Level lvl;

void initialize(){
    time_parameter = 0;
    timer_active = 0;

    x = 0;
    x_pom = 1;
    z = 0;

    lives = 3;
}

/* Funkcija za ucitavanje nivoa iz datoteke */
char** loadLevel(char * path, int *rowNumber, int *obstacleNumberInRow){

    FILE *in;
    in = fopen(path, "r");
    if(in == NULL){
        fprintf(stderr, "Error! Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX];

    fscanf(in, "%d\n", rowNumber);
    fscanf(in, "%d\n", obstacleNumberInRow);

    char **levelMatrix = NULL;
    levelMatrix = (char**) malloc(sizeof(char*) * (*rowNumber));
    if(levelMatrix == NULL){
        fprintf(stderr, "Error! Unsuccessful 1st malloc.\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while(fgets(buffer, 100, in) != NULL){

        levelMatrix[i] = NULL;
        levelMatrix[i] = (char*) malloc(sizeof(char) * (*obstacleNumberInRow));
        if(levelMatrix[i] == NULL){
            deallocLevel(levelMatrix, i);
            fprintf(stderr, "Error! Unsuccessful 2nd malloc.");
            exit(EXIT_FAILURE);
        }
        else{
            for(int j = 0; j < *obstacleNumberInRow; j++)
                levelMatrix[i][j] = buffer[j*2];
        }

        i++;
    }

    return levelMatrix;
}

/* Brisanje nivoa i oslobadjanje memorije */
void deallocLevel(char **levelMatrix, int rowNumber){
    for (int i = 0; i < rowNumber; i++)
        free(levelMatrix[i]);
    free(levelMatrix);
}

/* Funkcija za obradu kolizija */
bool hasCollision(double minPosition, char** lvlMatrix, int rowNumber){
    int i, j;

    // rade dobro samo za #
    if(x_pom == 0){
        i = nearbyint(z+2.5); 
        j = x_pom;
    }
    else if (x_pom == 1){
        i = nearbyint(z+2.5); 
        j = x_pom;
    }
    else{ // x-pom == 2
        i = nearbyint(z+8.6); 
        j = x_pom;
    }
    
    //printf("%d %d\n", i, j);
    //printf("%d\n", lives);
    if (i < rowNumber){
        if (lvlMatrix[i][j] == '#')
            return true;
        else if (lvlMatrix[i][j] == 'o')
        {   
            //lives--;
            // TODO - gubi se zivot
        }
        else if (lvlMatrix[i][j] == 'x')
        {
            if (lives < 3)
                lives++;
        }

        if (lives == 0)
            return true;
    }        

    return false;
}