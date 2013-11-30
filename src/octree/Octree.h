#ifndef OCTREE_IO
#define OCTREE_IO
#include <string>
#include <vector>
#include <octree/Node.h>
#include <primitives/primitive.h>
#include <common/scene.h>


class Octree
{
 public:
    Octree(Scene* scene);
    ~Octree(); 
    void build(int node_id, float xmin,float ymin,float zmin,float xmax,float ymax,float zmax);
    bool isTriangleInNode(Triangle triangle,float xmin,float ymin,float zmin,float xmax,float ymax,float zmax);
 private :
 	Node*	m_root;
	float m_xmin;
	float m_xmax;
	float m_ymin;
	float m_ymax;
	float m_zmin;
	float m_zmax;
	float m_sizeX;
	float m_sizeY;
	float m_sizeZ;
	
	int 	m_objects_number;
	int 	m_objects_max;
	int m_level;
	int m_max_level;
	std::vector<Node> m_nodes;
	int	m_cur_node_id;
	Scene* m_scene;
};

#endif //OCTREE_IO
