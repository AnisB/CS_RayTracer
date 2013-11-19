#include "shadermanager.h"

#include <common/defines.h>

#include <fstream>
#include <vector>
std::string ReadFile(const std::string& parFileName)
{
    PRINT_GREEN<< "Loading file: "<<parFileName<<END_PRINT_COLOR;
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
        PRINT_RED<< "Couldn't load shader source: "<<parFileName<<END_PRINT_COLOR;
    }
    return fileContent;
}


void CheckShader(GLuint parShaderID)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    glGetShaderiv(parShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(parShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength>0)
    {
        char errorMessage[InfoLogLength];
        glGetShaderInfoLog(parShaderID, InfoLogLength, NULL, errorMessage);
        PRINT_RED<< errorMessage <<END_PRINT_COLOR;
    }
}


void CheckProgram(GLuint parProgramID)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    glGetProgramiv(parProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(parProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength>0)
    {   
        char errorMessage[InfoLogLength];
        glGetProgramInfoLog(parProgramID, InfoLogLength, NULL, errorMessage);
        PRINT_RED<<"Program linking error: "<<std::endl<<errorMessage <<END_PRINT_COLOR;
    }
}

ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{

}
		
GLuint ShaderManager::CreateProgramVF(const std::string& parVertex,const std::string& parFragment)
{
 	
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    std::string VertexShaderCode = ReadFile(parVertex);
    const char *vsc_str = VertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vsc_str, NULL);
    glCompileShader(vertexShaderID);
    CheckShader(vertexShaderID);
    
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string FragmentShaderCode = ReadFile(parFragment);
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


        
GLuint ShaderManager::CreateProgramCF(const std::string& parCompute,const std::string& parFragment)
{
    
    GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);
    std::string computeShaderCode = ReadFile(parCompute);
    const char *csc_str = computeShaderCode.c_str();
    glShaderSource(computeShaderID, 1, &csc_str, NULL);
    glCompileShader(computeShaderID);
    CheckShader(computeShaderID);
    
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string FragmentShaderCode = ReadFile(parFragment);
    const char *fsc_str = FragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, (&fsc_str) , NULL);
    glCompileShader(fragmentShaderID);
    CheckShader(fragmentShaderID);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, computeShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
 
    CheckProgram(programID);
 
    glDeleteShader(computeShaderID);
    glDeleteShader(fragmentShaderID);
    return 0;
}


void ShaderManager::BindProgram( GLuint parProgram)
{
    glUseProgram(parProgram);
}