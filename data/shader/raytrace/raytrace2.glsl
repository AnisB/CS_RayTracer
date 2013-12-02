vec4 CouleurPixel@NB_ITER@(Ray parRayon)
{
	return vec4(1.0);
}

vec4 SecondRayTrace(Intersection parIntersect, int indexLight)
{
    vec4 ombrage = vec4(1.0);
    // Pour chacune des lumières
        // On lance un rayon en direction de la lumière
        Ray nouveauRayon;
        nouveauRayon.origin = parIntersect.point - 0.001*parIntersect.normal;
        nouveauRayon.direction = (listLight[indexLight].position - nouveauRayon.origin);
        ombrage *= (IntersectToLight(nouveauRayon,listLight[indexLight].position )*listLight[indexLight].colorSpec);
    return ombrage;
}
