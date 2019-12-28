#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "./headers/logic.h"
#include "./headers/scene.h"
#include "./headers/image.h"
#include "./headers/light.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 50

/* Callback funkcije */
static void on_display(void);
static void on_timer(int value);
static void on_reshape(int width, int height);
static void on_release(unsigned char key, int x, int y);
static void on_keyboard(unsigned char key, int x, int y);

/* Inicijalizacija promenljivih unutar strukture za nivo */
Level lvl = {
    .levelMatrix = NULL,
    .rowNumber = 0,
    .obstacleNumberInRow = 0,
    .viewDistance = 70,
    .backgroundID = 0
};

int main(int argc, char ** argv){

    /* Inicijalizacija GLUT-a */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreiranje prozora */
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("x-run");

    /* Omogucavanje full screen-a pri pokretanju */
    glutFullScreen();

    /* Registrovanje callback funkcija */
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_release);

    /* Inicijalizacije */
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

static void on_reshape(int width, int height){
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
                   (float) width/height,
                   1, 1500);
}

static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: 
        case 'q':
        case 'Q':
            // izlaz iz igre
            exit(0);
            break;
        case 's':
        case 'S':
            // pocetak/nastavak igre
            if(!timer_active && z < lvl.rowNumber && lives != 0){
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                timer_active = 1;
            }
            break;
        case 'p':
        case 'P':
            // pauziranje
            timer_active = 0;
            paused = 1;
            break;
        case 'r':
        case 'R': 
            // restart
            initialize();
            glutPostRedisplay();
            break;
        case 'a':
        case 'A':
            // skretanje levo
            moves[1] = 1;
            glutPostRedisplay();
            break;
        case 'd':
        case 'D':
            // skretanje desno
            moves[0] = 1;
            glutPostRedisplay();
            break;
        case 32:
            // pokretanje maca
            if(timer_active){
                sword = 1;
            }
            break;
    }
}

static void on_release(unsigned char key, int x, int y){
    switch (key){
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

static void on_timer(int value){
    
    if(value != TIMER_ID)
        return;

    /* skretanje desno */
    if(moves[0] && x <= 2.5){ 
        x += 0.5;
    }

    /* skretanje levo */
    if(moves[1] && x >= -2.5){ 
        x -= 0.5;
    }

    /* Polozaj na stazi - levo, sredina ili desno */
    if(x >= -3 && x <= -1.5)
        x_pom = 0;
    else if(x > -1.5 && x < 1.5)
        x_pom = 1;
    else if(x >= 1.5 && x <= 3)
        x_pom = 2;
    
    z += 0.2;

    /* kraj igrice */
    if((int)z == lvl.rowNumber-7){
        timer_active = 0;
        won = 1;
    }
    
    time_parameter++;

    glutPostRedisplay();
    
    if(timer_active)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
    /* Postavljanje kamere */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x*1.0, 1, 3, 
              x*1.0, 0, -3,
              0, 1, 0);

    // drawSystem();   

    /* Postavljanje teksture pozadine */
    drawBackground(lvl.backgroundID);

    /* Iscrtavanje staze */
    drawFloor(2);

    printf("%.1f\n", z);

    /* Postavljanje prepreka na stazu */
    drawObstacles(z, lvl.levelMatrix, lvl.rowNumber, lvl.obstacleNumberInRow, lvl.viewDistance, 3.0);

    /* Postavljanje zivota */
    drawHearts();

    /* Ako smo aktivirali mac, iscrtava se */
    if(sword){
        drawSword();
    }

    /* Ako je igra pauzirana ispisuje se tekst */
    if(!timer_active && paused){
        gamePaused();
        paused = 0;
    }

    /* Provera da li je doslo do kolizije */
    if(hasCollision(lvl.levelMatrix, lvl.rowNumber)){
        // zaustavlja se igra
        timer_active = 0;
        // ispisuje se tekst
        gameOver();
    }

    /* Ako smo dosli do kraja staze, ispisuje se tekst */
    if(won){
        gameWon();
    }
        
    glutSwapBuffers();
}