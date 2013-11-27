#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER


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
	ResourceManage();
	~ResourceManage();

	const Texture& LoadTexture(const std::string& parFileName);

protected:
	std::map<std::string, Texture*> FTextures;
};
#endif // RESOURCE_MANAGER