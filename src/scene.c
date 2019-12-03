#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "scene.h"
//#include "image.h"

#define MAX (1000)

extern Level lvl;

/* Funkcija za koordinatni sistem */
void drawSystem(){
    
    glLineWidth(1);
    
    // x-osa
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(200, 0, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(-200, 0, 0);
    glEnd();
    
    // y-osa
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 200, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, -200, 0);
    glEnd();

    // z-osa
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 200);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, -200);
    glEnd();
}

/* Funkcija za crtanje osnove */
void drawFloor(double width){
    
    glColor3f(0.7, 0, 0.5);
    
    glPushMatrix();
        glScalef(width, 1, 1);
        glBegin(GL_QUADS);
            glVertex3f(-2.5, -1, -500);
            glVertex3f(2.5, -1, -500);
            glVertex3f(2.5, -1, 10);
            glVertex3f(-2.5, -1, 10);
        glEnd();
    glPopMatrix();
}

/* Funkcija za zaglavlje u kojem se nalazi slika karaktera
   i informacije o preostalim zivotima */
// void drawHeader(){
//     glColor3f(0.2, 0.2, 0.2);

//     glPushMatrix();
//         glBegin(GL_POLYGON);
//             glVertex3f(0.3, -0.3, 0);
//             glVertex3f(0.3, 0.3, 0);
//             glVertex3f(-0.3, 0.3, 0);
//             glVertex3f(-0.2, -0.3, 0);
//         glEnd();
//     glPopMatrix();
// }

// void drawObjects(){
//     glColor3f(0, 0, 0);
//     
//     glPushMatrix();
//         glTranslatef(1, 1, 1);
//         glutSolidCube(0.2);
//     glPopMatrix();
// }

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
    // printf("%d %d\n", *rowNumber, *obstacleNumberInRow);

    char **levelMatrix = NULL;
    levelMatrix = (char**) malloc(sizeof(char*) * (*rowNumber));
    if(*levelMatrix == NULL){
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

/* Funkcija za iscrtavanje objekata */
static void drawObstacle(char type){
    
    switch (type)
    {
    case '#': // cube
        // drawCube();
        glPushMatrix();
            glColor3f(0, 0.6, 0.6);
            glScalef(1, 3, 0.5);
            glutSolidCube(1);
        glPopMatrix();
        break;
    
    case 'x': // heal
        glPushMatrix();
            glScalef(0.5, 3, 0);
            glRotatef(time_parameter*10.0f, 0, 1, 0);
            drawHeal();
        glPopMatrix();
        break;

    case 'o': // enemy
        glPushMatrix();
            glColor3f(0.3, 0, 0.6);
            glScalef(0.5, 4, 1);
            glTranslatef(0, 0.3, 0);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
        break;
    default:
        break;
    }
}

void drawObstacles(double spinningPath, char** levelMatrix, int rowNumber, int obstacleNumberInRow, int maxRows, double pathWidth){

    glPushMatrix();
        glTranslatef(0, -0.6, 0);
        glScalef(pathWidth, 0.4, pathWidth);
        glTranslatef(-obstacleNumberInRow/2, 0, spinningPath - floor(spinningPath));

        int m =  abs(4 > (int) spinningPath ? (int) spinningPath : -4);
        glTranslatef(0, 0, m);

        int sight = nearbyint(spinningPath) + maxRows;
        int n = rowNumber < sight ? rowNumber : sight;
        for (int i = (int) spinningPath - m; i < n; i++) {
            int j;
            for (j = 0; j < obstacleNumberInRow; j++) {
                drawObstacle(levelMatrix[i][j]);
                glTranslatef(1,0,0);
            }
            glTranslatef(-j, 0, -1);
        }

    glPopMatrix();
}

/* Funkcija za iscrtavanje heal-a */
void drawHeal(){

    glPushMatrix();
    	glColor3f(0.8, 0, 0);
    	glTranslatef(0, 0.5, 0);
    	glScalef(0.6, 0.2, 0.2);
    	glutSolidCube(1);
    glPopMatrix();

   glPushMatrix();
        glColor3f(0.8, 0, 0);
        glTranslatef(0, 0.5, 0);
        glScalef(0.2, 0.6, 0.3);
        glutSolidCube(1);
   glPopMatrix();
}