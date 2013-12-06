
/* 
 * Auteur Pierre Froumenty
 * Classe qui permet gérer les noeuds de l'octree (C++)
 */
 
#ifndef NODE_IO
#define NODE_IO
#include <string>
#include <vector>


struct Node {
	int	child[8]; // enfants
	float	coords[6]; // xmin,ymin,zmin,xmax,ymax,zmax
	std::vector<int> objects_id; // id des objets a afficher
};

#endif //NODE_IO
