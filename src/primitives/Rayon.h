#ifndef __RAY_H__
#define __RAY_H__

#include "Vecteur3.h"

using namespace Math3D;

///////////////////////////////////////////////////////////////////////////////
///  CRayon
///  Cette classe implémente un rayon
///
///  @author Olivier Dionne 
///  @date   13/08/2008 
///
///////////////////////////////////////////////////////////////////////////////
class CRayon
{
    private:
        /// Origine du rayon
        CVecteur3 m_Origine;
        /// Direction du rayon
        CVecteur3 m_Direction;
        /// Indice de réfraction du rayon
        REAL      m_IndiceDeRefraction;
        /// Énergie du rayon
        REAL      m_Energie;
        /// Nombre de rebonds du rayon
        int       m_NbRebonds;

    public:
        /// Constructeurs
        CRayon( void );
        CRayon( const CRayon& Rayon );
        /// Destructeurs
        ~CRayon( void );
        /// Opérateur copie
        CRayon& operator = ( const CRayon& Rayon );

        /// Méthodes d'ajustement
        inline void AjusterOrigine         ( const CVecteur3& Origine      ) { m_Origine = Origine;                       }
        inline void AjusterDirection       ( const CVecteur3& Direction    ) { m_Direction = Direction;                   }
        inline void AjusterIndiceRefraction( const REAL IndiceDeRefraction ) { m_IndiceDeRefraction = IndiceDeRefraction; }
        inline void AjusterEnergie         ( const REAL Energie            ) { m_Energie = Energie;                       }
        inline void AjusterNbRebonds       ( const int NbRebonds           ) { m_NbRebonds = NbRebonds;                   }

        /// Méthodes d'obtention
        inline CVecteur3 ObtenirOrigine         ( void ) const { return m_Origine;            }
        inline CVecteur3 ObtenirDirection       ( void ) const { return m_Direction;          }
        inline REAL      ObtenirIndiceRefraction( void ) const { return m_IndiceDeRefraction; }
        inline REAL      ObtenirEnergie         ( void ) const { return m_Energie;            }
        inline int       ObtenirNbRebonds       ( void ) const { return m_NbRebonds;          }
};

#endif