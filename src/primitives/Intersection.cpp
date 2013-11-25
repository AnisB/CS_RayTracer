#include "Intersection.h"

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CIntersection \n
///  Description : Constructeur par d�faut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection::CIntersection( void )
    : m_Surface ( NULL              )
    , m_Distance( RENDRE_REEL( -1 ) )
    , m_Normale ( CVecteur3::ZERO   )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CIntersection \n
///  Description : Constructeur par d�faut
///
///  @param [in]       Intersection const Scene::CIntersection &    L'intersection � copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection::CIntersection( const CIntersection& Intersection )
    : m_Surface ( Intersection.m_Surface  )
    , m_Distance( Intersection.m_Distance )
    , m_Normale ( Intersection.m_Normale  )
{}

///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CIntersection \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection::~CIntersection( void )
{
    // On ne supprime pas le pointeur de surface,
    // On laisse le gestionnaire de sc�ne s'occuper
    // des diff�rentes instances de surfaces.
}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Op�rateur de copie
///
///  @param [in]       Intersection const Scene::CIntersection &    L'Intersection � copier
///
///  @return Scene::CIntersection & L'intersection modifi�e
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection& CIntersection::operator = ( const CIntersection& Intersection )
{
    // On ne supprime pas ici la surface pr�c�demment assign�e.
    // On laisse le gestionnaire de sc�ne s'occuper des suppressions de surfaces.
    m_Surface  = Intersection.m_Surface;
    m_Distance = Intersection.m_Distance;
    m_Normale  = Intersection.m_Normale;
    return ( *this );
}
