#ifndef CSR_RENDERER
#define CSR_RENDERER

#include "io/parser.h"
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
        GLuint GetComputeProgID() {return FComputeShader;}

		void HandleKey(int parKey, int parAction);
		void HandleMouse(float parX, float parY);

		
	protected:
		void CreateRenderQuad();
        void LoadScene(const string & parFilename);
		
	protected:
		bool FIsRendering;
		GLFWwindow* FWindow;
		float FOldX;
		float FOldY;
		bool FInitDone;
		
		double FLastTime;
		ShaderManager FManager;
		Camera FCamera;

        // Loading scene
        Parser FParser;
        Scene* FScene;
		
		// RenderToQuad
		GLuint FVertexArrayID;
		GLuint FVertexbuffer;
		GLuint FVertexCoord;
		GLuint FPipelineShaderID;

		GLuint FComputeShader;

};


#endif // CSR_RENDERER
