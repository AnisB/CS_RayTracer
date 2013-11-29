// Constantes necessaires
#define PI 3.14159265359
#define EPSILON 0.000001
#define ENERGY_MIN 0.1
#define INDICE_PEAU 1.44

#define PRIMITIVE_TRIANGLE  0
#define PRIMITIVE_PLAN      1
#define PRIMITIVE_QUADRIQUE 2

const vec4 backGroundColor = vec4(0.0,0,0,1.0); 
// Données relatives a la caméra
// Camera position

uniform vec3 cameraPosition;
//Attributs précalcules pour soucis de perf
uniform vec3 coinSupGauche;
uniform vec3 unitX;
uniform vec3 unitY;


// Primitives
struct Triangle
{
	vec3 p0;
	vec3 p1;
	vec3 p2;
	vec3 normale;
};

struct Plan
{
	vec3 p0;
	vec3 p1;
	vec3 p2;
	vec3 p3;
	vec3 normale;
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
	float energy;			
};

// Primitive gobale
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
	vec3 point;
	float distance;				
	vec3 normal;
	int obj;
	vec2 uv;	
};

//Materiau
struct Materiau
{
	vec4 color;
	float refractance;
	float reflectance;
	float indiceRefraction;
	float diff;
	float spec;
	int texAlbedo;
	int texRough;
};

// Primitive gobale
struct Light
{
	vec3 position;
	float intensity;
	vec4 colorSpec;
	vec4 colorDiff;
};


// Headers
vec4 CouleurPixel(Ray parRayon);
//void proc_subtree (double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, Node node);

uniform	sampler2D textures[NB_TEX];

uniform	Quadrique listQuadrique[NB_QUAD];
uniform	Triangle listTriangle[NB_TRIANGLE];
uniform	Plan listPlan[NB_PLAN];
uniform	Primitive listPrim[NB_PRIM];
uniform	Materiau listMateriau[NB_MAT];
uniform	Light listLight[NB_LIGHTS];

