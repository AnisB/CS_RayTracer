#ifndef CSR_RENDERER
#define CSR_RENDERER


#include "shadermanager.h"
#include "defines.h"

class Renderer
{
	public:
		Renderer();
		~Renderer();

		bool Init();
		void Run();
		
	protected:
		void CreateRenderQuad();
		
	protected:
		bool FIsRendering;
		GLFWwindow* FWindow;

		ShaderManager FManager;
		
		// RenderToQuad
		GLuint FVertexArrayID;
		GLuint FVertexbuffer;
		GLuint FShaderID;
};


#endif // CSR_RENDERER
