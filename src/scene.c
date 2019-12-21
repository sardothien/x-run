#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./headers/logic.h"
#include "./headers/scene.h"
#include "./headers/image.h"
#include "./headers/light.h"

const static float PI = 3.141592653589793;

extern Level lvl;

/* Funkcija za iscrtavanje koordinatnog sistema */
void drawSystem(){
    
    glLineWidth(1);
    
    // x-osa
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(200, 0, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(-200, 0, 0);
    glEnd();
    
    // y-osa
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 200, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, -200, 0);
    glEnd();

    // z-osa
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 200);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, -200);
    glEnd();
}

/* Pomocna funkcija za iscrtavanje ravni */
static void drawPlane(){
    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f(0,0,1);
            
            glTexCoord2f(0, 0);
            glVertex2f(-0.5, 0.5);

            glTexCoord2f(0, 1);
            glVertex2f(-0.5, -0.5);

            glTexCoord2f(1, 1);
            glVertex2f(0.5, -0.5);

            glTexCoord2f(1, 0);
            glVertex2f(0.5, 0.5);
        glEnd();
    glPopMatrix();
}

/* Pomocna funkcija za iscrtavanje kocke */
static void drawCube(){
    // prednja stranica
    glPushMatrix();
        glTranslatef(0,0,-0.5);
        drawPlane();
    glPopMatrix();

    // zadnja stranica
    glPushMatrix();
        glRotatef(-90, 0, 0, 1);
        glTranslatef(0,0,0.5);
        drawPlane();
    glPopMatrix();

    // desna stranica
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0,0,0.5);
        drawPlane();
    glPopMatrix();

    // leva stranica
    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        glTranslatef(0,0,0.5);
        drawPlane();
    glPopMatrix();

    // donja stranica
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0,0,0.5);
        drawPlane();
    glPopMatrix();

    // gornja stranica
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glTranslatef(0,0,0.5);
        drawPlane();
    glPopMatrix();
}

/* Funkcija za iscrtavanje neba */
void drawSky(unsigned textureID){
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glScalef(800,800,1000);
        drawCube();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

/* Funkcija za crtanje staze */
void drawFloor(double width){
    
    // osvetljenje/boja
    elementsLight(1);
    
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

/* Funkcija za iscrtavanje objekta heal */
static void drawHeal(){

    // Horizontalni kvadar
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glScalef(0.6, 0.2, 0.2);
        glutSolidCube(1);
    glPopMatrix();

    // Gornji vertikalni kvadar
    glPushMatrix();
        glTranslatef(0, 0.7, 0);
        glScalef(0.2, 0.2, 0.2);
        glutSolidCube(1);
    glPopMatrix();   

    // Donji vertikalni kvadar
    glPushMatrix();
        glTranslatef(0, 0.3, 0);
        glScalef(0.2, 0.2, 0.2);
        glutSolidCube(1);
    glPopMatrix();
}

/* Pomocna funkcija za crtanje valjka */
static void drawCylinder(GLfloat radius, GLfloat height){
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat step = 0.1;

    glBegin(GL_QUAD_STRIP);
        angle = 0.0;
        while(angle < 2*PI) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y, height);
            glVertex3f(x, y, 0.0);
            angle += step;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();
}

/* Funkcija za iscrtavanje objekta enemy */
static void drawEnemy(){
    // Gornji deo glave
    glPushMatrix();
        enemyLight(1);
     	glTranslatef(0, 0.69, 0);
     	glutSolidSphere(0.35, 30, 30);
    glPopMatrix();
    
    // Valjak
    glPushMatrix();
        enemyLight(1);
        glRotatef(-90, 1, 0, 0);
        drawCylinder(0.35, 0.68);
    glPopMatrix();

    // Lice
    glPushMatrix();
        enemyLight(2);
        glTranslatef(0, 0.15, 0.15);
        glRotatef(-90, 1, 0, 0);
        drawCylinder(0.25, 0.45);
    glPopMatrix();

    // Desno oko
    glPushMatrix();
        enemyLight(4);
     	glTranslatef(0.10, 0.5, 0.35);
     	glutSolidSphere(0.06, 30, 30);
    glPopMatrix();

    // Levo oko
    glPushMatrix();
        enemyLight(4);
     	glTranslatef(-0.10, 0.5, 0.35);
     	glutSolidSphere(0.06, 30, 30);
    glPopMatrix();

    glLineWidth(2);

    // Desna obrva
    glBegin(GL_LINE_STRIP);
        enemyLight(3);
        glVertex3f(0.06, 0.55, 0.4);
        glVertex3f(0.22, 0.6, 0.4);
    glEnd();

    // Leva obrva
    glBegin(GL_LINE_STRIP);
        enemyLight(3);
        glVertex3f(-0.06, 0.55, 0.4);
        glVertex3f(-0.22, 0.6, 0.4);
    glEnd();

    // Usta    
    glBegin(GL_LINE_STRIP);
        enemyLight(3);
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

    switch (type){
        case '#': // cube
            glPushMatrix();
                elementsLight(2);
                glScalef(1.0, 3.3, 1.0);
                glTranslatef(0, 0.01, 0);
                glutSolidCube(1);
            glPopMatrix();
            break;
        
        case 'x': // heal
            glPushMatrix();
                elementsLight(3);
                glScalef(0.5, 3, 0);
                glRotatef(time_parameter*5.0f, 0, 1, 0);
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
    }
}

/* Funkcija za smestanje objekata na odgovarajuce mesto i njihovo iscrtavanje */
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
                glTranslatef(1, 0, 0);
            }
            glTranslatef(-j, 0, -1);
        }

    glPopMatrix();
}

/* Funkcija za iscrtavanje pojedinacnog srca */
static void drawHeart(){

    glScalef(0.15, 0.15, 0.15);
    glPushMatrix();
        glutSolidSphere(0.2, 30, 30);

        glTranslatef(0.4, 0, 0);
        glutSolidSphere(0.2, 30, 30);

        glScalef(1.4, 1.4, 0.2);
        glTranslatef(-0.15, -0.15, 0);
        glRotatef(50, 0, 0, 1);
        glRotatef(-5, 0, 0, 1);
        glutSolidCube(0.30);
	glPopMatrix();
}

/* Funkcija za pozicioniranje i iscrtavanje srca 
   u gornjem levom uglu ekrana */
void drawHearts(){

    glDisable(GL_LIGHTING);

    elementsLight(4);

    int health = lives;
    int i = 1;
    while(health){
        glPushMatrix();
            glTranslatef(-1.6 + (health-i)*0.1 + x, 2.0, 0);
            glRotatef(25, 0, 1, 0);
            glRotatef(-25, 1, 0, 0);
            drawHeart();
        glPopMatrix();
        i++;
        health--;
    }

    glEnable(GL_LIGHTING);
}