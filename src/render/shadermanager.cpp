#include "shadermanager.h"

#include "helper.h"


#include <common/defines.h>

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
#define compute_shader_raytrace "data/shader/raytrace/raytrace.glsl"
#define compute_shader_final "data/shader/raytrace/final.glsl"


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
    GLuint newTexture;
    glGenTextures(1, &newTexture);

    glBindTexture(GL_TEXTURE_2D, newTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, parW, parH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    #ifndef MACOSX
    glBindImageTexture(0, newTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    #endif
    glBindTexture(GL_TEXTURE_2D, 0);

    return newTexture;
}

void ShaderManager::InjectTex(GLuint parShaderID, size_t parIndexTex, const std::string& parName)
{
    BindProgram(parShaderID);
    glUniform1i(glGetUniformLocation(parShaderID, parName.c_str()), 0);
}

void ShaderManager::Injectd(GLuint parShaderID, double parValue, const std::string& parName)
{
    BindProgram(parShaderID);
    glUniform1f(glGetUniformLocation(parShaderID, parName.c_str()), parValue);
}
void ShaderManager::InjectVec3(GLuint parShaderID, const Vector3& parValue, const std::string& parName)
{
    PRINT_ORANGE("Injected "<<parValue);
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

 
GLuint ShaderManager::CreateProgramC(int parNbTriangle, int parNbPlan, int parNbQuad, int parNbNoeud, int parNbPrimMax)
{
    GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);
    std::string computeShader;

    std::string computeShaderHeader = ReadFile(compute_shader_header);
    std::string computeShaderCommon = ReadFile(compute_shader_common);
    std::string computeShaderOctree = ReadFile(compute_shader_octree);
    std::string computeShaderBrdf = ReadFile(compute_shader_brdf);
    std::string computeShaderIntersect = ReadFile(compute_shader_intersect);
    std::string computeShaderRaytrace = ReadFile(compute_shader_raytrace);
    std::string computeShaderFinal = ReadFile(compute_shader_final);

    computeShader+=computeShaderHeader;
    std::stringstream ss;
    ss<<"const int NB_TRIANGLE = " << convertToString(parNbTriangle)<<";"<<std::endl;
    ss<<"const int NB_PLAN = " <<convertToString(parNbPlan)<<";"<<std::endl;
    ss<<"const int NB_QUAD = " << convertToString(parNbQuad)<<";"<<std::endl;
    ss<<"const int NB_NOEUD = " << convertToString(parNbNoeud)<<";"<<std::endl;
    ss<<"const int NB_PRIM_MAX = " << convertToString(parNbPrimMax)<<";"<<std::endl;
    PRINT_ORANGE(ss.str());
    computeShader+=ss.str();
    computeShader+=computeShaderCommon;
    computeShader+=computeShaderOctree;
    computeShader+=computeShaderBrdf;
    computeShader+=computeShaderIntersect;
    computeShader+=computeShaderRaytrace;
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


void ShaderManager::BindProgram( GLuint parProgram)
{
    glUseProgram(parProgram);
}
