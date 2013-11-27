#ifndef RENDER_DEFINES
#define RENDER_DEFINES


#include <GL/glew.h>
#define GLFW_INCLUDE_GL3
#include <glfw3.h>

#ifdef SIMPLE
	#ifndef GL_COMPUTE_SHADER
	#define GL_COMPUTE_SHADER 8
	#endif
#endif


/*
const GLfloat mainQuadArray[] = {
     1.0f, -1.0f,0.0,
     1.0f, 1.0f,0.0,
     -1.0f, -1.0f,0.0,
     -1.0f,  1.0f,0.0,

};

const GLfloat mainQuadTex[] = {
    0.0,0.0,
    1.0,0.0,
    0.0,1.0,
    1.0,1.0,
};
*/

const GLfloat mainQuadArray[] = {
     1.0f, -1.0f,0.0, 
     1.0f, 1.0f,0.0, 
     -1.0f, -1.0f,0.0, 
     -1.0f,  1.0f,0.0,
     0.0, 0.0,
     1.0, 0.0,
     0.0, 1.0,
     1.0, 1.0,
};

#endif //RENDER_DEFINES
