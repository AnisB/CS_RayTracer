vec4 CouleurPixel@NB_ITER@(Ray parRayon)
{
	return vec4(1.0);
}

vec4 SecondRayTrace(Intersection parIntersect)
{
	vec4 ombrage = vec4(1.0);
	// Pour chacune des lumières
	for(int i = 0; i<NB_LIGHTS; ++i)
	{
		// On lance un rayon en direction de la lumière
		Ray nouveauRayon;
		nouveauRayon.origin = parIntersect.point - 0.001*parIntersect.normal;
		nouveauRayon.direction = (listLight[i].position - nouveauRayon.origin);
		ombrage *= (IntersectToLight(nouveauRayon,listLight[i].position )*listLight[i].colorSpec);
	}
	return ombrage;
}
