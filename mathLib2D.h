
#ifndef MATHLIB_2D_H
#define MATHLIB_2D_H

#include<iostream> 
using namespace std; 

class Point2D {
public:
    Point2D();
    Point2D(float inX, float inY);
    float mX;
    float mY;
    float distanceTo(Point2D other);
    float fastDistanceTo(Point2D other);
};


class Vec2D {
public:
    Vec2D();
    Vec2D(float inX, float inY);
    float mX;
    float mY;
    float length();

    Vec2D normalize();
    Vec2D multiply(float scalar);
    Point2D movePoint(Point2D source);
    static Vec2D createVector(Point2D p1, Point2D p2);
};

class Point3D {
public:
    Point3D();
    Point3D(float inX, float inY, float inZ);
    float mX;
    float mY;
    float mZ;
    float distanceTo(Point3D other);
    float fastDistanceTo(Point3D other);
};

class Vec3D {
public:
    Vec3D();
    Vec3D(float inX, float inY, float inZ);
    float mX;
    float mY;
    float mZ;
    float length();

    Vec3D normalize();
    Vec3D multiply(float scalar);
    Point3D movePoint(Point3D source);
    static Vec3D createVector(Point3D p1, Point3D p2);
    Vec3D crossMultiply(Vec3D a);
};

class Particle {
public:
    Particle();
    //newPos();
    //gravity();

    Point3D location;
    Vec3D direction;
    Vec3D rotation;
    float speed;
    int mC [3];
    float size;
    int material;
    int age;
};

#endif
