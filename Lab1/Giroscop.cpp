
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaJos(void);
void CALLBACK MutaSus(void);
void CALLBACK Cam1(void);
void CALLBACK Cam2(void);
GLUquadric* cylinder;

static GLfloat x = 0;
static GLfloat y = 0;

static GLfloat camX = 0;
static GLfloat camY = 0;
static GLfloat r = 0;
void myinit(void) {
    cylinder = gluNewQuadric();
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}


void CALLBACK MutaStanga(void)
{
    x = x - 10;
}


void CALLBACK MutaDreapta(void)
{
    x = x + 10;
}

void CALLBACK Cam1(void) {
    camX += 5;
}

void CALLBACK Cam2(void) {
    camX -= 5;
}

void CALLBACK Cam3(void) {
    camY += 5;
}

void CALLBACK Cam4(void) {
    camY -= 5;
}

void CALLBACK Rot1(void) {
    r += 10;
}

void CALLBACK Rot2(void) {
    r -= 10;
}

void CALLBACK MutaJos(void)
{
    y = y - 10;
}

void CALLBACK MutaSus(void)
{
    y = y + 10;
}

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(camX, camY, 100, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(0, -200, -100);


    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(0, 100, -10);

    glRotatef(90, 0, 0, 1);
    glRotatef(x, x, 0, 0);
    glRotatef(y, 0, y, 0);
    auxSolidBox(200, 200, 25);

    
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(0, 0, 600);
    gluDisk(cylinder, 0, 50, 300, 100);
    glPopMatrix();
    
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(0, 0, 600);
    glRotatef(90, 1, 0, 0);
    auxSolidCylinder(50, 600);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 300, 0);
    glColor3f(1, 1, 1);
    glTranslatef(10, -11, 0);
    glRotatef(r, 0, 1, 0);
    auxSolidBox(650, 20, 100);


    glColor3f(1, 1, 1);
    glTranslatef(-2, -11, 0);
    glRotatef(90, 0, 1, 0);
    

    auxSolidBox(650, 20, 100);
    glRotatef(90, 1, 0, 0);
    gluDisk(cylinder, 300, 400, 300, 200);
    glPopMatrix();
    glPopMatrix();

    glFlush();
}



void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2020.0, 2020.0, 2020.0 * (GLfloat)h / (GLfloat)w,
            -2020.0 * (GLfloat)h / (GLfloat)w, -2050.0, 2050.0);
    else
        glOrtho(-2020.0 * (GLfloat)w / (GLfloat)h,
            2020.0 * (GLfloat)w / (GLfloat)h, -2200.0, 2020.0, -2050.0, 2050.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
    auxInitPosition(0, 0, 1000, 1000);
    auxInitWindow("Un Giroscop");
    myinit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_q, Rot1);
    auxKeyFunc(AUX_e, Rot2);
    auxKeyFunc(AUX_w, Cam1);
    auxKeyFunc(AUX_s, Cam2);
    auxKeyFunc(AUX_d, Cam3);
    auxKeyFunc(AUX_a, Cam4);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}