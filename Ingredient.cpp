#include "ingredient.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
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
	//FILE * file = fopen(path, "r");
	printf("");

}

/*
//load materials from .mit file
void Ingredient::loadTexture(const char* filename)
{
	printf("");
}*/