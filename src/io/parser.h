#ifndef PARSER_IO
#define PARSER_IO
#include <string>
#include <fstream>

#include "common/scene.h"
#include "stringutils.h"
#include "primitives/primitive.h"
#include "math/vector3.h"
#include "math/vector4.h"

#define STRING_CHECKFIND( Buffer, String ) ( Buffer.find( String ) != string::npos )

class Parser
{
 public:
    Parser();
    ~Parser();    
    Scene* GetSceneFromFile(std::string filename);
    enum EtatTraitementScene
    { 
        TRAITEMENT_SCENE,
        TRAITEMENT_LUMIERE,
        TRAITEMENT_TRIANGLE,
        TRAITEMENT_PLAN,
        TRAITEMENT_QUADRIQUE
    };

    const static int NB_MAX_CAR_PAR_LIGNE = 80;
};

#endif //PARSER_IO
