#version 430
#define EPSILON 0.000001

//Destination du rendu
layout(rgba8) uniform image2D renderCanvas;

layout (local_size_x = 16, local_size_y = 16) in;

const int MAX_PRIM = 20;
// Camera Pos
uniform vec3 cameraPosition;
//Attributs précalcules pour soucis de perf
uniform vec3 coinSupGauche;
uniform float unitX;
uniform float unitY;
// octree
//uniform Octree octree;
uint a; // utile pour la traversee de l'octree

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

struct Node {
	int		id;
	bool	is_terminal;
	Node[8]	child;
};

struct Octree {
	Node		root;
	float		xmin;
	float		xmax;
	float		ymin;
	float		ymax;
	float		zmin;
	float		zmax;
	float		sizeX;
	float		sizeY;
	float		sizeZ;
};



// Headers
vec4 CouleurPixel(Ray parRayon);
void proc_subtree (double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, Node node);

Intersection IntersectWithScene(Ray parRay, Primitive[MAX_PRIM] parPrim)
{
	Intersection intersect;
	return intersect;
}
vec4 computeBRDF(Ray parRay, Intersection parIntersect)
{
	vec4 color;
	return color;
}

Primitive[MAX_PRIM] getPrimitives(Ray parRay)
{
	Primitive listePrim[MAX_PRIM];
	return  listePrim;
}

vec4 Reflect(Ray parRay, Intersection parIntersect)
{
	vec4 color;
	if(parIntersect.isValid)
	{
		Ray reflected;
		reflected.origin = parIntersect.point - EPSILON*parIntersect.normal;		
		reflected.direction = reflect(parRay.direction,parIntersect.normal);
		color = CouleurPixel(reflected);
	}
	return color;
}
vec4 Refract(Ray parRay, Intersection parIntersect)
{
	vec4 color;
	if(parIntersect.isValid)
	{
		Ray refracted;
		refracted.origin = parIntersect.point + EPSILON*parIntersect.normal;	
		// Indice de réraction a changer	
		refracted.direction = refract(parRay.direction,parIntersect.normal,0.5);
		color = CouleurPixel(refracted);
	}
	return color;
}

vec4 CouleurPixel(Ray parRayon)
{
	vec4 finalColor;
	Primitive listePrim[MAX_PRIM] = getPrimitives(parRayon);
	Intersection intersect = IntersectWithScene(parRayon,listePrim);
	finalColor = computeBRDF(parRayon, intersect);
	// Commente a cause du "recursive call" a CouleurPixel
	//finalColor*=Reflect(parRayon, intersect);
	//finalColor*=Refract(parRayon, intersect);
	return finalColor;
}

vec4 RayTrace(vec2 storePos)
{
	//Calcul du rayon a lancer
	Ray rayon;
	rayon.origin = cameraPosition;
	vec3 screenPoint = coinSupGauche + unitX * storePos.x + unitY * storePos.y;
	rayon.direction = screenPoint - cameraPosition;
	// Lancer
	return CouleurPixel(rayon);
}



// ------------------------------------
// void ray_parameter (OCTREE)
// ------------------------------------

void ray_paramter ( Octree octree, Ray ray){
	a = 0;
	
	// GENERALISING FOR RAYS WITH NEGATIVE DIRECTIONS
	if (ray.direction[0]<0.0){
		ray.origin[0] = octree.sizeX-ray.origin[0];
		ray.direction[0] = -ray.direction[0];
		a |= 4;
	}
	if (ray.direction[1]<0.0){
		ray.origin[1] = octree.sizeY-ray.origin[1];
		ray.direction[1] = -ray.direction[1];
		a |= 2;
	}
	if (ray.direction[2]<0.0){
		ray.origin[2] = octree.sizeZ-ray.origin[2];
		ray.direction[2] = -ray.direction[2];
		a |= 1;
	}
	 
	double tx0 = (octree.xmin - ray.origin[0]) * ray.direction[0];
	double tx1 = (octree.xmax - ray.origin[0]) * ray.direction[0];
	double ty0 = (octree.ymin - ray.origin[1]) * ray.direction[1];
	double ty1 = (octree.ymax - ray.origin[1]) * ray.direction[1];
	double tz0 = (octree.zmin - ray.origin[2]) * ray.direction[2];
	double tz1 = (octree.zmax - ray.origin[2]) * ray.direction[2];
	
	if( max(max(tx0,ty0),tz0) < min(min(tx1,ty1),tz1) ){
		proc_subtree(tx0,ty0,tz0,tx1,ty1,tz1,octree.root);
	}
}

// ------------------------------------
// int first_node (OCTREE)
// ------------------------------------	

uint first_node(double tx0, double ty0, double tz0, double txm, double tym, double tzm){
	uint answer = 0;	// 00000000
	double maximum = max(max(tx0,ty0),tz0);

	if(maximum == tx0){ // PLANE YZ
		if(tym < tx0) answer|=2;	// set bit at position 1
		if(tzm < tx0) answer|=1;	// set bit at position 0 			
		return answer; 		
	} 

	if(maximum == ty0){ // PLANE XZ
		if(txm < ty0) answer|=4;	// set bit at position 2
		if(tzm < ty0) answer|=1;	// set bit at position 0			
		return answer; 		
	} 
	
	if(maximum == tz0){ // PLANE XY
		if(txm < tz0) answer|=4;	// set bit at position 2
		if(tym < tz0) answer|=2;	// set bit at position 1
		return answer;	
	}
}


// ------------------------------------
// uint new_node (OCTREE)
// ------------------------------------	

uint new_node(double txm, int x, double tym, int y, double tzm, int z){
	if(txm < tym){
		if(txm < tzm){return x;}  // YZ plane
	}
	else{
		if(tym < tzm){return y;} // XZ plane
	}
	return z; // XY plane;
}


// ------------------------------------
// void proc_subtree (OCTREE)
// ------------------------------------

void proc_subtree (double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, Node node){
	double txm, tym, tzm;
	uint currNode;
 
	if(tx1 < 0.0 || ty1 < 0.0 || tz1 < 0.0) return; 	
	if(node.is_terminal){
		// TODO Noeud terminal atteint : node.id;
		return;
	}
	
	txm = 0.5*(tx0 + tx1);
	tym = 0.5*(ty0 + ty1);
	tzm = 0.5*(tz0 + tz1);
	
	currNode = first_node(tx0,ty0,tz0,txm,tym,tzm);
	do{ 		
		switch (currNode) 	{
		case 0: {  			
			proc_subtree(tx0,ty0,tz0,txm,tym,tzm,node.child[a]);
			currNode = new_node(txm,4,tym,2,tzm,1);
			break;}
		case 1: {
			proc_subtree(tx0,ty0,tzm,txm,tym,tz1,node.child[1^a]);
			currNode = new_node(txm,5,tym,3,tz1,8);
			break;}
		case 2: {
			proc_subtree(tx0,tym,tz0,txm,ty1,tzm,node.child[2^a]);
			currNode = new_node(txm,6,ty1,8,tzm,3);
			break;}
		case 3: {
			proc_subtree(tx0,tym,tzm,txm,ty1,tz1,node.child[3^a]);
			currNode = new_node(txm,7,ty1,8,tz1,8);
			break;}
		case 4: {
			proc_subtree(txm,ty0,tz0,tx1,tym,tzm,node.child[4^a]);
			currNode = new_node(tx1,8,tym,6,tzm,5);
			break;}
		case 5: {
			proc_subtree(txm,ty0,tzm,tx1,tym,tz1,node.child[5^a]);
			currNode = new_node(tx1,8,tym,7,tz1,8);
			break;}
		case 6: {
			proc_subtree(txm,tym,tz0,tx1,ty1,tzm,node.child[6^a]);
			currNode = new_node(tx1,8,ty1,8,tzm,7);
			break;}
		case 7: {
			proc_subtree(txm,tym,tzm,tx1,ty1,tz1,node.child[7^a]);
			currNode = 8;
			break;}
		}
	} while (currNode<8);
}

void main() 
{
	 // Recuperation de la taille de l'image
     ivec2 sizeXY = imageSize(renderCanvas);
     
     // On récupère le point de la texture qui nous a été attribue
     ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
     imageStore(renderCanvas, storePos, RayTrace(storePos));
}
