#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"

void drawFloor(){
    
    glColor3f(0.7, 0, 0.5);
    
    glPushMatrix();
        glScaled(15, 0.5, 5);
        glutSolidCube(1);
        glColor3f(0, 0, 0);
    glPopMatrix();
}
