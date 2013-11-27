#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <render/defines.h>
#include <common/singleton.h>
#include <primitives/primitive.h>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>

struct Texture
{
	GLuint id;
	int w;
	int l;
	GLubyte * content;
};


struct ObjFile
{
	std::list<Triangle> listTriangle; 
};

class ResourceManager: public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	const Texture* LoadTexture(const std::string& parFileName);
	const ObjFile* LoadModel(const std::string& parFileName);

protected:
	std::map<std::string, Texture*> FTextures;
	std::map<std::string, ObjFile*> FModels;
	int FTexIndex;
};

#endif // RESOURCE_MANAGER
