#include "Image.h"




void Image::load(char * filename) {
    mImage = LoadPPM(filename, &mWidth, &mHeight, &mMax);
    printf("%s %d %d\n", filename, mWidth, mHeight);
}

void Image::draw(unsigned int x, unsigned int y, float size1, float size2) {

    glRasterPos2i(x , y);
    glPixelZoom(-size1, size2);
    glDrawPixels(mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mImage);


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



