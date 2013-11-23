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

		void InjectFixedValues(GLuint parShaderID);
		void UpdateValues(GLuint parShaderID);

	protected:
		Matrix4 FTransformation;
		Vector3 FPosition;
		Vector3 FDirection;
		Vector3 FUpAxis;
		Vector3 FXAxis;
		double FLens;
		double FAngleView;
		double FHauteurEcran;
		double FPasX;
		double FPasY;

};

#endif //CAMERA