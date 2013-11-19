#include "helper.h"

#include <common/defines.h>
#include <render/defines.h>

void CheckGLState(const std::string& desc) 
{
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		PRINT_RED<<"OpenGL error in: "<<desc.c_str()<<" "<<gluErrorString(e)<<" "<<e<<END_PRINT_COLOR;
	}
	else
	{
		PRINT_ORANGE<<"No OpenGL errors."<<END_PRINT_COLOR;
	}
}