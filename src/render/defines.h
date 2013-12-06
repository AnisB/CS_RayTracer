
/* 
 * Auteur Anis Benyoub
 * Fichier qui regrouppe les includes opengl
 */
#ifndef RENDER_DEFINES
#define RENDER_DEFINES

// Includes glew et glfw
#include <GL/glew.h>
#define GLFW_INCLUDE_GL3
#include <glfw3.h>

// Pour compiler quand meme le programme dans le cas ou gl_compute shader n'a pas été défini
#ifdef SIMPLE
	#ifndef GL_COMPUTE_SHADER
	#define GL_COMPUTE_SHADER 8
	#endif
#endif

// Quad
const GLfloat mainQuadArray[] = {
     -1.0f, -1.0f,0.0, 
     -1.0f,  1.0f,0.0,
      1.0f, -1.0f,0.0, 
     1.0f, 1.0f,0.0, 
     0.0, 0.0,
     0.0, 1.0,     
     1.0, 0.0,
     1.0, 1.0
};

#endif //RENDER_DEFINES
