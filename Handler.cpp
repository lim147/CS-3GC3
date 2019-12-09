#include "Handler.h"

void (*mHandlerFunc)();

bool Handler::isInBounds(unsigned int x, unsigned int y) {

    return x >= mLeft && x <= mRight && y >= mBottom && y <= mTop;
}

void Handler::handleClickAt(unsigned int x, unsigned int y) {
    if (isInBounds(x, y)) {
        mHandlerFunc();
    }
}

void Handler::drawBoxVertices() {
    glVertex2f(mLeft, mTop);
    glVertex2f(mLeft, mBottom);
    glVertex2f(mRight, mTop);
    glVertex2f(mRight, mBottom);
    glVertex2f(mLeft, mTop);
    glVertex2f(mRight, mTop);
    glVertex2f(mLeft, mBottom);
    glVertex2f(mRight, mBottom);
}



