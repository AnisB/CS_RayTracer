#ifndef PARSER_IO
#define PARSER_IO
#include <string>
#include <fstream>

#include "common/scene.h"
#include "primitives/primitive.h"
#include "stringutils.h"
#include "primitives/light.h"
#include "primitives/surface.h"
#include "primitives/Triangle.h"
#include "primitives/Plan.h"
#include "primitives/Quadrique.h"
#include "primitives/Couleur.h"

#define STRING_CHECKFIND( Buffer, String ) ( Buffer.find( String ) != string::npos )

class Parser
{
 public:
    Parser();
    ~Parser();    
    Scene* GetSceneFromFile(std::string filename);
    void AddSurface( ISurface* const surface );
    void AddLight( CLumiere* const light );
    void AjusterCouleurArrierePlan( const CCouleur& Couleur );
    enum EtatTraitementScene
    { 
        TRAITEMENT_SCENE,
        TRAITEMENT_LUMIERE,
        TRAITEMENT_TRIANGLE,
        TRAITEMENT_PLAN,
        TRAITEMENT_QUADRIQUE
    };

    const static int NB_MAX_CAR_PAR_LIGNE = 80;
    std::vector<ISurface*> m_surfaces;
    std::vector<CLumiere*> m_lights;
    CCouleur        m_CouleurArrierePlan;
};

#endif //PARSER_IO
