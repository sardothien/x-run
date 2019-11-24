#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"

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

// void drawObjects(){
//     glColor3f(0, 0, 0);
//     
//     glPushMatrix();
//         glTranslatef(1, 1, 1);
//         glutSolidCube(0.2);
//     glPopMatrix();
// }

void drawObstacle(float x, float y, float z, int type){
    
    if(type == 1){ // cube
        glPushMatrix();
            glColor3f(0, 0.6, 0.6);
            glTranslatef(x, y, z);
            glutSolidCube(1);
        glPopMatrix();
    }
    /*else if(type == 2){ // heal
        
    }*/
    else if(type == 3){ // enemy
        glPushMatrix();
            glColor3f(0.3, 0, 0.6);
            glTranslatef(x, y, z);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
    }
}
