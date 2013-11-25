#include "Quadrique.h"

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CQuadrique \n
///  Description : Constructeur par défaut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::CQuadrique( void )
    : ISurface     (                  )
    , m_Quadratique( CVecteur3::ZERO  )
    , m_Lineaire   ( CVecteur3::ZERO  )
    , m_Mixte      ( CVecteur3::ZERO  )
    , m_Cst        ( RENDRE_REEL( 0 ) )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CQuadrique \n
///  Description : Constructeur par défaut
///
///  @param [in]       Quadric const Scene::CQuadrique &   la quadrique à copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::CQuadrique( const CQuadrique& Quadric )
    : ISurface     ( Quadric               )
    , m_Quadratique( Quadric.m_Quadratique )
    , m_Lineaire   ( Quadric.m_Lineaire    )
    , m_Mixte      ( Quadric.m_Mixte       )
    , m_Cst        ( Quadric.m_Cst         )
{}

///////////////////////////////////////////////////////////////////////////////
///  public virtual destructor  ~CQuadrique \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::~CQuadrique( void )
{
}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Opérateur de copie
///
///  @param [in]       Quadric const Scene::CQuadrique &    La quadrique à copier
///
///  @return Scene::CQuadrique & La quadrique modifiée
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique& CQuadrique::operator = ( const CQuadrique& Quadric )
{
    ISurface::operator =( Quadric );
    m_Quadratique = Quadric.m_Quadratique;
    m_Lineaire    = Quadric.m_Lineaire;
    m_Mixte       = Quadric.m_Mixte;
    m_Cst         = Quadric.m_Cst;
    return ( *this );
}

///////////////////////////////////////////////////////////////////////////////
///  protected virtual constant  AfficherInfoDebug \n
///  Description : Implémente le déboguage polymorphique par flux de sortie
///
///  @param [in, out]  Out std::ostream &    Le flux de sortie
///
///  @return std::ostream & Le flux de sortie modifié
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ostream& CQuadrique::AfficherInfoDebug( ostream& Out ) const
{
    Out << "[DEBUG]: Quadric.Quadratique       = " << m_Quadratique << endl;
    Out << "[DEBUG]: Quadric.Lineaire          = " << m_Lineaire    << endl;
    Out << "[DEBUG]: Quadric.Mixte             = " << m_Mixte       << endl;
    Out << "[DEBUG]: Quadric.Constante         = " << m_Cst;
    return Out;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Pretraitement \n
///  Description : Pretraitement des données de la quadrique( appelé AVANT le lancer)
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
void CQuadrique::Pretraitement( void )
{
   // Algorithme tiré de ... 
   // R. Goldman, "Two Approach to a Computer Model for Quadric Surfaces",
   // IEEE CG&A, Sept 1983, pp.21
   
    REAL A = m_Quadratique.x;
	REAL B = m_Quadratique.y;
    REAL C = m_Quadratique.z;
    REAL D = m_Mixte.z    * RENDRE_REEL( 0.5 );
	REAL E = m_Mixte.x    * RENDRE_REEL( 0.5 );
	REAL F = m_Mixte.y    * RENDRE_REEL( 0.5 );
	REAL G = m_Lineaire.x * RENDRE_REEL( 0.5 );
	REAL H = m_Lineaire.y * RENDRE_REEL( 0.5 );
	REAL J = m_Lineaire.z * RENDRE_REEL( 0.5 );
	REAL K = m_Cst;

	CMatrice4 Q( A, D, F, G,
			     D, B, E, H,
			     F, E, C, J,
			     G, H, J, K );

    CMatrice4 Inverse = m_Transformation.Inverse();

    Q = Inverse * Q * Inverse.Transpose();

    m_Quadratique.x = Q[ 0 ][ 0 ];
    m_Quadratique.y = Q[ 1 ][ 1 ];
	m_Quadratique.z = Q[ 2 ][ 2 ];
	m_Cst           = Q[ 3 ][ 3 ];
	m_Mixte.x       = Q[ 1 ][ 2 ] * RENDRE_REEL( 2.0 );
	m_Mixte.y       = Q[ 0 ][ 2 ] * RENDRE_REEL( 2.0 );
	m_Mixte.z       = Q[ 0 ][ 1 ] * RENDRE_REEL( 2.0 );
	m_Lineaire.x    = Q[ 0 ][ 3 ] * RENDRE_REEL( 2.0 );
	m_Lineaire.y    = Q[ 1 ][ 3 ] * RENDRE_REEL( 2.0 );
    m_Lineaire.z    = Q[ 2 ][ 3 ] * RENDRE_REEL( 2.0 );
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Intersection \n
///  Description : Effectue l'intersection Rayon/Quadrique
///
///  @param [in]       Rayon const CRayon &    Le rayon à tester
///
///  @return Scene::CIntersection Le résultat de l'ntersection
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection CQuadrique::Intersection( const CRayon& Rayon )
{
    CIntersection Result;

    // algorithme d'intersection tiré de ... 
    // Eric Haines, Paul Heckbert "An Introduction to Rayon Tracing",
    // Academic Press, Edited by Andrw S. Glassner, pp.68-73 & 288-293

    CVecteur3 RayonDirection = Rayon.ObtenirDirection();
    CVecteur3 RayonOrigin    = Rayon.ObtenirOrigine();

    const REAL ACoeff = RayonDirection.x * ( m_Quadratique.x * RayonDirection.x   +
                                             m_Mixte.z       * RayonDirection.y   +
                                             m_Mixte.y       * RayonDirection.z ) +
                        RayonDirection.y * ( m_Quadratique.y * RayonDirection.y   +
                                             m_Mixte.x       * RayonDirection.z ) +
                        RayonDirection.z * ( m_Quadratique.z * RayonDirection.z );

    const REAL BCoeff = RayonDirection.x * ( m_Quadratique.x * RayonOrigin.x + RENDRE_REEL( 0.5 )                     *
                                           ( m_Mixte.z * RayonOrigin.y + m_Mixte.y * RayonOrigin.z + m_Lineaire.x ) ) +
                        RayonDirection.y * ( m_Quadratique.y * RayonOrigin.y + RENDRE_REEL( 0.5 )                     * 
                                           ( m_Mixte.z * RayonOrigin.x + m_Mixte.x * RayonOrigin.z + m_Lineaire.y ) ) +
                        RayonDirection.z * ( m_Quadratique.z * RayonOrigin.z + RENDRE_REEL( 0.5 )                     * 
                                           ( m_Mixte.y * RayonOrigin.x + m_Mixte.x * RayonOrigin.y + m_Lineaire.z ) );

    const REAL CCoeff = RayonOrigin.x * ( m_Quadratique.x * RayonOrigin.x   +
                                          m_Mixte.z       * RayonOrigin.y   +
                                          m_Mixte.y       * RayonOrigin.z   +
                                          m_Lineaire.x                    ) +
                        RayonOrigin.y * ( m_Quadratique.y * RayonOrigin.y   +
                                          m_Mixte.x       * RayonOrigin.z   +
                                          m_Lineaire.y                    ) +
                        RayonOrigin.z * ( m_Quadratique.z * RayonOrigin.z   +
                                          m_Lineaire.z                    ) +
                        m_Cst;

    
    if( ACoeff != 0.0 )
    {
        REAL Ka    = -BCoeff / ACoeff;
        REAL Kb    =  CCoeff / ACoeff;
        REAL Delta = Ka * Ka - Kb;

        if( Delta > 0 )
        {
            Delta   = sqrt( Delta );
            REAL T0 = Ka - Delta;
            REAL T1 = Ka + Delta;

            REAL Distance = Min<REAL>( T0, T1 );
            if( Distance < EPSILON )
                Distance = Max<REAL>( T0, T1 );
            
            if( !( Distance < 0 ) )
            {
                Result.AjusterDistance( Distance );
                Result.AjusterSurface( this );

                // Calcule la normale de surface
                CVecteur3 HitPt = RayonOrigin + Distance * RayonDirection;
                
                CVecteur3 Normal;
                Normal.x = RENDRE_REEL( 2.0 ) * m_Quadratique.x * HitPt.x +
                           m_Mixte.y * HitPt.z                            +
                           m_Mixte.z * HitPt.y                            +
                           m_Lineaire.x;

                Normal.y = RENDRE_REEL( 2.0 ) * m_Quadratique.y * HitPt.y +
                           m_Mixte.x * HitPt.z                            +
                           m_Mixte.z * HitPt.x                            +
                           m_Lineaire.y;

                Normal.z = RENDRE_REEL( 2.0 ) * m_Quadratique.z * HitPt.z +
                           m_Mixte.x * HitPt.y                            +
                           m_Mixte.y * HitPt.x                            +
                           m_Lineaire.z;

                Result.AjusterNormale( CVecteur3::Normaliser( Normal ) );
            }
        }
    }
    else
    {
        Result.AjusterSurface ( this );
        Result.AjusterDistance( -RENDRE_REEL( 0.5 ) * ( CCoeff / BCoeff ) );
        Result.AjusterNormale ( CVecteur3::Normaliser( m_Lineaire ) );
    }

    return Result;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual constant  Copier \n
///  Description : Alloue une copie de la quadrique courante
///
///  @return Scene::CQuadrique *la copie de la quadrique
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique* CQuadrique::Copier( void ) const
{
    return new CQuadrique( *this );
}
