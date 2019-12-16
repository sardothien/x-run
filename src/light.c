#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "scene.h"
#include "image.h"
#include "light.h"

// #define FILENAME0 "cerebro.bmp"
// #define FILENAME1 "brick.bmp"

extern Level lvl;

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

    // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    glEnable(GL_COLOR_MATERIAL);
}

void floorLight(){

    // GLfloat ambient_coeffs[] = {0.5, 0.5, 0.5, 1 };
    // GLfloat diffuse_coeffs[] = {0.9, 0.9, 0.9, 1};
    // GLfloat specular_coeffs[] = {06, 0.6, 0.6, 1 };
    
    // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glColor3f(0.7, 0.5, 0.5);
}

void enemyLight(int part){

    switch(part){
        case 1: { // glava
            // GLfloat ambient_coeffs[] = {0.8, 0, 0, 1};
            // GLfloat diffuse_coeffs[] = {0.7, 0.1, 0.3, 1};
            // GLfloat specular_coeffs[] = {0.8, 0, 0, 1};
            
            // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            glColor3f(0.8, 0, 0);
            break;
        }
        case 2: { // lice
            
            // GLfloat ambient_coeffs[] = {0.95, 0.95, 0, 1};
            // GLfloat diffuse_coeffs[] = {0.95, 0.95, 0, 1};
            // GLfloat specular_coeffs[] = {0.8, 0.8, 0, 1};

            // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            glColor3f(1, 1, 0.2);
            break;
        }
        case 3: { // obrve i usta
        //     GLfloat ambient_coeffs[] = {0, 0, 0, 1};
        //     GLfloat diffuse_coeffs[] = {0, 0, 0, 1};
        //     GLfloat specular_coeffs[] = {0, 0, 0, 1};
            
        //     glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
        //     glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
        //     glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
            glColor3f(0, 0, 0);
            break;
        }
        case 4: { // oci
            // GLfloat ambient_coeffs[] = {1, 0, 0, 1};
            // GLfloat diffuse_coeffs[] = {1, 0, 0, 1};
            // GLfloat specular_coeffs[] = {0.4, 0, 0, 1};
            
            // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
            // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
            // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);

            glColor3f(1, 0, 0);
            break;
        }
    }
}

void cubeLight(){

    // GLfloat ambient_coeffs[] = {0, 1.0, 0, 1 };
    // GLfloat diffuse_coeffs[] = {0.3, 0.9, 0.4, 1};
    // GLfloat specular_coeffs[] = {0, 0.6, 0, 1 };
    
    // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);

    glColor3f(0, 0.7, 0.2);
}

void healLight(){
    
    // GLfloat ambient_coeffs[] = {1.0, 0, 0, 1 };
    // GLfloat diffuse_coeffs[] = {1.0, 0.4, 0.7, 1 };
    // GLfloat specular_coeffs[] = {1, 0, 0, 1 };
    
    // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);

    glColor3f(0.8, 0, 0);
}

void heartLight(){
    // GLfloat ambient_coeffs[] = {1.0, 0, 0, 1 };
    // GLfloat diffuse_coeffs[] = {1.0, 0, 0, 1 };
    // GLfloat specular_coeffs[] = {1, 0, 0, 1 };
    
    // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);

    glColor3f(0.8, 0, 0);
}

void initializeTextures(){
   
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    /* Uvitavnje teksture za pozadinu */
    Image* background = image_init(1024, 1024);
    image_read(background, "cerebro.bmp");
    lvl.backgroundID = backgroundTexture(background);
    image_done(background);
}

unsigned backgroundTexture(Image* img){
    glEnable(GL_TEXTURE_2D);

    GLuint textures;
    glGenTextures(1, &textures);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, textures);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                img->width, img->height, 0,
                GL_RGB, GL_UNSIGNED_BYTE, img->pixels);

    glDisable(GL_TEXTURE_2D);

    return textures;
}