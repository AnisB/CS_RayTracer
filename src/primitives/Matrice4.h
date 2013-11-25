#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <string.h>

#include "MathUtils.h"
#include "Vecteur3.h"

using namespace std;

namespace Math3D
{
    ///////////////////////////////////////////////////////////////////////////////
    ///  CMatrice4
    ///  Encapsule une simple matrice rangée 4X4
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008 
    ///
    ///////////////////////////////////////////////////////////////////////////////
    class CMatrice4
    {
        public:
            
            /// L'Ordre de la transformation
            enum OrdreTransformation { PRE, POST };

            /// La matrice nulle
            static const CMatrice4 ZERO;
            /// La matrice identité
            static const CMatrice4 IDENTITE;

            /// Les éléments de la matrice
            REAL m[ 4 ][ 4 ];

            /// Les constructeurs
            inline CMatrice4( void );
            inline CMatrice4( REAL m00, REAL m01, REAL m02, REAL m03,
                              REAL m10, REAL m11, REAL m12, REAL m13,
                              REAL m20, REAL m21, REAL m22, REAL m23,
                              REAL m30, REAL m31, REAL m32, REAL m33 );
            inline CMatrice4( const CMatrice4& Mat );

            /// Les opérateurs unitaires
            inline const REAL*     operator [] ( const int Row );
            inline CMatrice4&      operator =  ( const CMatrice4& Mat );
            
            inline const CMatrice4 operator -  ( void ) const;
            
            inline CMatrice4&      operator += ( const CMatrice4& Mat );
            inline CMatrice4&      operator -= ( const CMatrice4& Mat );
            inline CMatrice4&      operator *= ( const CMatrice4& Mat );

            /// Opérateurs binaires
            inline friend const CMatrice4 operator*  ( const CMatrice4& Mat1, const CMatrice4& Mat2 );
            inline friend const CVecteur3 operator*  ( const CVecteur3& Vecteur, const CMatrice4& Mat );
            inline friend ostream&        operator<< ( ostream& Out, const CMatrice4& Mat );

            /// Ajuster la matrice courante à une matrice fournie
            inline void Ajuster( const CMatrice4& Mat );
            /// Effectuer la rotation autour de l'axe des x
            inline void RotationAutourDesX( const REAL Rad, const OrdreTransformation Ordre = POST );
            /// Effectuer la rotation autour de l'axe des y
            inline void RotationAutourDesY( const REAL Rad, const OrdreTransformation Ordre = POST );
            /// Effectuer la rotation autour de l'axe des z
            inline void RotationAutourDesZ( const REAL Rad, const OrdreTransformation Ordre = POST );
            /// effectuer la translation
            inline void Translation( const REAL x, const REAL y, const REAL z, const OrdreTransformation Ordre = POST );
            /// Effectuer la mise à l'échelle
            inline void MiseAEchelle( const REAL x, const REAL y, const REAL z, const OrdreTransformation Ordre = POST );
            
            /// Inverser une matrice
            const CMatrice4 Inverse( void ) const;
            /// Transposer une matrice
            const CMatrice4 Transpose( void ) const;

            /// Concatener deux matrices
            inline const CMatrice4 Concatene( const CMatrice4& Mat ) const;
    };

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CMatrice4 \n
    ///  Description : Constructeur par défaut
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4::CMatrice4( void )
    {
        memset( ( void* )m, 0, 16 * sizeof( REAL ) );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CMatrice4 \n
    ///  Description : Constructeur par défaut
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    Matrice à copier
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4::CMatrice4( const CMatrice4& Mat )
    {
        memcpy( ( void* )m, ( void* )Mat.m, 16 * sizeof( REAL ) );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CMatrice4 \n
    ///  Description : 
    ///
    ///  @param [in]       m00 Math3D::REAL    Élément matriciel [ 0 ][ 0 ]
    ///  @param [in]       m01 Math3D::REAL    Élément matriciel [ 0 ][ 1 ]
    ///  @param [in]       m02 Math3D::REAL    Élément matriciel [ 0 ][ 2 ]
    ///  @param [in]       m03 Math3D::REAL    Élément matriciel [ 0 ][ 3 ]
    ///  @param [in]       m10 Math3D::REAL    Élément matriciel [ 1 ][ 0 ]
    ///  @param [in]       m11 Math3D::REAL    Élément matriciel [ 1 ][ 1 ]
    ///  @param [in]       m12 Math3D::REAL    Élément matriciel [ 1 ][ 2 ]
    ///  @param [in]       m13 Math3D::REAL    Élément matriciel [ 1 ][ 3 ]
    ///  @param [in]       m20 Math3D::REAL    Élément matriciel [ 2 ][ 0 ]
    ///  @param [in]       m21 Math3D::REAL    Élément matriciel [ 2 ][ 1 ]
    ///  @param [in]       m22 Math3D::REAL    Élément matriciel [ 2 ][ 2 ]
    ///  @param [in]       m23 Math3D::REAL    Élément matriciel [ 2 ][ 3 ]
    ///  @param [in]       m30 Math3D::REAL    Élément matriciel [ 3 ][ 0 ]
    ///  @param [in]       m31 Math3D::REAL    Élément matriciel [ 3 ][ 1 ]
    ///  @param [in]       m32 Math3D::REAL    Élément matriciel [ 3 ][ 2 ]
    ///  @param [in]       m33 Math3D::REAL    Élément matriciel [ 3 ][ 3 ]
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4::CMatrice4( REAL m00, REAL m01, REAL m02, REAL m03,
                                 REAL m10, REAL m11, REAL m12, REAL m13,
                                 REAL m20, REAL m21, REAL m22, REAL m23,
                                 REAL m30, REAL m31, REAL m32, REAL m33 )
    {
        m[ 0 ][ 0 ] = m00; m[ 0 ][ 1 ] = m01; m[ 0 ][ 2 ] = m02; m[ 0 ][ 3 ] = m03;
        m[ 1 ][ 0 ] = m10; m[ 1 ][ 1 ] = m11; m[ 1 ][ 2 ] = m12; m[ 1 ][ 3 ] = m13;
        m[ 2 ][ 0 ] = m20; m[ 2 ][ 1 ] = m21; m[ 2 ][ 2 ] = m22; m[ 2 ][ 3 ] = m23; 
        m[ 3 ][ 0 ] = m30; m[ 3 ][ 1 ] = m31; m[ 3 ][ 2 ] = m32; m[ 3 ][ 3 ] = m33;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator [] \n
    ///  Description : Opérateur d'indexation de la matrice
    ///
    ///  @param [in]       Rangee const int    L'index de la rangée
    ///
    ///  @return const Math3D::REAL * Returns the address of a row
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const REAL* CMatrice4::operator [] ( const int Rangee )
    {
        assert( Rangee > -1 && Rangee < 4 );
        return m[ Rangee ];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator = \n
    ///  Description : Opérateur de copie
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice à copier
    ///
    ///  @return Math3D::CMatrice4 & The current matrix
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4& CMatrice4::operator = ( const CMatrice4& Mat )
    {
        memcpy( ( void* ) m, ( void* ) Mat.m, 16 * sizeof( REAL ) );
	    return ( *this );
    }
            
    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public constant  operator - \n
    ///  Description : Opérateur de négation
    ///
    ///  @return const Math3D::CMatrice4 La matrice résultante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CMatrice4 CMatrice4::operator - ( void ) const
    {
        int i, j;
	    CMatrice4 Result;

	    for( i = 0; i < 4; i++ )
            for( j = 0; j < 4; j++ )
                Result.m[ i ][ j ] = -m[ i ][ j ];

        return Result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator -= \n
    ///  Description : Opérateur de soustraction
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice à soustraire
    ///
    ///  @return Math3D::CMatrice4 & La matrice résultante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4& CMatrice4::operator -= ( const CMatrice4& Mat )
    {
        int i, j;

	    for( i = 0; i < 4; i++ )
            for( j = 0; j < 4; j++ )
                m[ i ][ j ] -= Mat.m[ i ][ j ];

        return ( *this );
    }


    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator +=
    ///  Description : Opérateur d'addition
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice à ajouter
    ///
    ///  @return Math3D::CMatrice4 La matrice résultante
    ///
    ///  @author Olivier Dionne @date 11/08/2008
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4& CMatrice4::operator += ( const CMatrice4& Mat )
    {
        int i, j;

	    for( i = 0; i < 4; i++ )
            for( j = 0; j < 4; j++ )
                m[ i ][ j ] += Mat.m[ i ][ j ];

        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator *=
    ///  Description : Opérateur de multiplication
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice à multiplier
    ///
    ///  @return Math3D::CMatrice4 La matrice résultante
    ///
    ///  @author Olivier Dionne @date 11/08/2008
    ///////////////////////////////////////////////////////////////////////////////
    inline CMatrice4& CMatrice4::operator *= ( const CMatrice4& Mat )
    {
        ( *this ) = Concatene( Mat );
        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded  operator *
    ///  Description : Opérateur de multiplication (2 matrices)
    ///
    ///  @param [in]       Mat1 const Math3D::CMatrice4 &    Mat1
    ///  @param [in]       Mat2 const Math3D::CMatrice4 &    Mat2
    ///
    ///  @return Math3D::CMatrice4 La matrice résultante
    ///
    ///  @author Olivier Dionne @date 11/08/2008
    ///////////////////////////////////////////////////////////////////////////////
    inline const CMatrice4 operator* ( const CMatrice4& Mat1, const CMatrice4& Mat2 )
    {
        return Mat1.Concatene( Mat2 );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded  operator * \n
    ///  Description : Multiplication (vecteurs rangée) suppose que la matrice est toujours affine
    ///
    ///  @param [in]       Vecteur const Math3D::CVecteur3 &    le vecteur rangée
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice
    ///
    ///  @return const Math3D::CVecteur3 Le vecteur résultant
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CVecteur3 operator* ( const CVecteur3& Vecteur, const CMatrice4& Mat )
    {
        CVecteur3 Result;

        Result.x = ( Mat.m[ 0 ][ 0 ] * Vecteur.x + Mat.m[ 1 ][ 0 ] * Vecteur.y + Mat.m[ 2 ][ 0 ] * Vecteur.z + Mat.m[ 3 ][ 0 ] );
        Result.y = ( Mat.m[ 0 ][ 1 ] * Vecteur.x + Mat.m[ 1 ][ 1 ] * Vecteur.y + Mat.m[ 2 ][ 1 ] * Vecteur.z + Mat.m[ 3 ][ 1 ] );
        Result.z = ( Mat.m[ 0 ][ 2 ] * Vecteur.x + Mat.m[ 1 ][ 2 ] * Vecteur.y + Mat.m[ 2 ][ 2 ] * Vecteur.z + Mat.m[ 3 ][ 2 ] );

        return Result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator << \n
    ///  Description : opérateur de flux de sortie
    ///
    ///  @param [in, out]  Out std::ostream &    Le flux de sortie
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice à afficher
    ///
    ///  @return std::ostream & Le flux modifié
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline ostream& operator<< ( ostream& Out, const CMatrice4& Mat )
    {
	    Out << setprecision(3) << setw(3)
            << "| " << Mat.m[ 0 ][ 0 ] << ", " << Mat.m[ 0 ][ 1 ] << ", " << Mat.m[ 0 ][ 2 ] << ", " << Mat.m[ 0 ][ 3 ] << " |" << std::endl
            << "| " << Mat.m[ 1 ][ 0 ] << ", " << Mat.m[ 1 ][ 1 ] << ", " << Mat.m[ 1 ][ 2 ] << ", " << Mat.m[ 1 ][ 3 ] << " |" << std::endl
            << "| " << Mat.m[ 2 ][ 0 ] << ", " << Mat.m[ 2 ][ 1 ] << ", " << Mat.m[ 2 ][ 2 ] << ", " << Mat.m[ 2 ][ 3 ] << " |" << std::endl
            << "| " << Mat.m[ 3 ][ 0 ] << ", " << Mat.m[ 3 ][ 1 ] << ", " << Mat.m[ 3 ][ 2 ] << ", " << Mat.m[ 3 ][ 3 ] << " |";

	    return Out;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Set \n
    ///  Description : Fixe la matrice courante à la matrice spécifiée
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    La matrice à copier
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CMatrice4::Ajuster( const CMatrice4& Mat )
    {
        memcpy( ( void* ) m, ( void* ) Mat.m, 16 * sizeof( REAL ) );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  RotationAutourDesX \n
    ///  Description : Effectue une rotation autour de l'axe des X
    ///
    ///  @param [in]       Rad const Math3D::REAL    Radian
    ///  @param [in]       Ordre const Math3D::CMatrice4::OrdreTransformation [=POST]    Ordre de transfo
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CMatrice4::RotationAutourDesX( const REAL Rad, const OrdreTransformation Ordre )
    {
        CMatrice4 Rotation( IDENTITE );

        Rotation.m[ 1 ][ 1 ] =  cos( Rad );
        Rotation.m[ 1 ][ 2 ] =  sin( Rad );
        Rotation.m[ 2 ][ 2 ] =  Rotation.m[ 1 ][ 1 ];
	    Rotation.m[ 2 ][ 1 ] = -Rotation.m[ 1 ][ 2 ];
        
        ( *this ) = ( Ordre == PRE ) ? Rotation.Concatene( *this ) : Concatene( Rotation );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  RotationAutourDesY \n
    ///  Description : Effectue une rotation autour de l'axe des Y
    ///
    ///  @param [in]       Rad const Math3D::REAL    Radians
    ///  @param [in]       Ordre const Math3D::CMatrice4::OrdreTransformation [=POST]    Ordre de transfo
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CMatrice4::RotationAutourDesY( const REAL Rad, const OrdreTransformation Ordre )
    {
        CMatrice4 Rotation( IDENTITE );

        Rotation.m[ 0 ][ 0 ] =  cos( Rad );
        Rotation.m[ 0 ][ 2 ] = -sin( Rad );
        Rotation.m[ 2 ][ 2 ] =  Rotation.m[ 0 ][ 0 ];
        Rotation.m[ 2 ][ 0 ] = -Rotation.m[ 0 ][ 2 ];

        ( *this ) = ( Ordre == PRE ) ? Rotation.Concatene( *this ) : Concatene( Rotation );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  RotationAutourDesZ \n
    ///  Description : Effectue une rotation autour de l'axe des Z axis
    ///
    ///  @param [in]       Rad const Math3D::REAL    Radians
    ///  @param [in]       Ordre const Math3D::CMatrice4::OrdreTransformation [=POST]    Ordre de transfo
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CMatrice4::RotationAutourDesZ( const REAL Rad, const OrdreTransformation Ordre )
    {
        CMatrice4 Rotation( IDENTITE );

        Rotation.m[ 0 ][ 0 ] =  cos( Rad );
        Rotation.m[ 0 ][ 1 ] =  sin( Rad );
        Rotation.m[ 1 ][ 1 ] =  Rotation.m[ 0 ][ 0 ];   
	    Rotation.m[ 1 ][ 0 ] = -Rotation.m[ 0 ][ 1 ];

        ( *this ) = ( Ordre == PRE ) ? Rotation.Concatene( *this ) : Concatene( Rotation );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Translation \n
    ///  Description : effectue une translation
    ///
    ///  @param [in]       x const Math3D::REAL    Translation X
    ///  @param [in]       y const Math3D::REAL    Translation Y
    ///  @param [in]       z const Math3D::REAL    Translation Z
    ///  @param [in]       Ordre const Math3D::CMatrice4::OrdreTransformation [=POST]    Ordre de transfo
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CMatrice4::Translation( const REAL x, const REAL y, const REAL z, const OrdreTransformation Ordre )
    {
        CMatrice4 Translation( IDENTITE );

        Translation.m[ 3 ][ 0 ] = x;
        Translation.m[ 3 ][ 1 ] = y;
        Translation.m[ 3 ][ 2 ] = z;

        ( *this ) = ( Ordre == PRE ) ? Translation.Concatene( *this ) : Concatene( Translation );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  MiseAEchelle \n
    ///  Description : Effectue une mise à l'échelle
    ///
    ///  @param [in]       x const Math3D::REAL    MiseAEchelle X
    ///  @param [in]       y const Math3D::REAL    MiseAEchelle Y
    ///  @param [in]       z const Math3D::REAL    MiseAEchelle Z
    ///  @param [in]       Ordre const Math3D::CMatrice4::OrdreTransformation [=POST]    Ordre de transfo
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CMatrice4::MiseAEchelle( const REAL x, const REAL y, const REAL z, const OrdreTransformation Ordre )
    {
        CMatrice4 Echelle( IDENTITE );

        Echelle.m[ 0 ][ 0 ] = x;
        Echelle.m[ 1 ][ 1 ] = y;
        Echelle.m[ 2 ][ 2 ] = z;

        ( *this ) = ( Ordre == PRE ) ? Echelle.Concatene( *this ) : Concatene( Echelle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public constant  Concatene \n
    ///  Description : Concatene deux matrices
    ///
    ///  @param [in]       Mat const Math3D::CMatrice4 &    Matrice à concaténer à la matrice courante
    ///
    ///  @return const Math3D::CMatrice4 Résultat de la concaténation
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CMatrice4 CMatrice4::Concatene( const CMatrice4& Mat ) const
    {
        CMatrice4 Result;

        Result.m[ 0 ][ 0 ] = m[ 0 ][ 0 ] * Mat.m[ 0 ][ 0 ] + m[ 0 ][ 1 ] * Mat.m[ 1 ][ 0 ] + m[ 0 ][ 2 ] * Mat.m[ 2 ][ 0 ] + m[ 0 ][ 3 ] * Mat.m[ 3 ][ 0 ];
        Result.m[ 0 ][ 1 ] = m[ 0 ][ 0 ] * Mat.m[ 0 ][ 1 ] + m[ 0 ][ 1 ] * Mat.m[ 1 ][ 1 ] + m[ 0 ][ 2 ] * Mat.m[ 2 ][ 1 ] + m[ 0 ][ 3 ] * Mat.m[ 3 ][ 1 ];
        Result.m[ 0 ][ 2 ] = m[ 0 ][ 0 ] * Mat.m[ 0 ][ 2 ] + m[ 0 ][ 1 ] * Mat.m[ 1 ][ 2 ] + m[ 0 ][ 2 ] * Mat.m[ 2 ][ 2 ] + m[ 0 ][ 3 ] * Mat.m[ 3 ][ 2 ];
        Result.m[ 0 ][ 3 ] = m[ 0 ][ 0 ] * Mat.m[ 0 ][ 3 ] + m[ 0 ][ 1 ] * Mat.m[ 1 ][ 3 ] + m[ 0 ][ 2 ] * Mat.m[ 2 ][ 3 ] + m[ 0 ][ 3 ] * Mat.m[ 3 ][ 3 ];

        Result.m[ 1 ][ 0 ] = m[ 1 ][ 0 ] * Mat.m[ 0 ][ 0 ] + m[ 1 ][ 1 ] * Mat.m[ 1 ][ 0 ] + m[ 1 ][ 2 ] * Mat.m[ 2 ][ 0 ] + m[ 1 ][ 3 ] * Mat.m[ 3 ][ 0 ];
        Result.m[ 1 ][ 1 ] = m[ 1 ][ 0 ] * Mat.m[ 0 ][ 1 ] + m[ 1 ][ 1 ] * Mat.m[ 1 ][ 1 ] + m[ 1 ][ 2 ] * Mat.m[ 2 ][ 1 ] + m[ 1 ][ 3 ] * Mat.m[ 3 ][ 1 ];
        Result.m[ 1 ][ 2 ] = m[ 1 ][ 0 ] * Mat.m[ 0 ][ 2 ] + m[ 1 ][ 1 ] * Mat.m[ 1 ][ 2 ] + m[ 1 ][ 2 ] * Mat.m[ 2 ][ 2 ] + m[ 1 ][ 3 ] * Mat.m[ 3 ][ 2 ];
        Result.m[ 1 ][ 3 ] = m[ 1 ][ 0 ] * Mat.m[ 0 ][ 3 ] + m[ 1 ][ 1 ] * Mat.m[ 1 ][ 3 ] + m[ 1 ][ 2 ] * Mat.m[ 2 ][ 3 ] + m[ 1 ][ 3 ] * Mat.m[ 3 ][ 3 ];

        Result.m[ 2 ][ 0 ] = m[ 2 ][ 0 ] * Mat.m[ 0 ][ 0 ] + m[ 2 ][ 1 ] * Mat.m[ 1 ][ 0 ] + m[ 2 ][ 2 ] * Mat.m[ 2 ][ 0 ] + m[ 2 ][ 3 ] * Mat.m[ 3 ][ 0 ];
        Result.m[ 2 ][ 1 ] = m[ 2 ][ 0 ] * Mat.m[ 0 ][ 1 ] + m[ 2 ][ 1 ] * Mat.m[ 1 ][ 1 ] + m[ 2 ][ 2 ] * Mat.m[ 2 ][ 1 ] + m[ 2 ][ 3 ] * Mat.m[ 3 ][ 1 ];
        Result.m[ 2 ][ 2 ] = m[ 2 ][ 0 ] * Mat.m[ 0 ][ 2 ] + m[ 2 ][ 1 ] * Mat.m[ 1 ][ 2 ] + m[ 2 ][ 2 ] * Mat.m[ 2 ][ 2 ] + m[ 2 ][ 3 ] * Mat.m[ 3 ][ 2 ];
        Result.m[ 2 ][ 3 ] = m[ 2 ][ 0 ] * Mat.m[ 0 ][ 3 ] + m[ 2 ][ 1 ] * Mat.m[ 1 ][ 3 ] + m[ 2 ][ 2 ] * Mat.m[ 2 ][ 3 ] + m[ 2 ][ 3 ] * Mat.m[ 3 ][ 3 ];

        Result.m[ 3 ][ 0 ] = m[ 3 ][ 0 ] * Mat.m[ 0 ][ 0 ] + m[ 3 ][ 1 ] * Mat.m[ 1 ][ 0 ] + m[ 3 ][ 2 ] * Mat.m[ 2 ][ 0 ] + m[ 3 ][ 3 ] * Mat.m[ 3 ][ 0 ];
        Result.m[ 3 ][ 1 ] = m[ 3 ][ 0 ] * Mat.m[ 0 ][ 1 ] + m[ 3 ][ 1 ] * Mat.m[ 1 ][ 1 ] + m[ 3 ][ 2 ] * Mat.m[ 2 ][ 1 ] + m[ 3 ][ 3 ] * Mat.m[ 3 ][ 1 ];
        Result.m[ 3 ][ 2 ] = m[ 3 ][ 0 ] * Mat.m[ 0 ][ 2 ] + m[ 3 ][ 1 ] * Mat.m[ 1 ][ 2 ] + m[ 3 ][ 2 ] * Mat.m[ 2 ][ 2 ] + m[ 3 ][ 3 ] * Mat.m[ 3 ][ 2 ];
        Result.m[ 3 ][ 3 ] = m[ 3 ][ 0 ] * Mat.m[ 0 ][ 3 ] + m[ 3 ][ 1 ] * Mat.m[ 1 ][ 3 ] + m[ 3 ][ 2 ] * Mat.m[ 2 ][ 3 ] + m[ 3 ][ 3 ] * Mat.m[ 3 ][ 3 ];

        return Result;
    }  
}
#endif
