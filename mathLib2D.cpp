#include <math.h>
#include "mathLib2D.h"
#include<tuple>

typedef tuple <int,int,int> color;


// Point2D Class

/**
*  \brief Point2D Default constructor
*  \return Point2D
*/
Point2D::Point2D(){
	this->mX=0;
	this->mY=0;
}

/**
 *  \brief Point2D Constructor with two arguments
 *  \param inX x value of Point2D
 *  \param inY y value of Point2D
 *  \return Poing2D
 */
Point2D::Point2D(float inX, float inY){
	this->mX=inX;
	this->mY=inY;
}

// Point2D distance to function

/**
 *  \brief Point2D Distance function for vector
 *  \param other , the target Point2D to find the distance to
 *  \return float measurement of the distance
 */
float Point2D::distanceTo(Point2D other){
	return sqrt(pow((other.mX - this->mX),2)+ pow((other.mY-this->mY),2));
}

// Point2D distance to function that does not use square root
/**
 *  \brief Point2D Distance function for vector without square root
 *  \param other , the target Point2D to find the distance to
 *  \return float measurement of the distance
 */
float Point2D::fastDistanceTo(Point2D other){
	return pow((other.mX - this->mX),2)+ pow((other.mY-this->mY),2);
}


// Vec2D Class
/**
 *  \brief Vec2D default class constructor
 *  \return Vec2D
 */
Vec2D::Vec2D(){
	this->mX=0;
	this->mY=0;
}

/**
 *  \brief vec2D class constructor with two arguments
 *  \param inX x value of vector
 *  \param inY y value of vector
 *  \return Vec2D with corresponding x and y value
 */
Vec2D::Vec2D(float inX, float inY){
	this->mX=inX;
	this->mY=inY;
}

/**
 *  \brief vec2D calculates length of vector
 *  \return float measurement of the distance
 */
float Vec2D::length(){
	return sqrt(pow(this->mX,2) + pow(this->mY,2));
}

/**
 *  \brief vec2D Calculates a normalized vector of the given vector
 *  \return vec2D of the normalized vector
 */
Vec2D Vec2D::normalize(){
	//float magnitude = sqrt(pow(this->mX,2) + pow(this->mY,2));
	float m1 = this->length();
	return Vec2D(this->mX/m1, this->mY/m1);
}

/**
 *  \brief vec2D multiplies the given vector by scalar given
 *  \param scalar to multiply the vector by
 *  \return new Vec2D that is multiplied by the scalar
 */
Vec2D Vec2D::multiply(float scalar){
	return Vec2D(this->mX*scalar, this->mY*scalar);
}

/**
 *  \brief Vec2D Creates a vector with two points
 *  \param p1 first point
 *  \param p2 second point
 *  \return Vec2D made of the two points
 */
Vec2D Vec2D::createVector(Point2D p1, Point2D p2){
	return Vec2D(p2.mX - p1.mX,p2.mY-p1.mY);
}

/**
 *  \brief Vec2D Moves a Point2D by a vector
 *  \param source Point2D to move
 *  \return Point2D reflecting the moved Point2D
 */
Point2D Vec2D::movePoint(Point2D source){
	Point2D pointT=Point2D(source.mX+this->mX,source.mY+this->mY);
	return pointT;
}


Particle::Particle()
{
	this->location.mX = 0;
    this->location.mY = 0;
    this->location.mZ = 0;
    //initial direction:
    this->direction.mX = (((double)rand() / RAND_MAX) - 0.5); 
    this->direction.mY = (((double)rand() / RAND_MAX) - 0.5); 
    this->direction.mZ = (((double)rand() / RAND_MAX) - 0.5);

    //set rotation angle
    this->rotation.mX = rand () % 360;
    this->rotation.mX = rand () % 360;
    this->rotation.mX = rand () % 360;

    //initial speed
	this->speed = 1.008;

	//set the color:
    this->mC[0] = 0;
    this->mC[1] = 0;
    this->mC[2] = 1;

    //size: 0.05
    this->size = 0.05;

    //range: 0 - 2
    this->material = rand() % 3; 

    //age
    this->age = 0;


}

/*
void Particle::newPos()
{
    this->position.px = this->position.px + this->direction.dx * speed;
    this->position.py = this->position.py + this->direction.dy * speed;
    this->position.pz = this->position.pz + this->direction.dz * speed;
}

void Particle::gravity()
{
    this->direction.dy -= 0.007;
}
*/

// Point3D Class
Point3D::Point3D(){
	this->mX=0;
	this->mY=0;
	this->mZ=0;
}

Point3D::Point3D(float inX, float inY, float inZ){
	this->mX=inX;
	this->mY=inY;
	this->mZ=inZ;
}

// Vec3D Class
/**
 *  \brief Vec3D default class constructor
 *  \return Vec3D
 */
Vec3D::Vec3D(){
	this->mX=0;
	this->mY=0;
	this->mZ=0;
}

/**
 *  \brief vec2D class constructor with two arguments
 *  \param inX x value of vector
 *  \param inY y value of vector
 *  \return Vec2D with corresponding x and y value
 */
Vec3D::Vec3D(float inX, float inY, float inZ){
	this->mX=inX;
	this->mY=inY;
	this->mZ=inZ;
}


float Vec3D::length(){
	return sqrt(pow(this->mX,2) + pow(this->mY,2) + pow(this->mZ,2));
}


/**
 *  \brief vec2D Calculates a normalized vector of the given vector
 *  \return vec2D of the normalized vector
 */
Vec3D Vec3D::normalize(){
	//float magnitude = sqrt(pow(this->mX,2) + pow(this->mY,2));
	float m1 = this->length();
	return Vec3D(this->mX/m1, this->mY/m1, this->mZ/m1);
}

/**
 *  \brief Vec3D Moves a Point2D by a vector
 *  \param source Point2D to move
 *  \return Point3D reflecting the moved Point3D
 */
Point3D Vec3D::movePoint(Point3D source){
	Point3D pointT=Point3D(source.mX+this->mX,source.mY+this->mY, source.mZ+this->mZ);
	return pointT;
}

Vec3D Vec3D::multiply(float scalar){
	return Vec3D(this->mX*scalar, this->mY*scalar, this->mZ*scalar);
}

Vec3D Vec3D::crossMultiply(Vec3D a){
	float tempX;
	float tempY;
	float tempZ;
}