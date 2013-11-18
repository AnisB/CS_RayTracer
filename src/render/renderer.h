#ifndef CSR_RENDERER
#define CSR_RENDERER


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
		
		// RenderToQuad
		GLuint FVertexArrayID;
		GLuint FVertexbuffer;
};


#endif // CSR_RENDERER
