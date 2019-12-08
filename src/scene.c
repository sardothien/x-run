#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "scene.h"
#include "image.h"

#define MAX (1700)
const static float PI = 3.141592653589793;

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

/* Funkcija za iscrtavanje heal-a */
static void drawHeal(){

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

/* Funkcija za crtanje valjka */
void drawCylinder(GLfloat radius, GLfloat height){
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    glBegin(GL_QUAD_STRIP);
        angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();
}

/* Funkcija za iscrtavanje enemy-a */
static void drawEnemy(){
    // Gornji deo glave
    glPushMatrix();
     	glColor3f(0.5, 0, 0);
     	glTranslatef(0, 0.65, 0);
     	glutSolidSphere(0.35, 30, 30);
    glPopMatrix();
    
    // Valjak
    glPushMatrix();
        glColor3f(0.5, 0, 0);
        glRotatef(-90, 1, 0, 0);
        drawCylinder(0.35, 0.68);
    glPopMatrix();

    // Lice
    glPushMatrix();
        glColor3f(0.5, 0.5, 0);
        glTranslatef(0, 0.15, 0.15);
        glRotatef(-90, 1, 0, 0);
        drawCylinder(0.25, 0.45);
    glPopMatrix();

    // Desno oko
    glPushMatrix();
        glColor3f(1, 0, 0);
     	glTranslatef(0.10, 0.5, 0.35);
     	glutSolidSphere(0.06, 30, 30);
    glPopMatrix();

    // Levo oko
    glPushMatrix();
        glColor3f(1, 0, 0);
     	glTranslatef(-0.10, 0.5, 0.35);
     	glutSolidSphere(0.06, 30, 30);
    glPopMatrix();

    glLineWidth(2);
    glColor3f(0, 0, 0);

    // Desna obrva
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.06, 0.55, 0.4);
        glVertex3f(0.22, 0.6, 0.4);
    glEnd();

    // Leva obrva
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.06, 0.55, 0.4);
        glVertex3f(-0.22, 0.6, 0.4);
    glEnd();

    // Usta    
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.15, 0.2, 0.4);
        glVertex3f(0.15, 0.3, 0.4);
        glVertex3f(0.10, 0.35, 0.4);
        glVertex3f(-0.10, 0.35, 0.4); 
        glVertex3f(-0.15, 0.3, 0.4);
        glVertex3f(-0.15, 0.2, 0.4);
    glEnd();
}

/* Funkcija za iscrtavanje objekata */
static void drawObstacle(char type){
    
    switch (type)
    {
    case '#': // cube
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
            glTranslatef(0, sin(time_parameter / 2.0f) * 0.5f, 0);
            glScalef(0.7, 4, 0.7);
            drawEnemy();
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
