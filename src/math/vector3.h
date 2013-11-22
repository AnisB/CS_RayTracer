#ifndef VECTOR3
#define VECTOR3

class Vector3
{
	public:
		Vector3();
		Vector3(double parX, double parY, double parZ);
		Vector3(const Vector3& parVec);
		~Vector3();
		
		Vector3& operator*=(double parFactor);
		static double dotProduct(const Vector3& parV1, const Vector3& parV2);
		static Vector3 crossProduct(const Vector3& parV1, const Vector3& parV2);
		
		double Norm();
	public:
		double x;
		double y;
		double z;
	
};

#endif
