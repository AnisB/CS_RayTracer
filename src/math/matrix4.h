#ifndef MATRIX_4
#define MATRIX_4

#include <math/vector4.h>
#include <math/vector3.h>


class Vector4;
class Matrix4
{
	public:
		Matrix4();
		~Matrix4();
		
		void setIdentity();
		void resetToZero();
		Vector3 getTranslate();
		Vector3 getXAxis();
		Vector3 getYAxis();
		Vector3 getZAxis();
		
		double det() const;
		static Matrix4 inverse(const Matrix4& parMatrix);
		Vector4 operator*(const Vector4& parFactor);
		
	public:
		double ** m;
};

#endif //MATRIX_4
