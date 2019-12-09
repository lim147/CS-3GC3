// works
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

//window ID
GLint WindowID1, WindowID2;


//dictionary of ingredients
map<string, Ingredient> ll;

//dictionary to keep track of ingredients are cut or not
map<string, bool> cut;

int scene = 0;
// scene 0 is the select recipe state
// scene 1 is the salad state
//                curry state
//                steak state
int chosenRecipe = 1; // Variable to keep track of which recipe was chosen at start

GLfloat eye[] = {8, 21, 10}; //z should be 10
GLfloat lookAt[] = { 0, 20, 0 };
GLfloat up[] = { 0, 1, 0 };

// For displaying text on screen
int w = 600;
int h = 600;
// int font=(int)GLUT_BITMAP_9_BY_15;
char s[30];
char s2[30];

// Variables for time
double allotedTime = 50;
double startTime; // Time since the recipe was chosen
double passedTime;  // Time since the program compiled
double steakTime = 0; 
int tick = allotedTime;

Image selectRecipe; // Image with the recipes to choose from
Image Instructions;
Image Salad; // Image with the recipe of Salad
Image Curry; // Image with the recpie of Curry
Image Steak; // Image with the recipe of Steak
Image Score; // Image for score
Image Controls; // Image for controls
Image Done; // Image for done button
Image NotComplete; // Image for when recipe was not completed in time
Image CompleteSalad; // Image for when salad is complete
Image CompleteCurry; // Image for when curry is complete
Image CompleteSteak; // Image for when steak is complete

IHandler mouseHandler; // For selecting recipe
IHandler mouseHandler2; // For the try again button
IHandler mouseHandler3; // For the done button

int score;
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


GLubyte* tt[22];
GLuint textures[22];

int height[22];
int width[22];
int maximum[22];


//ray casting
double* m_start = new double[3];
double* m_end = new double[3];
double* m_position = new double[3];
double* obj_cposition = new double[3];
/*
    0 - steak
    1 - mango
*/


bool pick[5] = {
            //salad  //curry //steak 
    false, //knife   //knife   //knife 
    false, //banana  //pot     //pan 
    false, //orange  //potato //steak
    false, //mango   //tomato 
    false,           //onion  
    };
float size[5] = {1.5, 1.5,1.5, 1.5,1.5};
float selectable[5] = {true, true, true,true, true};

/*
Index  | Salad     | Curry     | Steak
___________________________________________
pos[0] | knife     | knife     | pan
pos[1] | banana    | pot       | beef
pos[2] | orange    | potato    | 
pos[3] | mango     | tomato    | 
pos[4] | bowl      | onion     | 

not loaded 
pos[] |           | cutOnion  | cookedBeef
pos[] | cutBanana | cutTomato |
pos[] | cutMango  | cutPotato |

*/
float pos[6][3] = {
    {-10, 30, -30}, // pos[0] 
    {-10, 25, -30}, // pos[1] 
    {-10, 20, -30}, // pos[2] 
    {-10, 15, -30}, // pos[3] 
    {-10, 10, -30}, // pos[4] 
    {-10, 5, -30}   // pos[5] 
}; 

double matModelView[16], matProjection[16]; 
int viewport[4]; 



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
        //setMaterials(0);
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
        //setMaterials(0);
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
        //setMaterials(1);
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
    loadIngredient("obj/bowl/bowl.obj", "bowl");
    
    //cut ingredients:
    loadIngredient("obj/cutOnion/cutOnion.obj", "cutOnion");
    loadIngredient("obj/cutTomato/cutTomato.obj", "cutTomato");
    loadIngredient("obj/cutPotato/cutPotato.obj", "cutPotato");
    loadIngredient("obj/cutBanana/cutBanana.obj", "cutBanana");
    loadIngredient("obj/cutMango/cutMango.obj", "cutMango");
    loadIngredient("obj/cutOrange/cutOrange.obj", "cutOrange");

    //cooked beef
    loadIngredient("obj/cookedBeef/cookedBeef.obj", "cookedBeef");
}

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
    glGenTextures(22, textures);

    
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
    texture("obj/cutOrange/cutOrange.ppm", 20);

    texture("obj/cutOnion/cutOnion.ppm", 10);
    texture("obj/cutPotato/cutPotato.ppm", 11);
    texture("obj/cutTomato/cutTomato.ppm", 12);
    texture("obj/cookedBeef/cookedBeef.ppm", 13);

    texture("obj/pan/pan.ppm", 14);
    texture("obj/knife/knife.ppm", 15);
    texture("obj/pot/pot.ppm", 16);
    texture("obj/bowl/bowl.ppm", 21);


    texture("obj/room/wall.ppm", 17);
    texture("obj/room/shelves.ppm", 18);
    texture("obj/room/floor.ppm", 19);

}

void gameRestart(){
    steakTime = 0;
    scene = 0;
    tick = allotedTime;
    for(int i = 0; i < 5; i++){
        pos[i][0] = -10; 
        pos[i][1] = 30 - i*5; 
        pos[i][3] = -30 ;

        pick[i] = false; 
        selectable[i] = true; 

    }
    cut["banana"] = false;
    cut["orange"] = false;
    cut["mango"] = false;
    cut["onion"] = false;
    cut["potato"] =  false;
    cut["tomato"] =  false;
    cut["beef"] = false;

}

void gameSetUp()
{
    loadIngrts();
    loadTextures();

    cut["banana"] = false;
    cut["orange"] = false;
    cut["mango"] = false;
    cut["onion"] = false;
    cut["potato"] =  false;
    cut["tomato"] =  false;
    cut["beef"] = false;


}


void displayInstructions(){

    glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
    glPushMatrix();
        glLoadIdentity();
           gluOrtho2D(0, w, 0, h);
        //glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);
        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
        glMatrixMode(GL_MODELVIEW);

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

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

}

/**
 *  \brief Displays ingredients needed for salad recipe
 */
void displaySaladIngrts(){
    glPushMatrix();
        glTranslatef(pos[0][0], pos[0][1], pos[0][2]); // z value larger moves it close to the camera
        glRotatef(100, 1, 0, 0); // rotating x will roll it towards you
        glRotatef(110, 1, 0, 0);
        glScalef(0.6, 0.6, 0.6); // rotating z will rotate counter clockwise on clock
        if(pick[0]){
            glScalef(1.6, 1.6, 1.6);
            
        }
        glBindTexture(GL_TEXTURE_2D, textures[15]);
        displayIngredient("knife");
    glPopMatrix();

    if(cut["banana"] == false)
    {   
        glPushMatrix();
            glTranslatef(pos[1][0], pos[1][1], pos[1][2]);
            glScalef(0.5, 0.5, 0.5);
            if(pick[1]){
                glScalef(1.5, 1.5, 1.5);
            }
            glBindTexture(GL_TEXTURE_2D, textures[1]);
            displayIngredient("banana");
        glPopMatrix();
    }

    if (cut["orange"] == false)
    {
        glPushMatrix();
            glTranslatef(pos[2][0], pos[2][1], pos[2][2]);
            glRotatef(-90, 1, 0, 0);
            glScalef(0.3, 0.3, 0.3);
            if(pick[2]){
                glScalef(1.3, 1.3, 1.3);
            }
            glBindTexture(GL_TEXTURE_2D, textures[2]);
            displayIngredient("orange");
        glPopMatrix();
    
    }


    if (cut["mango"] == false)
    {
        glPushMatrix();
            glTranslatef(pos[3][0], pos[3][1], pos[3][2]);
            glRotatef(90, 1, 0, 0);
            glScalef(0.5, 0.5, 0.5);
            if(pick[3]){
                glScalef(1.5, 1.5, 1.5);
            }
            glBindTexture(GL_TEXTURE_2D, textures[3]);
            displayIngredient("mango");
        glPopMatrix();
    }


    glPushMatrix();
        glTranslatef(pos[4][0], pos[4][1], pos[4][2]); // z value larger moves it close to the camera
        glScalef(5.0, 5.0, 5.0); // rotating z will rotate counter clockwise on clock
        if(pick[4]){
            glScalef(1, 1, 1);
            
        }
        glBindTexture(GL_TEXTURE_2D, textures[21]);
        displayIngredient("bowl");
    glPopMatrix();


    if (cut["banana"])
    {
        glPushMatrix();
            glTranslatef(pos[1][0], pos[1][1], pos[1][2]);
            glBindTexture(GL_TEXTURE_2D, textures[8]);
            glScalef(0.2, 0.2, 0.2);
            displayIngredient("cutBanana");
        glPopMatrix();
    }

    if (cut["orange"])
    {
        glPushMatrix();
            glTranslatef(pos[2][0], pos[2][1], pos[2][2]);
            glBindTexture(GL_TEXTURE_2D, textures[20]);
            glScalef(0.25, 0.25, 0.25);
            displayIngredient("cutOrange");
        glPopMatrix();
    }
     
    
    if (cut["mango"])
    {
        glPushMatrix();
            glTranslatef(pos[3][0], pos[3][1], pos[3][2]);
            glBindTexture(GL_TEXTURE_2D, textures[9]);
            glScalef(0.2, 0.2, 0.2);
            displayIngredient("cutMango");
        glPopMatrix();
    }
}

/**
 *  \brief Displays ingredients needed for curry recipe
 */
void displayCurryIngrts(){
    glPushMatrix();
        glTranslatef(pos[0][0], pos[0][1], pos[0][2]); // z value larger moves it close to the camera
        glRotatef(100, 1, 0, 0); // rotating x will roll it towards you
        glRotatef(110, 1, 0, 0);
        glScalef(0.6, 0.6, 0.6); // rotating z will rotate counter clockwise on clock
        if(pick[0])
            glScalef(1.6, 1.6, 1.6);
        glBindTexture(GL_TEXTURE_2D, textures[15]);
        displayIngredient("knife");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(pos[1][0], pos[1][1], pos[1][2]); // x value smaller moves to the left
        glScalef(0.15, 0.15, 0.15);
        if(pick[1])
            glScalef(1.15,1.15,1.15);
        glBindTexture(GL_TEXTURE_2D, textures[16]);
        displayIngredient("pot");
    glPopMatrix();


    if (cut["potato"] == false)
    {
        glPushMatrix();
            glTranslatef(pos[2][0], pos[2][1], pos[2][2]); // z value larger moves it close to the camera
            glScalef(0.4, 0.4, 0.4);
            if(pick[2])
                glScalef(1.4,1.4,1.4);
            glBindTexture(GL_TEXTURE_2D, textures[5]);
            displayIngredient("potato");
        glPopMatrix();
    }
    

    if (cut["tomato"] == false)
    {
        glPushMatrix();
            glTranslatef(pos[3][0], pos[3][1], pos[3][2]);
            glRotatef(-90, 1, 0, 0);
            glScalef(0.25, 0.25, 0.25);
            if(pick[3])
                glScalef(1.25,1.25,1.25);
            glBindTexture(GL_TEXTURE_2D, textures[6]);
            displayIngredient("tomato");
        glPopMatrix();
    }
    

    if (cut["onion"] == false)
    {
        glPushMatrix();
            glTranslatef(pos[4][0], pos[4][1], pos[4][2]); // z value larger moves it close to the camera
            glScalef(0.15, 0.15, 0.15);
            if(pick[4])
                glScalef(1.15,1.15,1.15);
            glBindTexture(GL_TEXTURE_2D, textures[4]);
            displayIngredient("onion");
        glPopMatrix();
    }
    

    if (cut["onion"])
    {
        glPushMatrix();
            glTranslatef(pos[4][0], pos[4][1], pos[4][2]);
            glRotatef(30, 1, 0, 0);
            glScalef(0.2, 0.2, 0.2);
            glBindTexture(GL_TEXTURE_2D, textures[10]);
            displayIngredient("cutOnion");
        glPopMatrix();
    }
    
    
    if (cut["tomato"])
    {
        glPushMatrix();
            glTranslatef(pos[3][0], pos[3][1], pos[3][2]);
            glRotatef(30, 1, 0, 0);
            glScalef(0.2, 0.2, 0.2);
            glBindTexture(GL_TEXTURE_2D, textures[12]);
            displayIngredient("cutTomato");
        glPopMatrix();
    }
    
    if (cut["potato"])
    {
        glPushMatrix();
            glTranslatef(pos[2][0], pos[2][1], pos[2][2]);
            glScalef(0.15, 0.15, 0.15);
            glBindTexture(GL_TEXTURE_2D, textures[11]);
            displayIngredient("cutPotato");
        glPopMatrix();
    }
    
}

/**
 *  \brief Displays ingredients needed for Steak recipe
 */
void displaySteakIngrts(){

    glPushMatrix();
        glTranslatef(pos[0][0], pos[0][1], pos[0][2]); // x value smaller moves to the left
        glRotatef(270, 1, 0, 0);
        glScalef(0.12, 0.12, 0.12);
        if(pick[0])
            glScalef(1.12,1.12,1.12);
        glBindTexture(GL_TEXTURE_2D, textures[14]);
        displayIngredient("pan");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(pos[1][0], pos[1][1], pos[1][2]);
        glRotatef(0, 1, 0, 0);
        glScalef(0.4, 0.4, 0.4);
        if(pick[1])
            glScalef(1.4,1.4,1.4);
        glBindTexture(GL_TEXTURE_2D, textures[7]);
        displayIngredient("steak");
    glPopMatrix();


    // glPushMatrix();
    //     glTranslatef(-10, 15, -30);
    //     glRotatef(90, 0, 1, 0);
    //     glBindTexture(GL_TEXTURE_2D, textures[13]);
    //     glScalef(0.15, 0.15, 0.15);
    //     displayIngredient("cookedBeef");
    // glPopMatrix();

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
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void displayScore(){

    sprintf(s2, "%2d", score);

        // The following is for the onscreen timer
    setOrthographicProjection();
    glColor3d(1.0, 0.0, 1.0);;
    glPushMatrix();
        glLoadIdentity();
        glDisable(GL_LIGHTING);
        renderBitmapString(300,480, (void*)GLUT_BITMAP_9_BY_15, s2);
        glEnable(GL_LIGHTING);


    glPopMatrix();
    resetPerspectiveProjection();


    glLoadIdentity();
    glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
    glDisable(GL_DEPTH_TEST); // Makes it so that it stays on screen even when the camera moves
    glLoadIdentity();
    glPushMatrix();
        
        glOrtho(0, w, 0, h, 0.0, 30.0); // Setup an Ortho view

        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
        glMatrixMode(GL_MODELVIEW);

    
        Score.texture();
        Score.draw(550, 430, 0.25, 0.25);

        glDisable(GL_LIGHTING);
        mouseHandler2.IHandler::drawHandlers();
        glEnable(GL_LIGHTING);

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

/**
 *  \brief Displays Menu of Recipes
 */
void displayMenu(){


    glLoadIdentity();
    glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
    glDisable(GL_DEPTH_TEST); // Makes it so that it stays on screen even when the camera moves
    glLoadIdentity();
    glPushMatrix();


        glOrtho(0, w, 0, h, 0.0, 30.0); // Setup an Ortho view
        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
        glMatrixMode(GL_MODELVIEW);
        
        selectRecipe.texture();
        selectRecipe.draw(550, 430, 0.25, 0.25);

        glDisable(GL_LIGHTING);
        mouseHandler.IHandler::drawHandlers();
        glEnable(GL_LIGHTING);

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

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
        else if (scene == 1){
            displaySaladIngrts();
            displayInstructions();
        }
        else if (scene == 2){
            displayCurryIngrts();
            displayInstructions();
        }
        else if (scene == 3){
            displaySteakIngrts();
            displayInstructions();
        }
        else if (scene == 4){
            displayScore();
        }
    glPopMatrix();

    if (scene == 1 or scene == 2 or scene == 3){
        glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION); // Tells opengl that we are doing project matrix work
            glDisable(GL_DEPTH_TEST); // Makes it so that it stays on screen even when the camera moves
            glLoadIdentity();

            glOrtho(0, w, 0, h, 0.0, 30.0); // Setup an Ortho view
            glScalef(1, -1, 1);
            glTranslatef(0, -h, 0);
            glMatrixMode(GL_MODELVIEW);
            
            Done.texture();
            Done.draw(580, 580, 0.05, 0.05); // second one moves up and down

            glDisable(GL_LIGHTING);
            mouseHandler3.IHandler::drawHandlers();
            glEnable(GL_LIGHTING);

            glEnable(GL_DEPTH_TEST);
        glPopMatrix();
}
    
    
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
        glDisable(GL_LIGHTING);
        renderBitmapString(20,40, (void*)GLUT_BITMAP_9_BY_15, s);
        glEnable(GL_LIGHTING);
        // Make a variable for the score, similar to the s here, which is defined at the top
        // Check if the scene is 4
        // if the scene is 4, then display the score
        // if you need help formatting this, check FPS function

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
    if (key == '0')
        scene = 0;
    if (key == '1'){
        startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
        scene = 1;
    }
    if (key == '2'){
        startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
        scene = 2;
    }
    if (key == '3'){
        startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
        scene = 3;
    }
    if (key == '4')
        scene = 4;
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

        //printf("Obj Intersection at t= %f, %f\n", t1, t2);

        pick[i] = !pick[i];
    }
}


bool rightClickKnife()
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
    R0Pc[0] = R0[0] - pos[0][0];
    R0Pc[1] = R0[1] - pos[0][1];
    R0Pc[2] = R0[2] - pos[0][2];

    double B = 2 * ( R0Pc[0] * Rd[0] + R0Pc[1] * Rd[1] + R0Pc[2] * Rd[2]);
    double C = (R0Pc[0]*R0Pc[0] + R0Pc[1] * R0Pc[1] + R0Pc[2] * R0Pc[2])
                - (size[0] * size[0]);

    double discriminant = B*B - 4* A *C;

    return (discriminant > 0);

}



// Mouse Handler for first press and first release
//mouse
void mouse(int btn, int state, int x, int y){
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            
        }

        if (state == GLUT_DOWN)
        {

            //printf("time for un projection!!!!\n");

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
            //printf("(%f,%f,%f)----(%f,%f,%f)\n\n", m_start[0], m_start[1], m_start[2], m_end[0], m_end[1], m_end[2]);
    

            int n = 0; 
            if (scene == 0)
            {
                mouseHandler.leftClickDown(x, y);

            }
            else if (scene ==4)
            {
                mouseHandler2.leftClickDown(x,y);
            }
            else if (scene==1 or scene==2 or scene==3)
            {
                mouseHandler3.leftClickDown(x,y);
                if(scene == 1)
                {
                    
                    for(int i = 0; i < 5; i++){

                        if (selectable[i]){
                            makeSelectable(i);
                        }

                    }
                    

                        Point2D bowlPos = Point2D(pos[4][0], pos[4][1]);

                        if (cut["banana"]){
                            Point2D bananaPos = Point2D(pos[1][0], pos[1][1]);
                            if(bowlPos.distanceTo(bananaPos) < 5.0){
                                selectable[1] = false; 
                                
                                pick[1] = pick[4];
                                pos[1][0] = pos[4][0];
                                pos[1][1] = pos[4][1];
                                pos[1][2] = pos[4][2];
                                
                            }

                        }
            
                        if (cut["orange"])
                        {
                            Point2D orangePos = Point2D(pos[2][0], pos[2][1]);
                            if(bowlPos.distanceTo(orangePos) < 5.0 ){
                                selectable[2] = false; 
                                
                                pick[2] = pick[4];
                                pos[2][0] = pos[4][0];
                                pos[2][1] = pos[4][1];
                                pos[2][2] = pos[4][2];
                                
                            }
                            
                        }
        
                        if (cut["mango"])
                        {
                            Point2D mangoPos = Point2D(pos[3][0], pos[3][1]);
                            if (bowlPos.distanceTo(mangoPos) < 5.0){
                                selectable[3] = false; 
                                
                                pick[3] = pick[4];
                                pos[3][0] = pos[4][0];
                                pos[3][1] = pos[4][1];
                                pos[3][2] = pos[4][2];
                    
                            }
                            
                        }

                }
                else if(scene == 2)
                {
                    for(int i = 0; i < 5; i++){

                        if (selectable[i]){
                            makeSelectable(i);
                        }

                    }

                    Point2D potPos = Point2D(pos[1][0], pos[1][1]);
                    
                    if (cut["potato"])
                    {
                        Point2D potatoPos = Point2D(pos[2][0], pos[2][1]);
                        if (potPos.distanceTo(potatoPos) < 5.0){
                            selectable[2] = false; 
                            pick[2] = pick[1];
                            pos[2][0] = pos[1][0];
                            pos[2][1] = pos[1][1];
                            pos[2][2] = pos[1][2];
                            
                        }else{
                            selectable[2] = true;
                        }
                
                    }

                    if(cut["tomato"]){
                        Point2D tomatoPos = Point2D(pos[3][0], pos[3][1]);
                        if (potPos.distanceTo(tomatoPos) < 5.0 ){
                            selectable[3] = false;
                            pick[3] = pick[1];
                            pos[3][0] = pos[1][0];
                            pos[3][1] = pos[1][1];
                            pos[3][2] = pos[1][2];
                            
                        }else{
                            selectable[3] = true;
                        }
                    }


                    if (cut["onion"])
                    {
                        Point2D onionPos = Point2D(pos[4][0], pos[4][1]);
                        if (potPos.distanceTo(onionPos) < 5.0 ){
                            selectable[4] = false;
                            pick[4] = pick[1];
                            pos[4][0] = pos[1][0];
                            pos[4][1] = pos[1][1];
                            pos[4][2] = pos[1][2];
                            
                        }else{
                            selectable[4] = true;
                            
                    }
                        }
                }
                else if (scene == 3)
                {
                  
                  for(int i = 0; i < 2; i++){
                        if (selectable[i]){
                            makeSelectable(i);
                        }

                    }
                    
                    Point2D panPos = Point2D(pos[0][0], pos[0][1]);
                    Point2D steakPos = Point2D(pos[1][0], pos[1][1]);

                    if (panPos.distanceTo(steakPos) < 4.0)
                        {
                            
                            selectable[1] = false; 
                            pick[1] = pick[0]; 
                            pos[1][0] = pos[0][0];
                            pos[1][1] = pos[0][1];
                            pos[1][2] = pos[0][2];
                            

                    }else{
                        selectable[1] = true;
                    }

                }

            }
            
        }
    }


    if (btn == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP)
        {

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


            //cutting obj
            if (scene == 1)
            {
                bool knifeIsRightClicjed = rightClickKnife();

                if (knifeIsRightClicjed) //right click on the knife
                {
                    cout << "knife is selected" << endl;
                    Point2D knifePos = Point2D(pos[0][0], pos[0][1]);

                    Point2D bananaPos = Point2D(pos[1][0], pos[1][1]);
                    Point2D orangePos = Point2D(pos[2][0], pos[2][1]);
                    Point2D mangoPos = Point2D(pos[3][0], pos[3][1]);

                    //compute the distance with banana, mango, orange
                    if (knifePos.distanceTo(bananaPos) < 3.0 && knifePos.mY>bananaPos.mY)
                    {
                        cut["banana"] = true;
                    }
                    
                    //printf("%f\n", knifePos.distanceTo(bananaPos) && knifePos.mY>orangePos.mY);

                    
                    if (knifePos.distanceTo(orangePos) < 3.0)
                    {
                        cut["orange"] = true;
                    }
                    printf("%f\n", knifePos.distanceTo(bananaPos) && knifePos.mY>orangePos.mY);

                    if (knifePos.distanceTo(mangoPos) < 3.0 && knifePos.mY>mangoPos.mY)
                    {
                        cut["mango"] = true;
                    }
                }
            }


            else if (scene == 2)
            {
                bool knifeIsRightClicjed = rightClickKnife();

                if (knifeIsRightClicjed) //right click on the knife
                {
                    cout << "knife is selected" << endl;
                    Point2D knifePos = Point2D(pos[0][0], pos[0][1]);

                    Point2D tomatoPos = Point2D(pos[3][0], pos[3][1]);
                    Point2D potatoPos = Point2D(pos[2][0], pos[2][1]);
                    Point2D onionPos = Point2D(pos[4][0], pos[4][1]);

                    //compute the distance with tomato, potato, onion
                    if (knifePos.distanceTo(tomatoPos) < 3.5 && knifePos.mY>tomatoPos.mY)
                    {
                        cut["tomato"] = true;
                    }
                    
                    printf("tomato: %f, %f\n", knifePos.distanceTo(tomatoPos), knifePos.mY-tomatoPos.mY);

                    
                    if (knifePos.distanceTo(potatoPos) < 3.0 && knifePos.mY>potatoPos.mY)
                    {
                        cut["potato"] = true;
                    }
                    printf("potato: %f, %f\n", knifePos.distanceTo(potatoPos), knifePos.mY-potatoPos.mY);
                    

                    if (knifePos.distanceTo(onionPos) < 3.5 && knifePos.mY>onionPos.mY)
                    {
                        cut["onion"] = true;
                    }
                    printf("onion: %f, %f\n", knifePos.distanceTo(onionPos), knifePos.mY-onionPos.mY);
                }
            }
            
        }
    }
}



// Is called when you move your mouse
void passive (int x, int y)
{ 
    int n = 0;
    if (scene == 1){
        n = 5; 
    }
    else if(scene == 2){
        n = 5; 
    }else if(scene == 3){
        n = 2;
    }
    for (int i = 0; i < n; i++){
        if (pick[i]){
           gluProject(pos[i][0],pos[i][1],pos[i][2],matModelView,matProjection,viewport,&obj_cposition[0],&obj_cposition[1],&obj_cposition[2]);

            double winX = (double)x; 
            double winY = viewport[3] - (double)y; 
            double winZ = obj_cposition[2];
            gluUnProject(winX,winY,winZ ,matModelView,matProjection,viewport,&m_position[0],&m_position[1],&m_position[2]); 


            pos[i][0] = m_position[0];
            pos[i][1] = m_position[1];
            pos[i][2] = m_position[2];
            //printf("(%f,%f,%f)", m_position[0],m_position[1],m_position[2]);
            //printf("(%f,%f,%f)", pos[i][0],pos[i][1],pos[i][2]);

        }    
    }
    
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


void FPS(int val)
{

    if (tick <= 1){
        chosenRecipe = 0;
        scene = 4;
    }


    if (scene == 1 or scene == 2 or scene == 3){
        passedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
        //glDisable(GL_LIGHTING);
        //glDisable(GL_TEXTURE_2D);
        tick = (int)(allotedTime-(passedTime-startTime));
        sprintf(s, "%2d", tick);
        //glEnable(GL_TEXTURE_2D)
        //glEnable(GL_LIGHTING);
    }

    glutTimerFunc(1000, FPS, 0);

    glutSetWindow( WindowID1 );
    glutPostRedisplay();

    glutSetWindow( WindowID2 );
    glutPostRedisplay();
}

void selectSalad() {
    chosenRecipe=1;
    scene=1;
    startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //std::cout << "menustate "<< menuState << std::endl;
}

void selectCurry(){
    chosenRecipe=2;
    scene=2;
    startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //std::cout << "menustate "<< menuState << std::endl;
}

void selectSteak(){
    chosenRecipe=3;
    scene=3;
    startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //std::cout << "menustate "<< menuState << std::endl;
}

void done(){

        if(chosenRecipe == 1){
        if((selectable[1] == false) && (selectable[2] == false ) && (selectable[3] == false)){
            score = allotedTime - (allotedTime-(passedTime-startTime));
            scene = 4; 
        }
    }else if(chosenRecipe == 2){
        if((selectable[2] == false) && (selectable[3] == false ) && (selectable[4] == false)){
            score = allotedTime - (allotedTime-(passedTime-startTime));
            scene = 4;
        }
    }else if(chosenRecipe == 3){
        if(selectable[1]){
            score = allotedTime - (allotedTime-(passedTime-startTime));
            scene = 4;
        }
    }

}
Handler saladButton = {
    220, //mLeft
    270, //mRight
    214, //mTop // is actually the bottom
    180, //mBottom
    selectSalad
};

Handler curryButton = {
    220, //mLeft
    270, //mRight
    287, //mTop
    249, //mBottom
    selectCurry
};

Handler steakButton = {
    220, //mLeft
    270, //mRight
    367, //mTop
    327, //mBottom
    selectSteak
};

Handler tryAgainButton = {
    220, 
    425, 
    367, 
    327, 
    gameRestart
};

Handler doneButton = {
    530, //left
    580, //right
    579, //bottom
    529,  //top
    done
};

void init()
{
    //Load textures for the recipe menu and instructions
    selectRecipe.load("ppm/Choose.ppm");
    Salad.load("ppm/Salad.ppm");
    Curry.load("ppm/Curry.ppm");
    Steak.load("ppm/Steak.ppm");
    Score.load("ppm/Score.ppm");
    Controls.load("ppm/Controls.ppm");
    Done.load("ppm/Done.ppm");

    NotComplete.load("ppm/NotComplete.ppm"); 
    CompleteSalad.load("ppm/CompleteFruit.ppm"); 
    CompleteCurry.load("ppm/CompleteCurry.ppm"); 
    CompleteSteak.load("ppm/CompleteSteak.ppm"); 


    //Add the buttons to the mouse handler
    mouseHandler.addHandler(&saladButton);
    mouseHandler.addHandler(&curryButton);
    mouseHandler.addHandler(&steakButton);
    mouseHandler2.addHandler(&tryAgainButton);
    mouseHandler3.addHandler(&doneButton);
}




/*
                Display instructions into a new window
--------------------------------------------------------------------
--------------------------------------------------------------------
*/

void display2D()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        if (scene == 0){
            Controls.texture();
            Controls.draw(320, 0, 0.18, 0.18);  
        }
        if (scene == 1){
            Salad.texture();
            Salad.draw(320, 0, 0.18, 0.18);
        }
        else if (scene == 2){
            Curry.texture();
            Curry.draw(320, 0, 0.18, 0.18);
        }
        else if (scene == 3) {
            Steak.texture();
            Steak.draw(320, 0, 0.18, 0.18);
        }
        else if (scene == 4){
            if (chosenRecipe == 0){
                NotComplete.texture();
                NotComplete.draw(320, 0, 0.18, 0.18);                
            }
            else if (chosenRecipe == 1){
                CompleteSalad.texture();
                CompleteSalad.draw(320, 0, 0.18, 0.18);
            }
            else if(chosenRecipe == 2){
                CompleteCurry.texture();
                CompleteCurry.draw(320, 0, 0.18, 0.18);
            }
            else if(chosenRecipe == 3){
                CompleteSteak.texture();
                CompleteSteak.draw(320, 0, 0.18, 0.18);
            }
        }

    glPopMatrix();
    glutSwapBuffers();
}




void reshape2D(int w, int h)
{
    glMatrixMode(GL_PROJECTION); //change camera, projection to the screen
    glLoadIdentity(); //reset the change
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}




/*
--------------------------------------------------------------------
--------------------------------------------------------------------
*/


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    WindowID1 = glutCreateWindow("Kitchen");
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

    gameSetUp();
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glEnable(GL_BLEND);



    glutInitWindowSize(320,270);
    glutInitWindowPosition(900,150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    WindowID2 = glutCreateWindow("Instructions");   // Create a window 2
    glutTimerFunc(0, FPS, 0);
    glutDisplayFunc(display2D);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape2D);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();


    return 0;
}