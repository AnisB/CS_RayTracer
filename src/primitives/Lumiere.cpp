#include "Lumiere.h"

using namespace Scene;

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CLumiere \n
///  Description : Constructeur par d�faut
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
///  Description : Constructeur par d�faut
///
///  @param [in]       Lumiere const Scene::CLumiere &    Lumi�res � copier
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
///  Description : Op�rateur de copie
///
///  @param [in]       Lumiere const Scene::CLumiere & Lumi�res � copier
///
///  @return Scene::CLumiere & La lumi�res modifi�e
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
