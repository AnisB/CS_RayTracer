

vec4 Reflect@NB_ITER@(Ray parRay, Intersection parIntersect)
{
	vec4 color = vec4(1.0);
	Ray reflected;
    reflected.energy = 0.2*parRay.energy ;
	reflected.origin = parIntersect.point-parIntersect.normal*0.01;		
	reflected.direction = reflect(parRay.direction,-parIntersect.normal);
        color = 0.2*CouleurPixel@NB_ITER2@(reflected);
	return color;
}
vec4 Refract@NB_ITER@(Ray parRay, Intersection parIntersect)
{
	vec4 color = vec4(1.0);
	Ray refracted;
        refracted.energy = 0.2*parRay.energy ;
	refracted.origin = parIntersect.point;	
	// Indice de réraction a changer	
	refracted.direction = refract(parRay.direction,-parIntersect.normal,1.0);
        color = 0.2*CouleurPixel@NB_ITER2@(refracted);
	return color;
}

vec4 CouleurPixel@NB_ITER@(Ray parRayon)
{
	if(parRayon.energy>ENERGY_MIN)
	{
            vec4 finalColor = vec4(1.0);
            int primitives[NB_PRIM]; //= getPrimitives(parRayon);
            Intersection intersect = IntersectWithScene(parRayon,primitives);
            if(BRDF_DEFINED)
        	finalColor = computeBRDF(parRayon, intersect);
            else
            {
                    finalColor = getMateriauColorByPrimID(intersect.obj);
                    finalColor*= SecondRayTrace(intersect,0);
            }
        // Commente a cause du "recursive call" a CouleurPixel
        if(intersect.isValid)
        {
            finalColor+=Reflect@NB_ITER@(parRayon, intersect);
            finalColor+=Refract@NB_ITER@(parRayon, intersect);
            return finalColor;
        }
        else
        {
            return backGroundColor;
        }
	}
	else
	{
		return backGroundColor;
	}
}
