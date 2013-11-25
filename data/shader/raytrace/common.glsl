
// Constantes necessaires
#define PI 3.14159265359
#define EPSILON 0.000001

// Données relatives a la caméra
// Camera Pos
uniform vec3 cameraPosition;
//Attributs précalcules pour soucis de perf
uniform vec3 coinSupGauche;
uniform float unitX;
uniform float unitY;

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
	int material;
};

struct ObjectT
{
	Triangle triangle;
	int material;
};

struct ObjectP
{
	Plan plan;
	int material;
};


// Headers
vec4 CouleurPixel(Ray parRayon);
void proc_subtree (double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, Node node);

uniform	ObjectQ listQuadric[MAX_QUAD];
uniform	ObjectT listTriangle[MAX_TRIANGLE];
uniform	ObjectP listPlan[MAX_PLAN];