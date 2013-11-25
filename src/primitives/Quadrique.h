#ifndef __QUADRIC_H__
#define __QUADRIC_H__

#include "surface.h"
#include "Vecteur3.h"

using namespace Math3D;

///////////////////////////////////////////////////////////////////////////////
///  CQuadrique
///  Cette classe implémente un Quadrique (ISurface)
///
///  Base class Scene::ISurface
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
class CQuadrique : public ISurface
{
	private:
		/// Termes quadratiques
		CVecteur3 m_Quadratique;
		/// Termes linéaires
		CVecteur3 m_Lineaire;
		/// Termes Linéaires
		CVecteur3 m_Mixte;
		/// Terme constant
		REAL      m_Cst;

	protected:
		/// Protected interface implementation
		virtual ostream& AfficherInfoDebug( ostream& Out ) const;

	public:
		/// Constructeurs
		CQuadrique( void );
		CQuadrique( const CQuadrique& Quadric );
		/// Destructeurs
		virtual ~CQuadrique( void );
		/// Opérateur copie
		CQuadrique& operator = ( const CQuadrique& Quadric );

		/// Méthodes d'ajustement
		inline void AjusterQuadratique( const CVecteur3& Quadratic ) { m_Quadratique = Quadratic; }
		inline void AjusterLineaire   ( const CVecteur3& Linear    ) { m_Lineaire = Linear;       }
		inline void AjusterMixte      ( const CVecteur3& Mixed     ) { m_Mixte = Mixed;           }
		inline void AjusterConstante  ( const REAL Cst             ) { m_Cst = Cst;               }

		/// Méthodes d'obtention
		inline CVecteur3 ObtenirQuadratique( void ) const { return m_Quadratique; }
		inline CVecteur3 ObtenirLineaire   ( void ) const { return m_Lineaire;    }
		inline CVecteur3 ObtenirMixte      ( void ) const { return m_Mixte;       }
		inline REAL      ObtenirConstante  ( void ) const { return m_Cst;         }

		/// Public interface implementation
		virtual void          Pretraitement( void );
		virtual CIntersection Intersection ( const CRayon& Rayon );
		virtual CQuadrique*   Copier       ( void ) const;
};

#endif
