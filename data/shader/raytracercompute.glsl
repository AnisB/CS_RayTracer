#version 430


// Constantes numériques utiles

layout(rgba8) uniform image2D renderCanvas;

layout (local_size_x = 16, local_size_y = 16) in;

// Camera informations
uniform vec3 cameraPosition;
uniform vec3 cameraDirection;
uniform vec3 cameraUpAxis;
uniform float viewAngle;
uniform float focalDistance;

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
	Quadrique quadric;
	Materiau material;
};

struct ObjectP
{
	Quadrique quadric;
	Materiau material;
};

vec4 Intersect(Ray parRayon)
{
	return vec4(0.3,0.4,0.8,1.0);
}

vec4 RayTrace(vec2 storePos)
{
	//Calcul du rayon a lancer
	Ray rayon;
	rayon.origin = cameraPosition;
	//rayon.direction =...
	
	return Intersect(rayon);
}
void main() 
{
	 // Recuperation de la taille de l'image
     ivec2 sizeXY = imageSize(renderCanvas);
     
     // On récupère le point de la texture qui nous a été attribue
     ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
     imageStore(renderCanvas, storePos, RayTrace(storePos));
}




