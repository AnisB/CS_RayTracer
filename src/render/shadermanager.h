#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
#include "defines.h"


class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();
		
		GLuint CreateProgram( const std::string& parVertex,const std::string& parFragment);
};
#endif // SHADER_MANAGER
