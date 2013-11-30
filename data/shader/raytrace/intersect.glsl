
Intersection IntersectWithTriangle(Ray parRay, int indexTriangle)
{
    Intersection intersect;
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.obj = 0;	
    intersect.distance = 0;
    
    Triangle monTriangle;
    monTriangle.p0.x = texture(listTriangles, vec2(0/17.0,(float(indexTriangle))/4.0)).r;
    monTriangle.p0.y = texture(listTriangles, vec2(1/17.0,(float(indexTriangle))/4.0)).r;
    monTriangle.p0.z = texture(listTriangles, vec2(2/17.0,(float(indexTriangle))/4.0)).r;

    monTriangle.p1.x = texture(listTriangles, vec2(5/17.0,(float(indexTriangle))/4.0)).r;
    monTriangle.p1.y = texture(listTriangles, vec2(6/17.0,(float(indexTriangle))/4.0)).r;
    monTriangle.p1.z = texture(listTriangles, vec2(7/17.0,(float(indexTriangle))/4.0)).r;    
    
    monTriangle.p2.x = texture(listTriangles, vec2(10/17.0,(float(indexTriangle))/4.0)).r;
    monTriangle.p2.y = texture(listTriangles, vec2(11/17.0,(float(indexTriangle))/4.0)).r;
    monTriangle.p2.z = texture(listTriangles, vec2(12/17.0,(float(indexTriangle))/4.0)).r;    
    
    
    monTriangle.p0-= vec3(0.5);
    monTriangle.p1-= vec3(0.5);
    monTriangle.p2-= vec3(0.5);
    
    monTriangle.p0*=400;
    monTriangle.p1*=400;
    monTriangle.p2*=400;   
    
    vec3 edge1 = monTriangle.p1 - monTriangle.p0;
    vec3 edge2 = monTriangle.p2 - monTriangle.p0;
    vec3 vecP = cross(parRay.direction, edge2);
    float det = dot(edge1, vecP);
        
    if(abs(det)<EPSILON)
        return intersect;
    float invDet = 1.0f / det;
    vec3 vecS = parRay.origin - monTriangle.p0;
    float u = dot(vecS, vecP) * invDet;
    if(u<0 || u>1)
        return intersect;    
    vec3 vecQ = cross(vecS, edge1);
    float v = dot(parRay.direction, vecQ) * invDet;
    if(v<0 || u + v > 1)
        return intersect;
    intersect.distance = dot(edge2, vecQ) * invDet;
    vec3 I = parRay.origin + intersect.distance * parRay.direction ;
    if(intersect.distance > EPSILON)
        return intersect;         
    intersect.distance = abs(intersect.distance);
    vec3 v1 = I - monTriangle.p0;
    vec3 v2 = monTriangle.p1 - monTriangle.p0;
    float uTex = dot(v1, v2);
    v2 = monTriangle.p2 - monTriangle.p0;
    float vTex = dot(v1, v2);
    intersect.point = I;
    intersect.uv = vec2(uTex, vTex);
    intersect.isValid = true;
    if(dot(parRay.direction, listTriangle[indexTriangle].normale) > 0)
        intersect.normal = -listTriangle[indexTriangle].normale;
    else
        intersect.normal = listTriangle[indexTriangle].normale;
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
    intersectResult.distance = 0.0;
    intersectResult.obj = 0;
    for(int i=0; i<NB_PRIM; i++)
    {
        intersectCourant = IntersectWithTriangle(parRay, i);
        if(intersectCourant.isValid && (!intersectResult.isValid || intersectCourant.distance < intersectResult.distance))
        {
            intersectResult = intersectCourant;
            intersectResult.obj = listPrim[i].index;
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
                if( listMateriau[i].reflectance == 1.0)
                {
                	return  vec4(0.0);
                }
                else
                {
                	return colorFilter*listMateriau[i].reflectance;
                }
            }
        }
    }
    return colorFilter;
}
