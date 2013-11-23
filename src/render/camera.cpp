#include "camera.h"

#include "shadermanager.h"
#include <math.h>
#include "common/defines.h"

Camera::Camera()
: FTransformation(MatrixInit::Identity)
, FLens(50.0)
, FAngleView(45.0)
{
	FHauteurEcran =  tan(FAngleView)*FLens;
	FPasX = RATIO * FHauteurEcran * 2/SCREEN_X; 
	FPasY = FHauteurEcran * 2/SCREEN_Y;
}

Camera::~Camera()
{
	
}

void Camera::Yaw(double parAngle)
{
	// TODO 
}
void Camera::Pitch(double parAngle)
{
	// TODO 
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
	ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.getTranslate(), "cameraPos");
	ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.zAxis(), "cameraDir");
	ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.yAxis(), "cameraUpAxis");
	ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.xAxis(), "cameraPos");


	// Precalcules 
	const Vector3& centreEcran = pos+zAxis*FLens;
	const Vector3& coinSupGauche = centreEcran - yAxis * SCREEN_Y - xAxis * SCREEN_X * RATIO;
	ShaderManager::Instance().InjectVec3(parShaderID, coinSupGauche, "coinSupGauche");
	ShaderManager::Instance().InjectVec3(parShaderID, xAxis*FPasX, "unitX");
	ShaderManager::Instance().InjectVec3(parShaderID, yAxis*FPasY, "unitY");
}