#include "matrix4.h"


Matrix4::Matrix4()
{
	m = new double*[4];
	for(int i = 0; i<4; ++i)
	{
		m[i] = new double[4];
	}
	resetToZero();
}

Matrix4::~Matrix4()
{
	delete [] m;
}


void Matrix4::setIdentity()
{
	
	m[0][0] = 1.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	m[0][3] = 0.0;
	
	m[1][0] = 0.0;
	m[1][1] = 1.0;
	m[1][2] = 0.0;
	m[1][3] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 1.0;
	m[2][3] = 0.0;
	
	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;
}

double Matrix4::det() const
{
	//TODO
	return 0.0;
}
void Matrix4::resetToZero()
{
	m[0][0] = 0.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	m[0][3] = 0.0;

	m[1][0] = 0.0;
	m[1][1] = 0.0;
	m[1][2] = 0.0;
	m[1][3] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 0.0;
	m[2][3] = 0.0;

	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 0.0;
}

Vector3 Matrix4::getTranslate()
{
	return Vector3(m[0][3],m[1][3],m[2][3]);
}

Vector3 Matrix4::getXAxis()
{
	return Vector3(m[0][0],m[1][0],m[2][0]);
}
Vector3 Matrix4::getYAxis()
{
	return Vector3(m[0][1],m[1][1],m[2][1]);
}
Vector3 Matrix4::getZAxis()
{
	return Vector3(m[0][2],m[1][2],m[2][2]);
}
Vector4 operator*(const Vector4& parFactor)
{
	Vector4 result;
	return result;
}

Matrix4 Matrix4::inverse(const Matrix4& parMatrix)
{
	Matrix4 inverseMatrix;
	// TODO
	return inverseMatrix;
}
