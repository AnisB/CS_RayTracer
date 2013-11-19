#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
#include "defines.h"


class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();
		
		GLuint CreateProgramVF( const std::string& parVertex,const std::string& parFragment);
		GLuint CreateProgramCF( const std::string& parCompute,const std::string& parFragment);
		void BindProgram( GLuint parProgram);
};


#endif // SHADER_MANAGER
