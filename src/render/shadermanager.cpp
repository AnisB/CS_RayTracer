#include "shadermanager.h"

#include "helper.h"


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



    if(InfoLogLength>1)
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
    if(InfoLogLength>1)
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
 	CheckGLState("CreateProgramVF b");
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
 	CheckGLState("CreateProgramVF e");
    return programID;
}


GLuint ShaderManager::GenerateTexture(size_t parW, size_t parH) 
{
    CheckGLState("GenerateTexture begin");
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
    CheckGLState("GenerateTexture end"); 
    glBindTexture(GL_TEXTURE_2D, 0);

    return newTexture;
}

void ShaderManager::InjectToShader(GLuint parShaderID, size_t parIndexTex, const std::string& parName)
{
	CheckGLState("InjectToShader b");
    BindProgram(parShaderID);
    CheckGLState("InjectToShader m1");
    glUniform1i(glGetUniformLocation(parShaderID, parName.c_str()), 0);
    CheckGLState("InjectToShader m2");
    CheckGLState("InjectToShader e");
}
    
void ShaderManager::BindTexture(size_t parIndexTex)
{
	CheckGLState("BindTexture");
    glBindTexture(GL_TEXTURE_2D, parIndexTex);
}   
void ShaderManager::UnbindTexture()
{
	CheckGLState("UnbindTexture");
    glBindTexture(GL_TEXTURE_2D, 0);
}   

 
GLuint ShaderManager::CreateProgramC(const std::string& parCompute)
{
	CheckGLState("CreateProgramC b");
    GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);
    CheckGLState("CreateProgramC m1");
    std::string computeShaderCode = ReadFile(parCompute);
    const char *csc_str = computeShaderCode.c_str();
    std::cout<<csc_str<<std::endl;
    glShaderSource(computeShaderID, 1, &csc_str, NULL);
    CheckGLState("CreateProgramC m2");
    glCompileShader(computeShaderID);
    CheckGLState("CreateProgramC m3");
    //CheckShader(computeShaderID);

    GLuint programID = glCreateProgram();
    CheckGLState("CreateProgramC m3");
    glAttachShader(programID, computeShaderID);
    CheckGLState("CreateProgramC m4");
    glLinkProgram(programID);
 	CheckGLState("CreateProgramC m5");
    //CheckProgram(programID);
    CheckGLState("CreateProgramC e");
    return 0;
}


void ShaderManager::BindProgram( GLuint parProgram)
{
    glUseProgram(parProgram);
}
