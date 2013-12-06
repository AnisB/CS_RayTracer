
/* 
 * Auteur Anis Benyoub
 * Classe qui permet de gérer la camera
 */

#include "camera.h"

#include "shadermanager.h"
#include <math.h>
#include "common/defines.h"

Camera::Camera()
: FTransformation(MatrixInit::Identity)
, FLens(50.0)
, FAngleView(45.0)
{
	// Calul de la hayeur de l'ecran
	FHauteurEcran =  tan(FAngleView/2)*FLens;
	FPasX = SCREEN_X;
	FPasY = SCREEN_Y;
}

Camera::~Camera()
{
	
}

// Rotation autour de Y
void Camera::Yaw(double parAngle)
{
	FTransformation = FTransformation*Matrix4::rotateYAxis(parAngle);
}
// Translation d'un vecteur
void Camera::Translate(const Vector3& parDir)
{
	FTransformation = FTransformation*Matrix4::translate(parDir);
}
// Rotation autour de X
void Camera::Pitch(double parAngle)
{
	FTransformation = FTransformation*Matrix4::rotateXAxis(parAngle);
}
void Camera::UpdateValues(GLuint parShaderID)
{
	// Transformations
	const Vector3& pos = FTransformation.getTranslate();
	const Vector3& zAxis = FTransformation.zAxis();
	const Vector3& yAxis = FTransformation.yAxis();
	const Vector3& xAxis = FTransformation.xAxis();
	// Injection de la position
	ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.getTranslate(), "cameraPosition");

	// Precalcules 
	const Vector3& centreEcran = pos+zAxis*FLens;
	const Vector3& coinSupGauche = centreEcran - yAxis * FHauteurEcran - xAxis * FHauteurEcran * RATIO;
	// Injection des données pour calculer les rayons primaires
	ShaderManager::Instance().InjectVec3(parShaderID, coinSupGauche, "coinSupGauche");
	ShaderManager::Instance().InjectVec3(parShaderID, xAxis*FHauteurEcran*2, "unitX");
	ShaderManager::Instance().InjectVec3(parShaderID, yAxis*FHauteurEcran*2, "unitY");
}
