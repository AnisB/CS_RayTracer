#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "surface.h"
#include "Vecteur3.h"
///////////////////////////////////////////////////////////////////////////////
///  CTriangle
///  Cette classe implémente un triangle (ISurface)
///
///  Base class Scene::ISurface
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
class CTriangle : public ISurface
{
	private:
		/// Les points du triangle
		CVecteur3 m_Pts[ 3 ];
		/// La normale du triangle
		CVecteur3 m_Normale;

		/// Calculer la normale à partir des trois côtés
		void CalculerNormale( void );

	protected:
		/// Protected interface implementation
		virtual ostream& AfficherInfoDebug( ostream& Out ) const;

	public:
		/// Constructeurs
		CTriangle( void );
		CTriangle( const CTriangle& Triangle );
		/// Destructeur
		virtual ~CTriangle( void );
		/// Opérateur copie
		CTriangle& operator = ( const CTriangle& Triangle );

		/// Méthodes d'ajustement
		inline void AjusterPoints( const CVecteur3& Pt0, const CVecteur3& Pt1, const CVecteur3& Pt2 )
		{
			 m_Pts[ 0 ] = Pt0;
			 m_Pts[ 1 ] = Pt1;
			 m_Pts[ 2 ] = Pt2;
		}

		inline void AjusterPoint( const int PointIdx, const CVecteur3& Pt )
		{
			assert( PointIdx > -1 && PointIdx < 3 );
			m_Pts[ PointIdx ] = Pt;
		}

		/// Méthodes d'obtention
		inline CVecteur3 ObtenirPoint( const int PointIdx ) const
		{
			assert( PointIdx > -1 && PointIdx < 3 );
			return m_Pts[ PointIdx ];
		}

		/// Public interface implementation
		virtual void          Pretraitement( void );
		virtual CIntersection Intersection ( const CRayon& Rayon );
		virtual CTriangle*    Copier       ( void ) const;
};

#endif
