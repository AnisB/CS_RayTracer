#ifndef MATRIX_3
#define MATRIX_3

#include<math/vector3.h>


class Vector3;
class Matrix3
{
	public:
		Matrix3();
		~Matrix3();
		
		void setIdentity();
		void resetToZero();
		
		double det() const;
		static Matrix3 inverse(const Matrix3& parMatrix);
		Vector3 operator*=(const Vector3& parFactor);
		
	public:
		double ** m;
};

#endif //MATRIX_3
