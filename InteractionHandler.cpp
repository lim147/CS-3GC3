#include "InteractionHandler.h"


    void IHandler::leftClickDown(int x, int y) {
        std::cout << "Left click at " << x << ", " << y << std::endl;
        for (Handler *handler : mHandlers) {
            /**
             * YOUR CODE HERE
             */
            handler->handleClickAt(x, y);
        }
    }

    void IHandler::drawHandlers() {
        glColor3f(1, 1, 1);
        glLineWidth(2);
        glBegin(GL_LINES);
        for (Handler *handler : mHandlers) {
            handler->drawBoxVertices();
        }
        glEnd();
    }

    void IHandler::addHandler(Handler *handler) {
        /**
         * YOUR CODE HERE
         */
        mHandlers.push_back(handler);
    }
