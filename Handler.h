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

#ifndef HANDLER_H
#define HANDLER_H

#include "PPM.h"
#include <stdio.h>
#include <stdlib.h>

struct Handler {
    unsigned int mLeft, mRight, mTop, mBottom;

    void (*mHandlerFunc)();
    bool isInBounds(unsigned int x, unsigned int y);
    void handleClickAt(unsigned int x, unsigned int y);
    void drawBoxVertices();
};

#endif