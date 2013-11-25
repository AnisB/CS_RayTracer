#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
#include "defines.h"
#include "common/singleton.h"
#include <primitives/primitive.h>
#include "math/vector3.h"


class ShaderManager : public Singleton<ShaderManager>
{
	public:
		ShaderManager();
		~ShaderManager();
		
		GLuint CreateProgramVF();
		GLuint CreateProgramC(int parNbTriangle, int parNbPlan, int parNbQuad, int parNbNoeud, int parNbPrimMax);
		void BindProgram( GLuint parProgram);


		GLuint GenerateTexture(size_t parW, size_t parH);
		void InjectTex(GLuint parShaderID, size_t parIndex, const std::string& parName);
		void Injectd(GLuint parShaderID, double parValue, const std::string& parName);
		void InjectVec3(GLuint parShaderID, const Vector3& parValue, const std::string& parName);

		// Injection de structures
		void InjectTriangle(GLuint parShaderID, const Triangle& parValue, int parIndex);
		void InjectPlan(GLuint parShaderID, const Plan& parValue, int parIndex);
		void InjectQuadrique(GLuint parShaderID, const Quadrique& parValue, int parIndex);
		void InjectMateriau(GLuint parShaderID, const Materiau& parValue, int parIndex);
		void InjectPrimitive(GLuint parShaderID, const Primitive& parValue, int parIndex);

		void BindTexture(size_t parIndexTex);
		void UnbindTexture();
  

};


#endif // SHADER_MANAGER
