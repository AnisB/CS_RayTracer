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
	return (m[0][0]*m[1][1]*m[2][2]-m[2][1]*m[1][2])
           -m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])
           +m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
}
void Matrix4::resetToZero()
{
	m[0][0] = 0.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	p
	m[1][0] = 0.0;
	m[1][1] = 0.0;
	m[1][2] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 0.0;
}


Vector4 Matrix4::operator*=(const Vector4& parFactor)
{
	Vector4 result;

	return result;
}

Matrix4 Matrix4::inverse(const Matrix3& parMatrix)
{
	Matrix4 inverseMatrix;
	double invdet = 1.0/parMatrix.det();
	inverseMatrix.m[0][0] =  (parMatrix.m[1][1]*parMatrix.m[2][2]-parMatrix.m[2][1]*parMatrix.m[1][2])*invdet;
	inverseMatrix.m[1][0] = -(parMatrix.m[0][1]*parMatrix.m[2][2]-parMatrix.m[0][2]*parMatrix.m[2][1])*invdet;
	inverseMatrix.m[2][0] =  (parMatrix.m[0][1]*parMatrix.m[1][2]-parMatrix.m[0][2]*parMatrix.m[1][1])*invdet;
	inverseMatrix.m[0][1] = -(parMatrix.m[1][0]*parMatrix.m[2][2]-parMatrix.m[1][2]*parMatrix.m[2][0])*invdet;
	inverseMatrix.m[1][1] =  (parMatrix.m[0][0]*parMatrix.m[2][2]-parMatrix.m[0][2]*parMatrix.m[2][0])*invdet;
	inverseMatrix.m[2][1] = -(parMatrix.m[0][0]*parMatrix.m[1][2]-parMatrix.m[1][0]*parMatrix.m[0][2])*invdet;
	inverseMatrix.m[0][2] =  (parMatrix.m[1][0]*parMatrix.m[2][1]-parMatrix.m[2][0]*parMatrix.m[1][1])*invdet;
	inverseMatrix.m[1][2] = -(parMatrix.m[0][0]*parMatrix.m[2][1]-parMatrix.m[2][0]*parMatrix.m[0][1])*invdet;
	inverseMatrix.m[2][2] =  (parMatrix.m[0][0]*parMatrix.m[1][1]-parMatrix.m[1][0]*parMatrix.m[0][1])*invdet;
	return inverseMatrix;
}
