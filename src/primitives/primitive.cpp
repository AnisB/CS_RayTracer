
/* 
 * Auteur Anis Benyoub
 * Fichier qui permet de gérer les primitive en parralèle avec le glsl
 */

#include "primitive.h"
 
 
 
 // Triangle
std::ostream& operator<< (std::ostream& stream, const Triangle& parTriangle)
{
	stream<<"P0 "<<parTriangle.p0<<std::endl;
	stream<<"P1 "<<parTriangle.p1<<std::endl;
	stream<<"P3 "<<parTriangle.p2<<std::endl;
	stream<<"normale "<<parTriangle.normale<<std::endl;
	return stream;
}



// Materiau 
std::ostream& operator<< (std::ostream& stream, const Materiau& parMat)
{
	stream<<"color "<<parMat.color<<std::endl;
	stream<<"refractance "<<parMat.coeffReflexion<<std::endl;
	stream<<"reflectance "<<parMat.coeffRefraction<<std::endl;
	return stream;
}

// Primitive 
std::ostream& operator<< (std::ostream& stream, const Primitive& parTriangle)
{
	stream<<"type "<<parTriangle.type<<std::endl;
	stream<<"index "<<parTriangle.index<<std::endl;
	stream<<"materiau "<<parTriangle.materiau<<std::endl;
	return stream;
}


// Lumière
std::ostream& operator<< (std::ostream& stream, const Light& parLum)
{
	stream<<"color "<<parLum.color<<std::endl;
	stream<<"intensity "<<parLum.intensity<<std::endl;
	stream<<"position "<<parLum.position<<std::endl;
	return stream;
}
