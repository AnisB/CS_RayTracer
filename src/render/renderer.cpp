
#include "renderer.h"


#include "helper.h"

#include <common/defines.h>


static void error_callback(int error, const char* description)
{
    PRINT_RED(error<<" "<<description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    Renderer::Instance().HandleKey(key,action);
}

static void cursor_callback(GLFWwindow *window, double xpos, double ypos)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float) height;
    float x = ratio*(2*xpos/(float)width - 1);
    float y = 2*-ypos/(float)height + 1;
    Renderer::Instance().HandleMouse(x,-y);
}

Renderer::Renderer()
: FIsRendering(false)
, FVertexArrayID(0)
, FVertexbuffer(0)
, FManager()
, FInitDone(false)
, FLastTime(-1)
{
	
}

Renderer::~Renderer()
{
	
}

void Renderer::HandleMouse(float parX, float parY)
{
	if(FInitDone)
	{
		// Calcul des déplacements relatifs
		float xMove = parX - FOldX;
		float yMove = parY - FOldY;
		FOldX = parX;
		FOldY = parY;
	    PRINT_ORANGE("x: "<<xMove<<"y: "<<yMove);
	    // Rotations
	    FCamera.Yaw(xMove);
	    FCamera.Pitch(yMove);
		FCamera.UpdateValues(FComputeShader);
	}
	else
	{
		FOldX = parX;
		FOldY = parY;
		FInitDone = true;
	}


}
void Renderer::HandleKey(int parKey, int parAction)
{
	if(parKey == GLFW_KEY_LEFT && parAction == GLFW_PRESS)
	{
		FCamera.Translate(Vector3(1.0,0.0,0.0));
		FCamera.UpdateValues(FComputeShader);

	}
	if(parKey == GLFW_KEY_RIGHT && parAction == GLFW_PRESS)
	{
		FCamera.Translate(Vector3(-1.0,0.0,0.0));
		FCamera.UpdateValues(FComputeShader);
	}
	if(parKey == GLFW_KEY_UP && parAction == GLFW_PRESS)
	{
		FCamera.Translate(Vector3(0.0,0.0,1.0));
		FCamera.UpdateValues(FComputeShader);

	}
	if(parKey == GLFW_KEY_DOWN && parAction == GLFW_PRESS)
	{
		FCamera.Translate(Vector3(0.0,0.0,-1.0));
		FCamera.UpdateValues(FComputeShader);
	}
}

bool Renderer::Init()
{
    // Initialise GLFW
    if(!glfwInit())
    {
        PRINT_RED("The glfw init failed");
        return false;
    }
    else
    {
	  PRINT_GREEN("The glfw init succeeded");
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
	FWindow = glfwCreateWindow(512, 512, "CS_RayTracer", NULL, NULL);
	if(FWindow == NULL)
	{
		PRINT_RED("The glfw open windows failed");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(FWindow);

	glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(FWindow, key_callback);
    glfwSetCursorPosCallback(FWindow, cursor_callback);

	glewExperimental = GL_TRUE;
	GLenum glewReturn = glewInit();
	if(glewReturn)
	{
	    PRINT_RED("Glew returned: "<<glewGetErrorString(glewReturn));
	}
	// Pour vérifier la version
	const GLubyte* renderer = glGetString (GL_RENDERER); 
	const GLubyte* version = glGetString (GL_VERSION); 
	PRINT_ORANGE("Renderer: "<<renderer);
	PRINT_ORANGE("Version: "<<version);
	// Everything went ok let's render
	FIsRendering = true;
	InitShaders();
	//Creating the render to quad
	CreateRenderQuad();

    // Loading the scene file
    LoadScene("data/scenes/scene_test.dat");
	PRINT_GREEN("The renderer was created succesfully");

	FLastTime = glfwGetTime();
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

	//Création du shader de la pipline fixe
	FPipelineShaderID = FManager.CreateProgramVF();

	#ifndef SIMPLE
	//Création du shader de calcul
	FComputeShader = FManager.CreateProgramC(4,3,1,1,1,3);
	#endif
	
	//Création de la texture
	GLuint renderTexture = FManager.GenerateTexture(512,512);
	
	//Activtion de la texture
	FManager.BindTexture(renderTexture);
	
	//Mappage de la texturepour dessin
	FManager.InjectTex(FPipelineShaderID,renderTexture,"displaySource");
	#ifndef SIMPLE
	//Mappage de la texture pour écriture
	FManager.InjectTex(FComputeShader,renderTexture,"renderCanvas");
	#endif
}

void Renderer::RayTracing()
{
    #ifndef SIMPLE
	FManager.BindProgram(FComputeShader);
	glDispatchCompute(512/16, 512/16, 1); 
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
    glClearColor(0.0,0.0,0.0,0.0);
	FCamera.UpdateValues(FComputeShader);
	while (!glfwWindowShouldClose (FWindow)) 
	{
	  //START_COUNT_TIME(temps);
	  glClear (GL_COLOR_BUFFER_BIT);
	  RayTracing();
	  RenderResultToScreen();
	  glfwPollEvents ();
	  glfwSwapBuffers (FWindow);
	  //END_COUNT_TIME(temps);
	  //PRINT_ORANGE("Temps pour la frame"<<temps);

	}
}


void Renderer::LoadScene(const std::string& parFilename)
{
    int index = 0;
    FScene = FParser.GetSceneFromFile(parFilename);
    if(FScene == NULL)
    {
        PRINT_RED("Fichier de scene " << parFilename << " non trouve.");
    }
    foreach(triangle, FScene->m_triangles)
    {
        FManager.InjectTriangle(FComputeShader, *triangle, index++);
    }
    /*
    index = 0;
    foreach(plan, FScene->m_planes)
    {
        FManager.InjectPlan(FComputeShader, *plan, index++);
    }
    index = 0;
    foreach(quadric, FScene->m_quadrics)
    {
        FManager.InjectQuadrique(FComputeShader, *quadric, index++);
    }
    */
	index = 0;
    foreach(light, FScene->m_lights)
    {
        FManager.InjectLight(FComputeShader, *light, index++);
    }
    index = 0;
    foreach(primitive, FScene->m_primitives)
    {
        FManager.InjectPrimitive(FComputeShader, *primitive, index++);
    }
    index = 0;
    foreach(materiau, FScene->m_materiaux)
    {
        FManager.InjectMateriau(FComputeShader, *materiau, index++);
    }
}
