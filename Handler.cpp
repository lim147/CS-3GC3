#include "Handler.h"


    void (*mHandlerFunc)();

    bool Handler::isInBounds(unsigned int x, unsigned int y) {

        return x >= mLeft && x <= mRight && y >= mBottom && y <= mTop;
    }

    void Handler::handleClickAt(unsigned int x, unsigned int y) {
        if (isInBounds(x, y)) {
            mHandlerFunc;
        }
    }

    void Handler::drawBoxVertices() {
        glVertex3f(mLeft, mTop, 1);
        glVertex3f(mLeft, mBottom, 1);
        glVertex3f(mRight, mTop, 1);
        glVertex3f(mRight, mBottom, 1);
        glVertex3f(mLeft, mTop, 1);
        glVertex3f(mRight, mTop, 1);
        glVertex3f(mLeft, mBottom, 1);
        glVertex3f(mRight, mBottom, 1);
    }



