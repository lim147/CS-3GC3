#include "ingredient.h"
#include "mathLib2D.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

//load the object file
bool Ingredient::loadObject(const char* filename)
{
	cout << "Loaded object" << endl;

    // Counters
    int p = 0;
    int t = 0;
    int n = 0;
    int f = 0;
    
    // Open OBJ file
    ifstream inOBJ;
    inOBJ.open(filename);
    if(!inOBJ.good())
    {
        cout << "ERROR OPENING OBJ FILE" << endl;
        exit(1);
    }
    
    // Read OBJ file
    while(!inOBJ.eof())
    {
        string line;
        getline(inOBJ, line);
        string type = line.substr(0,2);
        
        // Positions
        if(type.compare("v ") == 0)
        {
    		// 1
    		// Copy line for parsing
    		char* l = new char[line.size()+1];
    		memcpy(l, line.c_str(), line.size()+1);
    		        
    		// 2
    		// Extract tokens
    		Point3D vertex; // Create a Point3D to hold the values
    		strtok(l, " "); // Skips past the "v" part

    		//The stof() function in C++ interprets the contents of a string as a floating point number
    		vertex.mX = stof(strtok(NULL, " "));

    		vertex.mY = stof(strtok(NULL, " ")); 
    		vertex.mZ = stof(strtok(NULL, " ")); 

    		temp_vertices.push_back(vertex);

    		// 3
    		// Wrap up
    		delete[] l;
    		p++;
        }
	        
		        // Texels
		else if(type.compare("vt") == 0)
		{
		    char* l = new char[line.size()+1];
		    memcpy(l, line.c_str(), line.size()+1);

			Point2D uv;      
		    strtok(l, " ");

		    uv.mX = stof(strtok(NULL, " ")); 
		    uv.mY = stof(strtok(NULL, " "));

		    temp_uvs.push_back(uv);

		    delete[] l;
		    t++;
		}
		        
		// Normals
		else if(type.compare("vn") == 0)
		{
		    char* l = new char[line.size()+1];
		    memcpy(l, line.c_str(), line.size()+1);
		            
		    Vec3D normal;
		    strtok(l, " ");
		    normal.mX = stof(strtok(NULL, " "));
		    normal.mY = stof(strtok(NULL, " "));
		    normal.mZ = stof(strtok(NULL, " "));

		    temp_normals.push_back(normal);
		            
		    delete[] l;
		    n++;		
		}

/*
		    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
		    	&vertexIndex[0], &uvIndex[0], &normalIndex[0], 
		    	&vertexIndex[1], &uvIndex[1], &normalIndex[1], 
		    	&vertexIndex[2], &uvIndex[2], &normalIndex[2] );
*/   

		// Faces
		else if(type.compare("f ") == 0)
		{
		    char* l = new char[line.size()+1];
		    memcpy(l, line.c_str(), line.size()+1);

		    /*
		    string str = l;
		    vector<string> v = split(str, ' ');
		    v.erase (myvector.begin()); // deletes the f from the vector? 
		    vector<string> v2; // Second vector to hold the numbers

		    for(std::size_t i=0; i<v.size(); ++i) 
    			v2.push_back(split(v[i], ' ')); 
			 //f 1214/1543/426 1215/1545/358 1172/1546/369 1173/1544/370
		     */  
		        
		    strtok(l, " ");
		    for(int i=0; i<3; i++){
		    	vertexIndices.push_back(stoi(strtok(NULL, " /")));
		    	uvIndices    .push_back(stoi(strtok(NULL, " /")));
		    	normalIndices.push_back(stoi(strtok(NULL, " /")));
		    	//f 140/154/127 119/153/126 135/176/149 155/167/140		    	
		    }

		    delete[] l;
		    f++;
		}

	}
	    // Close OBJ file
	    inOBJ.close();
	    return true;
}



/*
//load materials from .mit file
void Ingredient::loadTexture(const char* filename)
{
	printf("");
}*/