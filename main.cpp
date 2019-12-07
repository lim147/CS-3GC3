#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#  include <GL/freeglut.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <map>
//#include <windows.h> 
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#include "Ingredient.h"
#include "mathLib2D.h"
#include "PPM.h"
#include "Image.h"
#include "InteractionHandler.h"
#include "Handler.h"

//dictionary of ingredients
map<string, Ingredient> ll;

int scene = 0;

GLfloat eye[] = {8, 21, 10}; //z should be 10
GLfloat lookAt[] = { 0, 20, 0 };
GLfloat up[] = { 0, 1, 0 };

// For displaying text on screen
int w = 600;
int h = 600;
// int font=(int)GLUT_BITMAP_9_BY_15;
char s[30]; 
double t; 

Image selectRecipe; // Image with the recipes to choose from
Image instructions; // Image with the instructions of the game

/* 
//origin light

GLfloat ambient[2][4] = {
    { 0.2, 0.2, 0.2, 1 },
    {1 , 1, 1 , 1}
};
GLfloat diffuse[2][4] = {
    {0.8, 0.8, 0.8, 1 },
    {0,0,1,1}

};
GLfloat specular[2][4] = {
    { 0.5, 0.5, 0.5, 1 },
    {1,1,1,1}

};
*/

GLfloat ambient[2][4] = {
    { 1, 1, 1, 1 },
    {1 , 1, 1 , 1}
};
GLfloat diffuse[2][4] = {
    {1, 1, 1, 1 },
    {1,1,1,1}

};
GLfloat specular[2][4] = {
    { 1, 1, 1, 1 },
    {1,1,1,1}

};
GLfloat lightPos[2][4] = {
    { 20.0, 20.0, 20.0, 1.0 },
    { 20,20, -20,0}
};
//material0 is pearl 
//material1 is black plastic
GLfloat materialAmbient[2][4] = {
    { 0.25, 0.20725, 0.20725, 1.0}, 
    {0,0,0,1}
};
GLfloat materialDiffuse[2][4] = {
    { 1,   0.829 ,0.829 , 1.0 },
    {0.01,0.01,0.01}
};
GLfloat materialSpecular[2][4] = {
    { 0.296648,  0.296648,    0.296648 , 1.0 },
    {0.5,0.5,0.5}
};
GLfloat materialShiny[2] = {
    0.088,
    0.25
};

//GLfloat ambient[4] = { 0.2, 0.2, 0.2, 1 };
//GLfloat diffuse[4] = { 0.8, 0.8, 0.8, 1 };
//GLfloat specular[4] = { 1, 1, 1, 1 };
//GLfloat lightPos[4] = { 30, 30, 20, 1 };

// Array for generating the room ( There is no roof)
float verts[8][3] = {{-40, 0, 40}, //0
                    {-40, 40, 40}, //1
                    {40,40,40},    //2
                    {40, 0, 40},   //3
                    {-40,0,-40},   //4
                    {-40,40,-40},  //5
                    {40,40,-40},   //6
                    {40, 0,-40}};  //7
                    
int indices[3][4] = {
                    {1,5,4,0}, //leftface 
                    {5,6,7,4}, //rightface 
                    {0,4,7,3} //bottom face
                    };


GLubyte* tt[20];
GLuint textures[20];

int height[20];
int width[20];
int maximum[20];


//ray casting
double* m_start = new double[3];
double* m_end = new double[3];

/*
    0 - steak
    1 - mango
*/
bool pick[2] = {false, false};
float size[2] = {1.5, 1.5};
float pos[2][3] = {
    {-5, 15, -16},
    {-15, 15, -20}
}; 





void setMaterials(unsigned int index){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS , materialShiny[index]);
}


/**
 *  \brief Displays the room of the kitchen
 */
void drawFloor() // Floor of the room, change this to do the room
{
    glBindTexture(GL_TEXTURE_2D, textures[17]);
    //left wall
    glBegin(GL_POLYGON);
        setMaterials(0);
        glNormal3f(1, 0, 0);

        glTexCoord2f(0, 1);
        glVertex3fv(verts[1]);

        glTexCoord2f(1, 1);
        glVertex3fv(verts[5]);

        glTexCoord2f(1, 0);
        glVertex3fv(verts[4]);

        glTexCoord2f(0, 0);
        glVertex3fv(verts[0]);
    glEnd();



    glBindTexture(GL_TEXTURE_2D, textures[18]);
    //right wall
    glBegin(GL_POLYGON);
        setMaterials(0);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 1);
        glVertex3fv(verts[5]);

        glTexCoord2f(1, 1);
        glVertex3fv(verts[6]);

        glTexCoord2f(1, 0);
        glVertex3fv(verts[7]);

        glTexCoord2f(0, 0);
        glVertex3fv(verts[4]);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, textures[19]);
    //floor
    glBegin(GL_POLYGON);
        setMaterials(1);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3fv(verts[0]);

        glTexCoord2f(0, 1);
        glVertex3fv(verts[4]);

        glTexCoord2f(1, 1);
        glVertex3fv(verts[7]);

        glTexCoord2f(1, 0);
        glVertex3fv(verts[3]);
    glEnd();
    
    /*
    for(int idx = 0; idx < 3; idx++){
        glBegin(GL_POLYGON);
        setMaterials(0);
        for (int i = 0; i < 4; i++){
            if ( idx == 2){
                setMaterials(1);
            }
            vIndex = indices[idx][i];
            glVertex3fv(verts[vIndex]);
        }
        glEnd();
    }
    */
    
}


void loadIngredient(const char* filename, string name){
    Ingredient ingredient;
    ingredient = Ingredient();
    ingredient.loadObject(filename);
    /*
    cout << ingredient.vertexIndices.size() << endl;
    cout << ingredient.uvIndices.size() << endl;
    cout << ingredient.normalIndices.size() << endl;
    */
    ll[name] = ingredient;
}

/**
 *  \brief Sets the normals and builds the ingredient object based on mesh information
 *  \param name - identifier for particular ingredient object to be displayed
 */
void displayIngredient(string name){
    //display ingredient
    glPushMatrix();
        //glCullFace(GL_FRONT);
        glBegin(GL_TRIANGLES);
        int size = ll[name].vertexIndices.size();
        // Render each triangle
        for (int i = 0; i < size; i++) {
            //normal:
            Vec3D v = ll[name].temp_normals[ll[name].normalIndices[i]-1];
            glNormal3f(v.mX, v.mY, v.mZ);

            //texture:
            Point2D t = ll[name].temp_uvs[ll[name].uvIndices[i]-1];
            glTexCoord2f(t.mX, t.mY);
            //cout << t.mX << endl;

            //vertex:
            Point3D m = ll[name].temp_vertices[ll[name].vertexIndices[i]-1];
            glVertex3f(m.mX, m.mY, m.mZ);
            //cout << m.mX << endl;
        }

        glEnd();
    glPopMatrix();

}

/**
 *  \brief Loads object information from file
 */
void loadIngrts(){
    
    loadIngredient("obj/ktc_table/ktc_table.obj", "ktc_table");

    //fruit:
    loadIngredient("obj/banana/banana.obj", "banana");
    loadIngredient("obj/orange/orange.obj", "orange");
    loadIngredient("obj/mango/mango.obj", "mango");
    
    //vegetable:
    loadIngredient("obj/onion/onion.obj", "onion");
    loadIngredient("obj/potato/potato.obj", "potato");
    loadIngredient("obj/tomato/tomato.obj", "tomato");

    //meat
    loadIngredient("obj/steak/steak.obj", "steak");
    
    //tools
    loadIngredient("obj/pot/pot.obj", "pot");
    loadIngredient("obj/pan/pan.obj", "pan");
    loadIngredient("obj/knife/knife.obj", "knife");
    
    //cut ingredients:
    loadIngredient("obj/cutOnion/cutOnion.obj", "cutOnion");
    loadIngredient("obj/cutTomato/cutTomato.obj", "cutTomato");
    loadIngredient("obj/cutPotato/cutPotato.obj", "cutPotato");
    loadIngredient("obj/cutBanana/cutBanana.obj", "cutBanana");
    loadIngredient("obj/cutMango/cutMango.obj", "cutMango");

    //cooked beef
    loadIngredient("obj/cookedBeef/cookedBeef.obj", "cookedBeef");
}


/**
 *  \brief Displays ingredients needed for salad recipe
 */
void displaySaladIngrts(){
    //glTranslatef(-20, 15, -40);
     glPushMatrix();
        glTranslatef(-10, 15, 7); // z value larger moves it close to the camera
        glRotatef(90, 1, 0, 0); // rotating x will roll it towards you
        //glScalef(0.3, 0.3, 0.3); // rotating z will rotate counter clockwise on clock
        displayIngredient("knife");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(13, 15, 5);
        glScalef(0.5, 0.5, 0.5);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        displayIngredient("banana");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(15, 13, -3);
        glRotatef(-90, 1, 0, 0);
        //glScalef(0.3, 0.3, 0.3);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        displayIngredient("orange");
    glPopMatrix();
    
    glPushMatrix();
        //glTranslatef(8, 14, -2);
        glRotatef(90, 1, 0, 0);
        //glScalef(0.5, 0.5, 0.5);
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        displayIngredient("mango");
    glPopMatrix();

    
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[8]);
        displayIngredient("cutBanana");
    glPopMatrix();
    
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[9]);
        glTranslatef(0, 10, 0);
        displayIngredient("cutMango");
    glPopMatrix();
    
}

/**
 *  \brief Displays ingredients needed for curry recipe
 */
void displayCurryIngrts(){
    //glTranslatef(-20, 15, -40);
    glPushMatrix();
        glTranslatef(-12, 15, -1); // z value larger moves it close to the camera
        glScalef(0.3, 0.3, 0.3);
        glBindTexture(GL_TEXTURE_2D, textures[5]);
        displayIngredient("potato");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-8, 13, -1);
        glRotatef(-90, 1, 0, 0);
        //glScalef(0.2, 0.2, 0.2);
        glBindTexture(GL_TEXTURE_2D, textures[6]);
        displayIngredient("tomato");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-13, 15, 7); // z value larger moves it close to the camera
        glScalef(0.1, 0.1, 0.1);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        displayIngredient("onion");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10, 15, 7); // z value larger moves it close to the camera
        glRotatef(90, 1, 0, 0); // rotating x will roll it towards you
        glScalef(0.3, 0.3, 0.3); // rotating z will rotate counter clockwise on clock
        glBindTexture(GL_TEXTURE_2D, textures[15]);
        displayIngredient("knife");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2, 14, -1); // x value smaller moves to the left
        glScalef(0.2, 0.2, 0.2);
        glBindTexture(GL_TEXTURE_2D, textures[16]);
        displayIngredient("pot");
    glPopMatrix();

    glPushMatrix();
        glRotatef(30, 1, 0, 0);
        glBindTexture(GL_TEXTURE_2D, textures[10]);
        displayIngredient("cutOnion");
    glPopMatrix();
    

    glPushMatrix();
        glRotatef(30, 1, 0, 0);
        glBindTexture(GL_TEXTURE_2D, textures[12]);
        displayIngredient("cutTomato");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 10, 0);
        glScalef(0.2, 0.2, 0.2);
        glBindTexture(GL_TEXTURE_2D, textures[11]);
        displayIngredient("cutPotato");
    glPopMatrix();
}

/**
 *  \brief Displays ingredients needed for Steak recipe
 */
void displaySteakIngrts(){
    //glTranslatef(-20, 15, -40);
    glPushMatrix();
        glTranslatef(-3, 15, 7); // x value smaller moves to the left
        glRotatef(270, 1, 0, 0);
        glScalef(0.09, 0.09, 0.09);
        glBindTexture(GL_TEXTURE_2D, textures[14]);
        displayIngredient("pan");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(8, 14, 4);
        glRotatef(0, 1, 0, 0);
        glScalef(0.4, 0.4, 0.4);
        glBindTexture(GL_TEXTURE_2D, textures[7]);
        displayIngredient("steak");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10, 15, 7); // z value larger moves it close to the camera
        glRotatef(90, 1, 0, 0); // rotating x will roll it towards you
        glScalef(0.3, 0.3, 0.3); // rotating z will rotate counter clockwise on clock
        glBindTexture(GL_TEXTURE_2D, textures[15]);
        displayIngredient("knife");
    glPopMatrix();


    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[13]);
        displayIngredient("cookedBeef");
    glPopMatrix();

}

/**
 *  \brief Displays furniture in kitchen
 */
void displayFurniture(){
    glPushMatrix();
        glRotatef(45, 0, 1, 0);
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(40, 0, -60); //make x greater, z smaller
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        displayIngredient("ktc_table");
    glPopMatrix();
}

/**
 *  \brief Sets the orthographic properties needed for orthographic aspects on screen
 */
void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
    glPushMatrix();
        glLoadIdentity();
           gluOrtho2D(0, w, 0, h);
        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
        glMatrixMode(GL_MODELVIEW);

}

/**
 *  \brief Sets the perspective properties needed for perspective aspects on screen
 */
void setPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 *  \brief Resets perspective projection
 */
void resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

/**
 *  \brief Displays a string on screen
 *  \param x - x value of text
 *  \param y - y value of text
 *  \param *font - font pointer(?)
 *  \param string - The string to be displayed
 *  Referenced from https://www.programming-techniques.com/2012/05/font-rendering-in-glut-using-bitmap-fonts-with-sample-example.html
 */
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

/**
 *  \brief Displays Menu of Recipes
 */
void displayMenu(){
    glPushMatrix();
        glTranslatef(pos[0][0], pos[0][1], pos[0][2]);
        glScalef(0.4, 0.4, 0.4);
        if (pick[0])
            glColor3f(1,0,0);
        else
            glBindTexture(GL_TEXTURE_2D, textures[7]);
        displayIngredient("steak");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(pos[1][0], pos[1][1], pos[1][2]);
        //glRotatef(90, 1, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        if (pick[1])
            glColor3f(1,0,0);
        else
            glBindTexture(GL_TEXTURE_2D, textures[3]);
        displayIngredient("mango");
    glPopMatrix();

    glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
    glPushMatrix();
        glLoadIdentity();
           gluOrtho2D(0, w, 0, h);
        //glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);
        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
        glMatrixMode(GL_MODELVIEW);

    /*
    glPushMatrix();
    glLoadIdentity();
        renderBitmapString(20,60, (void*)GLUT_BITMAP_9_BY_15, s);
        //selectRecipe.draw(0, 0);
    glPopMatrix();
    */

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
    glDisable(GL_DEPTH_TEST); // Makes it so that it stays on screen even when the camera moves
    glLoadIdentity();
    glPushMatrix();
        
        //gluOrtho2D(0, w, 0, h); // Old Orthoview
        //glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0); // Setup an Ortho view
        glOrtho(0, w, 0, h, 0.0, 30.0); // Setup an Ortho view

        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
        glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 1.0, 1.0);
    /*
    glBegin(GL_QUADS); // In case we want to use a normal square instead
        glVertex2f(0,0); // Top left
        glVertex2f(0,300); // Bottom left (?)
        glVertex2f(300,300); // Bottom right(?)
        glVertex2f(300,0); // Top right
    glEnd();*/

    //selectRecipe.draw(560, 580, 0.25, 0.25);
    //instructions.draw(550, 430, 0.25, 0.25);

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

    //resetPerspectiveProjection();
    //setPerspectiveProjection();

    /* Trying to get the 3d steak on top of the 2d texture, but this doesn't work
    glPushMatrix();
        glTranslatef(pos[0][0], pos[0][1], pos[0][2]);
        glScalef(0.4, 0.4, 0.4);
            glBindTexture(GL_TEXTURE_2D, textures[7]);
        displayIngredient("steak");
    glPopMatrix();
    */
}

/**
 *  \brief Sets up the scene, and loads objects
 */
void draw3DScene(){

    for (unsigned int i = 0; i < 2; i++) {
            
        glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse[i]);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient[i]);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular[i]);
    }

    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]
    );
    
    //glColor3f(1,0,0);
    glPushMatrix();
        glTranslatef(-10, 0, -10);
        drawFloor();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(45, 0, 1, 0);
        displayFurniture();
    glPopMatrix();

    // Toggles ingredients to be displayed
    glPushMatrix();
        if (scene == 0)
            displayMenu();
        else if (scene == 1)
            displaySaladIngrts();
        else if (scene == 2)
            displayCurryIngrts();
        else if (scene == 3)
            displaySteakIngrts();
    glPopMatrix();
    
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
    setPerspectiveProjection();
    draw3DScene();

    // The following is for the onscreen timer
    setOrthographicProjection();
    glColor3d(1.0, 0.0, 1.0);;
    glPushMatrix();
        glLoadIdentity();
        renderBitmapString(20,40, (void*)GLUT_BITMAP_9_BY_15, s);
    glPopMatrix();
    resetPerspectiveProjection();

    glutSwapBuffers();
    glutPostRedisplay(); //force a redisplay, to keep the animation running
}

void handleReshape(int width, int height) {
    const float ar = (float) width / (float) height;
    w = width;
    h = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);     
    //gluPerspective(45, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    //
    glLoadIdentity() ;
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' or key == 27)
        exit(0);
    if (key == '1')
        scene = 1;
    if (key == '2')
        scene = 2;
    if (key == '3')
        scene = 3;
}


void makeSelectable(int i)
{
    double* R0 = new double[3];
    double* Rd = new double[3];

    double xDiff = m_end[0] - m_start[0];
    double yDiff = m_end[1] - m_start[1];
    double zDiff = m_end[2] - m_start[2];

    double mag = sqrt(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff);
    R0[0] = m_start[0];
    R0[1] = m_start[1];
    R0[2] = m_start[2];

    Rd[0] = xDiff / mag;
    Rd[1] = yDiff / mag;
    Rd[2] = zDiff / mag;
    

    double A = Rd[0] * Rd[0] + Rd[1] * Rd[1] + Rd[2] * Rd[2];
    double* R0Pc = new double[3];
    R0Pc[0] = R0[0] - pos[i][0];
    R0Pc[1] = R0[1] - pos[i][1];
    R0Pc[2] = R0[2] - pos[i][2];

    double B = 2 * ( R0Pc[0] * Rd[0] + R0Pc[1] * Rd[1] + R0Pc[2] * Rd[2]);
    double C = (R0Pc[0]*R0Pc[0] + R0Pc[1] * R0Pc[1] + R0Pc[2] * R0Pc[2])
                - (size[i] * size[i]);

    double discriminant = B*B - 4* A *C;

    if( discriminant < 0)
        printf("no intersection!\n");
    else{
        double t1 = (-B + sqrt(discriminant)) / (2*A);
        double t2 = (-B - sqrt(discriminant)) / (2*A);

        printf("Obj Intersection at t= %f, %f\n", t1, t2);

        pick[i] = !pick[i];
    }
}

// Mouse Handler for first press and first release
//mouse
void mouse(int btn, int state, int x, int y){
    if (btn == GLUT_LEFT_BUTTON){
        if (state == GLUT_UP){
        }

        if (state == GLUT_DOWN){

            printf("time for un projection!!!!\n");

            double matModelView[16], matProjection[16]; 
            int viewport[4]; 

            // get matrix and viewport:
            glGetDoublev( GL_MODELVIEW_MATRIX, matModelView ); 
            glGetDoublev( GL_PROJECTION_MATRIX, matProjection );
            
            //the x and y window coordinates of the viewport, followed by its width and height.
            glGetIntegerv( GL_VIEWPORT, viewport ); 

            // window pos of mouse, Y is inverted on Windows
            double winX = (double)x; 
            double winY = viewport[3] - (double)y; 

            // get point on the 'near' plane (third param is set to 0.0)
            gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
                    viewport, &m_start[0], &m_start[1], &m_start[2]); 

            // get point on the 'far' plane (third param is set to 1.0)
            gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
                    viewport, &m_end[0], &m_end[1], &m_end[2]); 

            // now you can create a ray from m_start to m_end
            printf("(%f,%f,%f)----(%f,%f,%f)\n\n", m_start[0], m_start[1], m_start[2], m_end[0], m_end[1], m_end[2]);
        

            //----------------------------------------
            // test steak - Ray intersection
            //----------------------------------------
            makeSelectable(0);


            //----------------------------------------
            // test mango - Ray intersection
            //----------------------------------------
            makeSelectable(1);

            
        }
    }
}

// Is called when you move your mouse
void passive (int x, int y){ 
    //std::cout << " mouseMotion coords2: ";
    //std:: cout << x << ", " << y << std::endl;
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP){ eye[1]++; }
    if (key == GLUT_KEY_DOWN){ eye[1]--; }
    if (key == GLUT_KEY_LEFT){ eye[0]++; }
    if (key == GLUT_KEY_RIGHT){ eye[0]--; }
}

//Idle function 
void idle(){
   //timer+=1;
}

// Callback function
void callBackInit(){

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(handleReshape);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passive);
    glutIdleFunc(idle);
    glutDisplayFunc(display); //registers "display" as the display callback function

    //initialize the values
    m_start[0] = 0;
    m_start[1] = 0;
    m_start[2] = 0;

    m_end[0] = 0;
    m_end[1] = 0;
    m_end[2] = 0;
}

/*
TO DO:
    1. knife, cutMango make use of 2 images for texture, but i only know how to apply one ppm...
        - Either search on line to figire out apply multiple texture on the same obj
        - Or combine 2 jpg(/png...) into one jpg(/png..). Could check ktc_table for example.
    2. Find new obj online: bowl(to make salad), spoon
*/

//load the ppm file in the given filename as the ith texture
void texture(const char* filename, int i)
{
    GLubyte* obj = LoadPPM(filename, &width[i], &height[i], &maximum[i]);
    tt[i] = obj;

    glBindTexture(GL_TEXTURE_2D, textures[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, tt[i]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}



void loadTextures()
{
    glMatrixMode(GL_TEXTURE);
    glScalef(-1,1,-1);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(20, textures);

    
    texture("obj/ktc_table/ktc_table.ppm", 0);

    texture("obj/banana/banana.ppm", 1);
    texture("obj/orange/orange.ppm", 2);
    texture("obj/mango/mango.ppm", 3);

    texture("obj/onion/onion.ppm", 4);
    texture("obj/potato/potato.ppm", 5);
    texture("obj/tomato/tomato.ppm", 6);

    texture("obj/steak/steak.ppm", 7);

    texture("obj/cutBanana/cutBanana.ppm", 8);
    texture("obj/cutMango/cutMango.ppm", 9);

    texture("obj/cutOnion/cutOnion.ppm", 10);
    texture("obj/cutPotato/cutPotato.ppm", 11);
    texture("obj/cutTomato/cutTomato.ppm", 12);
    texture("obj/cookedBeef/cookedBeef.ppm", 13);

    texture("obj/pan/pan.ppm", 14);
    texture("obj/knife/knife.ppm", 15);
    texture("obj/pot/pot.ppm", 16);

    texture("obj/room/wall.ppm", 17);
    texture("obj/room/shelves.ppm", 18);
    texture("obj/room/floor.ppm", 19);
}


void FPS(int val)
{
    t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    int time = (int)t;
    sprintf(s, "%2d", time);
    glutTimerFunc(1000, FPS, 0);
    glutPostRedisplay();
}

void init()
{
    selectRecipe.load("instructions1.ppm");
    instructions.load("instructions1.ppm");
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Prototype");
    glutReshapeFunc(handleReshape);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glutTimerFunc(0, FPS, 0);
    init();
    callBackInit();

    loadTextures();
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glEnable(GL_BLEND);
    loadIngrts();
    glutMainLoop();


    return 0;
}