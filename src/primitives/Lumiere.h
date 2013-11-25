#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Couleur.h"
#include "Vecteur3.h"

using namespace Math3D;

namespace Scene
{
    ///////////////////////////////////////////////////////////////////////////////
    ///  CLumiere
    ///  Encapsule une lumière de scene
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    class CLumiere
    {
        private:
            /// Position de la lumière
            CVecteur3 m_Position;
            /// Couleur de la lumière
            CCouleur  m_Couleur;
            /// Intensité de la lumière
            REAL      m_Intensite;

        public:
            
            /// Constructeurs
            CLumiere( void );
            CLumiere( const CLumiere& Lumiere );
            /// Destructeur
            ~CLumiere( void );
            /// Opérateur copie
            CLumiere& operator = ( const CLumiere& Lumiere );

            /// Méthodes d'ajustement
            inline void SetPosition    ( const CVecteur3& Position ) { m_Position = Position;   }
            inline void AjusterCouleur ( const CCouleur& Color     ) { m_Couleur = Color;       }
            inline void SetIntensity   ( const REAL Intensity      ) { m_Intensite = Intensity; }

            /// Méthodes d'obtention
            inline CVecteur3 GetPosition   ( void ) const { return m_Position;  }
            inline CCouleur  ObtenirCouleur( void ) const { return m_Couleur;   }
            inline REAL      GetIntensity  ( void ) const { return m_Intensite; }
    };
}

#endif
