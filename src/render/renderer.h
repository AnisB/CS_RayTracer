#ifndef CSR_RENDERER
#define CSR_RENDERER


#include "shadermanager.h"
#include "camera.h"
#include "defines.h"
#include "common/singleton.h"

class Renderer : public Singleton<Renderer>
{
	public:
		Renderer();
		~Renderer();

		bool Init();
		void InitShaders();

		void Run();

		void RayTracing();
		void RenderResultToScreen();
		GLuint GetComputeProgID() {return FComputeShader;};

		void HandleKey(int parKey, int parAction);

		
	protected:
		void CreateRenderQuad();
		
	protected:
		bool FIsRendering;
		GLFWwindow* FWindow;

		ShaderManager FManager;
		Camera FCamera;
		
		// RenderToQuad
		GLuint FVertexArrayID;
		GLuint FVertexbuffer;
		GLuint FVertexCoord;
		GLuint FPipelineShaderID;

		GLuint FComputeShader;

};


#endif // CSR_RENDERER
