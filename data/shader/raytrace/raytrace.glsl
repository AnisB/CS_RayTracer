

vec4 Reflect@NB_ITER@(Ray parRay, Intersection parIntersect)
{
	vec4 color = vec4(1.0);
	Ray reflected;
    reflected.energy = 0.4;
	reflected.origin = parIntersect.point;		
	reflected.direction = reflect(parRay.direction,parIntersect.normal);
	color = 0.4*CouleurPixel@NB_ITER2@(reflected);
	return color;
}
vec4 Refract@NB_ITER@(Ray parRay, Intersection parIntersect)
{
	vec4 color = vec4(1.0);
	Ray refracted;
    refracted.energy = 0.1;

	refracted.origin = parIntersect.point ;	
	// Indice de réraction a changer	
	refracted.direction = refract(parRay.direction,parIntersect.normal,1.0);
	color = 0.4*CouleurPixel@NB_ITER2@(refracted);
	return color;
}

vec4 CouleurPixel@NB_ITER@(Ray parRayon)
{
	if(parRayon.energy>ENERGY_MIN)
	{
		vec4 finalColor = vec4(1.0);
		int primitives[NB_PRIM]; //= getPrimitives(parRayon);
		Intersection intersect = IntersectWithScene(parRayon,primitives);
		//finalColor = listTex[getMateriauByIndex(getPrimitiveByIndex(intersect.obj).materiau).texAlbedo];
		finalColor = getMateriauByIndex(getPrimitiveByIndex(intersect.obj).materiau).color;
		//finalColor = vec4(intersect.uv.x,intersect.uv.y,0.0,1.0);
		//finalColor *=SecondRayTrace(intersect);

		//finalColor = computeBRDF(parRayon, intersect);
		
		// Commente a cause du "recursive call" a CouleurPixel
		if(intersect.isValid)
		{
			//finalColor =vec4(1.0,0.0,0.0,1.0);
			//finalColor+=Reflect@NB_ITER@(parRayon, intersect);
			//finalColor+=Refract@NB_ITER@(parRayon, intersect);		
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
