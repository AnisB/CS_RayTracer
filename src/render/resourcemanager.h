#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <render/defines.h>
#include <common/singleton.h>
#include <primitives/primitive.h>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

struct Texture
{
	GLuint id;
	int w;
	int l;
	unsigned char * content;
};


struct ObjFile
{
	std::list<Triangle> listTriangle;
	Materiau material;
	const Texture* albTex;
	const Texture* rugTex;
	const Texture* specTex;
	const Texture* normalTex;
};

class ResourceManager: public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	const Texture* LoadTexture(const std::string& parFileName);
	ObjFile* LoadModel(const std::string& parFileName, const std::string& parAlbTexFileName, const std::string& parRugTexFileName, const std::string& parSpecTexFileName, const std::string& parNormalTexFileName );

protected:
	std::map<std::string, Texture*> FTextures;
	std::map<std::string, ObjFile*> FModels;
	int FTexIndex;
};

#endif // RESOURCE_MANAGER
