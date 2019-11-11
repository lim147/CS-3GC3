#include "ingredient.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

Ingredient::Ingredient(){
	px = 0;
	py = 0;
	pz = 0;
	state = false;
}
//set the position

Ingredient::Ingredient(float a, float b, float c)
{
	px = a;
	py = b;
	pz = c;
	state = false; //initially not being used
}


//load the object file
void Ingredient::loadObject(const char* filename)
{
	cout << "Loaded object" << endl;
	/*
	int verticesN;
    int positionsN;
    int textureN;
    int normalsN;
    int facesN;

	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;
	std::vector <glm::vec3> temp_normals;
	FILE * file = fopen(filename, "r");

	while (1){
		char lineHeader[128]; 
		int res = fscanf(file, "%s", lineHeader); // LineHeader is the first word of the line
		if (res == EOF)
			break; // end of file


		// If we are on a vertice line, then there are three floats
		if (strcmp (lineHeader, "v") == 0){ 
			glm::vec3 vertex;
			// Now read the rest of the line and store it in vertex
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}

		//If we are on a vt line, then there are two floats
		else if (strcmp (lineHeader, "vt" ) == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}

		else if (strcmp (lineHeader, "vn" ) == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y &normal.z);
			temp_normals.push_back(normal);
		}

		else if ( strcmp( lineHeader, "f" ) == 0 ){
		    std::string vertex1, vertex2, vertex3;
		    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
		    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
		    if (matches != 9){
		        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
		    }
		    vertexIndices.push_back(vertexIndex[0]);
		    vertexIndices.push_back(vertexIndex[1]);
		    vertexIndices.push_back(vertexIndex[2]);
		    uvIndices    .push_back(uvIndex[0]);
		    uvIndices    .push_back(uvIndex[1]);
		    uvIndices    .push_back(uvIndex[2]);
		    normalIndices.push_back(normalIndex[0]);
		    normalIndices.push_back(normalIndex[1]);
		    normalIndices.push_back(normalIndex[2]);
		}*/



	/*
	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;
	std::vector <glm::vec3> temp_normals;
	FILE * file = fopen(filename, "r");

	while (1){
		char lineHeader[128]; 
		int res = fscanf(file, "%s", lineHeader); // LineHeader is the first word of the line
		if (res == EOF)
			break; // end of file


		// If we are on a vertice line, then there are three floats
		if (strcmp (lineHeader, "v") == 0){ 
			glm::vec3 vertex;
			// Now read the rest of the line and store it in vertex
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}

		//If we are on a vt line, then there are two floats
		else if (strcmp (lineHeader, "vt" ) == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}

		else if (strcmp (lineHeader, "vn" ) == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y &normal.z);
			temp_normals.push_back(normal);
		}

		else if ( strcmp( lineHeader, "f" ) == 0 ){
		    std::string vertex1, vertex2, vertex3;
		    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
		    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
		    if (matches != 9){
		        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
		    }
		    vertexIndices.push_back(vertexIndex[0]);
		    vertexIndices.push_back(vertexIndex[1]);
		    vertexIndices.push_back(vertexIndex[2]);
		    uvIndices    .push_back(uvIndex[0]);
		    uvIndices    .push_back(uvIndex[1]);
		    uvIndices    .push_back(uvIndex[2]);
		    normalIndices.push_back(normalIndex[0]);
		    normalIndices.push_back(normalIndex[1]);
		    normalIndices.push_back(normalIndex[2]);
		}

*/

}

/*
//load materials from .mit file
void Ingredient::loadTexture(const char* filename)
{
	printf("");
}*/