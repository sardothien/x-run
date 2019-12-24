#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "./headers/logic.h"
#include "./headers/scene.h"
#include "./headers/image.h"
#include "./headers/light.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 50

static void on_display(void);
static void on_timer(int value);
static void on_reshape(int width, int height);
static void on_release(unsigned char key, int x, int y);
static void on_keyboard(unsigned char key, int x, int y);

Level lvl = {
    .levelMatrix = NULL,
    .rowNumber = 0,
    .obstacleNumberInRow = 0,
    .viewDistance = 70,
    .backgroundID = 0
};

int main(int argc, char ** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("x-run");

    glutFullScreen();

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_release);

    initialize();
    initializeLight();
    initializeTextures();

    glClearColor(0, 0, 0, 0);
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
            // izlaz iz igre
            deallocLevel(lvl.levelMatrix, lvl.rowNumber);
            printf("Izašli ste iz igre.\n");
            exit(0);
            break;
        case 's':
        case 'S':
            // pocetak/nastavak igre
            if(!timer_active && z < lvl.rowNumber){
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                timer_active = 1;
            }
            printf("start\n");
            break;
        case 'p':
        case 'P':
            // pauziranje
            timer_active = 0;
            printf("pause\n");
            break;
        case 'r':
        case 'R': 
            // restart
            // TODO - nestaje metak
            initialize();
            glutPostRedisplay();
            printf("restart\n");
            break;
        case 'a':
        case 'A':
            // skretanje levo
            printf("left\n");
            moves[1] = 1;
            glutPostRedisplay();
            break;
        case 'd':
        case 'D':
            // skretanje desno
            printf("right\n");
            moves[0] = 1;
            glutPostRedisplay();
            break;
        case 32:
            // ubijanje neprijatelja
            printf("killed\n");
            if(timer_active){
                sword = 1;
            }
            break;
    }
}

static void on_release(unsigned char key, int x, int y){
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
    
    if(value != TIMER_ID)
        return;
    
    if(moves[0] && x <= 2.5){ // skrece desno
        x += 1.1;
    }
    
    if(moves[1] && x >= -2.5){ // skrece levo
        x -= 1.1;
    }

    if(x >= -3 && x <= -1.5)
        x_pom = 0;
    else if(x > -1.5 && x < 1.5)
        x_pom = 1;
    else if(x >= 1.5 && x <= 3)
        x_pom = 2;
    
    z += 0.2;

    if(z > lvl.rowNumber){
        timer_active = 0;
        printf("Presli ste igricu!!!");
    }
    
    time_parameter++;

    glutPostRedisplay();
    
    if(timer_active)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x*1.0, 1, 3, 
              x*1.0, 0, -3,
              0, 1, 0);

    //drawSystem();   

    drawSky(lvl.backgroundID);
    drawFloor(2);
    drawObstacles(z, lvl.levelMatrix, lvl.rowNumber, lvl.obstacleNumberInRow, lvl.viewDistance, 3.0);

    drawHearts();

    if(sword){
        drawSword();
    }

    if(hasCollision(lvl.levelMatrix, lvl.rowNumber)){
        timer_active = 0;
        printf("Izgubili ste. Pritisnite R za restart.\n");
        // dodati obradu da S vise ne radi
        // dodati ekran na kom pise Game Over ili slicno
    }
        
    glutSwapBuffers();
}