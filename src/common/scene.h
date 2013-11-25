#ifndef SCENE_COMMON
#define SCENE_COMMON
#include <vector>

#include "../primitives/primitive.h"

class Scene
{
 public:
    Scene();
    ~Scene(); 
    void AddPrimitive(Primitive *pr);
    std::vector<Primitive*> getPrimitives();
 private:
    std::vector<Primitive*> m_primitives;
};

#endif //SCENE_COMMON
