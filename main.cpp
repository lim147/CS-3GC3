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
#include "mathLib2D.h"

using namespace std;
#include <vector>
#include <math.h>

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

vector<Ingredient> ll;

GLdouble eye[] = {30, 30, 30};
GLdouble lookAt[] = { 0, 0, 0 };
GLdouble up[] = { 0, 1, 0 };

GLfloat ambient[4] = { 0.1, 0.1, 0.1, 1 };
GLfloat diffuse[4] = { 1, 1, 1, 1 };
GLfloat specular[4] = { 1, 1, 1, 1 };
GLfloat lightPos[4] = { 30, 30, 20, 1 };

// Array for generating the room ( There is no roof)
float verts[8][3] = {{-10, -10, 10},
                    {-10, 10, 10},
                    {10,10,10},
                    {10, -10, 10},
                    {-10,-10,-10},
                    {-10,10,-10},
                    {10,10,-10},
                    {10,-10,-10}};

int indices[5][4] = {
                    {1,5,4,0},
                    {5,6,7,4},
                    {2,6,7,3},
                    {0,4,7,3},
                    {1,0,3,2}};




void drawFloor() // Floor of the room, change this to do the room
{
    glBegin(GL_QUADS);
    //glNormal3f(0,10,0);
    glColor3f(1, 1, 1);

    //glVertex3f(-10,0,10);
    //glVertex3f(10,0,10);
    //glVertex3f(10,0,-10);
    //glVertex3f(-10,0,-10);

    glEnd();
    int vIndex;

    for(int idx = 0; idx < 6; idx++){
		    glBegin(GL_POLYGON);
		    for (int i = 0; i < 4; i++){
		        vIndex = indices[idx][i];
		        glVertex3fv(verts[vIndex]);
		    }
		    glEnd();
    }
}

// Ingredient information should only need to be loaded once
void loadIngredient(const char* filename){
	Ingredient ingredient;
	ingredient = Ingredient();
	ingredient.loadObject(filename);
    /*
    cout << ingredient.vertexIndices.size() << endl;
    cout << ingredient.uvIndices.size() << endl;
    cout << ingredient.normalIndices.size() << endl;
    */
    ll.push_back(ingredient);
}



void displayIngredient(int index){
    //display ingredient
    glPushMatrix();
        //glCullFace(GL_FRONT);
        glBegin(GL_TRIANGLES);
        int size = ll[index].vertexIndices.size();
        // Render each triangle
        for (int i = 0; i < size; i++) {
            //normal:
            Vec3D v = ll[index].temp_normals[ll[index].normalIndices[i]];
            glNormal3f(v.mX, v.mY, v.mZ);
    
            //texture:
            Point2D t = ll[index].temp_uvs[ll[index].uvIndices[i]];
            glTexCoord2f(t.mX, t.mY);
            cout << t.mX << endl;

            //vertex:
            Point3D m = ll[index].temp_vertices[ll[index].vertexIndices[i]];
            glVertex3f(m.mX, m.mY, m.mZ);
            //cout << m.mX << endl;
        }

        glEnd();
    glPopMatrix();

}


void loadIngrts(){
    //loadIngredient("obj/banana/banana.obj");
    //loadIngredient("obj/orange/orange.obj");
    loadIngredient("obj/ktc_table/ktc_table.obj");
}


void displayIngrts(){
    for (int index = 0; index < ll.size(); index++)
    {

        glScalef(0.4, 0.4, 0.4);
        //glRotatef(180, 0, 1, 0);
        displayIngredient(index);
    }
}

void draw3DScene(){
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]
    );
    
    glPushMatrix();
    glColor3f(1,0,0);
    
    //drawFloor();
    displayIngrts();

    glPopMatrix();

}

void display()
{
    draw3DScene();
    glutSwapBuffers();
    glutPostRedisplay(); //force a redisplay, to keep the animation running
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glutTimerFunc(0, FPS, 0);
    glutReshapeFunc(handleReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    loadIngrts();
    glutMainLoop();

    return 0;
}