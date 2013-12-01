
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

    //vec3 v1 = I - parTheTriangle.p0;
    //vec3 v2 = parTheTriangle.p1 - parTheTriangle.p0;
    //float uTex = dot(v1, v2);
    //v2 = parTheTriangle.p2 - parTheTriangle.p0;
    //float vTex = dot(v1, v2);

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
    intersect.isValid = false;
    intersect.uv = vec2(0.0);
    intersect.point = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.distance = 0.0;
    intersect.obj = 0;


    float ACoeff = parRay.direction.x * ( parTheQuadric.A * parRay.direction.x   +
                                             parTheQuadric.F       * parRay.direction.y   +
                                             parTheQuadric.E       * parRay.direction.z ) +
                        parRay.direction.y * ( parTheQuadric.B * parRay.direction.y   +
                                             parTheQuadric.D       * parRay.direction.z ) +
                        parRay.direction.z * ( parTheQuadric.C * parRay.direction.z );

    float BCoeff = parRay.direction.x * ( parTheQuadric.A * parRay.origin.x + 0.5 *
                                           ( parTheQuadric.F * parRay.origin.y + parTheQuadric.E * parRay.origin.z + parTheQuadric.G ) ) +
                        parRay.direction.y * ( parTheQuadric.B * parRay.origin.y + 0.5                     *
                                           ( parTheQuadric.F * parRay.origin.x + parTheQuadric.D * parRay.origin.z + parTheQuadric.H ) ) +
                        parRay.direction.z * ( parTheQuadric.C * parRay.origin.z + 0.5                     *
                                           ( parTheQuadric.E * parRay.origin.x + parTheQuadric.D * parRay.origin.y + parTheQuadric.I ) );

    float CCoeff = parRay.origin.x * ( parTheQuadric.A * parRay.origin.x   +
                                          parTheQuadric.F       * parRay.origin.y   +
                                          parTheQuadric.E       * parRay.origin.z   +
                                          parTheQuadric.G                    ) +
                        parRay.origin.y * ( parTheQuadric.B * parRay.origin.y   +
                                          parTheQuadric.D       * parRay.origin.z   +
                                          parTheQuadric.H                    ) +
                        parRay.origin.z * ( parTheQuadric.C * parRay.origin.z   +
                                          parTheQuadric.I                    ) +
                        parTheQuadric.J;


    if( ACoeff != 0.0 )
    {
        float Ka    = -BCoeff / ACoeff;
        float Kb    =  CCoeff / ACoeff;
        float Delta = Ka * Ka - Kb;

        if( Delta > 0 )
        {
            Delta   = sqrt( Delta );
            float T0 = Ka - Delta;
            float T1 = Ka + Delta;

            float Distance = min( T0, T1 );
            if( Distance < EPSILON )
                Distance = max( T0, T1 );

            if( !( Distance < 0 ) )
            {
                intersect.distance = Distance;
                // Calcule la normale de surface
                vec3 HitPt = parRay.origin + Distance * parRay.direction;

                vec3 Normal;
                Normal.x = 2.0 * parTheQuadric.A * HitPt.x +
                           parTheQuadric.E * HitPt.z                            +
                           parTheQuadric.F * HitPt.y                            +
                           parTheQuadric.G;

                Normal.y = 2.0 * parTheQuadric.B * HitPt.y +
                           parTheQuadric.D * HitPt.z                            +
                           parTheQuadric.F * HitPt.x                            +
                           parTheQuadric.H;

                Normal.z = 2.0 * parTheQuadric.C * HitPt.z +
                           parTheQuadric.D * HitPt.y                            +
                           parTheQuadric.E * HitPt.x                            +
                           parTheQuadric.I;
                intersect.point = HitPt;
                intersect.normal = normalize(Normal);
                vec3 centre = vec3(-parTheQuadric.D/(2*parTheQuadric.A), -parTheQuadric.E/(2*parTheQuadric.B), -parTheQuadric.F/(2*parTheQuadric.C));
                float u = 0.5 + atan(centre.z, centre.x)/(2*PI);
                float v = 0.5 - asin(centre.y)/PI;
                intersect.uv = vec2(u, v);
                intersect.isValid = true;
            }
        }
    }
//    else
//    {
//        Result.AjusterSurface ( this );
//        Result.AjusterDistance( -RENDRE_REEL( 0.5 ) * ( CCoeff / BCoeff ) );
//        Result.AjusterNormale ( CVecteur3::Normaliser( m_Lineaire ) );
//    }
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
//        case PRIMITIVE_PLAN :
//            Triangle tri = getTriangleByIndex(prim.index);
//            intersectCourant = IntersectWithTriangle(parRay, tri);
//            break;
        case PRIMITIVE_QUADRIQUE :
            //Quadrique quad = getQuadricByIndex(prim.index);
            Quadrique quad = listQuadrique[prim.index];
            intersectCourant = IntersectWithQuadric(parRay, quad);
            break;
        }
        if(intersectCourant.isValid && (!intersectResult.isValid || intersectCourant.distance < intersectResult.distance))
        {
            intersectResult = intersectCourant;
            //intersectResult.obj = parPrim[i];
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
        intersect = IntersectWithTriangle(parRay, tri);
        float distanceToLight = length(lightPos-intersect.point);
        if(intersect.isValid && distanceToLight < distance)
        {
                return  vec4(0.5);
        /*
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
        */
        }
    }
    return colorFilter;
}
