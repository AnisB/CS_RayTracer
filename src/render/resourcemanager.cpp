#include "resourcemanager.h"

#include <common/defines.h>
#include <common/helper.h>

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
    FILE *fd;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    unsigned char * line;
    unsigned long size;        // size of the new texture in bytes.
    int format = GL_RGB;

    cinfo.err = jpeg_std_error (&jerr);
    jpeg_create_decompress (&cinfo);

    if (0 == (fd = fopen(parFileName.c_str(), "rb")))
    {
        PRINT_RED("Error reading from file " << parFileName);
        delete newTex;
        return 0;
    }


    jpeg_stdio_src (&cinfo, fd);
    jpeg_read_header (&cinfo, TRUE);
    newTex->w = cinfo.output_width;
    newTex->l = cinfo.output_height;
    size = newTex->w * newTex->l * 3;
    newTex->content = (GLubyte *) malloc(size);

    if (GL_RGB == format)
    {
        if (cinfo.out_color_space == JCS_GRAYSCALE)
        {
            PRINT_RED("Error reading from file " << parFileName);
            delete newTex;
            return 0;
        }
    }
    else
        if (cinfo.out_color_space != JCS_GRAYSCALE)
        {
            PRINT_RED("Error reading from file " << parFileName);
            delete newTex;
            return 0;
        }

    jpeg_start_decompress (&cinfo);

    while (cinfo.output_scanline < cinfo.output_height)
    {
        line = newTex->content + (GL_RGB == format ? 3 * size : size) * cinfo.output_scanline;
        jpeg_read_scanlines (&cinfo, &line, 1);
    }
    jpeg_finish_decompress (&cinfo);
    jpeg_destroy_decompress (&cinfo);

    glGenTextures(1, &newTex->id);
    glBindTexture(GL_TEXTURE_2D, newTex->id);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, newTex->w, newTex->l, 0, GL_RGB, GL_FLOAT, newTex->content);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
	FTexIndex++;
	return newTex;
}

ObjFile* ResourceManager::LoadModel(const std::string& parFileName, const std::string& parAlbTexFileName, const std::string& parRugTexFileName, const std::string& parSpecTexFileName )
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
	    else if (line.substr(0,2) == "f ") 
	    {
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
		  
	      PRINT_ORANGE("Indexes "<<triangleIndex.p0<<" "<<triangleIndex.p1<<" "<<triangleIndex.p2);
	      //index.push_back(a); 
	      //index.push_back(b); 
	      //index.push_back(c);
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
 	if(normales.size()==0)
 	{
 		// Les normales n'ont pas été précalculées dans le obj
		for (int i = 0; i < vertices.size(); i+=3) 
		{
			// Il fuat les calculer
		}
 	}
	for (int i = 0; i < indexes.size(); i+=1) 
	{
		Triangle newTriangle;
		newTriangle.p0 = vertices[indexes[i].p0];
		newTriangle.p1 = vertices[indexes[i].p1];
		newTriangle.p2 = vertices[indexes[i].p2];
		newTriangle.uv0 = mapping[uvList[i].p0];
		newTriangle.uv1 = mapping[uvList[i].p1];
		newTriangle.uv2 = mapping[uvList[i].p2];	
 		newModel->listTriangle.push_back(newTriangle);
	}
	foreach(triangle,newModel->listTriangle)
	{
		newModel->material.color = Vector4(0.2,0.3,0.8,1.0);
		newModel->material.indiceRefraction = 1.44;
		newModel->material.texAlbedo = 0;
		newModel->material.texRough = 1;
		newModel->material.texSpec = 2;
	}
	newModel->albTex = LoadTexture(parAlbTexFileName);
	newModel->rugTex = LoadTexture(parRugTexFileName);
	newModel->specTex = LoadTexture(parSpecTexFileName);
	
	return newModel;
}
