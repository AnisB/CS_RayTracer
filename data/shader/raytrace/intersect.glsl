
Intersection IntersectWithTriangle(Ray parRay, int indexTriangle)
{
    Intersection intersect;
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.obj = 0;	
    intersect.distance = 0;
    vec3 edge1 = listTriangle[indexTriangle].p1 - listTriangle[indexTriangle].p0;
    vec3 edge2 = listTriangle[indexTriangle].p2 - listTriangle[indexTriangle].p0;
    vec3 vecP = cross(parRay.direction, edge2);
    float det = dot(edge1, vecP);
        
    if(abs(det)<EPSILON)
        return intersect;
    float invDet = 1.0f / det;
    vec3 vecS = parRay.origin - listTriangle[indexTriangle].p0;
    float u = dot(vecS, vecP) * invDet;
    if(u<0 || u>1)
        return intersect;    
    vec3 vecQ = cross(vecS, edge1);
    float v = dot(parRay.direction, vecQ) * invDet;
    if(v<0 || u + v > 1)
        return intersect;
    intersect.isValid = true;
    intersect.distance = dot(edge2, vecQ) * invDet;
    vec3 I = parRay.origin + parRay.direction * intersect.distance;
    intersect.distance = abs(intersect.distance);
    vec3 v1 = I - listTriangle[indexTriangle].p0;
    vec3 v2 = listTriangle[indexTriangle].p1 - listTriangle[indexTriangle].p0;
    float uTex = dot(v1, v2);
    v2 = listTriangle[indexTriangle].p2 - listTriangle[indexTriangle].p0;
    float vTex = dot(v1, v2);
    intersect.point = I;
    intersect.uv = vec2(uTex, vTex);
    return intersect;
}


Intersection IntersectWithScene(in Ray parRay,in int parPrim[NB_PRIM])
{
    Intersection intersectResult, intersectCourant;
    intersectCourant.isValid = false;
    intersectCourant.uv = vec2(0.0);
    intersectCourant.point = vec3(0.0);
    intersectCourant.normal = vec3(0.0);
    intersectCourant.obj = 0;
    intersectResult.isValid = false;
    intersectResult.uv = vec2(0.0);
    intersectResult.point = vec3(0.0);
    intersectResult.normal = vec3(0.0);
    intersectResult.distance = 1000.0;
    intersectResult.obj = 0;
    for(int i=0; i<NB_PRIM; i++)
    {
        intersectCourant = IntersectWithTriangle(parRay, i);
        if(intersectCourant.isValid && intersectCourant.distance < intersectResult.distance)
        {
            intersectResult = intersectCourant;
            intersectResult.obj = listPrim[i].index;
            intersectResult.normal = listTriangle[i].normale;
        }
    }
    return intersectResult;
}



vec4 IntersectToLight(in Ray parRay, vec3 lightPos)
{
    Intersection intersect;
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.obj = 0;
	vec4 colorFilter =  vec4(1.0);
	float distance = length(lightPos-parRay.origin);
    for(int i=0; i<NB_TRIANGLE; i++)
    {
        intersect = IntersectWithTriangle(parRay, i);
        float distanceToLight = length(lightPos-intersect.point);
        if(intersect.isValid && distanceToLight < distance)
        {
            if( listMateriau[i].reflectance > 0)
            {
            	colorFilter*=vec4(0.5);
            }
        }
    }
    return colorFilter;
}
