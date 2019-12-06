#include "Image.h"




void Image::load(char * filename) {
    mImage = LoadPPM(filename, &mWidth, &mHeight, &mMax);
    printf("%s %d %d\n", filename, mWidth, mHeight);
}

void Image::draw(unsigned int x, unsigned int y) {

    glColor3d(1.0, 1.0, 1.0);;
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(0,300);
        glVertex2f(300,300);
        glVertex2f(300,0);
    glEnd();

}

void Image::texture() {
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



