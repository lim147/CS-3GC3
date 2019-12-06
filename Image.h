#define IMAGE_H

#include "mathLib2D.h"
#include <vector>

struct Image {
    int mWidth;
    int mHeight;
    GLubyte * mImage;

    void load(char * filename);
    void draw(unsigned int x, unsigned int y);
    void texture();
};


void setMaterials(unsigned int index);
static GLubyte* LoadPPM(char* file, int* width, int* height, int* max);



#endif