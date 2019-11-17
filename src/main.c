#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);

void drawSystem();

int main(int argc, char ** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("x-run");

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    glClearColor(1, 1, 0.6, 0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: 
            printf("Izašli ste iz igre.\n");
            exit(0);
            break;
        case 's':
        case 'S':
            // start game
            printf("start\n");
            break;
        case 'p':
        case 'P':
            // pause
            printf("pause\n");
            break;
        case 'r':
        case 'R':
            // restart
            printf("restart\n");
            break;
    }
}

static void on_reshape(int width, int height){
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
                   (float) width/height,
                   1, 100);
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 5, 0.3, 
              0, 0, 0,
              0, 1, 0);

    drawSystem();   
    drawFloor();
    
    glutSwapBuffers();
}


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
