#ifndef CAMERA
#define CAMERA

#include "math/matrix4.h"
#include "math/vector3.h"
#include "defines.h"

class Camera
{
	public:
		Camera();
		~Camera();

		void UpdateValues(GLuint parShaderID);

	protected:
		Matrix4 FTransformation;
		Vector3 FPosition;
		Vector3 FDirection;
		double FLens;
		double FAngleView;

};

#endif //CAMERA