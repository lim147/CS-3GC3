#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "Ingredient.h"
using namespace std;


/**
Current Tasks:
Rachel - Onion, Tomato, Pot
May - Pan, Fire, Mango
Lily - Knife, Potato, Steak
Alice - Main file (Table, floor , wall, stove), Banana

Other Tasks to be Done for Prototype:
- Brief two paragraph write up including features needed to be added or fixed for the final implementation as well as a list
of commands available for the prototype - Alice made the skeleton for this file in our repo under the documents folder, 
Our prototype and this writeup will need to be submitted to one of our course git repositories, under the project folder

- We need a file that parses *.obj files and "mesh drawings"(?)

- Ingrediant class:
- Position of object
- Whether or not the object is selected
- Pointer to appropriate object mesh
- Texture for object
- Status ( is the object cut or inside the pan)
- "You may want to have an array of loaded meshes depending on the state (i.e., a cut tomato will load a different mesh than a whole tomato)"

- Rough prepping room
- Place the prepping room items into the 3D room
- To make this room, we can either use assets that we load in using the obj loader, or we can use glut primitives

Our Recipes So Far:
- Soup - potato, tomato, onion, salt, Knife, Pot
- Salad - Mango, banana, sugar, Knife, Bowl
- Steak - Steak, bbq sauce, Knife, Pan

Tools Required:
- Knife, Pot, Pan
*/

GLdouble eye[] = {30, 30, 30};
GLdouble lookAt[] = { 0, 0, 0 };
GLdouble up[] = { 0, 1, 0 };


//Floor size

void drawFloor()
{
    // Floor of the fountain
    glBegin(GL_QUADS);
    glNormal3f(0,10,0);
    glColor3f(0.5, 0.5, 0.5);

    glVertex3f(-10,0,10);
    glVertex3f(10,0,10);
    glVertex3f(10,0,-10);
    glVertex3f(-10,0,-10);

    glEnd();
}

void draw3DScene(){
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]
    );
    
    glPushMatrix();
    glColor3f(1,0,0);
    drawFloor();

    glPopMatrix();

}

/* display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
void display()
{

    draw3DScene();
    glutSwapBuffers();
    //force a redisplay, to keep the animation running
    glutPostRedisplay();
}



void handleReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' or key == 27)
		exit(0);
}


void FPS(int val)
{
	glutPostRedisplay(); //registers "display" as the display callback function
	glutTimerFunc(10, FPS, 0); //1sec = 1000, 60fps = 1000/60 = ~17
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP){}
    if (key == GLUT_KEY_DOWN){}
    if (key == GLUT_KEY_LEFT){}
    if (key == GLUT_KEY_RIGHT){}
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Prototype");

    glutTimerFunc(0, FPS, 0);
    glutReshapeFunc(handleReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);

    glutMainLoop();

    return 0;
}