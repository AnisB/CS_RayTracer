#ifndef PRIMITIVE
#define PRIMITIVE

#include <vector>

// Vectors
struct vec3
{
    float x;
    float y;
    float z;
};

struct vec4
{
    float x;
    float y;
    float z;
    float w;
};

// Primitives
struct Triangle
{
    vec3 p0;
    vec3 p1;
    vec3 p2;
};

struct Plan
{
    vec3 p1;
    vec3 p2;
    vec3 p3;
    vec3 p4;
};

struct Quadrique
{
    float A;
    float B;
    float C;
    float D;
    float E;
    float F;
    float G;
    float H;
    float I;
    float J;
};

// Rayon
struct Ray
{
    vec3 origin;
    vec3 direction;
};

// Primitive
struct Primitive
{
    int type;
    int index;
};

// Intersection
struct Intersection
{
    bool isValid;
    vec3 point;
    float distance;
    vec3 normal;
    Primitive obj;
};

//Materiau
struct Materiau
{
    vec4 color;
};

// Objets
struct ObjectQ
{
    Quadrique quadric;
    Materiau material;
};

struct ObjectT
{
    Triangle triangle;
    Materiau material;
};

struct ObjectP
{
    Plan plan;
    Materiau material;
};

// Lumieres
struct Light
{
    vec3 position;
    float intensity;
};

#endif //PRIMITIVE
