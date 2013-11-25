#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "Vecteur3.h"
#include "Couleur.h"

using namespace Math3D;

/// déclaration "forward"
class ISurface;

///////////////////////////////////////////////////////////////////////////////
///  CIntersection
///  Cette classe conserve l'information importante requise pour analyser la couleur
///  la couleur à une intersection donnée lors du lancer de rayons
///
///  @author Olivier Dionne 
///  @date   13/08/2008 
///
///////////////////////////////////////////////////////////////////////////////
class CIntersection
{
	private:
		/// Pointeur vers une surface en intersection
		ISurface* m_Surface;
		/// La distance parcourue par le rayon avant l'intersection
		REAL      m_Distance;
		/// La normale de la surface en intersection
		CVecteur3 m_Normale;

	public:
		/// Constructeurs
		CIntersection( void );
		CIntersection( const CIntersection& Intersection );
		/// Destructeur
		~CIntersection( void );
		/// Opérateur copie
		CIntersection& operator = ( const CIntersection& Intersection );

		/// Méthodes d'ajustement 
		inline void AjusterSurface ( ISurface* Surface       ) { m_Surface  = Surface;  }
		inline void AjusterDistance( const REAL Distance     ) { m_Distance = Distance; }
		inline void AjusterNormale ( const CVecteur3& Normal ) { m_Normale   = Normal;  }

		/// Méthodes d'obtention
		inline ISurface* ObtenirSurface  ( void ) const { return m_Surface;  }
		inline REAL      ObtenirDistance ( void ) const { return m_Distance; }
		inline CVecteur3 ObtenirNormale  ( void ) const { return m_Normale;  }
};


#endif
