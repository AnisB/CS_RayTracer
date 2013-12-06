/*
 * Auteur : Anis Benyoub
 * Classe qui permet de gérer les nuanceurs
 *
 */
 // include header
#include "shadermanager.h"
//Include projet
#include "helper.h"
#include <common/defines.h>
#include <common/helper.h>
// Includes autres
#include <fstream>
#include <vector>
#include <sstream>

// Define des path vers les shaders d'affichage
#define vertex_shader "data/shader/vertex.glsl"
#define fragment_shader "data/shader/fragment.glsl"

// Define des path de toutes les composantes du compute shader
#define compute_shader_header "data/shader/raytrace/head.glsl"
#define compute_shader_common "data/shader/raytrace/common.glsl"
#define compute_shader_octree "data/shader/raytrace/octree.glsl"
#define compute_shader_brdf "data/shader/raytrace/brdf.glsl"
#define compute_shader_intersect "data/shader/raytrace/intersect.glsl"
#define compute_shader_raytrace2 "data/shader/raytrace/raytrace2.glsl"
#define compute_shader_raytrace "data/shader/raytrace/raytrace.glsl"
#define compute_shader_final "data/shader/raytrace/final.glsl"

// Méthode de normalisation 400.0 étant la distance du far clipping plane
#define TO_GLSL_UNIT(Val) (Val/400.0 +0.5)

// Lecture d'un fichier et renvoie sous forme string
std::string ReadFile(const std::string& parFileName)
{
    PRINT_GREEN( "Loading file: "<<parFileName);
    std::string fileContent;
    std::fstream fileStream;
    fileStream.open(parFileName.c_str());
    if(fileStream.is_open())
    {
        std::string Line = "";
        while(getline(fileStream, Line))
            fileContent += "\n" + Line;
        fileStream.close();
    }
    else
    {
        PRINT_RED( "Couldn't load shader source: "<<parFileName);
    }
    return fileContent;
}

// Méthode d'écriture d'une string dans un fichier
std::string WriteFile(const std::string& parFileName, const std::string & parContent)
{
    PRINT_GREEN( "Loading file: "<<parFileName);
    std::string fileContent;
    std::fstream fileStream;
    fileStream.open(parFileName.c_str(), std::ios::out );
    if(fileStream.is_open())
    {
        fileStream<<parContent;
        fileStream.close();
    }
    else
    {
        PRINT_RED( parContent);
    }
    return fileContent;
}

// Méthode de vérification d'un shader et d'affichage des erreurs 
// pour un shader
void CheckShader(GLuint parShaderID)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    glGetShaderiv(parShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(parShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength>1)
    {
        char errorMessage[InfoLogLength];
        glGetShaderInfoLog(parShaderID, InfoLogLength, NULL, errorMessage);
        PRINT_RED( "Shader error:"<< parShaderID);
        PRINT_RED( errorMessage );
    }
}

// Méthode de vérification d'un shader et d'affichage des erreurs 
// pour le linkage
void CheckProgram(GLuint parProgramID)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    glGetProgramiv(parProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(parProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength>1)
    {   
        char errorMessage[InfoLogLength];
        glGetProgramInfoLog(parProgramID, InfoLogLength, NULL, errorMessage);
        PRINT_RED("Program linking error: "<<std::endl<<errorMessage );
    }
}

// Fonction de concatenation
std::string concatenate(const std::string& parBase, int parIndex, const std::string& parAttrib)
{
    std::string result = parBase;
    result+="[";
    result+=convertToString(parIndex);
    result+="].";
    result+=parAttrib;
    return result;
}

// Constructeur du shader manager
ShaderManager::ShaderManager()
{

}

// Destructeur du shader manager
ShaderManager::~ShaderManager()
{

}

// Méthode de création de la pipline d'affichage	
GLuint ShaderManager::CreateProgramVF()
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    std::string VertexShaderCode = ReadFile(vertex_shader);
    const char *vsc_str = VertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vsc_str, NULL);
    glCompileShader(vertexShaderID);
    CheckShader(vertexShaderID);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string FragmentShaderCode = ReadFile(fragment_shader);
    const char *fsc_str = FragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, (&fsc_str) , NULL);
    glCompileShader(fragmentShaderID);
    CheckShader(fragmentShaderID);
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
 
    CheckProgram(programID);
    return programID;
}

// Méthode de génération de la texture de communication
GLuint ShaderManager::GenerateTexture(size_t parW, size_t parH) 
{
    glGenTextures(1, &FTexture);
    glBindTexture(GL_TEXTURE_2D, FTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, parW, parH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    #ifndef MACOSX
    glBindImageTexture(0, FTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    #endif
    glBindTexture(GL_TEXTURE_2D, 0);
    return FTexture;
}
// Méthode d'injectino d'une texture avec un offset
void ShaderManager::InjectTex(GLuint parShaderID, size_t parIndexTex, const std::string& parName, GLuint parOffset)
{
	BindProgram(parShaderID);
   	glActiveTexture(GL_TEXTURE0+parOffset);
    glBindTexture(GL_TEXTURE_2D, parIndexTex);
    GLint texRef = glGetUniformLocation(parShaderID, parName.c_str());
    glUniform1i(texRef, 0+parOffset);
    BindProgram(0);
}

void ShaderManager::Injectd(GLuint parShaderID, double parValue, const std::string& parName)
{
    glUniform1f(glGetUniformLocation(parShaderID, parName.c_str()), parValue);
}
void ShaderManager::InjectVec3(GLuint parShaderID, const Vector3& parValue, const std::string& parName)
{
	BindProgram(parShaderID);
    glUniform3f(glGetUniformLocation(parShaderID, parName.c_str()), parValue.x, parValue.y, parValue.z);
}

void ShaderManager::BindTexture(size_t parIndexTex)
{
    glBindTexture(GL_TEXTURE_2D, parIndexTex);
}   
void ShaderManager::UnbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}   

GLuint ShaderManager::CreateProgramC(int parMaxRecur, int parNbTriangle, int parNbPlan, int parNbQuad, int parNbNoeud, int parNbPrimMax, int nbMat, bool oreille)
{
    GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);

    std::string computeShader;
    std::string computeShaderHeader = ReadFile(compute_shader_header);
    std::string computeShaderCommon = ReadFile(compute_shader_common);
    std::string computeShaderOctree = ReadFile(compute_shader_octree);
    std::string computeShaderBrdf = ReadFile(compute_shader_brdf);
    std::string computeShaderIntersect = ReadFile(compute_shader_intersect);
    std::string computeShaderRaytrace2 = ReadFile(compute_shader_raytrace2);
    std::string computeShaderRaytrace = ReadFile(compute_shader_raytrace);
    std::string computeShaderFinal = ReadFile(compute_shader_final);

    computeShader+=computeShaderHeader;
    std::stringstream ss;
    ss<<"#define NB_TRIANGLE " << convertToString(parNbTriangle)<<std::endl;
    ss<<"#define NB_PLAN " <<convertToString(parNbPlan)<<std::endl;
    ss<<"#define NB_QUAD " << convertToString(parNbQuad)<<std::endl;
    ss<<"#define NB_MAT " << convertToString(parNbTriangle)<<std::endl;
    ss<<"#define NB_NOEUD " << convertToString(parNbNoeud)<<std::endl;
    ss<<"#define NB_PRIM " << convertToString(parNbPrimMax)<<std::endl;
    ss<<"#define NB_PRIM_MAX " << convertToString(parNbPrimMax)<<std::endl;
	ss<<"#define NB_TEX " << convertToString(nbMat)<<std::endl;
	ss<<"#define NB_LIGHTS " << convertToString(1)<<std::endl;
	if(oreille)
	{
		ss<<"#define BRDF_DEFINED true" <<std::endl;
	}
	else
	{
		ss<<"#define BRDF_DEFINED false" <<std::endl;
	}
    computeShader+=ss.str();
    computeShader+=computeShaderCommon;
    computeShader+=computeShaderOctree;
    computeShader+=computeShaderBrdf;
    computeShader+=computeShaderIntersect;
    
    computeShader+= replaceAll(computeShaderRaytrace2,"@NB_ITER@", convertToString(parMaxRecur));
    for(int i = parMaxRecur-1 ; i!= 0; --i)
    {
    	const std::string& firstPass=replaceAll(computeShaderRaytrace,"@NB_ITER@", convertToString(i));
    	const std::string& secondPass=replaceAll(firstPass,"@NB_ITER2@", convertToString(i+1));
    	computeShader+=secondPass;
    }
    //computeShader+=computeShaderRaytrace;
    computeShader+=computeShaderFinal;

    WriteFile("computeLog.glsl", computeShader);
    
    const char *csc_str = computeShader.c_str();
    glShaderSource(computeShaderID, 1, &csc_str, NULL);
    glCompileShader(computeShaderID);
    CheckShader(computeShaderID);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, computeShaderID);
    glLinkProgram(programID);
    CheckProgram(programID);
    return programID;
}

GLuint ShaderManager::CreateTexTriangle(const std::vector<Triangle>& parValue)
{
	GLuint triangleTex;
	GLfloat * triangleData = new GLfloat[18*parValue.size()];
	int index = 0;
	foreach(triangle, parValue)
	{

		triangleData[index*18+0] = TO_GLSL_UNIT(triangle->p0.x);
		triangleData[index*18+1] = TO_GLSL_UNIT(triangle->p0.y); 
		triangleData[index*18+2] = TO_GLSL_UNIT(triangle->p0.z);

		triangleData[index*18+3] = triangle->uv0.u; 
		triangleData[index*18+4] = triangle->uv0.v;	
			
		triangleData[index*18+5] = TO_GLSL_UNIT(triangle->p1.x);
		triangleData[index*18+6] = TO_GLSL_UNIT(triangle->p1.y); 
		triangleData[index*18+7] = TO_GLSL_UNIT(triangle->p1.z);
		
		triangleData[index*18+8] = triangle->uv1.u; 
		triangleData[index*18+9] = triangle->uv1.v;
		
		triangleData[index*18+10] = TO_GLSL_UNIT(triangle->p2.x);
		triangleData[index*18+11] = TO_GLSL_UNIT(triangle->p2.y); 
		triangleData[index*18+12] = TO_GLSL_UNIT(triangle->p2.z);
		
		triangleData[index*18+13] = triangle->uv2.u; 
		triangleData[index*18+14] = triangle->uv2.v;	
		
		triangleData[index*18+15] = triangle->normale.x;
		triangleData[index*18+16] = triangle->normale.y; 
		triangleData[index*18+17] = triangle->normale.z;
		PRINT_ORANGE("First "<<triangleData[index*18+0]<<" "<<triangleData[index*18+1]<<" "<<triangleData[index*18+2]);

		index++;		
	}
	
	glGenTextures(1, &triangleTex);
	glBindTexture (GL_TEXTURE_2D, triangleTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 18, parValue.size(),0, GL_RED, GL_FLOAT, triangleData);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
    #ifndef MACOSX
    glBindImageTexture(1, triangleTex, 0, GL_TRUE, 0, GL_READ_ONLY, GL_R32F);
    #endif
	glBindTexture (GL_TEXTURE_2D, 0);
	
	delete [] triangleData;
	return triangleTex;
}


GLuint ShaderManager::CreateTexQuad(const std::vector<Quadrique>& parValue)
{
	GLuint quadTex;
	GLfloat * quadData = new GLfloat[10*parValue.size()];
	int index = 0;
	foreach(quad, parValue)
	{

		quadData[index*10+0] = TO_GLSL_UNIT(quad->A);
		quadData[index*10+1] = TO_GLSL_UNIT(quad->B); 
		quadData[index*10+2] = TO_GLSL_UNIT(quad->C);
		
		quadData[index*10+3] = TO_GLSL_UNIT(quad->D);
		quadData[index*10+4] = TO_GLSL_UNIT(quad->E);	
		quadData[index*10+5] = TO_GLSL_UNIT(quad->F);
				
		quadData[index*10+6] = TO_GLSL_UNIT(quad->G);
		quadData[index*10+7] = TO_GLSL_UNIT(quad->H);
		quadData[index*10+8] = TO_GLSL_UNIT(quad->I);
		
		quadData[index*10+9] = TO_GLSL_UNIT(quad->J);	
		PRINT_ORANGE("Quad "<<quadData[index*10+0]<<" "<<quadData[index*10+1]<<" "<<quadData[index*10+2]);

		index++;		
	}
	
	glGenTextures(1, &quadTex);
	glBindTexture (GL_TEXTURE_2D, quadTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 10, parValue.size(),0, GL_RED, GL_FLOAT, quadData);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture (GL_TEXTURE_2D, 0);
	
	delete [] quadData;
	return quadTex;
}

GLuint ShaderManager::CreateTexNoeud(const std::vector<Node>& parValue, int par_nb_prim_max, int par_nb_prim)
{
	PRINT_ORANGE("CreateTexNoeud" );
	GLuint noeudTex;
	GLint NODE_STRIDE = 24;  // 24 HARDCODED
	GLfloat * noeudData = new GLfloat[NODE_STRIDE*parValue.size()];
	int index = 0;
	foreach(node, parValue)
	{
		
		// childs (int)
		noeudData[index*NODE_STRIDE+0] = ((node->child[0]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+1] = ((node->child[1]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+2] = ((node->child[2]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+3] = ((node->child[3]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+4] = ((node->child[4]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+5] = ((node->child[5]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+6] = ((node->child[6]+1)/((float)parValue.size()-1)); 
		noeudData[index*NODE_STRIDE+7] = ((node->child[7]+1)/((float)parValue.size()-1)); 

		// coords (float)
		noeudData[index*NODE_STRIDE+8] = TO_GLSL_UNIT(node->coords[0]);
		noeudData[index*NODE_STRIDE+9] = TO_GLSL_UNIT(node->coords[1]);
		noeudData[index*NODE_STRIDE+10] = TO_GLSL_UNIT(node->coords[2]);
		noeudData[index*NODE_STRIDE+11] = TO_GLSL_UNIT(node->coords[3]);
		noeudData[index*NODE_STRIDE+12] = TO_GLSL_UNIT(node->coords[4]);
		noeudData[index*NODE_STRIDE+13] = TO_GLSL_UNIT(node->coords[5]);
		
		// objects_ids (int)
		for (int j=0;j<par_nb_prim_max;j++){
			if (j < int(node->objects_id.size())){ //data
				noeudData[index*NODE_STRIDE+14+j] = ((node->objects_id[j]+1)/((float)par_nb_prim-1)); 
			}
			else { // no data
				//noeudData[index*NODE_STRIDE+14+j] = (-1+1)/((float)par_nb_prim-1);
				noeudData[index*NODE_STRIDE+14+j] = 0.0;
			}
		}
     	
		index++;		
	}
	
	glGenTextures(1, &noeudTex);
	glBindTexture (GL_TEXTURE_2D, noeudTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, float(NODE_STRIDE), parValue.size(),0, GL_RED, GL_FLOAT, noeudData);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture (GL_TEXTURE_2D, 0);
	
	delete [] noeudData;
	return noeudTex;
}

GLuint ShaderManager::CreateTexPrimitive(const std::vector<Primitive>& parValue, int parNbMateriau)
{
	GLuint primTex;
	GLfloat * primData = new GLfloat[3*parValue.size()];
	int index = 0;
	foreach(prim, parValue)
	{
		primData[index*3+0] = (prim->type/2.0);
        primData[index*3+1] = (prim->index/((float)parValue.size()-1));
		primData[index*3+2] = (prim->materiau/((float)parNbMateriau -1));

		PRINT_ORANGE("Prim "<<primData[index*3+0]<<" "<<primData[index*3+1]<<" "<<primData[index*3+2]);
		index++;		
	}
	
	glGenTextures(1, &primTex);
	glBindTexture (GL_TEXTURE_2D, primTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 3, parValue.size(),0, GL_RED, GL_FLOAT, primData);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture (GL_TEXTURE_2D, 0);
	
	delete [] primData;
	return primTex;
}


GLuint ShaderManager::CreateTexMat(const std::vector<Materiau>& parValue)
{
	GLuint matTex;
	GLfloat * matData = new GLfloat[11*parValue.size()];
	int index = 0;
	foreach(mat, parValue)
	{
		matData[index*11+0] = (mat->color.x);
		matData[index*11+1] = (mat->color.y);
		matData[index*11+2] = (mat->color.z);

		matData[index*11+3] = (mat->coeffReflexion);
		matData[index*11+4] = (mat->coeffRefraction);
		matData[index*11+5] = (mat->indiceRefraction);
		
		matData[index*11+6] = (mat->diff);
		matData[index*11+7] = (mat->spec);		
		
		matData[index*11+8] = (mat->texAlbedo);
		matData[index*11+9] = (mat->texRough);
		matData[index*11+10] = (mat->texSpec);
		
		index++;		
	}
	
	glGenTextures(1, &matTex);
	glBindTexture (GL_TEXTURE_2D, matTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 11, parValue.size(),0, GL_RED, GL_FLOAT, matData);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture (GL_TEXTURE_2D, 0);
	delete [] matData;
	return matTex;	
}
void ShaderManager::InjectLight(GLuint parShaderID, const Light& parLight, int parIndex)
{
	BindProgram(parShaderID);
	PRINT_ORANGE("On injecte la lumière :"<<std::endl<<parLight);
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listLight",parIndex,"position").c_str()), parLight.position.x, parLight.position.y, parLight.position.z);    
    glUniform1i(glGetUniformLocation(parShaderID, concatenate("listLight",parIndex,"intensity").c_str()), parLight.intensity);  
    glUniform4f(glGetUniformLocation(parShaderID, concatenate("listLight",parIndex,"colorSpec").c_str()), parLight.color.x, parLight.color.y, parLight.color.z, 1.0);   
}
void ShaderManager::BindProgram( GLuint parProgram)
{
    glUseProgram(parProgram);
}
