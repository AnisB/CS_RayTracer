#ifndef PRIMITIVE
#define PRIMITIVE

#include <vector>
#include "math/vector3.h"
#include "math/vector4.h"

enum TypePrimitive
{
    PRIMITIVE_TRIANGLE = 0,
    PRIMITIVE_PLAN = 1,
    PRIMITIVE_QUADRIQUE = 2
};

struct Triangle
{
    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
};

struct Plan
{
    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;
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

// Primitive
struct Primitive
{
    int type;
    int index;
    int materiau;
};

// Intersection
struct Intersection
{
    bool isValid;
    Vector3 point;
    float distance;
    Vector3 normal;
    Primitive obj;
};

//Materiau
struct Materiau
{
    Vector4 color;
    float coeffReflexion;
    float coeffRefraction;
    float indiceRefraction;
    float diff;
    float spec;
    int texAlbedo;
    int texRough;
};

// Lumieres
struct Light
{
    Vector3 position;
    Vector3 color;
    float intensity;
};

#endif //PRIMITIVE
