
#include "renderer.h"

#include <common/defines.h>


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
	
	// Everything went ok let's render
	FIsRendering = true;
	
	//Creating the render to quad
	CreateRenderQuad();
	
	PRINT_GREEN<<"The renderer was created succesfully"<<END_PRINT_COLOR;
    return true;
}


void Renderer::CreateRenderQuad()
{
	glGenVertexArrays(1, &FVertexArrayID);
	
	glBindVertexArray(FVertexArrayID);
	 
	glGenBuffers(1, &FVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, FVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mainQuadArray), mainQuadArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0,2, GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
	FShaderID = FManager.CreateProgramVF("data/shader/vertex.glsl","data/shader/fragment.glsl");
	
}
void Renderer::Run()
{
	glColor4f(1.0,1.0,1.0,1.0);
	FManager.BindProgram(FShaderID);
	while (!glfwWindowShouldClose(FWindow))
	{
		glBindBuffer(GL_ARRAY_BUFFER, FVertexbuffer);
		 
		glDrawArrays(GL_TRIANGLES, 0, 4);
		 
		glDisableVertexAttribArray(0);
	}
}
