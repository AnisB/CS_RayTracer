#include "scene.h"

void Scene::AddLight(Light light)
{
    m_lights.push_back(light);
}

void Scene::AddQuadric(const Quadrique& quadric, const Materiau& materiau)
{
    m_quadrics.push_back(quadric);
    m_materiaux.push_back(materiau);
    Primitive primitive;
    primitive.type = PRIMITIVE_QUADRIQUE;
    primitive.materiau = m_materiaux.size() - 1;
    primitive.index = m_quadrics.size() - 1;
    m_primitives.push_back(primitive);

}


void Scene::AddPlane(const Plan& plane, const Materiau& materiau)
{
    m_planes.push_back(plane);
    m_materiaux.push_back(materiau);
    Primitive primitive;
    primitive.type = PRIMITIVE_PLAN;
    primitive.materiau = m_materiaux.size() - 1;
    primitive.index = m_planes.size() - 1;
    m_primitives.push_back(primitive);
}


void Scene::AddTriangle(const Triangle& triangle, const Materiau& materiau)
{
    m_triangles.push_back(triangle);
    m_materiaux.push_back(materiau);
    Primitive primitive;
    primitive.type = PRIMITIVE_TRIANGLE;
    primitive.materiau = m_materiaux.size() - 1;
    primitive.index = m_triangles.size() - 1;
    m_primitives.push_back(primitive);
    PRINT_RED(triangle.p0.x << " " << m_triangles[m_triangles.size() - 1].p0.x);
}
