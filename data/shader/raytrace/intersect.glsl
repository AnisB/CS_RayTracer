
Intersection IntersectWithTriangle(Ray parRay, Triangle parTheTriangle)
{
    Intersection intersect;
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.distance = 0.0;
    intersect.obj = 0;

    vec3 edge1 = parTheTriangle.p1 - parTheTriangle.p0;
    vec3 edge2 = parTheTriangle.p2 - parTheTriangle.p0;
    vec3 vecP = cross(parRay.direction, edge2);
    float det = dot(edge1, vecP);

    if(abs(det)<EPSILON)
        return intersect;
    float invDet = 1.0f / det;
    vec3 vecS = parRay.origin - parTheTriangle.p0;
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


    vec2 uv0 = parTheTriangle.uv0;
    vec2 uv1 = parTheTriangle.uv1;
    vec2 uv2 = parTheTriangle.uv2;

    vec2 uvI = u*(uv1-uv0)+v*(uv2-uv0)+uv0;

    intersect.point = I;
    intersect.uv = uvI;
    if(dot(parRay.direction, parTheTriangle.normale) > 0)
        intersect.normal = -parTheTriangle.normale;
    else
        intersect.normal = parTheTriangle.normale;
    intersect.isValid = true;
    return intersect;
}


Intersection IntersectWithQuadric(Ray parRay, Quadrique parTheQuadric)
{
    Intersection intersect;
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.distance = 0.0;
    intersect.obj = 0;


    float ACoeff =      parTheQuadric.A * parRay.direction.x * parRay.direction.x +
                        parTheQuadric.B * parRay.direction.y * parRay.direction.y +
                        parTheQuadric.C * parRay.direction.z * parRay.direction.z +
                        parTheQuadric.D * parRay.direction.x * parRay.direction.y +
                        parTheQuadric.E * parRay.direction.y * parRay.direction.z +
                        parTheQuadric.F * parRay.direction.x * parRay.direction.z;

    float BCoeff =      2*(parTheQuadric.A * parRay.origin.x * parRay.direction.x +
                           parTheQuadric.B * parRay.origin.y * parRay.direction.y +
                           parTheQuadric.C * parRay.origin.z * parRay.direction.z) +
                        parTheQuadric.D * (parRay.origin.x * parRay.direction.y +
                                           parRay.origin.y * parRay.direction.x) +
                        parTheQuadric.E * (parRay.origin.y * parRay.direction.z +
                                           parRay.origin.z * parRay.direction.y) +
                        parTheQuadric.F * (parRay.origin.x * parRay.direction.z +
                                           parRay.origin.z * parRay.direction.x) +
                        parTheQuadric.G * parRay.direction.x +
                        parTheQuadric.H * parRay.direction.y +
                        parTheQuadric.I * parRay.direction.z;

    float CCoeff =      parRay.origin.x * (parTheQuadric.G + parTheQuadric.D * parRay.origin.y) +
                        parRay.origin.y * (parTheQuadric.H + parTheQuadric.E * parRay.origin.z) +
                        parRay.origin.z * (parTheQuadric.I + parTheQuadric.F * parRay.origin.z) +
                        parTheQuadric.A * parRay.origin.x * parRay.origin.x +
                        parTheQuadric.B * parRay.origin.y * parRay.origin.y +
                        parTheQuadric.C * parRay.origin.z * parRay.origin.z +
                        parTheQuadric.J;
    if( ACoeff != 0.0 )
    {
        float Delta = BCoeff * BCoeff - 4*ACoeff * CCoeff;

        if( Delta > 0 )
        {
            intersect.isValid = true;
            
            return intersect;
        }
    }
    return intersect;
}


Intersection IntersectWithScene(in Ray parRay,in int parPrim[NB_PRIM])
{
    Intersection intersectResult, intersectCourant;
    intersectCourant.isValid = false;
    intersectCourant.uv = vec2(0.0);
    intersectCourant.point = vec3(0.0);
    intersectCourant.normal = vec3(0.0);
    intersectCourant.distance = 0.0;
    intersectCourant.obj = 0;
    intersectResult.isValid = false;
    intersectResult.uv = vec2(0.0);
    intersectResult.point = vec3(0.0);
    intersectResult.normal = vec3(0.0);
    intersectResult.distance = 0.0;
    intersectResult.obj = 0;
    for(int i=0; i<NB_PRIM; i++)
    {
		//Primitive prim = getPrimitiveByIndex(parPrim[i]);
		// en fait le tableau parPrim est un tableau de -1 ou 1, selon qu'on test ou non la primitive i
		//if (parPrim[i]!=1) continue;

        Primitive prim = getPrimitiveByIndex(i);

        switch(prim.type)
        {
        case PRIMITIVE_TRIANGLE :
            Triangle tri = getTriangleByIndex(prim.index);
            intersectCourant = IntersectWithTriangle(parRay, tri);
            break;
        case PRIMITIVE_QUADRIQUE :
            Quadrique quad = getQuadricByIndex(prim.index);
            intersectCourant = IntersectWithQuadric(parRay, quad);
            break;
        }
        if(intersectCourant.isValid && (!intersectResult.isValid || intersectCourant.distance < intersectResult.distance))
        {
            intersectResult = intersectCourant;
            intersectResult.obj = i;
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
        Triangle tri = getTriangleByIndex(i);
        Ray newRay = parRay;
        newRay.direction = -parRay.direction;
        intersect = IntersectWithTriangle(newRay, tri);
        float distanceToLight = length(lightPos-intersect.point);
        if(intersect.isValid && distanceToLight < distance)
        {
             return colorFilter*0.5;
        }
    }
    return colorFilter;
}
