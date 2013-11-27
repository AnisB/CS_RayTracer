
Intersection IntersectWithTriangle(Ray parRay, int indexTriangle)
{
    Intersection intersect;
    int i;
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.obj = 0;	
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
    vec3 v1 = I - listTriangle[indexTriangle].p0;
    vec3 v2 = listTriangle[indexTriangle].p1 - listTriangle[indexTriangle].p0;
    float uTex = dot(v1, v2);
    v2 = listTriangle[indexTriangle].p2 - listTriangle[indexTriangle].p0;
    float vTex = dot(v1, v2);
    intersect.point = I;
    intersect.uv = vec2(uTex, vTex);
    return intersect;
}


Intersection IntersectWithScene(Ray parRay, int[NB_PRIM] parPrim)
{
    Intersection intersectResult, intersectCourant;
    int i;
    intersectCourant.isValid = false;
    intersectCourant.uv = vec2(0.0);
    intersectCourant.point = vec3(0.0);
    intersectCourant.normal = vec3(0.0);
    intersectCourant.obj = 0;
    intersectResult.isValid = false;
    intersectResult.uv = vec2(0.0);
    intersectResult.point = vec3(0.0);
    intersectResult.normal = vec3(0.0);
    intersectResult.obj = 0;
    for(i=0; i<NB_PRIM; i++)
    {
        if(parPrim[i] < 0)
            return intersectResult;
        switch(listPrim[parPrim[i]].type)
        {
        case PRIMITIVE_TRIANGLE:
            intersectCourant = IntersectWithTriangle(parRay, listPrim[parPrim[i]].index);
            if(intersectCourant.isValid && intersectCourant.distance < intersectResult.distance)
            {
                intersectResult = intersectCourant;
                intersectResult.obj = parPrim[i];
                intersectResult.normal = listTriangle[listPrim[parPrim[i]].index].normale;
            }
            break;
        case PRIMITIVE_PLAN:
            break;
        case PRIMITIVE_QUADRIQUE:
            break;
        default:
            return intersectResult;
        }
    }
    return intersectResult;
}
