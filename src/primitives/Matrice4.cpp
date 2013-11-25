#include "Matrice4.h"
#include <string>
#include <assert.h>

using namespace Math3D;

/// Zero matrix
const CMatrice4 CMatrice4::ZERO = CMatrice4( 0, 0, 0, 0,
                                             0, 0, 0, 0,
                                             0, 0, 0, 0,
                                             0, 0, 0, 0 );

/// Identity matrix
const CMatrice4 CMatrice4::IDENTITE = CMatrice4( 1, 0, 0, 0,
                                                 0, 1, 0, 0,
                                                 0, 0, 1, 0,
                                                 0, 0, 0, 1 );

///////////////////////////////////////////////////////////////////////////////
///  public constant  Inverse \n
///  Description : Inverse une matrice
///
///  @return const Math3D::CMatrice4 Ma matrice inversée
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
const CMatrice4 CMatrice4::Inverse( void ) const
{
    REAL m00 = m[ 0 ][ 0 ], m01 = m[ 0 ][ 1 ], m02 = m[ 0 ][ 2 ], m03 = m[ 0 ][ 3 ];
    REAL m10 = m[ 1 ][ 0 ], m11 = m[ 1 ][ 1 ], m12 = m[ 1 ][ 2 ], m13 = m[ 1 ][ 3 ];
    REAL m20 = m[ 2 ][ 0 ], m21 = m[ 2 ][ 1 ], m22 = m[ 2 ][ 2 ], m23 = m[ 2 ][ 3 ];
    REAL m30 = m[ 3 ][ 0 ], m31 = m[ 3 ][ 1 ], m32 = m[ 3 ][ 2 ], m33 = m[ 3 ][ 3 ];

    REAL v0 = m20 * m31 - m21 * m30;
    REAL v1 = m20 * m32 - m22 * m30;
    REAL v2 = m20 * m33 - m23 * m30;
    REAL v3 = m21 * m32 - m22 * m31;
    REAL v4 = m21 * m33 - m23 * m31;
    REAL v5 = m22 * m33 - m23 * m32;

    REAL t00 =  ( v5 * m11 - v4 * m12 + v3 * m13 );
    REAL t10 = -( v5 * m10 - v2 * m12 + v1 * m13 );
    REAL t20 =  ( v4 * m10 - v2 * m11 + v0 * m13 );
    REAL t30 = -( v3 * m10 - v1 * m11 + v0 * m12 );

    REAL invDet = RENDRE_REEL( 1 ) / ( t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03 );

    REAL d00 = t00 * invDet;
    REAL d10 = t10 * invDet;
    REAL d20 = t20 * invDet;
    REAL d30 = t30 * invDet;

    REAL d01 = -( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
    REAL d11 =  ( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
    REAL d21 = -( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
    REAL d31 =  ( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

    v0 = m10 * m31 - m11 * m30;
    v1 = m10 * m32 - m12 * m30;
    v2 = m10 * m33 - m13 * m30;
    v3 = m11 * m32 - m12 * m31;
    v4 = m11 * m33 - m13 * m31;
    v5 = m12 * m33 - m13 * m32;

    REAL d02 =  ( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
    REAL d12 = -( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
    REAL d22 =  ( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
    REAL d32 = -( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

    v0 = m21 * m10 - m20 * m11;
    v1 = m22 * m10 - m20 * m12;
    v2 = m23 * m10 - m20 * m13;
    v3 = m22 * m11 - m21 * m12;
    v4 = m23 * m11 - m21 * m13;
    v5 = m23 * m12 - m22 * m13;

    REAL d03 = -( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
    REAL d13 =  ( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
    REAL d23 = -( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
    REAL d33 =  ( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

    return CMatrice4( d00, d01, d02, d03,
                      d10, d11, d12, d13,
                      d20, d21, d22, d23,
                      d30, d31, d32, d33 );
}

///////////////////////////////////////////////////////////////////////////////
///  public constant  Transpose \n
///  Description : Transpose une matrix
///
///  @return const Math3D::CMatrice4 Ma matrice transposée
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
const CMatrice4 CMatrice4::Transpose( void ) const
{
    return CMatrice4( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ],
                      m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ],
                      m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ],
                      m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ] );
}

