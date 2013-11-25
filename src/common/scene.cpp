#include "scene.h"

std::vector<Primitive*> Scene::getPrimitives()
{
    return m_primitives;
}

void Scene::AddPrimitive(Primitive *pr)
{
    m_primitives.push_back(pr);
}
