#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "scene.h"
#include "image.h"
#include "light.h"

void initializeLight(){
    GLfloat light_position[] = { 1, 1, 1, 0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1};
    GLfloat light_specular[] = {0.1, 0.1, 0.1, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void floorLight(){

    GLfloat ambient_coeffs[] = {0.5, 0.5, 0.5, 1 };
    GLfloat diffuse_coeffs[] = {0.9, 0.9, 0.9, 1};
    GLfloat specular_coeffs[] = {06, 0.6, 0.6, 1 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
}

void enemyLight(int part){

    switch(part){
        case 1: { // glava
            GLfloat ambient_coeffs[] = {0.8, 0, 0, 1};
            GLfloat diffuse_coeffs[] = {0.7, 0.1, 0.3, 1};
            GLfloat specular_coeffs[] = {0.8, 0, 0, 1};
            
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            break;
        }
        case 2: { // lice
            
            GLfloat ambient_coeffs[] = {0.95, 0.95, 0, 1};
            GLfloat diffuse_coeffs[] = {0.95, 0.95, 0, 1};
            GLfloat specular_coeffs[] = {0.8, 0.8, 0, 1};

            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            break;
        }
        case 3: { // obrve i usta
            GLfloat ambient_coeffs[] = {0, 0, 0, 1};
            GLfloat diffuse_coeffs[] = {0, 0, 0, 1};
            GLfloat specular_coeffs[] = {0, 0, 0, 1};
            
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            break;
        }
        case 4: { // oci
            GLfloat ambient_coeffs[] = {1, 0, 0, 1};
            GLfloat diffuse_coeffs[] = {1, 0, 0, 1};
            GLfloat specular_coeffs[] = {0.4, 0, 0, 1};
            
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            break;
        }
    }
}

void cubeLight(){

    GLfloat ambient_coeffs[] = {0, 1.0, 0, 1 };
    GLfloat diffuse_coeffs[] = {0.3, 0.9, 0.4, 1};
    GLfloat specular_coeffs[] = {0, 0.6, 0, 1 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
}

void healLight(){
    
    GLfloat ambient_coeffs[] = {1.0, 0, 0, 1 };
    GLfloat diffuse_coeffs[] = {1.0, 0.4, 0.7, 1 };
    GLfloat specular_coeffs[] = {1, 0, 0, 1 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
}

void heartLight(){
    GLfloat ambient_coeffs[] = {1.0, 0, 0, 1 };
    GLfloat diffuse_coeffs[] = {1.0, 0, 0, 1 };
    GLfloat specular_coeffs[] = {1, 0, 0, 1 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
}