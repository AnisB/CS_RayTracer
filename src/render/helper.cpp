/* 
 * Auteur Anis Benyoub
 * Petit fichier qui regroupe quelques fonctions d'aide au développment opengl
 *
 */
#include "helper.h"

#include <common/defines.h>
#include <sstream>
#include <string>
#include <render/defines.h>

using namespace std;
void CheckGLState(const std::string& desc) 
{
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		PRINT_RED("OpenGL error in: "<<desc.c_str()<<" "<<gluErrorString(e)<<" "<<e);
	}
	else
	{
		PRINT_ORANGE("No OpenGL errors@"<<desc);
	}
}

std::string convertToString(int parToConvert)
{
	stringstream ss;
	ss<<parToConvert;
	std::string result;
	ss>>result;
	return result;	
}
