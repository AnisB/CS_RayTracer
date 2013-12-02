// Constantes necessaires
#define PI 3.14159265359
#define EPSILON 0.000001
#define ENERGY_MIN 0.01
#define INDICE_PEAU 1.44

#define PRIMITIVE_TRIANGLE  0
#define PRIMITIVE_PLAN      1
#define PRIMITIVE_QUADRIQUE 2

#define TRIANGLE_PARAM 17.0

#define p0x 0.0/TRIANGLE_PARAM
#define p0y 1.0/TRIANGLE_PARAM
#define p0z 2.0/TRIANGLE_PARAM

#define u0 3.0/TRIANGLE_PARAM
#define v0 4.0/TRIANGLE_PARAM

#define p1x 5.0/TRIANGLE_PARAM
#define p1y 6.0/TRIANGLE_PARAM
#define p1z 7.0/TRIANGLE_PARAM

#define u1 8.0/TRIANGLE_PARAM
#define v1 9.0/TRIANGLE_PARAM

#define p2x 10.0/TRIANGLE_PARAM
#define p2y 11.0/TRIANGLE_PARAM
#define p2z 12.0/TRIANGLE_PARAM

#define u2 13.0/TRIANGLE_PARAM
#define v2 14.0/TRIANGLE_PARAM

#define nx 15.0/TRIANGLE_PARAM
#define ny 16.0/TRIANGLE_PARAM
#define nz 17.0/TRIANGLE_PARAM


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
	vec2 uv0;
	vec3 p1;
	vec2 uv1;
	vec3 p2;
	vec2 uv2;
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
	int texSpecular;
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

uniform sampler2D  listTriangles;
uniform sampler2D listPrimitives;
uniform sampler2D listMateriaux;
uniform sampler2D listNoeuds;
uniform	sampler2D listQuadriques;

uniform	sampler2D listTex[NB_TEX];


uniform	Plan listPlan[NB_PLAN];
uniform	Light listLight[NB_LIGHTS];



Triangle getTriangleByIndex(int parIndexTriangle)
{
	Triangle unTriangle;
	/*
		Triangle unTriangle;

	float triNormIndex = float(parIndexTriangle)/(float(NB_TRIANGLE)-1);
	
    unTriangle.p0 = texture(listTriangles, vec2(0.0/6.0,triNormIndex)).r;
    unTriangle.uv0 = texture(listTriangles, vec2(0.0/6.0,triNormIndex)).r;

    unTriangle.p1 = texture(listTriangles, vec2(2.0/6.0,triNormIndex)).rgb;    
    unTriangle.uv1 = texture(listTriangles, vec2(3.0/6.0,triNormIndex)).rg;

    unTriangle.p2 = texture(listTriangles, vec2(4.0/6.0,triNormIndex)).rgb;    
    unTriangle.uv2 = texture(listTriangles, vec2(5.0/6.0,triNormIndex)).rg;

    unTriangle.normale = texture(listTriangles, vec2(6.0/6.0,triNormIndex)).rgb;
    */
	float triNormIndex = float(parIndexTriangle)/(float(NB_TRIANGLE)-1);
    unTriangle.p0.x = texture(listTriangles, vec2(p0x,triNormIndex)).r;
    unTriangle.p0.y = texture(listTriangles, vec2(p0y,triNormIndex)).r;
    unTriangle.p0.z = texture(listTriangles, vec2(p0z,triNormIndex)).r;

    unTriangle.uv0.x = texture(listTriangles, vec2(u0,triNormIndex)).r;
    unTriangle.uv0.y = texture(listTriangles, vec2(v0,triNormIndex)).r;

    unTriangle.p1.x = texture(listTriangles, vec2(p1x,triNormIndex)).r;
    unTriangle.p1.y = texture(listTriangles, vec2(p1y,triNormIndex)).r;
    unTriangle.p1.z = texture(listTriangles, vec2(p1z,triNormIndex)).r;    
    
    unTriangle.uv1.x = texture(listTriangles, vec2(u1,triNormIndex)).r;
    unTriangle.uv1.y = texture(listTriangles, vec2(v1,triNormIndex)).r;

    unTriangle.p2.x = texture(listTriangles, vec2(p2x,triNormIndex)).r;
    unTriangle.p2.y = texture(listTriangles, vec2(p2y,triNormIndex)).r;
    unTriangle.p2.z = texture(listTriangles, vec2(p2z,triNormIndex)).r;
    
    unTriangle.uv2.x = texture(listTriangles, vec2(u2,triNormIndex)).r;
    unTriangle.uv2.y = texture(listTriangles, vec2(v2,triNormIndex)).r;

    unTriangle.normale.x = texture(listTriangles, vec2(nx,triNormIndex)).r;
    unTriangle.normale.y = texture(listTriangles, vec2(ny,triNormIndex)).r;
    unTriangle.normale.z = texture(listTriangles, vec2(nz,triNormIndex)).r;
 	
    unTriangle.p0-= vec3(0.5);
    unTriangle.p1-= vec3(0.5);
    unTriangle.p2-= vec3(0.5);
    unTriangle.normale-= vec3(0.5);
    
    unTriangle.p0*=400;
    unTriangle.p1*=400;
    unTriangle.p2*=400; 
    unTriangle.normale*=400;
    return unTriangle;
}

Quadrique getQuadricByIndex(int parIndexQuad)
{
	Quadrique uneQuad;

	float quadNormIndex = 0.0;
    uneQuad.A = texture(listQuadriques, vec2(0.0,quadNormIndex)).r;
    uneQuad.B = texture(listQuadriques, vec2(1.0/9.0,quadNormIndex)).r;
 	uneQuad.C = texture(listQuadriques, vec2(2.0/9.0,quadNormIndex)).r;

    uneQuad.D = texture(listQuadriques, vec2(3.0/9.0,quadNormIndex)).r;
    uneQuad.E = texture(listQuadriques, vec2(4.0/9.0,quadNormIndex)).r;
 	uneQuad.F = texture(listQuadriques, vec2(5.0/9.0,quadNormIndex)).r;
 	
    uneQuad.G = texture(listQuadriques, vec2(6.0/9.0,quadNormIndex)).r;
    uneQuad.H = texture(listQuadriques, vec2(7.0/9.0,quadNormIndex)).r;
 	uneQuad.I = texture(listQuadriques, vec2(8.0/9.0,quadNormIndex)).r; 
 	
 	uneQuad.J = texture(listQuadriques, vec2(9.0/9.0,quadNormIndex)).r; 
 	
    uneQuad.A-= vec3(0.5);
    uneQuad.B-= vec3(0.5);
    uneQuad.C-= vec3(0.5);
    
    uneQuad.D-= vec3(0.5);
    uneQuad.E-= vec3(0.5);
    uneQuad.F-= vec3(0.5);
    
    uneQuad.G-= vec3(0.5);
    uneQuad.H-= vec3(0.5);
    uneQuad.I-= vec3(0.5);
    
    uneQuad.J-= vec3(0.5);
    
    uneQuad.A*=400;
    uneQuad.B*=400;
    uneQuad.C*=400;
    
    uneQuad.D*=400;
    uneQuad.E*=400;
    uneQuad.F*=400;
    
    uneQuad.G*=400;
    uneQuad.H*=400;
    uneQuad.I*=400;
    
    uneQuad.J*=400;

    return uneQuad;
}


Primitive getPrimitiveByIndex(int parIndexPrim)
{
    Primitive unePrim;
    float primIndex = float(parIndexPrim)/(float(NB_PRIM)-1);
    float type = texture(listPrimitives, vec2(0.0,primIndex)).r;
    float index = texture(listPrimitives,vec2(0.5,primIndex)).r;
    float materiau = texture(listPrimitives, vec2(1.0,primIndex)).r;

    
    index*=float(NB_PRIM-1);
    type*=2.0;
    materiau*=float(NB_MAT-1);
    
    unePrim.index = int(index);
    unePrim.type = int(type);
    unePrim.materiau = int(materiau);
    return unePrim;
}

Materiau getMateriauByIndex(int parMateriauIndex)
{
	Materiau unMat;
	float matIndex = float(parMateriauIndex)/(float(NB_MAT)-1);
	vec4 colorMat;
    colorMat.x = texture(listMateriaux, vec2(0.0,matIndex)).r;
    colorMat.y = texture(listMateriaux,vec2(1.0/10.0,matIndex)).r;
    colorMat.z = texture(listMateriaux, vec2(2.0/7.0,matIndex)).r;
    colorMat.w = 1.0;
    unMat.color = colorMat;
    float albeFloat = texture(listMateriaux,vec2(0.8,matIndex)).r;
    float roughFloat = texture(listMateriaux, vec2(0.9,matIndex)).r;
    float specFloat = texture(listMateriaux, vec2(1.0,matIndex)).r;
    unMat.texAlbedo = int( albeFloat*2.0);
    unMat.texSpecular = int( albeFloat*2.0);
    unMat.texRough = int( albeFloat*2.0);
	
    
    return unMat;
}

vec4 getMateriauColorByPrimID(int parIndexPrim)
{
	Primitive prim = getPrimitiveByIndex(parIndexPrim);
	return getMateriauByIndex(prim.materiau).color;
}


