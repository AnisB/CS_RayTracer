#include "surface.h"

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  ISurface \n
///  Description : Constructeur par défaut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ISurface::ISurface( void )
    : m_Couleur           ( CCouleur::NOIR      )
    , m_CoeffAmbient      ( RENDRE_REEL( 0.2 )  )
    , m_CoeffDiffus       ( RENDRE_REEL( 0.8 )  )
    , m_CoeffSpeculaire   ( RENDRE_REEL( 0.0 )  )
    , m_CoeffShininess    ( RENDRE_REEL( 0.0 )  )
    , m_CoeffReflexion    ( RENDRE_REEL( 0.0 )  )
    , m_CoeffRefraction   ( RENDRE_REEL( 0.0 )  )
    , m_IndiceDeRefraction( RENDRE_REEL( 0.0 )  )
    , m_Transformation    ( CMatrice4::IDENTITE ) 
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  ISurface \n
///  Description : Constructeur par défaut
///
///  @param [in]       Surface const Scene::ISurface &    La surface à copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ISurface::ISurface( const ISurface& Surface )
    : m_Couleur           ( Surface.m_Couleur            )
    , m_CoeffAmbient      ( Surface.m_CoeffAmbient       )
    , m_CoeffDiffus       ( Surface.m_CoeffDiffus        )
    , m_CoeffSpeculaire   ( Surface.m_CoeffSpeculaire    )
    , m_CoeffShininess    ( Surface.m_CoeffShininess     )
    , m_CoeffReflexion    ( Surface.m_CoeffReflexion     )
    , m_CoeffRefraction   ( Surface.m_CoeffRefraction    )
    , m_IndiceDeRefraction( Surface.m_IndiceDeRefraction )
    , m_Transformation    ( Surface.m_Transformation     ) 
{}

///////////////////////////////////////////////////////////////////////////////
///  public virtual destructor  ~ISurface \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ISurface::~ISurface( void )
{}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Opérateur de copie
///
///  @param [in]       Surface const Scene::ISurface &    La surface à copier
///
///  @return Scene::ISurface & The current surface
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ISurface& ISurface::operator =( const ISurface& Surface )
{
    m_Couleur            = Surface.m_Couleur;
    m_CoeffAmbient       = Surface.m_CoeffAmbient;
    m_CoeffDiffus        = Surface.m_CoeffDiffus;
    m_CoeffSpeculaire    = Surface.m_CoeffSpeculaire;
    m_CoeffShininess     = Surface.m_CoeffShininess;
    m_CoeffReflexion     = Surface.m_CoeffReflexion;
    m_CoeffRefraction    = Surface.m_CoeffRefraction;
    m_IndiceDeRefraction = Surface.m_IndiceDeRefraction;
    m_Transformation     = Surface.m_Transformation; 
    return ( *this );
}
