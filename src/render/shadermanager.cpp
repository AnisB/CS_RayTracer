#include "shadermanager.h"

#include "helper.h"


#include <common/defines.h>
#include <common/helper.h>


#include <fstream>
#include <vector>
#include <sstream>



#define vertex_shader "data/shader/vertex.glsl"
#define fragment_shader "data/shader/fragment.glsl"

#define compute_shader_header "data/shader/raytrace/head.glsl"
#define compute_shader_common "data/shader/raytrace/common.glsl"
#define compute_shader_octree "data/shader/raytrace/octree.glsl"
#define compute_shader_brdf "data/shader/raytrace/brdf.glsl"
#define compute_shader_intersect "data/shader/raytrace/intersect.glsl"
#define compute_shader_raytrace2 "data/shader/raytrace/raytrace2.glsl"
#define compute_shader_raytrace "data/shader/raytrace/raytrace.glsl"
#define compute_shader_final "data/shader/raytrace/final.glsl"

#define TO_GLSL_UNIT(Val) (Val/400.0 +0.5)


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
std::string concatenate(const std::string& parBase, int parIndex, const std::string& parAttrib)
{
    std::string result = parBase;
    result+="[";
    result+=convertToString(parIndex);
    result+="].";
    result+=parAttrib;
    return result;
}
ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{

}
		
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

GLuint ShaderManager::CreateProgramC(int parMaxRecur, int parNbTriangle, int parNbPlan, int parNbQuad, int parNbNoeud, int parNbPrimMax)
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
    ss<<"#define NB_PRIM " << convertToString(parNbTriangle)<<std::endl;
	ss<<"#define NB_TEX " << convertToString(10)<<std::endl;
	ss<<"#define NB_LIGHTS " << convertToString(1)<<std::endl;
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


void ShaderManager::InjectTriangle(GLuint parShaderID, const Triangle& parValue, int parIndex)
{
	//PRINT_ORANGE("On injecte le triangle :"<<std::endl<<parValue);
	BindProgram(parShaderID);
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"p0").c_str()), parValue.p0.x, parValue.p0.y, parValue.p0.z);      
    glUniform2f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"uv0").c_str()), parValue.uv0.u, parValue.uv0.v);      
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"p1").c_str()), parValue.p1.x, parValue.p1.y, parValue.p1.z);  
    glUniform2f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"uv1").c_str()), parValue.uv1.u, parValue.uv1.v);      
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"p2").c_str()), parValue.p2.x, parValue.p2.y, parValue.p2.z);
    glUniform2f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"uv2").c_str()), parValue.uv2.u, parValue.uv2.v);      
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listTriangle",parIndex,"normale").c_str()), parValue.normale.x, parValue.normale.y, parValue.normale.z);
}

GLuint ShaderManager::CreateTexTriangle(const std::vector<Triangle>& parValue)
{
	GLuint triangleTex;
	GLfloat * triangleData = new GLfloat[18*parValue.size()];
	int index = 0;
	foreach(triangle, parValue)
	{
		//PRINT_ORANGE("First "<<
		triangleData[index*18+0] = TO_GLSL_UNIT(triangle->p0.x);
		triangleData[index*18+1] = TO_GLSL_UNIT(triangle->p0.y); 
		triangleData[index*18+2] = TO_GLSL_UNIT(triangle->p0.z);
		
		triangleData[index*18+3] = TO_GLSL_UNIT(triangle->uv0.u); 
		triangleData[index*18+4] = TO_GLSL_UNIT(triangle->uv0.v);	
			
		triangleData[index*18+5] = TO_GLSL_UNIT(triangle->p1.x);
		triangleData[index*18+6] = TO_GLSL_UNIT(triangle->p1.y); 
		triangleData[index*18+7] = TO_GLSL_UNIT(triangle->p1.z);
		
		triangleData[index*18+8] = TO_GLSL_UNIT(triangle->uv1.u); 
		triangleData[index*18+9] = TO_GLSL_UNIT(triangle->uv1.v);
		
		triangleData[index*18+10] = TO_GLSL_UNIT(triangle->p2.x);
		triangleData[index*18+11] = TO_GLSL_UNIT(triangle->p2.y); 
		triangleData[index*18+12] = TO_GLSL_UNIT(triangle->p2.z);
		
		triangleData[index*18+13] = TO_GLSL_UNIT(triangle->uv2.u); 
		triangleData[index*18+14] = TO_GLSL_UNIT(triangle->uv2.v);	
		
		triangleData[index*18+15] = TO_GLSL_UNIT(triangle->normale.x);
		triangleData[index*18+16] = TO_GLSL_UNIT(triangle->normale.y); 
		triangleData[index*18+17] = TO_GLSL_UNIT(triangle->normale.z);
		PRINT_ORANGE("First "<<triangleData[index*18+0]<<" "<<triangleData[index*18+1]<<" "<<triangleData[index*18+2]);
		index++;		
	}
	
	glGenTextures(1, &triangleTex);
	glBindTexture (GL_TEXTURE_2D, triangleTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 18.0, parValue.size(),0, GL_RED, GL_FLOAT, triangleData);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture (GL_TEXTURE_2D, 0);
	
	delete [] triangleData;
	return triangleTex;
}


GLuint ShaderManager::CreateTexNoeud(const std::vector<Node>& parValue)
{
	PRINT_ORANGE("CreateTexNoeud" );
	GLuint noeudTex;
	GLint NODE_STRIDE = 24;  // 24 HARDCODED
	GLfloat * noeudData = new GLfloat[NODE_STRIDE*parValue.size()];
	int index = 0;
	foreach(node, parValue)
	{
		// childs
		noeudData[index*NODE_STRIDE+0] = TO_GLSL_UNIT(node->child[0]);
		noeudData[index*NODE_STRIDE+1] = TO_GLSL_UNIT(node->child[1]);
		noeudData[index*NODE_STRIDE+2] = TO_GLSL_UNIT(node->child[2]);
		noeudData[index*NODE_STRIDE+3] = TO_GLSL_UNIT(node->child[3]);
		noeudData[index*NODE_STRIDE+4] = TO_GLSL_UNIT(node->child[4]);
		noeudData[index*NODE_STRIDE+5] = TO_GLSL_UNIT(node->child[5]);
		noeudData[index*NODE_STRIDE+6] = TO_GLSL_UNIT(node->child[6]);
		noeudData[index*NODE_STRIDE+7] = TO_GLSL_UNIT(node->child[7]);

		// coords
		noeudData[index*NODE_STRIDE+8] = TO_GLSL_UNIT(node->coords[0]);
		noeudData[index*NODE_STRIDE+9] = TO_GLSL_UNIT(node->coords[1]);
		noeudData[index*NODE_STRIDE+10] = TO_GLSL_UNIT(node->coords[2]);
		noeudData[index*NODE_STRIDE+11] = TO_GLSL_UNIT(node->coords[3]);
		noeudData[index*NODE_STRIDE+12] = TO_GLSL_UNIT(node->coords[4]);
		noeudData[index*NODE_STRIDE+13] = TO_GLSL_UNIT(node->coords[5]);
		
		// objects_ids
		noeudData[index*NODE_STRIDE+14] = TO_GLSL_UNIT(node->objects_id[0]);
		noeudData[index*NODE_STRIDE+15] = TO_GLSL_UNIT(node->objects_id[1]);
		noeudData[index*NODE_STRIDE+16] = TO_GLSL_UNIT(node->objects_id[2]);
		noeudData[index*NODE_STRIDE+17] = TO_GLSL_UNIT(node->objects_id[3]);
		noeudData[index*NODE_STRIDE+18] = TO_GLSL_UNIT(node->objects_id[4]);
		noeudData[index*NODE_STRIDE+19] = TO_GLSL_UNIT(node->objects_id[5]);
		noeudData[index*NODE_STRIDE+20] = TO_GLSL_UNIT(node->objects_id[6]);
		noeudData[index*NODE_STRIDE+21] = TO_GLSL_UNIT(node->objects_id[7]);
		noeudData[index*NODE_STRIDE+22] = TO_GLSL_UNIT(node->objects_id[8]);
		noeudData[index*NODE_STRIDE+23] = TO_GLSL_UNIT(node->objects_id[9]);

     	
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 3.0, parValue.size(),0, GL_RED, GL_FLOAT, primData);
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
	GLfloat * matData = new GLfloat[8*parValue.size()];
	int index = 0;
	foreach(mat, parValue)
	{
		matData[index*8+0] = (mat->color.x);
		matData[index*8+1] = (mat->color.y);
		matData[index*8+2] = (mat->color.z);

		matData[index*8+3] = (mat->coeffReflexion);
		matData[index*8+4] = (mat->coeffRefraction);
		matData[index*8+5] = (mat->indiceRefraction);
		
		matData[index*8+6] = (mat->diff);
		matData[index*8+7] = (mat->spec);		
		
		PRINT_ORANGE("Mat "<<matData[index*8+0]<<" "<<matData[index*8+1]<<" "<<matData[index*8+2]<<" "<<matData[index*8+3]);
		index++;		
	}
	
	glGenTextures(1, &matTex);
	glBindTexture (GL_TEXTURE_2D, matTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 8.0, parValue.size(),0, GL_RED, GL_FLOAT, matData);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture (GL_TEXTURE_2D, 0);
	delete [] matData;
	return matTex;	
}
void ShaderManager::InjectPlan(GLuint parShaderID, const Plan& parValue, int parIndex)
{
	BindProgram(parShaderID);
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listPlan",parIndex,"p0").c_str()), parValue.p0.x, parValue.p0.y, parValue.p0.z);      
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listPlan",parIndex,"p1").c_str()), parValue.p1.x, parValue.p1.y, parValue.p1.z);  
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listPlan",parIndex,"p2").c_str()), parValue.p2.x, parValue.p2.y, parValue.p2.z);
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listPlan",parIndex,"p3").c_str()), parValue.p3.x, parValue.p3.y, parValue.p3.z); 
    glUniform3f(glGetUniformLocation(parShaderID, concatenate("listPlan",parIndex,"normale").c_str()), parValue.normale.x, parValue.normale.y, parValue.normale.z);

}
void ShaderManager::InjectQuadrique(GLuint parShaderID, const Quadrique& parValue, int parIndex)
{
	BindProgram(parShaderID);
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"A").c_str()), parValue.A);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"B").c_str()), parValue.B);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"C").c_str()), parValue.C);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"D").c_str()), parValue.D);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"E").c_str()), parValue.E);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"F").c_str()), parValue.F);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"G").c_str()), parValue.G);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"H").c_str()), parValue.H);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"I").c_str()), parValue.I);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listQuadrique",parIndex,"J").c_str()), parValue.J);  
}
void ShaderManager::InjectMateriau(GLuint parShaderID, const Materiau& parValue, int parIndex)
{
	BindProgram(parShaderID);
	//PRINT_ORANGE("On injecte le materiau :"<<std::endl<<parValue);
    glUniform4f(glGetUniformLocation(parShaderID, concatenate("listMateriau",parIndex,"color").c_str()), parValue.color.x, parValue.color.y, parValue.color.z, parValue.color.w); 
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listMateriau",parIndex,"reflectance").c_str()), parValue.coeffReflexion);  
    glUniform1f(glGetUniformLocation(parShaderID, concatenate("listMateriau",parIndex,"refractance").c_str()), parValue.coeffRefraction);  
}
void ShaderManager::InjectPrimitive(GLuint parShaderID, const Primitive& parValue, int parIndex)
{
	BindProgram(parShaderID);
	PRINT_ORANGE("On injecte la primitive :"<<std::endl<<parValue);
    glUniform1i(glGetUniformLocation(parShaderID, concatenate("listPrim",parIndex,"type").c_str()), parValue.type);  
    glUniform1i(glGetUniformLocation(parShaderID, concatenate("listPrim",parIndex,"index").c_str()), parValue.index);  
    glUniform1i(glGetUniformLocation(parShaderID, concatenate("listPrim",parIndex,"materiau").c_str()), parValue.materiau);  
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
