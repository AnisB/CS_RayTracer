/*
 * Auteur : Anis Benyoub
 * Classe qui permet de gérer les nuanceurs
 *
 */
 
#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
#include <vector>
#include "defines.h"
#include "common/singleton.h"
#include <primitives/primitive.h>
#include "math/vector3.h"
#include "octree/Node.h"


class ShaderManager : public Singleton<ShaderManager>
{
	public:
		// Constructeur
		ShaderManager();
		// Destructeur
		~ShaderManager();
		// Creation de la pipline de rendu principale
		GLuint CreateProgramVF();
		// Creation du compute shader avec les paramètres d'initialisation
		GLuint CreateProgramC(int parMaxRecur, int parNbTriangle, int parNbPlan, int parNbQuad, int parNbNoeud, int parNbPrimMax, int nbMat, bool oreille);
		// méthode pour binder un programe
		void BindProgram( GLuint parProgram);
	
		// Methode qui génère la texture de communication
		GLuint GenerateTexture(size_t parW, size_t parH);
		// méthode de génération des textures de description de scene
		GLuint CreateTexTriangle(const std::vector<Triangle>& parValue);
		GLuint CreateTexQuad(const std::vector<Quadrique>& parValue);
		GLuint CreateTexPrimitive(const std::vector<Primitive>& parValue, int parNbMat);
		GLuint CreateTexMat(const std::vector<Materiau>& parValue);
		//Méthode de création de la texture des noeud
		GLuint CreateTexNoeud(const std::vector<Node>& parValue, int nb_prim_max, int par_nb_prim);
		// Méthode d'injection d'une texture dans un shader
		void InjectTex(GLuint parShaderID, size_t parIndex, const std::string& parName, GLuint parOffset);
		// Méthode d'injection d'un double dans un shader
		void Injectd(GLuint parShaderID, double parValue, const std::string& parName);
		// Méthode d'injection d'un vec3 dan un shader
		void InjectVec3(GLuint parShaderID, const Vector3& parValue, const std::string& parName);

		// Injection des lumières
		void InjectLight(GLuint parShaderID, const Light& parLight, int parIndex);
		// Biding d'une texture
		void BindTexture(size_t parIndexTex);
		// unbiding d'une texture
		void UnbindTexture();
		
		
	protected:
		GLuint FTexture;
  

};


#endif // SHADER_MANAGER
