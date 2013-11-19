
#include "renderer.h"


#include "helper.h"

#include <common/defines.h>

#define BUFFER_OFFSET(i) ((void*)(i))

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

Renderer::Renderer()
: FIsRendering(false)
, FVertexArrayID(0)
, FVertexbuffer(0)
, FManager()
{
	
}

Renderer::~Renderer()
{
	
}


bool Renderer::Init()
{
    // Initialise GLFW
    if(!glfwInit())
    {
        PRINT_RED<<"The glfw init failed"<<END_PRINT_COLOR;
        return false;
    }
    else
    {
	  PRINT_GREEN<<"The glfw init succeeded"<<END_PRINT_COLOR;
    }
    // Defintion du core profile
    #ifdef MACOSX
    // Création d'une fenetre OpenGL 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    #else
    // Création d'une fenetre OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	#endif
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	// Open a window and create its OpenGL context
	FWindow = glfwCreateWindow(640, 480, "CS_RayTracer", NULL, NULL);
	if(FWindow == NULL)
	{
		PRINT_RED<<"The glfw open windows failed"<<END_PRINT_COLOR;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(FWindow);

	glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(FWindow, key_callback);

	glewExperimental = GL_TRUE;
	GLenum glewReturn = glewInit();
	if(glewReturn)
	{
	    PRINT_RED<<"Glew returned: "<<glewGetErrorString(glewReturn)<<END_PRINT_COLOR;
	}
	// Pour vérifier la version
	const GLubyte* renderer = glGetString (GL_RENDERER); 
	const GLubyte* version = glGetString (GL_VERSION); 
	PRINT_ORANGE<<"Renderer: "<<renderer<<END_PRINT_COLOR;
	PRINT_ORANGE<<"Version: "<<version<<END_PRINT_COLOR;
	// Everything went ok let's render
	FIsRendering = true;

	InitShaders();

	//Creating the render to quad
	CreateRenderQuad();

	
	PRINT_GREEN<<"The renderer was created succesfully"<<END_PRINT_COLOR;
    return true;
}


void Renderer::CreateRenderQuad()
{
	glGenVertexArrays (1, &FVertexArrayID);
	glBindVertexArray (FVertexArrayID);
	glGenBuffers(1, &FVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, FVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mainQuadArray), mainQuadArray, GL_STATIC_DRAW);
	GLuint posAtt = glGetAttribLocation(FPipelineShaderID, "Vertex_Pos");
	GLuint texAtt = glGetAttribLocation(FPipelineShaderID, "Vertex_TexCoord");
	glEnableVertexAttribArray (posAtt);
	glEnableVertexAttribArray (texAtt);
	glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer (texAtt, 2, GL_FLOAT, GL_TRUE, sizeof (GLfloat) * 3, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);
}
void Renderer::InitShaders()
{
	//Création de la texture
	GLuint renderTexture = FManager.GenerateTexture(512,512);
	//Création du shader de la pipline fixe
	FPipelineShaderID = FManager.CreateProgramVF("data/shader/vertex.glsl","data/shader/fragment.glsl");
	//Mappage de la texturepour dessin
	FManager.BindTexture(FPipelineShaderID,renderTexture,"displaySource");

	#ifndef MACOSX
	//Création du shader de calcul
	FComputeShader = FManager.CreateProgramC("data/shader/basecompute.glsl");
	//Mappage de la texture pour écriture
	FManager.BindTexture(FComputeShader,renderTexture,"renderCanvas");
	#endif

	
}
void Renderer::RayTracing()
{
	#ifndef MACOSX
	FManager.BindProgram(FComputeShader);
	glDispatchCompute(512/16, 512/16, 1); // 512^2 threads in blocks of 16^2
	CheckGLState("RayTracing");
	#endif
}

void Renderer::RenderResultToScreen()
{
	  FManager.BindProgram(FPipelineShaderID);
	  glBindVertexArray (FVertexArrayID);
	  glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
	  glBindVertexArray (0);
}

void Renderer::Run()
{
	glColor4f(1.0,1.0,1.0,1.0);
	FManager.BindProgram(FPipelineShaderID);
	while (!glfwWindowShouldClose (FWindow)) 
	{
	  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  RayTracing();
	  RenderResultToScreen();
	  glfwPollEvents ();
	  glfwSwapBuffers (FWindow);
	}
}
