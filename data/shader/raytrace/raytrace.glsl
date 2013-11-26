

vec4 Reflect(Ray parRay, Intersection parIntersect)
{
	vec4 color;
	Ray reflected;
	reflected.origin = parIntersect.point - EPSILON*parIntersect.normal;		
	reflected.direction = reflect(parRay.direction,parIntersect.normal);
	//color = CouleurPixel(reflected);
	return color;
}
vec4 Refract(Ray parRay, Intersection parIntersect)
{
	vec4 color;
	Ray refracted;
	refracted.origin = parIntersect.point + EPSILON*parIntersect.normal;	
	// Indice de réraction a changer	
	refracted.direction = refract(parRay.direction,parIntersect.normal,0.5);
	//color = CouleurPixel(refracted);
	return color;
}

vec4 CouleurPixel1(Ray parRayon)
{
	if(parRayon.energy>ENERGY_MIN)
	{
		vec4 finalColor;
		int listePrim[NB_PRIM] = getPrimitives(parRayon);
		Intersection intersect = IntersectWithScene(parRayon,listePrim);
		finalColor = computeBRDF(parRayon, intersect);
		// Commente a cause du "recursive call" a CouleurPixel
		if(intersect.isValid)
		{
			finalColor*=Reflect(parRayon, intersect);
			finalColor*=Refract(parRayon, intersect);		
		}
		return finalColor;
	}
	else
	{
		return backGroundColor;
	}
}

vec4 RayTrace(vec2 storePos)
{
	//Calcul du rayon a lancer
	Ray rayon;
	rayon.origin = cameraPosition;
	vec3 screenPoint = coinSupGauche + unitX * storePos.x + unitY * storePos.y;
	rayon.direction = screenPoint - cameraPosition;
	// Lancer
	return CouleurPixel1(rayon);
}
