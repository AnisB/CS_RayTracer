#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <string>

#include "defines.h"
#include "common/singleton.h"

struct Texture
{
	GLuint id;
	int w;
	int l;
	GLbyte ** content;
};

class ResourceManager: public Singleton<ResourceManager>
{
public:
    ResourceManager();
    ~ResourceManager();

	const Texture& LoadTexture(const std::string& parFileName);

protected:
	std::map<std::string, Texture*> FTextures;
};
#endif // RESOURCE_MANAGER
