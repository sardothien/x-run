#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"
#include "image.h"

static void on_display(void);
static void on_timer(int value);
static void on_reshape(int width, int height);
// static void on_special_key(int key, int x, int y);
static void on_release(unsigned char key, int x, int y);
static void on_keyboard(unsigned char key, int x, int y);

static int timer_active;
static int moves[] = {0, 0};

Level lvl = {
    .levelMatrix = NULL,
    .rowNumber = 0,
    .obstacleNumberInRow = 0,
    .viewDistance = 70
};

int main(int argc, char ** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("x-run");

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    // glutSpecialFunc(on_special_key);
    glutKeyboardUpFunc(on_release);
    
    time_parameter = 0;
    timer_active = 0;
    x = 0;
    z = 0;
    
    glClearColor(1, 1, 0.6, 0);
    glEnable(GL_DEPTH_TEST);

    /* Ucitavanje nivoa iz datoteke */
    lvl.levelMatrix = loadLevel("level.txt", &lvl.rowNumber, &lvl.obstacleNumberInRow);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: 
        case 'q':
        case 'Q':
            // quit/exit
            deallocLevel(lvl.levelMatrix, lvl.rowNumber);
            printf("Izašli ste iz igre.\n");
            exit(0);
            break;
        case 's':
        case 'S':
            // start game
            if(!timer_active){
                timer_active = 1;
                glutTimerFunc(50, on_timer, 0);
            }
            printf("start\n");
            break;
        case 'p':
        case 'P':
            // pause
            timer_active = 0;
            printf("pause\n");
            break;
        case 'r':
        case 'R':
            // restart
            glutPostRedisplay();
            printf("restart\n");
            break;
        case 'a':
        case 'A':
            // levo
            printf("left\n");
            moves[1] = 1;
            glutPostRedisplay();
            break;
        case 'd':
        case 'D':
            // desno
            printf("right\n");
            moves[0] = 1;
            glutPostRedisplay();
            break;
        // dodati i za space - pucanje
    }
}

// static void on_special_key(int key, int x, int y){
//     switch(key){
//         case GLUT_KEY_LEFT:
//             printf("right\n");
//             moves[1] = 1;
//             glutPostRedisplay();
//             break;
//         case GLUT_KEY_RIGHT:
//             printf("left\n");
//             moves[0] = 1;
//             glutPostRedisplay();
//             break;
//     }
// }

static void on_release(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
        moves[1] -= 1;
        break;
    case 'd':
    case 'D':
        moves[0] -= 1;
        break;
    }
}

static void on_reshape(int width, int height){
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
                   (float) width/height,
                   1, 1500);
}

static void on_timer(int value){
    
    if(value != 0)
        return;
    
    if(moves[0] && x < 3)
        x += 0.6;
    
    if(moves[1] && x > -3)
        x -= 0.6;
    
    z += 0.15;
    time_parameter++;

   glutPostRedisplay();
    
    if(timer_active)
        glutTimerFunc(50, on_timer, 0);
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, 1.5, 3-z, 
              x, 0, -3-z,
              0, 1, 0);

    //drawSystem();   
    drawFloor(2);

    drawObstacles(z, lvl.levelMatrix, lvl.rowNumber, lvl.obstacleNumberInRow, lvl.viewDistance, 3.0);
        
    glutSwapBuffers();
}