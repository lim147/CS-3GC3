#include "Image.h"

struct Image {
    int mWidth;
    int mHeight;
    GLubyte * mImage;

    void load(char * filename) {
        /**
         * YOUR CODE HERE
         */
        mImage = LoadPPM(filename, &mWidth, &mHeight);
        printf("%s %d %d\n", filename, mWidth, mHeight);
    }

    void draw(unsigned int x, unsigned int y) {
        //glRasterPos2i(x + mWidth, y);
        /**
         * If you are on a retina display then you should replace the values
         * from -1, 1 to -2, 2 to ensure they appear at full size!
         *
         * The PPM parser packs the image mirrored horizontally. Thus we use
         * glPixelZoom to "flip" the image back the correct way by scaling the
         * x axis by -1. This is the same concept as mirroring an object with
         * glScalef(-1, 1, 1).
         *
         * Aside: Using the parsing code from last year. I don't think the code
         * is very good. There is definitely a way to parse PPM bitmaps without
         * needing to flip the image like this.
         */
        //glPixelZoom(-2, 2);
        /**
         * YOUR CODE HERE
         */
        //glDrawPixels(mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mImage);
        glColor3d(1.0, 1.0, 1.0);;
        glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(0,300);
            glVertex2f(300,300);
            glVertex2f(300,0);
        glEnd();

    }

    void texture() {
        /**
         * YOUR CODE HERE
         *
         * Add the glTexImage2D and glTexParameterf calls.
         * I strongly recommend reading the documentation to get a loose sense
         * of what these values mean.
         */
        unsigned int name;
        glGenTextures(1, &name);
        glBindTexture(GL_TEXTURE_2D, name);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            mWidth,
            mHeight,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            mImage
        );

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
};


void setMaterials(unsigned int index){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS , materialShiny[index]);
}

/**
 *  \brief loads the specified ppm file, and returns the image data as a GLubyte
 *         (unsigned byte) array. Also returns the width and height of the image, and the
 *         maximum colour value by way of arguments
 *         usage: GLubyte myImg = LoadPPM("myImg.ppm", &width, &height, &max);
 *  \param file - ppm file name
 *  \param width - 
 *  \param height - 
 *  \param max - 
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