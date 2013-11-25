#include "Plan.h"

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CPlan \n
///  Description : Constructeur par d�faut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CPlan::CPlan( void )
    : ISurface (                  )
    , m_Normale( CVecteur3::ZERO  )
    , m_Cst    ( RENDRE_REEL( 0 ) )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CPlan \n
///  Description : Constructeur par d�faut
///
///  @param [in]       Plan const Scene::CPlan &    Le plan � copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CPlan::CPlan( const CPlan& Plan )
    : ISurface ( Plan           )
    , m_Normale( Plan.m_Normale )
    , m_Cst    ( Plan.m_Cst     )
{}

///////////////////////////////////////////////////////////////////////////////
///  public virtual destructor  ~CPlan \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CPlan::~CPlan( void )
{}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Op�rateur de copie
///
///  @param [in]       Plan const Scene::CPlan &    Le plan � copier
///
///  @return Scene::CPlan & Le plan courant
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CPlan& CPlan::operator = ( const CPlan& Plan )
{
    ISurface::operator =( Plan );
    m_Normale = Plan.m_Normale;
    m_Cst     = Plan.m_Cst;
    return ( *this );
}

///////////////////////////////////////////////////////////////////////////////
///  protected virtual constant  AfficherInfoDebug \n
///  Description : Impl�mente la m�thode "debug" de la classe de base pour les sorties
///
///  @param [in, out]  Out std::ostream &    Le flux de sortie
///
///  @return std::ostream & Le flux de sortie modifi�
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ostream& CPlan::AfficherInfoDebug( ostream& Out ) const
{
    Out << "[DEBUG]: Plan.Normal            = " << m_Normale << endl;
    Out << "[DEBUG]: Plan.Cst               = " << m_Cst;
    return Out;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Pretraitement \n
///  Description : Pr�traitement des infos du plan ( appel� AVANT le lancer de rayons)
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
void CPlan::Pretraitement( void )
{
    m_Normale = CVecteur3::Normaliser( m_Normale * m_Transformation );

	CVecteur3 Pt;
	for( int i = 0; i < 3; i++ )
	{
		if( m_Normale[ i ] != 0 )
			Pt[ i ] = -( m_Cst / m_Normale[ i ] );
	}

	Pt    = Pt * m_Transformation;
    m_Cst = CVecteur3::ProdScal( -m_Normale, Pt );
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Intersection \n
///  Description : Effectue l'intersection rayon/plan et retourne le r�sultat
///
///  @param [in]       Rayon const CRayon &   Le rayon � tester 
///
///  @return Scene::CIntersection Le r�sultat de l'ntersection
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection CPlan::Intersection( const CRayon& Rayon )
{
    CIntersection Result;

    // From http://www.siggraph.org/education/materials/HyperGraph/raytrace/rayplane_intersection.htm

    REAL Vd = CVecteur3::ProdScal( m_Normale, Rayon.ObtenirDirection() );

    if( Abs<REAL>( Vd ) > EPSILON )
    {
        Result.AjusterSurface( this );
        Result.AjusterDistance( -( CVecteur3::ProdScal( m_Normale, Rayon.ObtenirOrigine() ) + m_Cst ) / Vd );
        Result.AjusterNormale( m_Normale );
    }
    
    return Result;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual constant  Copier \n
///  Description : Allocates a copy of the current plane
///
///  @return Scene::CPlan * copie du nouveau plan ( si utilis�, ne pas oublier de l'effacer)
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CPlan* CPlan::Copier( void ) const
{
    return new CPlan( *this );
}
