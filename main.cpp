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
#include <map>

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

//dictionary of ingredients
map<string, Ingredient> ll;

int scene = 1;

GLfloat eye[] = {30, 30, 30};
GLfloat lookAt[] = { 0, 0, 0 };
GLfloat up[] = { 0, 1, 0 };

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


//Timer
int timer = 0;

//GLfloat ambient[4] = { 0.2, 0.2, 0.2, 1 };
//GLfloat diffuse[4] = { 0.8, 0.8, 0.8, 1 };
//GLfloat specular[4] = { 1, 1, 1, 1 };
//GLfloat lightPos[4] = { 30, 30, 20, 1 };



// Array for generating the room ( There is no roof)
float verts[8][3] = {{-10, 0, 10},
                    {-10, 20, 10},
                    {10,20,10},
                    {10, 0, 10},
                    {-10,0,-10},
                    {-10,20,-10},
                    {10,20,-10},
                    {10, 0,-10}};
                    
int indices[3][4] = {
                    {1,5,4,0}, //leftface 
                    {5,6,7,4}, //rightface 
                    //{2,6,7,3},
                    {0,4,7,3}, //bottom face
                    //{1,0,3,2}
                    };



void setMaterials(unsigned int index){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS , materialShiny[index]);
}


/* LoadPPM -- loads the specified ppm file, and returns the image data as a GLubyte
 *  (unsigned byte) array. Also returns the width and height of the image, and the
 *  maximum colour value by way of arguments
 *  usage: GLubyte myImg = LoadPPM("myImg.ppm", &width, &height, &max);
 */
GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
{
    GLubyte* img;
    FILE *fd;
    int n, m;
    int  k, nm;
    char c;
    int i;
    char b[100];
    float s;
    int red, green, blue;
    
    fd = fopen(file, "r");
    fscanf(fd,"%[^\n] ",b);
    if(b[0]!='P'|| b[1] != '3')
    {
        printf("%s is not a PPM file!\n",file);
        exit(0);
    }
    printf("%s is a PPM file\n", file);
    fscanf(fd, "%c",&c);
    while(c == '#')
    {
        fscanf(fd, "%[^\n] ", b);
        printf("%s\n",b);
        fscanf(fd, "%c",&c);
    }
    ungetc(c,fd);
    fscanf(fd, "%d %d %d", &n, &m, &k);
    
    printf("%d rows  %d columns  max value= %d\n",n,m,k);
    
    nm = n*m;
    
    img = (GLubyte*)(malloc(3*sizeof(GLuint)*nm));
    
    s=255.0/k;
    
    
    for(i=0;i<nm;i++)
    {
        fscanf(fd,"%d %d %d",&red, &green, &blue );
        img[3*nm-3*i-3]=red*s;
        img[3*nm-3*i-2]=green*s;
        img[3*nm-3*i-1]=blue*s;
    }
    
    *width = n;
    *height = m;
    *max = k;
    
    return img;
}


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
}

// Ingredient information should only need to be loaded once
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


void loadIngrts(){
    /*
    loadIngredient("obj/ktc_table/ktc_table.obj", "ktc_table");

    
    //fruit:
    loadIngredient("obj/banana/banana.obj", "banana");
    loadIngredient("obj/orange/orange.obj", "orange");
    loadIngredient("obj/mango/mango.obj", "mango");
    


    //vegetable:
    //loadIngredient("obj/onion/onion.obj", "onion");  //huge file, significantly slow down the system
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
    */
    

    //loadIngredient("obj/orange/orange.obj", "orange");
    //loadIngredient("obj/ktc_table/ktc_table.obj", "ktc_table");
    //loadIngredient("obj/banana/banana.obj", "banana");
    //loadIngredient("obj/mango/mango.obj", "mango");

    //loadIngredient("obj/onion/onion.obj", "onion");
    //loadIngredient("obj/potato/potato.obj", "potato");
    //loadIngredient("obj/tomato/tomato.obj", "tomato");

    //loadIngredient("obj/steak/steak.obj", "steak");

    //loadIngredient("obj/cutBanana/cutBanana.obj", "cutBanana");
    //loadIngredient("obj/cutOnion/cutOnion.obj", "cutOnion");
    //loadIngredient("obj/cutTomato/cutTomato.obj", "cutTomato");
    loadIngredient("obj/cutPotato/cutPotato.obj", "cutPotato");
    //loadIngredient("obj/cookedBeef/cookedBeef.obj", "cookedBeef");

    //loadIngredient("obj/pan/pan.obj", "pan");
    //loadIngredient("obj/knife/knife.obj", "knife");
    //loadIngredient("obj/pot/pot.obj", "pot");
}



void displaySaladIngrts(){
    
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        displayIngredient("ktc_table");
    glPopMatrix();

     glPushMatrix();
        glTranslatef(-10, 15, 7); // z value larger moves it close to the camera
        glRotatef(90, 1, 0, 0); // rotating x will roll it towards you
        //glScalef(0.3, 0.3, 0.3); // rotating z will rotate counter clockwise on clock
        displayIngredient("knife");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(13, 15, 5);
        glScalef(0.5, 0.5, 0.5);
        displayIngredient("banana");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(15, 13, -3);
        glRotatef(-90, 1, 0, 0);
        //glScalef(0.3, 0.3, 0.3);
        displayIngredient("orange");
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(8, 14, -2);
        glRotatef(90, 1, 0, 0);
        //glScalef(0.5, 0.5, 0.5);
        displayIngredient("mango");
    glPopMatrix();


    glPushMatrix();
        displayIngredient("cutBanana");
    glPopMatrix();


    glPushMatrix();
        glRotatef(30, 1, 0, 0);
        displayIngredient("cutOnion");
    glPopMatrix();
    

    glPushMatrix();
        glRotatef(30, 1, 0, 0);
        displayIngredient("cutTomato");
    glPopMatrix();


    glPushMatrix();
        displayIngredient("cookedBeef");
    glPopMatrix();

    glPushMatrix();
        displayIngredient("cutPotato");
    glPopMatrix();
    
}



void displayCurryIngrts(){
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        displayIngredient("ktc_table");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-12, 15, -1); // z value larger moves it close to the camera
        glScalef(0.3, 0.3, 0.3);
        displayIngredient("potato");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-8, 13, -1);
        glRotatef(-90, 1, 0, 0);
        //glScalef(0.2, 0.2, 0.2);
        displayIngredient("tomato");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-13, 15, 7); // z value larger moves it close to the camera
        glScalef(0.1, 0.1, 0.1);
        displayIngredient("onion");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10, 15, 7); // z value larger moves it close to the camera
        glRotatef(90, 1, 0, 0); // rotating x will roll it towards you
        glScalef(0.3, 0.3, 0.3); // rotating z will rotate counter clockwise on clock
        displayIngredient("knife");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2, 14, -1); // x value smaller moves to the left
        glScalef(0.2, 0.2, 0.2);
        displayIngredient("pot");
    glPopMatrix();

}



void displaySteakIngrts(){
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        displayIngredient("ktc_table");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3, 15, 7); // x value smaller moves to the left
        glRotatef(270, 1, 0, 0);
        glScalef(0.09, 0.09, 0.09);
        displayIngredient("pan");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(8, 14, 4);
        glRotatef(0, 1, 0, 0);
        glScalef(0.4, 0.4, 0.4);
        displayIngredient("steak");
    glPopMatrix();

    glPushMatrix();

        glTranslatef(-10, 15, 7); // z value larger moves it close to the camera
        glRotatef(90, 1, 0, 0); // rotating x will roll it towards you
        glScalef(0.3, 0.3, 0.3); // rotating z will rotate counter clockwise on clock
        displayIngredient("knife");
    glPopMatrix();

}



void draw3DScene(){
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
    
    //glPushMatrix();
    //glColor3f(1,0,0);
    glPushMatrix();
        glTranslatef(0, 0, -10);
        glScalef(2, 2, 2);
        //drawFloor();
    glPopMatrix();


    glPushMatrix();
        glRotatef(45, 0, 1, 0);
        if (scene == 1)
            displaySaladIngrts();
        if (scene == 2)
            displayCurryIngrts();
        if (scene == 3)
            displaySteakIngrts();
    glPopMatrix();

    //glPopMatrix();

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
    if (key == '1')
        scene = 1;
    if (key == '2')
        scene = 2;
    if (key == '3')
        scene = 3;
}

// Mouse Handler for first press and first release
void mouse(int btn, int state, int x, int y){
        //std::cout << " mouseMotion coords2: ";
        //std:: cout << x << ", " << y << std::endl;
        if (state == GLUT_UP){}
        if (state == GLUT_DOWN){}
}

// Is called when you move your mouse
void passive (int x, int y){ 
    //std::cout << " mouseMotion coords2: ";
    //std:: cout << x << ", " << y << std::endl;
}

void FPS(int val)
{
    glutPostRedisplay(); //registers "display" as the display callback function
    glutTimerFunc(17, FPS, 0); //1sec = 1000, 60fps = 1000/60 = ~17
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP){ eye[1]++; }
    if (key == GLUT_KEY_DOWN){ eye[1]--; }
    if (key == GLUT_KEY_LEFT){ eye[0]--; }
    if (key == GLUT_KEY_RIGHT){ eye[0]++; }
}

//Idle function 
void idle(){
   timer+=1;
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
}

/*
TO DO:
    1. knife, cutMango make use of 2 images for texture, but i only know how to apply one ppm...
        - Either search on line to figire out apply multiple texture on the same obj
        - Or combine 2 jpg(/png...) into one jpg(/png..). Could check ktc_table for example.
    2. Find new obj online: bowl(to make salad), spoon
*/
void init()
{
    glEnable(GL_TEXTURE_2D);

    int width = 0;
    int height = 0;
    int max = 0;

    //GLubyte* obj = LoadPPM("obj/ktc_table/ktc_table.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/orange/orange.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/banana/banana.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/mango/mango.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/onion/onion.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/potato/potato.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/tomato/tomato.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/steak/steak.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/cutBanana/cutBanana.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/cutOnion/cutOnion.ppm", &width, &height, &max);
    GLubyte* obj = LoadPPM("obj/cutPotato/cutPotato.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/cutTomato/cutTomato.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/cookedBeef/cookedBeef.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/pan/pan.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/knife/knife.ppm", &width, &height, &max);
    //GLubyte* obj = LoadPPM("obj/pot/pot.ppm", &width, &height, &max);


    glMatrixMode(GL_TEXTURE);
    glScalef(-1,1,-1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, obj);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Prototype");

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);


    glutTimerFunc(0, FPS, 0);
    glutReshapeFunc(handleReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    callBackInit();
    init();
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glEnable(GL_BLEND);
    loadIngrts();
    glutMainLoop();


    return 0;
}