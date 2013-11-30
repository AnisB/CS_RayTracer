#include "resourcemanager.h"

#include <common/defines.h>
#include <render/helper.h>
#include <render/renderer.h>

#include <fstream>
#include <sstream>

ResourceManager::ResourceManager()
: FTexIndex(0)
{

}


ResourceManager::~ResourceManager()
{
	foreach(tex, FTextures)
	{
		free(tex->second->content);
		delete tex->second;
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
		delete newTex;
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = (unsigned long)fread(&newTex->w, 4, 1, file)) != 1) 
	{
		PRINT_RED("Erreur de lecture de la largeur de l'image "<<parFileName);
		delete newTex;

		return 0;
	}

	// read the height 
	if ((i = (unsigned long)fread(&newTex->l, 4, 1, file)) != 1) 
	{
		PRINT_RED("Erreur de lecture de la hauteur de l'image "<<parFileName);
		delete newTex;

	}

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = newTex->w * newTex->l * 3;

	// read the planes
	if (((unsigned long)fread(&planes, 2, 1, file)) != 1) 
	{
		PRINT_RED("Erreur de lecture des plans de l'image "<<parFileName);
		delete newTex;

		return 0;
	}

	if (planes != 1) 
	{
		printf("Planes from %s is not 1: %u\n", parFileName.c_str(), planes);
		delete newTex;

		return 0;
	}

	// read the bpp
	if ((i = (unsigned long)fread(&bpp, 2, 1, file)) != 1) 
	{
		printf("Error reading bpp from %s.\n", parFileName.c_str());
		delete newTex;

		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", parFileName.c_str(), bpp);
		delete newTex;

		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data. 
	newTex->content = (GLubyte *) malloc(size);
	if (newTex->content == NULL) {
		printf("Error allocating memory for color-corrected newTex data");
		delete newTex;
		return 0;
	}

	if ((i = (unsigned long)fread(newTex->content, size, 1, file)) != 1) 
	{
		printf("Error reading newTex data from %s.\n", parFileName.c_str());
		free(newTex->content);
		delete newTex;
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


	//GLint tex0 = glGetUniformLocation(Renderer::Instance().GetComputeProgID(), concatenate("listTex",FTexIndex).c_str());
	//glActiveTexture(GL_TEXTURE0+ FTexIndex + 1);
	//glBindTexture(GL_TEXTURE_2D, newTex->id);
	//glUniform1i(tex0, FTexIndex + 1);
	FTexIndex++;
	return newTex;
}

ObjFile* ResourceManager::LoadModel(const std::string& parFileName, const std::string& parAlbTexFileName, const std::string& parRugTexFileName, const std::string& parSpecTexFileName )
{
	std::vector<Vector3> vertices;
	std::vector<Vector3> normales;
	std::vector<vec2> mapping;
	std::vector<short> index;
	fstream in;
	in.open(parFileName.c_str(), std::fstream::in);
  	if (!in) 
  	{ 
  		PRINT_RED("Cannot find model obj: "<<parFileName); 
  		return NULL;
  	}
  	else
  	{
  		PRINT_ORANGE("Parsing model obj: "<<parFileName<<" ..."); 
  	}
 	ObjFile * newModel = new ObjFile();
	string line;
	while (getline(in, line)) 
	{
	    if (line.substr(0,2) == "v ") 
	    {
	      stringstream s(line.substr(2));
	      Vector3 v; 
	      s >> v.x; 
	      s >> v.y; 
	      s >> v.z; 
	      vertices.push_back(v);
	    }
	    /*  
	    else if (line.substr(0,2) == "f ") 
	    {
	      stringstream s(line.substr(2));
	      short a,b,c;
	      s >> a; s >> b; s >> c;
	      a--; 
	      b--; 
	      c--;
	      index.push_back(a); 
	      index.push_back(b); 
	      index.push_back(c);
	    }
	    */
	    else if(line[0] == 'v' && line[1] == 't') 
	    { 	
			istringstream s(line.substr(2));
			float u,v;
			s >> u;
			s >> v;
			vec2 map;
			map.u = u;
			map.v = v;
	      	mapping.push_back(map);
		}
	    else if(line[0] == 'v' && line[1] == 'n') 
	    { 
			istringstream s(line.substr(2));
			Vector3 normal;
			s >> normal.x;
			s >> normal.y;
			s >> normal.z;
	      	normales.push_back(normal);
		}
	    else if (line[0] == '#') 
	    { 
	    	// Commentaire
		}
	}			
 	if(normales.size()==0)
 	{
 		// Les normales n'ont pas été précalculées dans le obj
		for (int i = 0; i < vertices.size(); i+=3) 
		{
			// Il fuat les calculer
		}
 	}
	for (int i = 0; i < vertices.size(); i+=3) 
	{
		Triangle newTriangle;
		// Coordonnées
		//newTriangle.p0 = vertices[index[i]];
		//newTriangle.p1 = vertices[index[i+1]];
		//newTriangle.p2 = vertices[index[i+2]];
		newTriangle.p0 = vertices[i];
		newTriangle.p1 = vertices[i+1];
		newTriangle.p2 = vertices[i+2];	
		// Mappage
		//newTriangle.uv0 = mapping[i];
		//newTriangle.uv1 = mapping[i+1];
		//newTriangle.uv2 = mapping[i+2];
		// Normale
		//newTriangle.normale = normales[i/3];
 		newModel->listTriangle.push_back(newTriangle);
	}
	
	newModel->albTex = LoadTexture(parAlbTexFileName);
	newModel->rugTex = LoadTexture(parRugTexFileName);
	newModel->specTex = LoadTexture(parSpecTexFileName);
	
	return newModel;
}
