#ifndef SCENE_COMMON
#define SCENE_COMMON
#include <vector>

#include "common/defines.h"
#include "../primitives/primitive.h"

class Scene
{
 public:
    Scene() {}
    ~Scene() {}
    void AddTriangle(Triangle triangle, Materiau materiau);
    void AddPlane(Plan plane, Materiau materiau);
    void AddQuadric(Quadrique quadric, Materiau materiau);
    void AddLight(Light light);
    std::vector<Plan> m_planes;
    std::vector<Triangle> m_triangles;
    std::vector<Quadrique> m_quadrics;
    std::vector<Materiau> m_materiaux;
    std::vector<Primitive> m_primitives;
    std::vector<Light> m_lights;
};

#endif //SCENE_COMMON
