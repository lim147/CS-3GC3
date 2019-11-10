#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

class Ingredient{
public:
	Ingredient(); //initially 0, 0, 0
	Ingredient(loat a, float b, float c);

	float px;
	float py;
	float pz;

	bool state;

	void loadObject(const char* filename);
	void loadtexture(const char* filename);


};



#endif