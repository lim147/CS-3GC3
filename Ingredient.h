#ifndef ingredient_h
#define ingredient_h

#include <vector>

class Ingredient{
public:
	Ingredient(); //initially 0, 0, 0
	Ingredient(float a, float b, float c);

	float px;
	float py;
	float pz;

	bool state;

	bool loadObject(const char* filename);
	//void loadtexture(const char* filename);



};



#endif