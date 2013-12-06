
/* 
 * Auteur Anis Benyoub
 * Classe qui permet de gérer la camera
 */
 
#ifndef CAMERA
#define CAMERA

#include "math/matrix4.h"
#include "math/vector3.h"
#include "defines.h"

class Camera
{
	public:
		// Constructeur
		Camera();
		// Destructeur
		~Camera();
		// méthode de rotation
		void Yaw(double parAngle);
		void Pitch(double parAngle);
		// Methode de translation
		void Translate(const Vector3& parDir);
		// Mise a jour des valeurs dans un programme
		void UpdateValues(GLuint parShaderID);

	protected:
		// Transformation
		Matrix4 FTransformation;
		// Informations de perspective
		double FLens;
		double FAngleView;
		double FHauteurEcran;
		double FPasX;
		double FPasY;

};

#endif //CAMERA
