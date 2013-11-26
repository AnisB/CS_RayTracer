
Intersection IntersectWithScene(Ray parRay, int[NB_PRIM] parPrim)
{
	Intersection intersect;
	intersect.isValid = false;
	intersect.uv = vec2(0.0);
	intersect.point = vec3(0.0);
	intersect.normal = vec3(0.0);
	intersect.obj = 0;
	return intersect;
}
