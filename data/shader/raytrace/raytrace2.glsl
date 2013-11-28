vec4 CouleurPixel@NB_ITER@(Ray parRayon)
{
	return vec4(1.0);
}

vec4 SecondRayTrace(Intersection parIntersect)
{
	vec4 ombrage = vec4(1.0);
	// Pour chacune des lumières
	int i = 0;
	//for(int i = 0; i<NB_LIGHTS; ++i)
	//{
		// On lance un rayon en direction de la lumière
		Ray nouveauRayon;
		nouveauRayon.origin = parIntersect.point;
		nouveauRayon.direction = (listLight[i].position - nouveauRayon.origin);
		int prim[NB_PRIM] = getPrimitives(nouveauRayon);
		//ombrage *= IntersectToLight(nouveauRayon, prim)*listLight[i].colorSpec;
	//}
	return ombrage;
}
