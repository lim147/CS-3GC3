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
using namespace std;

GLdouble eye[] = {5, 5, 10};
GLdouble lookAt[] = { 0, 3, 0 };
GLdouble up[] = { 0, 1, 0 };

void display(void)
{

    /** for (unsigned int i = 0; i < 2; i++) {
        glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse[i]);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient[i]);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular[i]);
    }*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]
    );

    glutSwapBuffers();

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
	//'q' or esc
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