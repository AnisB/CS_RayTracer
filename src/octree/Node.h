
/* 
 * Auteur Pierre Froumenty
 * Classe qui permet gérer les noeuds de l'octree
 */
 
#ifndef NODE_IO
#define NODE_IO
#include <string>
#include <vector>



struct Node {
	//int		id;
	//bool	is_terminal;
	//	int[3]	object_id; // objets a afficher
	int	child[8]; // enfants
	float	coords[6]; // xmin,ymin,zmin,xmax,ymax,zmax
	std::vector<int> objects_id; // objets a afficher 10?
	//int objects_id[10]; // objets a afficher 10?

	//int[10] objects_id; // objets a afficher
};

/*
struct Octree_struct {
	//int		id;
	//bool	is_terminal;
	//	int[3]	object_id; // objets a afficher
	int[8]	child; // enfants
	//std::vector<int> objects_id; // objets a afficher
	int[10] objects_id; // objets a afficher
};
*/
#endif //NODE_IO
