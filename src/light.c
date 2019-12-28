#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./headers/logic.h"
#include "./headers/scene.h"
#include "./headers/image.h"
#include "./headers/light.h"

extern Level lvl;

/* Inicijalizacija osvetljenja */
void initializeLight(){
    GLfloat light_position[] = {1, 1, 1, 0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1};
    GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat light_specular[] = {0.1, 0.1, 0.1, 1};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
}

/* Osvetljenje kod objekta enemy ukoliko nije ubijen */
void enemyLight(int part){

    switch(part){
        case 1: { // glava
            glColor3f(0.8, 0, 0);
            break;
        }
        case 2: { // lice
            glColor3f(1, 1, 0.2);
            break;
        }
        case 3: { // obrve i usta
            glColor3f(0, 0, 0);
            break;
        }
        case 4: { // oci
            glColor3f(1, 0, 0);
            break;
        }
    }
}

/* Osvetljenje raznih objekata na sceni */
void elementsLight(int part){
    switch (part){
        case 1: // osvetljenje/boja poda
            glColor3f(0.7, 0.5, 0.5);
            break;
        case 2: // osvetljenje/boja prepreke
            glColor3f(0.4, 0.4, 0.6);
            break;
        case 3: // osvetljenje/boja objekta heal
            glColor3f(0.8, 0, 0);
            break;
        case 4: // osvetljenje/boja srca
            glColor3f(0.8, 0.2, 0);
            break;
    }
}

/* Inicijalizacija tekstura */
void initializeTextures(){
   
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    /* Ucitavnje teksture za pozadinu */
    Image* background = image_init(1024, 1024);
    image_read(background, "cerebro.bmp");
    lvl.backgroundID = backgroundTexture(background);
    image_done(background);
}

/* Postavljanje teksture za pozadinu */
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
