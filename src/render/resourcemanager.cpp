/*
 * Auteur : Anis Benyoub
 * Classe qui permet de gérer les resources de l'application
 *
 */
 
// Include header
#include "resourcemanager.h"

//Includes projet
#include <common/defines.h>
#include <common/helper.h>
#include <render/helper.h>
#include <render/renderer.h>

// includes autres
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

// Fonction de chargement de texture, ne gère que les BMP
const Texture* ResourceManager::LoadTexture(const std::string& parFileName)
{
    PRINT_GREEN("Chargement de la texture: " << parFileName);
	// Creation de la texture
    Texture * newTex = new Texture();
    // Onverture du fichier
    FILE* f = fopen(parFileName.c_str(), "rb");

    if(f==NULL)
    {
    	PRINT_RED("Erreur ouverture fichier "<<parFileName);	
    	delete newTex;
    	return NULL;
    }
    else
    {
    	PRINT_GREEN("Fichier ouvert"<<parFileName);	

    }
    // Lecture de l'entete BMP de taille 54
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); 

    // Récupération des informations de taille de l'image
    newTex->w = *(int*)&info[18];
    newTex->l = *(int*)&info[22];
	
	// 3 composantesz RGB * tailleX * tailleY
    int size = 3 * newTex->w  * newTex->l;
    // Lecture de tout le reste du fichier
    unsigned char* data = new unsigned char[size];
    fread(data, sizeof(unsigned char), size, f);
    // Fermeture du fichier
    fclose(f);
	//Copie des données dans la structure data
    for(int i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }
	// Copie dans la structure textures
    newTex->content = data;
    // Génération d'une texture contenant ces données
    glGenTextures(1, &newTex->id);
    glBindTexture(GL_TEXTURE_2D, newTex->id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, newTex->w, newTex->l, 0, GL_RGB, GL_UNSIGNED_BYTE, newTex->content);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
	FTexIndex++;
	return newTex;
}

// Chargement d'un fichier .obj avec 3 textures associées, on ignore le fichier .mtl
// Inspiré de http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
ObjFile* ResourceManager::LoadModel(const std::string& parFileName, const std::string& parAlbTexFileName, const std::string& parRugTexFileName, const std::string& parSpecTexFileName, const std::string& parNormalTexFileName )
{
	// Liste des points
	std::vector<Vector3> vertices;
	// Liste des normales par triangle
	std::vector<Vector3> normales;
	// Gestion des triangles
	std::vector<indexList> indexes;
	std::vector<indexList> uvList;
	
	// Liste des coordonnées de mappage
	std::vector<vec2> mapping;
	
	// Onverture du fichier
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
  	// Creation de l'objet
 	ObjFile * newModel = new ObjFile();
	string line;
	while (getline(in, line)) 
	{
		// On a trouvé "v " on est dans le cas d'un vertice
	    if (line.substr(0,2) == "v ") 
	    {
	      stringstream s(line.substr(2));
	      Vector3 v; 
	      s >> v.x; 
	      s >> v.y; 
	      s >> v.z; 
	      // On sauvegarde un vertice
	      vertices.push_back(v);
	    }
	    else if (line.substr(0,2) == "f ") 
	    {
	      // On a trouvé "f " C'est la définition d'un triangle avec son UV mapping
	      stringstream s(line.substr(2));
	      std::string a,b,c;
	      std::vector<std::string> lineSplitted = split(line,' ');
	      a = lineSplitted[1];
	      b = lineSplitted[2];
	      c = lineSplitted[3];
	      std::vector<std::string> index1 = split(a,'/');
	      std::vector<std::string> index2 = split(b,'/');
	      std::vector<std::string> index3 = split(c,'/');
	      indexList triangleIndex;
	      triangleIndex.p0 = convertToInt(index1[0]);
	      triangleIndex.p1 = convertToInt(index2[0]);
	      triangleIndex.p2 = convertToInt(index3[0]);
		  triangleIndex.p0--;
		  triangleIndex.p1--;
		  triangleIndex.p2--;
		  indexes.push_back(triangleIndex);
		  indexList uvindex;
  	      uvindex.p0 = convertToInt(index1[1]);
	      uvindex.p1 = convertToInt(index2[1]);
	      uvindex.p2 = convertToInt(index3[1]);
		  uvindex.p0--;
		  uvindex.p1--;
		  uvindex.p2--;
		  uvList.push_back(uvindex);
	    }
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
 	
	for (int i = 0; i < indexes.size(); i+=1) 
	{
		// Création du triangle
		Triangle newTriangle;
		newTriangle.p0 = vertices[indexes[i].p0];
		newTriangle.p1 = vertices[indexes[i].p1];
		newTriangle.p2 = vertices[indexes[i].p2];
		newTriangle.uv0 = mapping[uvList[i].p0];
		newTriangle.uv1 = mapping[uvList[i].p1];
		newTriangle.uv2 = mapping[uvList[i].p2];
		// Calcul des normales
    	newTriangle.normale = Vector3::crossProduct(newTriangle.p1-newTriangle.p0,newTriangle.p2-newTriangle.p0);
    	newTriangle.normale/=newTriangle.normale.Norm();
 		newModel->listTriangle.push_back(newTriangle);
	}
	// Creation du fichier de texture en dur pour l'obj
	foreach(triangle,newModel->listTriangle)
	{
		newModel->material.color = Vector4(0.2,0.3,0.8,1.0);
		newModel->material.indiceRefraction = 1.44;
		newModel->material.texAlbedo = 0;
		newModel->material.texRough = 1;
		newModel->material.texSpec = 2;
	}
	// On charge les textures
	newModel->albTex = LoadTexture(parAlbTexFileName);
	newModel->rugTex = LoadTexture(parRugTexFileName);
	newModel->specTex = LoadTexture(parSpecTexFileName);
	newModel->normalTex = LoadTexture(parNormalTexFileName);
	
	return newModel;
}
