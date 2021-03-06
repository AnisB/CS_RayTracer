
/* 
 * Auteur Anis Benyoub
 * Classe qui permet de traiter de traiter des Matrix4
 */
 

#ifndef MATRIX_4
#define MATRIX_4

#include <math/vector4.h>
#include <math/vector3.h>


class Vector4;

namespace MatrixInit
{
	enum Type
	{
		Zero,
		Identity,
		None
	};
}

class Matrix4
{
	public:
		Matrix4(MatrixInit::Type reset = MatrixInit::Zero);
		Matrix4(const Matrix4& parMatrix);
		~Matrix4();
		
		void setIdentity();
		void resetToZero();
		Vector3 getTranslate();
		Vector3 xAxis();
		Vector3 yAxis();
		Vector3 zAxis();
		
		double det() const;
		static Matrix4 inverse(const Matrix4& parMatrix);
		static Matrix4 translate(const Vector4& parVector);
		static Matrix4 translate(const Vector3& parVector);
		// TODO 
		// =>
		static Matrix4 rotate(double parAngle, const Vector3& parAxis);

		static Matrix4 rotateXAxis(double parAngle);
		static Matrix4 rotateYAxis(double parAngle);
		static Matrix4 rotateZAxis(double parAngle);

		Vector4 operator*(const Vector4& parFactor);
		Matrix4 operator*(const Matrix4& parMatrix);
		Matrix4& operator=(const Matrix4& parMatrix);

		
	public:
		double ** m;
};
std::ostream& operator<< (std::ostream& os, const Matrix4& obj); 

#endif //MATRIX_4
