vec4 computeBRDF(Ray parRay, Intersection parIntersect)
{
	vec4 color;
	Material material = Materiau[listPrim[intersecti.obj].material];
	vec4 m = texture(textures[material.texRough], intersect.uv);
	vec4 albedo = texture(textures[material.texAlbedo], intersect.uv);
	return color;
}