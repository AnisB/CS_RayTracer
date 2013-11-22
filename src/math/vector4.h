#ifndef VECTOR4
#define VECTOR4

class Vector4
{
	public:
		Vector4();
		Vector4(double parX, double parY, double parZ, double parW);
		Vector4(const Vector4& parVec);
		~Vector4();
		
		Vector4& operator*=(double parFactor);
		static double dotProduct(const Vector4& parV1, const Vector4& parV2);
		static Vector4 crossProduct(const Vector4& parV1, const Vector4& parV2);
		
		double Norm();
		
	public:
		double x;
		double y;
		double z;
		double w;
	
};

#endif
