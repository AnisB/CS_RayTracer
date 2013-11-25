#ifndef __PLANE_H__
#define __PLANE_H__

#include "surface.h"

///////////////////////////////////////////////////////////////////////////////
///  CPlan
///  Cette classe encaspsule un plan (ISurface)
///
///  Base class Scene::ISurface 
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
class CPlan : public ISurface
{
	private:
		/// normale au plan
		CVecteur3 m_Normale;
		/// Plan constant
		REAL      m_Cst;

	protected:
		/// Protected interface implementation
		virtual ostream& AfficherInfoDebug( ostream& Out ) const;

	public:
		/// Constructeurs
		CPlan( void );
		CPlan( const CPlan& Plan );
		/// Destructeur
		virtual ~CPlan( void );
		/// Opérateur copie
		CPlan& operator = ( const CPlan& Plan );

		/// Méthodes d'ajustement
		inline void AjusterNormale  ( const CVecteur3& Normal ) { m_Normale = Normal; }
		inline void AjusterConstante( const REAL Cst          ) { m_Cst = Cst;        }

		/// Méthodes d'obtention
		inline CVecteur3 ObtenirNormale  ( void ) const { return m_Normale; }
		inline REAL      ObtenirConstante( void ) const { return m_Cst;     }

		/// Public interface implementation
		virtual void          Pretraitement( void );
		virtual CIntersection Intersection ( const CRayon& Rayon );
		virtual CPlan*        Copier       ( void ) const;
};
#endif
