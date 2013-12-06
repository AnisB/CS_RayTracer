
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
	FHauteurEcran =  tan(FAngleView/2)*FLens;
	//FPasX = RATIO * FHauteurEcran * 2/SCREEN_X; 
	//FPasY = FHauteurEcran * 2/SCREEN_Y;
	FPasX = SCREEN_X;
	FPasY = SCREEN_Y;
}

Camera::~Camera()
{
	
}

void Camera::Yaw(double parAngle)
{
	FTransformation = FTransformation*Matrix4::rotateYAxis(parAngle);
}
void Camera::Translate(const Vector3& parDir)
{
	FTransformation = FTransformation*Matrix4::translate(parDir);
}
void Camera::Pitch(double parAngle)
{
	FTransformation = FTransformation*Matrix4::rotateXAxis(parAngle);
}
void Camera::InjectFixedValues(GLuint parShaderID)
{
	// Data de base
	ShaderManager::Instance().Injectd(parShaderID ,FLens, "focalDistance");
	ShaderManager::Instance().Injectd(parShaderID, FAngleView, "viewAngle");	
}

void Camera::UpdateValues(GLuint parShaderID)
{
	// Transformations
	const Vector3& pos = FTransformation.getTranslate();
	const Vector3& zAxis = FTransformation.zAxis();
	const Vector3& yAxis = FTransformation.yAxis();
	const Vector3& xAxis = FTransformation.xAxis();
	ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.getTranslate(), "cameraPosition");

	// Precalcules 
	const Vector3& centreEcran = pos+zAxis*FLens;
	const Vector3& coinSupGauche = centreEcran - yAxis * FHauteurEcran - xAxis * FHauteurEcran * RATIO;
	ShaderManager::Instance().InjectVec3(parShaderID, coinSupGauche, "coinSupGauche");
	ShaderManager::Instance().InjectVec3(parShaderID, xAxis*FHauteurEcran*2, "unitX");
	ShaderManager::Instance().InjectVec3(parShaderID, yAxis*FHauteurEcran*2, "unitY");
}
