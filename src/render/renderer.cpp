
#include "renderer.h"

#include <common/defines.h>


Renderer::Renderer()
: FIsRendering(false)
, FVertexArrayID(0)
, FVertexbuffer(0)
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
    // Création d'une fenetre OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Defintion du core profile
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
	
}
void Renderer::Run()
{
	glColor4f(1.0,1.0,1.0,1.0);
	while (!glfwWindowShouldClose(FWindow))
	{
		glBindBuffer(GL_ARRAY_BUFFER, FVertexbuffer);
		 
		glDrawArrays(GL_TRIANGLES, 0, 4);
		 
		glDisableVertexAttribArray(0);
	}
}
