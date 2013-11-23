#include "camera.h"

#include "shadermanager.h"
#include <math.h>
#include "common/defines.h"

Camera::Camera()
: FTransformation()
, FPosition(0.0,0.0,0.0)
, FDirection(0.0,0.0,1.0)
, FUpAxis(0.0,1.0,0.0)
, FXAxis(1.0,0.0,0.0)
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


void Camera::InjectFixedValues(GLuint parShaderID)
{
	// Data de base
	ShaderManager::Instance().Injectd(parShaderID ,FLens, "focalDistance");
	ShaderManager::Instance().Injectd(parShaderID, FAngleView, "viewAngle");	
}

void Camera::UpdateValues(GLuint parShaderID)
{
	// Transformations a utiliser ultérieurement
	//const Vector3& pos = FTransformation.getTranslate();
	//const Vector3& zAxis = FTransformation.zAxis();
	//const Vector3& yAxis = FTransformation.yAxis();
	//const Vector3& xAxis = FTransformation.xAxis();
	//ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.getTranslate(), "cameraPos");
	//ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.zAxis(), "cameraDir");
	//ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.yAxis(), "cameraUpAxis");
	//ShaderManager::Instance().InjectVec3(parShaderID, FTransformation.xAxis(), "cameraPos");

	// Code intermédiaire
	const Vector3& pos = FPosition;
	const Vector3& zAxis = FDirection;
	const Vector3& yAxis = FUpAxis;
	const Vector3& xAxis = FXAxis;
	ShaderManager::Instance().InjectVec3(parShaderID, FPosition, "cameraPos");
	ShaderManager::Instance().InjectVec3(parShaderID, FDirection, "cameraDir");
	ShaderManager::Instance().InjectVec3(parShaderID, FUpAxis, "cameraUpAxis");
	ShaderManager::Instance().InjectVec3(parShaderID, FXAxis, "cameraXAxis");

	// Precalcules 
	const Vector3& centreEcran = pos+zAxis*FLens;
	const Vector3& coinSupGauche = centreEcran - yAxis * SCREEN_Y - xAxis * SCREEN_X * RATIO;
	ShaderManager::Instance().InjectVec3(parShaderID, coinSupGauche, "coinSupGauche");
	ShaderManager::Instance().InjectVec3(parShaderID, xAxis*FPasX, "unitX");
	ShaderManager::Instance().InjectVec3(parShaderID, yAxis*FPasY, "unitY");
}