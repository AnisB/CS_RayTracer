#ifndef __ISURFACE_H__
#define __ISURFACE_H__

#include "Couleur.h"
#include "Intersection.h"
#include "Rayon.h"
#include "Matrice4.h"

using namespace Math3D;
///////////////////////////////////////////////////////////////////////////////
///  abstract ISurface
///  Définit une surface de base. TOUS les objets de la scène DOIVENT implémenter cette interface
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
class ISurface
{
        protected:
                /// Couleur de la surface
                CCouleur  m_Couleur;
                /// Coefficient ambiant de la surface
                REAL      m_CoeffAmbient;
                /// Coefficient diffus de la surface
                REAL     m_CoeffDiffus;
                /// Coefficient spéculaire de la surface
                REAL       m_CoeffSpeculaire;
                /// Coefficient de "brillance" de la surface
                REAL      m_CoeffShininess;
                /// Coefficient de réflexion de la surface
                REAL      m_CoeffReflexion;
                /// Coefficient de réfraction de la surface
                REAL      m_CoeffRefraction;
                /// Indice de réfraction de la surface
                REAL      m_IndiceDeRefraction;
                /// Matrice de transformation de la surface
                CMatrice4 m_Transformation;
                
                /// Patron Template Method pour un debug polymorphique 
                virtual ostream& AfficherInfoDebug( ostream& Out ) const = 0;

        public:

                /// Constructeurs
                ISurface( void );
                ISurface( const ISurface& Surface );
                /// Destructeur virtuel
                virtual ~ISurface( void );
                /// Opérateur copie
                ISurface& operator = ( const ISurface& Surface );

                /// Méthodes virtuelles pures à implémenter par les classes dérivées
                virtual void          Pretraitement( void )                = 0;
                virtual CIntersection Intersection ( const CRayon& Rayon ) = 0;
                virtual ISurface*     Copier       ( void )          const = 0;

                /// Méthodes d'ajustement
                inline void AjusterCouleur         ( const CCouleur& Color           ) { m_Couleur = Color;                       }
                inline void AjusterCoeffAmbiant    ( const REAL Ambient              ) { m_CoeffAmbient = Ambient;                }
                inline void AjusterCoeffDiffus     ( const REAL Diffuse              ) { m_CoeffDiffus = Diffuse;                 }
                inline void AjusterCoeffSpeculaire ( const REAL Specular             ) { m_CoeffSpeculaire = Specular;            }
                inline void AjusterCoeffBrillance  ( const REAL Shininess            ) { m_CoeffShininess = Shininess;            }
                inline void AjusterCoeffReflexion  ( const REAL Reflexion            ) { m_CoeffReflexion = Reflexion;            }
                inline void AjusterCoeffRefraction ( const REAL Refraction           ) { m_CoeffRefraction = Refraction;          }
                inline void AjusterIndiceRefraction( const REAL IndiceRefraction     ) { m_IndiceDeRefraction = IndiceRefraction; }
                inline void AjusterTransformation  ( const CMatrice4& Transformation ) { m_Transformation = Transformation;       }
           
                /// Méthodes d'obtention
                inline CCouleur  ObtenirCouleur         ( void ) const { return m_Couleur;            }
                inline REAL      ObtenirCoeffAmbiant    ( void ) const { return m_CoeffAmbient;       }
                inline REAL      ObtenirCoeffDiffus     ( void ) const { return m_CoeffDiffus;        }
                inline REAL      ObtenirCoeffSpeculaire ( void ) const { return m_CoeffSpeculaire;    }
                inline REAL      ObtenirCoeffBrillance  ( void ) const { return m_CoeffShininess;     }
                inline REAL      ObtenirCoeffReflexion  ( void ) const { return m_CoeffReflexion;     }
                inline REAL      ObtenirCoeffRefraction ( void ) const { return m_CoeffRefraction;    }
                inline REAL      ObtenirIndiceRefraction( void ) const { return m_IndiceDeRefraction; }
                inline CMatrice4 ObtenirTransformation  ( void ) const { return m_Transformation;     }

                /// Méthode de sortie de flux par défaut pour toutes les surfaces concrètes
                inline friend ostream& operator<< ( ostream& Out, const ISurface& Surface );
};



///////////////////////////////////////////////////////////////////////////////
///  inline public  operator << \n
///  Description : Afiche une surface vers un flux de sortie
///
///  @param [in, out]  Out std::ostream &    Un flux de sortie
///  @param [in]       Surface const Scene::ISurface &    La surface à afficher
///
///  @return std::ostream & Le flux de sortie modifié
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
inline ostream& operator<< ( ostream& Out, const ISurface& Surface )
{
        Surface.AfficherInfoDebug( Out );
        Out << endl;
        Out << "[DEBUG]: Surface.Couleur          = " << Surface.m_Couleur         << endl;
        Out << "[DEBUG]: Surface.Ambiant          = " << Surface.m_CoeffAmbient    << endl;
        Out << "[DEBUG]: Surface.Diffus           = " << Surface.m_CoeffDiffus     << endl;
        Out << "[DEBUG]: Surface.Speculaire       = " << Surface.m_CoeffSpeculaire << endl;
        Out << "[DEBUG]: Surface.Shininess        = " << Surface.m_CoeffShininess  << endl;
        Out << "[DEBUG]: Surface.Reflexion        = " << Surface.m_CoeffReflexion  << endl;
        Out << "[DEBUG]: Surface.Refraction       = " << Surface.m_CoeffRefraction << endl;
        Out << "[DEBUG]: Surface.IndiceRefraction = " << Surface.m_CoeffRefraction << endl;
        Out << "[DEBUG]: Surface.Transformation   = " << Surface.m_Transformation;
        return Out;
}

#endif