#include <common/defines.h>
#include <io/parser.h>
#include <stdio.h>

int main()
{
    PRINT_GREEN("Loading scene...");
    Parser parser;
    Scene *scene = parser.GetSceneFromFile("data/scenes/scene_octree.dat");
    if(!scene)
    {
        PRINT_RED("Couldn't load scene file.");
        return 1;
    }
    PRINT_ORANGE("Nombre de plans charges : " << scene->m_planes.size());
    PRINT_ORANGE("Nombre de triangles charges : " << scene->m_triangles.size());
    PRINT_ORANGE("Nombre de primitives chargees : " << scene->m_primitives.size());
    PRINT_ORANGE("Nombre de quadriques chargees : " << scene->m_quadrics.size());
    return 0;
}
