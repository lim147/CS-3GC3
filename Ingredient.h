#ifndef ingredient_h
#define ingredient_h

#include "mathLib2D.h"
#include <vector>

class Ingredient{
public:
	Ingredient(); //initially 0, 0, 0
	Ingredient(float a, float b, float c);

	float px;
	float py;
	float pz;

	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector <Point3D> temp_vertices; //mesh
	std::vector <Point2D> temp_uvs; //texture
	std::vector <Vec3D> temp_normals; //normals

	bool state;

	bool loadObject(const char* filename);
	//void loadtexture(const char* filename);



};



#endif