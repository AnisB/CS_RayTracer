vec4 SecondRayTrace(Intersection parIntersect, int indexLight);
vec4 computeBRDF(Ray parRay, Intersection parIntersect)
{
    vec4 albedo = texture(listTex[0],parIntersect.uv);
    float roughness = texture(listTex[1],parIntersect.uv).r;
    float specCoeff = texture(listTex[2],parIntersect.uv).r;
    //float refractInd = material.indiceRefraction;
   
    vec3 V = normalize(cameraPosition-parIntersect.point);
    float m2 = roughness*roughness;
    float Ro = 0.0325;
   
    vec4 specularReflection = vec4(0.0,0.0,0.0,1.0);
    vec4 diffuseReflection = vec4(0.0,0.0,0.0,1.0);
    int i = 0;
    //Pour toutes les lumières
    //for(int i  = 0; i < NB_LIGHTS; i++)
    //{
        vec3 L = normalize(listLight[i].position-parIntersect.point);
        vec3 H = (V+L)/2.0;
        vec3 N = -normalize(parIntersect.normal);
       
        //La source de lumiere est bien devant la surface
        float NdotL = abs(dot(N,L));
        float HdotV = abs(dot(H,V));
        float NdotH = abs(dot(N,H));
        float NdotV = abs(dot(N,V));
        float NdotH2 = NdotH*NdotH;
   
        //F - Fresnel term (Schlick's Approximation)
        //float Ro = (1.0-refractInd)/(1.0+refractInd);
        //Ro = Ro*Ro;
        float F = Ro + (1.0-Ro)*pow((1.0-HdotV),5.0);
       
        //D - Micro-facet Slope Distribution
        float gaussConstant = 100.0;
        float alpha = acos(NdotH);
        float D = gaussConstant*exp(-(alpha*alpha)/(m2));

        //G - Geometric attenuation factor
        float G = 2*NdotH*min(NdotL,NdotV)/(HdotV);
       
        float cookTorranceSpecularCoefficient = F * D * G  / (PI*NdotL*NdotV);

        vec4 ombrage = SecondRayTrace(parIntersect,i);
       
        specularReflection += listLight[i].colorSpec * specCoeff * cookTorranceSpecularCoefficient*ombrage ;
       
        diffuseReflection += listLight[i].colorSpec * albedo * NdotL*ombrage;
    //}

    return specularReflection + diffuseReflection;
}
