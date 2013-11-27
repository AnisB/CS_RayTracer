#include "resourcemanager.h"

#include <common/defines.h>
#include <render/helper.h>
#include <render/renderer.h>


ResourceManager::ResourceManager()
: FTexIndex(0)
{

}


ResourceManager::~ResourceManager()
{
	foreach(tex, FTextures)
	{

	}
}

std::string concatenate(const std::string& parBase, int parIndex)
{
    std::string result = parBase;
    result+="[";
    result+=convertToString(parIndex);
    result+="]";
    return result;
}

const Texture* ResourceManager::LoadTexture(const std::string& parFileName)
{
	Texture * newTex = new Texture();
	FILE *file;
	unsigned long size;        // size of the new texture in bytes.
	unsigned long i;           // standard counter.
	unsigned short int planes; // number of planes in newTex (must be 1) 
	unsigned short int bpp;    // number of bits per pixel (must be 24)
	char temp;                 // temporary color storage for bgr-rgb conversion.

	if ((file = fopen(parFileName.c_str(), "rb"))==NULL) 
	{
		PRINT_RED("Texture introuvable "<<parFileName);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = (unsigned long)fread(&newTex->w, 4, 1, file)) != 1) 
	{
		PRINT_RED("Erreur de lecture de la largeeur de l'image "<<parFileName);
		return 0;
	}

	// read the height 
	if ((i = (unsigned long)fread(&newTex->l, 4, 1, file)) != 1) 
	{
		PRINT_RED("Erreur de lecture de la hauteur de l'image "<<parFileName);
	}

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = newTex->w * newTex->l * 3;

	// read the planes
	if (((unsigned long)fread(&planes, 2, 1, file)) != 1) 
	{
		PRINT_RED("Erreur de lecture des plans de l'image "<<parFileName);
		return 0;
	}

	if (planes != 1) 
	{
		printf("Planes from %s is not 1: %u\n", parFileName.c_str(), planes);
		return 0;
	}

	// read the bpp
	if ((i = (unsigned long)fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", parFileName.c_str());
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", parFileName.c_str(), bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data. 
	newTex->content = (GLubyte *) malloc(size);
	if (newTex->content == NULL) {
		printf("Error allocating memory for color-corrected newTex data");
		return 0;
	}

	if ((i = (unsigned long)fread(newTex->content, size, 1, file)) != 1) {
		printf("Error reading newTex data from %s.\n", parFileName.c_str());
		free(newTex->content);
		return 0;
	}

	for (i=0;i<size;i+=3) 
	{
		temp = newTex->content[i];
		newTex->content[i] = newTex->content[i+2];
		newTex->content[i+2] = temp;
	}

    glGenTextures(1, &newTex->id);
    glBindTexture(GL_TEXTURE_2D, newTex->id);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, newTex->w, newTex->l, 0, GL_RGB, GL_FLOAT, newTex->content);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);


	GLint tex0 = glGetUniformLocation(Renderer::Instance().GetComputeProgID(), concatenate("listTex",FTexIndex).c_str());
	glActiveTexture(GL_TEXTURE0+ FTexIndex + 1);
	glBindTexture(GL_TEXTURE_2D, newTex->id);
	glUniform1i(tex0, FTexIndex + 1);
	FTexIndex++;
	return newTex;  // OK
}

const ObjFile* ResourceManager::LoadModel(const std::string& parFileName)
{
	return 0;
}