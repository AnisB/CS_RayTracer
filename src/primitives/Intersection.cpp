#include "Intersection.h"

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CIntersection \n
///  Description : Constructeur par défaut
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
///  Description : Constructeur par défaut
///
///  @param [in]       Intersection const Scene::CIntersection &    L'intersection à copier
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
    // On laisse le gestionnaire de scène s'occuper
    // des différentes instances de surfaces.
}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Opérateur de copie
///
///  @param [in]       Intersection const Scene::CIntersection &    L'Intersection à copier
///
///  @return Scene::CIntersection & L'intersection modifiée
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection& CIntersection::operator = ( const CIntersection& Intersection )
{
    // On ne supprime pas ici la surface précédemment assignée.
    // On laisse le gestionnaire de scène s'occuper des suppressions de surfaces.
    m_Surface  = Intersection.m_Surface;
    m_Distance = Intersection.m_Distance;
    m_Normale  = Intersection.m_Normale;
    return ( *this );
}
