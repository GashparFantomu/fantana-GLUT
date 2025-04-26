#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")  
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glui32.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#include "glos.h"
#include <glut.h>
#include <gl.h>
#include <glu.h>
#include <glaux.h>

GLfloat eye_x = 3.0, eye_y = 3.0, eye_z = 6.0, center_x = 0.0, center_y = 0.0, center_z = 0.0;

void initScene() {
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_LIGHTING);   
    glEnable(GL_LIGHT0);     

    
    glClearColor(0.2, 0.4, 0.6, 1.0);

    // poziția luminii
    GLfloat light_pos[] = { 2.0, 5.0, 5.0, 1.0 }; // x, y, z, w
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void camera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye_x, eye_y, eye_z,   // ochiul (camera)
        center_x, center_y, center_z,   // punctul spre care privește
        0.0, 1.0, 0.0    //orientarea
    );
}

void moveCameraPoint(int arrowKey, int x, int y) {
    switch (arrowKey) {
    case GLUT_KEY_RIGHT:
        center_x -= 0.1;
        break;
    case GLUT_KEY_LEFT:
        center_x += 0.1;
        break;
    case GLUT_KEY_UP:
        center_y += 0.1;
        break;
    case GLUT_KEY_DOWN:
        center_y -= 0.1;
        break;
    case GLUT_KEY_PAGE_UP:
        center_z += 0.1;
        break;
    case GLUT_KEY_PAGE_DOWN:
        center_z -= 0.1;
        break;

    }
    glutPostRedisplay();
}

void sun() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(2.0, 5.0, 5.0);
    glColor3f(1.0, 9.0, 0.0);
    glutSolidSphere(0.1, 16, 16);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void MoveCamera(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        eye_x += 0.1;
        break;
    case 'd':
        eye_x -= 0.1;
        break;
    case 'w':
        eye_y += 0.1;
        break;
    case 's':
        eye_y -= 0.1;
        break;
    case 'z':
        eye_z += 0.1;
        break;
    case 'x':
        eye_z -= 0.1;
        break;
    }
    glutPostRedisplay();
}

void drawGround() {
    glDisable(GL_LIGHTING);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(-5.0, 0.0, 5.0);
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glEnd();
    glEnable(GL_LIGHTING);

}

void coordinates() {
    GLUquadric* coordinates = gluNewQuadric();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(5.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    gluSphere(coordinates, 0.1, 16.0, 16.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 5.0);
    gluSphere(coordinates, 0.1, 16.0, 16.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -5.0);
    glutSolidCube(0.2);
    glPopMatrix();

    glEnable(GL_LIGHTING);
    gluDeleteQuadric(coordinates);
}
//void roof_debug() {
//    glDisable(GL_LIGHTING);
//    glColor3f(1.0, 0.0, 0.0); // roșu pentru contur
//    glBegin(GL_LINE_LOOP); // doar linia care unește punctele
//    glVertex3f(0.0, 2.5, -1.2);
//    glVertex3f(-1.0, 2.1, -1.2);
//    glVertex3f(-1.0, 2.1, 1.2);
//    glVertex3f(0.0, 2.5, 1.2);
//    glEnd();
//
//    glColor3f(0.0, 0.0, 1.0); // albastru pentru al doilea contur
//    glBegin(GL_LINE_LOOP);
//    glVertex3f(0.0, 2.5, -1.2);
//
//    glVertex3f(1.0, 2.1, -1.2);
//    glVertex3f(0.0, 2.5, 1.2);
//    glVertex3f(1.0, 2.1, 1.2);
//    glEnd();
//    glEnable(GL_LIGHTING);
//}

void roof() {
    glBegin(GL_QUADS); //platforma 1
    glVertex3f(0.0, 2.5, -1.2);
    glVertex3f(-1.0, 2.1, -1.2);
    glVertex3f(-1.0, 2.1, 1.2); 
    glVertex3f(0.0, 2.5, 1.2);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0, 2.5, -1.2);
    glVertex3f(0.0, 2.5, 1.2);
    glVertex3f(1.0, 2.1, 1.2);
    glVertex3f(1.0, 2.1, -1.2);
    glEnd();

}

void barBucketWell() {
    GLUquadric* bucketBar = gluNewQuadric();
    glPushMatrix();

    glPushMatrix();
    glTranslatef(0.0, 2.0, -1.05);
    gluCylinder(bucketBar, 0.03, 0.03, 2.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 2.0, -0.55);
    gluCylinder(bucketBar, 0.1, 0.1, 1.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 2.0, 0.55);
    gluDisk(bucketBar, 0, 0.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 2.0, -0.55);
    gluDisk(bucketBar, 0, 0.1, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

void barWellLeft() {
    GLUquadric* bar = gluNewQuadric();

    glPushMatrix();

    glTranslatef(0.0, 1.0, 1.05);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(bar, 0.05, 0.05, 1.5, 5.0, 5.0);

    glPopMatrix();

    gluDeleteQuadric(bar);
}

void barWellRight() {
    GLUquadric* bar = gluNewQuadric();

    glPushMatrix();

    glTranslatef(0.0, 1.0, -1.05);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(bar, 0.05, 0.05, 1.5, 5.0, 5.0);

    glPopMatrix();

    gluDeleteQuadric(bar);
}

void topRingWell() {
    GLUquadric* top = gluNewQuadric();

    glPushMatrix();

    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    
    gluDisk(top, 1.0, 1.1, 32, 32);

    glPopMatrix();
    gluDeleteQuadric(top);

}

void baseWell() {
    GLUquadric* cilindru = gluNewQuadric();

    glPushMatrix();

    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(cilindru, 1.0, 1.0, 1.0, 32, 32);
    
    
    glPopMatrix();


    glPushMatrix();

    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(cilindru, 1.1, 1.1, 1.0, 32, 32);
    
    
    glPopMatrix();
    gluDeleteQuadric(cilindru);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera();
    sun();
    coordinates();

    drawGround();
    baseWell();
    topRingWell();
    barWellLeft();
    barWellRight();
    roof(); //revenim la acoperis mai tarziu
    barBucketWell();

    glutSwapBuffers();
}


void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 600);
    glutCreateWindow("Fantana - Proiect OpenGL");

    initScene();

    glutKeyboardFunc(MoveCamera);
    glutSpecialFunc(moveCameraPoint);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
