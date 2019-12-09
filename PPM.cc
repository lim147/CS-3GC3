#include "PPM.h"
#include <stdio.h>
#include <stdlib.h>

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
GLubyte* LoadPPM(const char* file, int* width, int* height, int* max)
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
        //printf("%s is not a PPM file!\n",file);
        exit(0);
    }
    //printf("%s is a PPM file\n", file);
    fscanf(fd, "%c",&c);
    while(c == '#')
    {
        fscanf(fd, "%[^\n] ", b);
        printf("%s\n",b);
        fscanf(fd, "%c",&c);
    }
    ungetc(c,fd);
    fscanf(fd, "%d %d %d", &n, &m, &k);
    
    //printf("%d rows  %d columns  max value= %d\n",n,m,k);
    
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
