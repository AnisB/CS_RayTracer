
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
, FInitDone(false)
, FLastTime(-1)
, FFoward(false)
, FBackward(false)
, FLeftward(false)
, FRightward(false)
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
		FLeftward = true;
	}
	if(parKey == GLFW_KEY_RIGHT && parAction == GLFW_PRESS)
	{
		FRightward = true;
	}
	if(parKey == GLFW_KEY_UP && parAction == GLFW_PRESS)
	{
		FFoward = true;
	}
	if(parKey == GLFW_KEY_DOWN && parAction == GLFW_PRESS)
	{
		FBackward = true;
	}
	if(parKey == GLFW_KEY_LEFT && parAction == GLFW_RELEASE)
	{
		FLeftward = false;
	}
	if(parKey == GLFW_KEY_RIGHT && parAction == GLFW_RELEASE)
	{
		FRightward = false;
	}
	if(parKey == GLFW_KEY_UP && parAction == GLFW_RELEASE)
	{
		FFoward = false;
	}
	if(parKey == GLFW_KEY_DOWN && parAction == GLFW_RELEASE)
	{
		FBackward = false;
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
	FWindow = glfwCreateWindow(1280, 720, "CS_RayTracer", NULL, NULL);
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
	CheckGLState("Vidage buffer");
	// Loading the scene file
    LoadScene("data/scenes/scene_test_quad.dat");
    
    // Octree
    octree = new Octree(FScene);
    
	InitShaders();
	//Creating the render to quad
	CreateRenderQuad();

	// Injecting the scene to the shader
	InjectScene();
    
	PRINT_GREEN("The renderer was created succesfully");
	//ShaderManager::Instance().BindTexture(FRenderTexture);
	FLastTime = glfwGetTime();

    glfwSetInputMode(FWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
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
	FPipelineShaderID = ShaderManager::Instance().CreateProgramVF();

	#ifndef SIMPLE
	//Création du shader de calcul
	FComputeShader = ShaderManager::Instance().CreateProgramC(2,FScene->m_triangles.size(),1,1,int(octree->m_nodes.size()),octree->m_nb_prim_max);
	//Création des texture
	FRenderTexture = ShaderManager::Instance().GenerateTexture(512,512);
	FTriangleTex = ShaderManager::Instance().CreateTexTriangle(FScene->m_triangles);
	FPrimitiveTex = ShaderManager::Instance().CreateTexPrimitive(FScene->m_primitives, FScene->m_materiaux.size());
	FMateriauTex = ShaderManager::Instance().CreateTexMat(FScene->m_materiaux);
	#endif

	//FNoeudTex = ShaderManager::Instance().CreateTexNoeud(octree->m_nodes, octree->m_nb_prim_max);

	//Mappage de la texturepour dessin
	ShaderManager::Instance().InjectTex(FPipelineShaderID,FRenderTexture,"bling",0);
	//ShaderManager::Instance().InjectTex(FPipelineShaderID,FEarModel->rugTex->id,"tex2",1);


	#ifndef SIMPLE
	//Mappage de la texture pour écriture
	ShaderManager::Instance().InjectTex(FComputeShader,FRenderTexture,"renderCanvas",0);
	ShaderManager::Instance().InjectTex(FComputeShader,FTriangleTex,"listTriangles",1);
	ShaderManager::Instance().InjectTex(FComputeShader,FPrimitiveTex,"listPrimitives",2);
	ShaderManager::Instance().InjectTex(FComputeShader,FMateriauTex,"listMateriaux",3);
	ShaderManager::Instance().InjectTex(FComputeShader,FEarModel->albTex->id,"listTex[0]",4);
	ShaderManager::Instance().InjectTex(FComputeShader,FEarModel->rugTex->id,"listTex[1]",5);
	//ShaderManager::Instance().InjectTex(FComputeShader,FEarModel->specTex->id,"listTex[2]",6);
	//ShaderManager::Instance().InjectTex(FComputeShader,FNoeudTex,"listNoeuds",4);
	#endif
}

void Renderer::RayTracing()
{
    #ifndef SIMPLE
	ShaderManager::Instance().BindProgram(FComputeShader);
	glDispatchCompute(512/16, 512/16, 1);
	ShaderManager::Instance().BindProgram(0);
	#endif
}

void Renderer::RenderResultToScreen()
{
	  ShaderManager::Instance().BindProgram(FPipelineShaderID);
	  glBindVertexArray (FVertexArrayID);
	  glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
	  glBindVertexArray (0);
	  ShaderManager::Instance().BindProgram(0);
}

void Renderer::UpdateDisplacement()
{
	if(FFoward)
	{
		FCamera.Translate(Vector3(0.0,0.0,-1.0));
	}
	if(FBackward)
	{
		FCamera.Translate(Vector3(0.0,0.0,1.0));
	}
	if(FLeftward)
	{
		FCamera.Translate(Vector3(1.0,0.0,0.0));
	}
	if(FRightward)
	{
		FCamera.Translate(Vector3(-1.0,0.0,0.0));
	}
	FCamera.UpdateValues(FComputeShader);		
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
	  UpdateDisplacement();
	  glfwPollEvents ();
	  glfwSwapBuffers (FWindow);
	  //END_COUNT_TIME(temps);
	  //PRINT_ORANGE("Temps pour la frame"<<temps);

	}
}


void Renderer::LoadScene(const std::string& parFilename)
{

    FScene = FParser.GetSceneFromFile(parFilename);
    if(FScene == NULL)
    {
        PRINT_RED("Fichier de scene " << parFilename << " non trouve.");
   }
   	
    FEarModel = ResourceManager::Instance().LoadModel("data/model/final/ear.obj", "data/model/final/diff.bmp","data/model/final/rugo.bmp", "data/model/final/spec.bmp");
   
    #ifndef SIMPLE
    FScene->AddMateriau(FEarModel->material);
    foreach(triangle, FEarModel->listTriangle)
    {
        //Ajoute un triangle ayant pour materiau le dernier materiau ajoute dans la scene
        FScene->AddTriangle(*triangle);
    }

    #endif
}

void Renderer::InjectScene()
{
	#ifndef SIMPLE
	int index = 0;
	index = 0;
    foreach(light, FScene->m_lights)
    {
        ShaderManager::Instance().InjectLight(FComputeShader, *light, index++);
    }
    #endif
}
