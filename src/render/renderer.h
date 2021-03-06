/*
 * Auteur : Anis Benyoub
 * Classe principale de l'application
 *
 */

#ifndef CSR_RENDERER
#define CSR_RENDERER

#include "io/parser.h"
#include "shadermanager.h"
#include "camera.h"
#include "defines.h"
#include "common/singleton.h"
#include "octree/Octree.h"
#include <render/resourcemanager.h>

class Renderer : public Singleton<Renderer>
{
	public:
		Renderer();
		~Renderer();

		bool Init(const char* scene, bool parOreille);
		void InitShaders();

		void Run();

		void RayTracing();
		void RenderResultToScreen();
        GLuint GetComputeProgID() {return FComputeShader;}

		void HandleKey(int parKey, int parAction);
		void HandleMouse(float parX, float parY);

		
	protected:
		void CreateRenderQuad();
        void LoadScene(const std::string& parFilename);
        void InjectScene();
        void UpdateDisplacement();
		
	protected:
		bool FIsRendering;
		GLFWwindow* FWindow;
		float FOldX;
		float FOldY;
		bool FInitDone;
		
		bool FOreille;
		
		double FLastTime;
		ShaderManager FManager;
		Camera FCamera;

        // Loading scene
        Parser FParser;
        Scene* FScene;
		
		// Octree;
		Octree* octree;
		ObjFile * FEarModel;
		
		// RenderToQuad
		GLuint FVertexArrayID;
		GLuint FVertexbuffer;
		GLuint FVertexCoord;
		GLuint FPipelineShaderID;

		GLuint FComputeShader;
		GLuint FRenderTexture;
		GLuint FTriangleTex;
		GLuint FQuadTex;
		GLuint FPrimitiveTex;
		GLuint FMateriauTex;
		
		GLuint FNoeudTex;
		
		bool FFoward;
		bool FBackward;
		bool FLeftward;
		bool FRightward;
						
};


#endif // CSR_RENDERER
