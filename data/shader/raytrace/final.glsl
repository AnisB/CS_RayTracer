
vec4 RayTrace(vec2 storePos)
{
	//Calcul du rayon a lancer
	Ray rayon;
	rayon.energy = 1.0;
	rayon.origin = cameraPosition;
	vec3 screenPoint = coinSupGauche + unitX * storePos.x + unitY * storePos.y;
	rayon.direction = normalize(screenPoint - cameraPosition);
	// Lancer
	return CouleurPixel1(rayon);
}

// Le main du programme
void main() 
{
	 // Recuperation de la taille de l'image
     ivec2 sizeXY = imageSize(renderCanvas);
     
     // On récupère le point de la texture qui nous a été attribue
     ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
     vec2 pixelFloat = vec2(storePos)/512.0;
     imageStore(renderCanvas, storePos, RayTrace(pixelFloat));
     //vec2 pixelFloat2 = vec2(storePos.x/8.0,storePos.y/4.0);
	 //imageStore(renderCanvas, storePos, texture(listTriangles,pixelFloat));
    // imageStore(renderCanvas, storePos, texture(listTriangles,vec2(0.4/4.0, 5.4/9.0)));
}
