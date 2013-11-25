#include "Lumiere.h"

using namespace Scene;

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CLumiere \n
///  Description : Constructeur par défaut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CLumiere::CLumiere( void )
    : m_Position ( CVecteur3::ZERO  )
    , m_Couleur  ( CCouleur::BLANC  )
    , m_Intensite( RENDRE_REEL( 0 ) )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CLumiere \n
///  Description : Constructeur par défaut
///
///  @param [in]       Lumiere const Scene::CLumiere &    Lumières à copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CLumiere::CLumiere( const CLumiere& Lumiere )
    : m_Position ( Lumiere.m_Position  )
    , m_Couleur  ( Lumiere.m_Couleur   )
    , m_Intensite( Lumiere.m_Intensite )
{}

///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CLumiere \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CLumiere::~CLumiere( void )
{}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Opérateur de copie
///
///  @param [in]       Lumiere const Scene::CLumiere & Lumières à copier
///
///  @return Scene::CLumiere & La lumières modifiée
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CLumiere& CLumiere::operator = ( const CLumiere& Lumiere )
{
    m_Position  = Lumiere.m_Position;
    m_Couleur   = Lumiere.m_Couleur;
    m_Intensite = Lumiere.m_Intensite;
    return ( *this );
}
