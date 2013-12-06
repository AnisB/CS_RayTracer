
/* 
 * Auteur Pierre Froumenty
 */
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>


namespace tribox {
	using namespace std;
	struct Vector {
	  float x, y, z;       

	  Vector(void)
	  {        
	  }

	  Vector(float a, float b, float c)
	  {
	    x=a;            
	    y=b;
	    z=c;            
	  }

	  Vector operator-(Vector &v2)
	  {
	    Vector v3;
	    v3.x = x - v2.x;
	    v3.y = y - v2.y;
	    v3.z = z - v2.z;
	    return v3;
	  }

	}; 

	struct Point {
	  float x, y, z;  

	  Point(void)
	  {        
	  }

	  Point(float a, float b, float c)
	  {
	    x=a;            
	    y=b;
	    z=c;            
	  }

	  Vector operator-(Point &p2)
	  {
	    Vector v3;
	    v3.x = x - p2.x;
	    v3.y = y - p2.y;
	    v3.z = z - p2.z;
	    return v3;
	  }

	}; 

	struct Sphere {
	  Point c; // Sphere center
	  float r; // Sphere radius
	};

	float Dot(Vector v1, Vector v2)
	{
	  return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
	}

	float Dot(Point p1, Vector v2)
	{
	  return (p1.x*v2.x + p1.y*v2.y + p1.z*v2.z);
	}

	Vector Cross(Vector v1, Vector v2)
	{
	  Vector v3;       
	  v3.x = v1.y*v2.z - v2.y*v1.z;
	  v3.y = v1.z*v2.x - v1.x*v2.z;
	  v3.z = v1.x*v2.y - v1.y*v2.x;
	  return v3;
	}

	Vector operator*(float scale, Vector v)
	{
	  Vector v3;
	  v3.x = scale*v.x;
	  v3.y = scale*v.y;
	  v3.z = scale*v.z;
	  return v3;
	}

	Point operator+(Point p, Vector v)
	{
	  Point p2;
	  p2.x = p.x + v.x;
	  p2.y = p.y + v.y;
	  p2.z = p.z + v.z;
	  return p2;
	}

	Point operator+(Point p, Point p2)
	{
	  Point p3;
	  p3.x = p.x + p2.x;
	  p3.y = p.y + p2.y;
	  p3.z = p.z + p2.z;
	  return p3;
	}

	Point operator*(float scale, Point p)
	{
	  Point p2;
	  p2.x = scale*p.x;
	  p2.y = scale*p.y;
	  p2.z = scale*p.z;
	  return p2;
	}


	float getmin(const vector<Point> &points, Vector axis)
	{
	  float min = std::numeric_limits<float>::max(); 

	  for (int ctr = 0; ctr < points.size(); ctr++)
	    {
	      float dotprod = Dot(points[ctr], axis);
	      if (dotprod < min) min = dotprod;
	    }
	  return min;
	}

	float getmax(const vector<Point> &points, Vector axis)
	{
	  float max = -std::numeric_limits<float>::max(); 

	  for (int ctr = 0; ctr < points.size(); ctr++)
	    {
	      float dotprod = Dot(points[ctr], axis);
	      if (dotprod > max) max = dotprod;
	    }
	  return max;
	}

	bool isect(const vector<Point> &points1, const vector<Point> &points2, Vector axis)
	{
	  if (getmin(points1, axis) > getmax(points2, axis)) return false;
	  if (getmax(points1, axis) < getmin(points2, axis)) return false;
	  return true;     
	}

	bool isectboxtri(float center[3], float r[3], float triverts[3][3])
	{
	  vector<Point> boxpoints;
	  boxpoints.push_back(Point(center[0]+r[0], center[1]+r[1], center[2]+r[2]));
	  boxpoints.push_back(Point(center[0]+r[0], center[1]+r[1], center[2]-r[2]));
	  boxpoints.push_back(Point(center[0]+r[0], center[1]-r[1], center[2]+r[2]));
	  boxpoints.push_back(Point(center[0]+r[0], center[1]-r[1], center[2]-r[2]));
	  boxpoints.push_back(Point(center[0]-r[0], center[1]+r[1], center[2]+r[2]));
	  boxpoints.push_back(Point(center[0]-r[0], center[1]+r[1], center[2]-r[2]));
	  boxpoints.push_back(Point(center[0]-r[0], center[1]-r[1], center[2]+r[2]));
	  boxpoints.push_back(Point(center[0]-r[0], center[1]-r[1], center[2]-r[2]));
	 
	  vector<Point> tripoints;
	  tripoints.push_back(Point(triverts[0][0], triverts[0][1], triverts[0][2]));
	  tripoints.push_back(Point(triverts[1][0], triverts[1][1], triverts[1][2]));
	  tripoints.push_back(Point(triverts[2][0], triverts[2][1], triverts[2][2]));

	  // test the x, y, and z axes
	  if (!isect(boxpoints, tripoints, Vector(1, 0, 0))) return false;
	  if (!isect(boxpoints, tripoints, Vector(0, 1, 0))) return false;
	  if (!isect(boxpoints, tripoints, Vector(0, 0, 1))) return false;

	  // test the triangle normal
	  Vector triedge1 = tripoints[1] - tripoints[0];
	  Vector triedge2 = tripoints[2] - tripoints[1];
	  Vector trinormal = Cross(triedge1, triedge2);
	  if (!isect(boxpoints, tripoints, trinormal)) return false;

	  // test the 9 edge cross products
	  Vector triedge3 = tripoints[0] - tripoints[2];

	  Vector boxedge1 = Vector(1, 0, 0);
	  Vector boxedge2 = Vector(0, 1, 0);
	  Vector boxedge3 = Vector(0, 0, 1);

	  if (!isect(boxpoints, tripoints, Cross(boxedge1, triedge1))) return false;
	  if (!isect(boxpoints, tripoints, Cross(boxedge1, triedge2))) return false;
	  if (!isect(boxpoints, tripoints, Cross(boxedge1, triedge3))) return false;

	  if (!isect(boxpoints, tripoints, Cross(boxedge2, triedge1))) return false;
	  if (!isect(boxpoints, tripoints, Cross(boxedge2, triedge2))) return false;
	  if (!isect(boxpoints, tripoints, Cross(boxedge2, triedge3))) return false;

	  if (!isect(boxpoints, tripoints, Cross(boxedge3, triedge1))) return false;
	  if (!isect(boxpoints, tripoints, Cross(boxedge3, triedge2))) return false;
	  if (!isect(boxpoints, tripoints, Cross(boxedge3, triedge3))) return false;

	  return true;
	     
	}
}
