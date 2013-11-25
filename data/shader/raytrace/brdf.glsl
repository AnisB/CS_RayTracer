vec4 computeBRDF(Ray parRay, Intersection parIntersect)
{
	Material material = Materiau[listPrim[parIntersect.obj].material];
    float m = texture(textures[material.texRough], intersect.uv).r;
    vec4 albedo = texture(textures[material.texAlbedo], intersect.uv);
	vec3 V = -parRay.direction;
	
	float refractInd = material.indiceRefraction;
	
	float m2 = m*m;
	float brillance = 2*(1-m2)/m2;
	
	vec4 specularReflection = vec4(0.0,0.0,0.0,1.0);
	vec4 diffuseReflection = vec4(0.0,0.0,0.0,1.0);

	//Pour toutes les lumières
	for(int i  = 0; i < NOMBRE_DE_LUMIERES; i++)
	{
		if(pasOmbrager(lights(i),parIntersect.point))
		{
			vec3 L = normalize(positionLumiere[i].position-parIntersect.point);
			vec3 H = V+L/2;
			vec3 N = normalize(parIntersect.normal);
			
			//La source de lumiere est bien devant la surface
			float NdotL = dot(N,L);
			float HdotV = dot(H,V);
			float NdotH = dot(N,H);
			float NdotH2 = NdotH*NdotH;
		
			//F - Fresnel term (Schlick's Approximation)
			float Ro = (1.0-n2)/(1.0+n2);
			Ro = Ro*Ro;
			float F = Ro + (1-Ro)*pow((1-HdotV),5);
			
			//D - Micro-facet Slope Distribution
			float D = ((NdotH2)-1)/(m2*NdotH2);
			D = exp(D)/(PI*m2*NdotH2*NdotH2);

			//G - Geometric attenuation factor
			float k = m*sqrt(2/PI);
			float G = NdotV/(NdotV*(1-k)+k);
			
			float cookTorranceSpecularCoefficient = F * D * G / (PI*NdotL*NdotV);
			
			specularReflection += lightColor[i].specular * brillance * cookTorranceSpecularCoefficient;
			
			diffuseReflection += lightColor[i].diffuse * albedo * LdotN;
		}
	}
	
	color = diffuseReflection+specularReflection;
	return color;
}
