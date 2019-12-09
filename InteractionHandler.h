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

#ifndef INTERACTIONHANDLER_H
#define INTERACTIONHANDLER_H

#include "PPM.h"
#include <stdio.h>
#include <stdlib.h>
#include "Handler.h"
#include <iostream>
#include <vector>

struct IHandler {
    std::vector<Handler *> mHandlers;

    void leftClickDown(int x, int y);
    void drawHandlers();
    void addHandler(Handler *handler);
};

#endif


