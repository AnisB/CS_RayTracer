#include "camera.h"

#include "shadermanager.h"

Camera::Camera()
: FPosition(0.0,0.0,0.0)
, FDirection(0.0,0.0,1.0)
, FLens(50.0)
, FAngleView(45.0)
{
	
}

Camera::~Camera()
{
	
}


void Camera::UpdateValues(GLuint parShaderID)
{
	ShaderManager::Instance().InjectVec3(parShaderID, FPosition, "cameraPos");
	ShaderManager::Instance().InjectVec3(parShaderID, FDirection, "cameraDir");
	ShaderManager::Instance().Injectd(parShaderID ,FLens, "focalDistance");
	ShaderManager::Instance().Injectd(parShaderID, FAngleView, "viewAngle");
}