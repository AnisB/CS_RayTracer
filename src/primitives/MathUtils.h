///////////////////////////////////////////////////////////////////////////////
///  @file MathUtils.h
///
///  @brief    Ce fichier contient plusieurs constantes et fonctions mathématiques utiles.
///
///  @author  Olivier Dionne 
///  @date    13/08/2008
///  @version 1.0.0
///
///////////////////////////////////////////////////////////////////////////////
#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

#include <math.h>
#include <iostream>
#include <iomanip>

namespace Math3D
{
    ///////////////////// TYPEDEFS ///////////////////////
    typedef double REAL;

    ///////////////////// DEFINES ////////////////////////
    #ifndef M_PI
        #define PI 3.14159265359
    #else
        #define PI M_PI
    #endif

    #define EPSILON RENDRE_REEL( 1.0e-6 )

    ///////////////////// MACROS /////////////////////////
    #define RENDRE_REEL( A ) static_cast<REAL>( A )

    ///////////////////// FONCTIONS ///////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Max \n
    ///  Description : Retourne la valeur maximale entre les deux paramètres fournis
    ///
    ///  @param [in]       A const T &
    ///  @param [in]       B const T &
    ///
    ///  @return const T La valeur maximale
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline const T Max( const T& A, const T& B )
    {
        return A > B ? A : B;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Min \n
    ///  Description : Retourne la valeur minimale entre les deux paramètres fournis
    ///
    ///  @param [in]       A const T &
    ///  @param [in]       B const T &
    ///
    ///  @return const T La valeur minimale
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline const T Min( const T& A, const T& B )
    {
        return A < B ? A : B;
    }


    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Abs \n
    ///  Description : Retourne la valeur absolue du paramètre fourni
    ///
    ///  @param [in]       A const T &
    ///
    ///  @return const T The absolute value
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline const T Abs( const T& A )
    {
        return A > 0 ? A : -A;
    }


    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Borner \n
    ///  Description : Borne la valeur du paramètre fourni entre deux valeurs frontières
    ///
    ///  @param [in]       Val const T &    La valeur à borner
    ///  @param [in]       Min const T &    La frontière min
    ///  @param [in]       Max const T &    La frontière max
    ///
    ///  @return const T La valeur bornée
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline const T Borner( const T& Val, const T& Min, const T& Max )
    {
        return ( Val < Min ? Min : ( Val > Max ? Max : Val ) );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Deg2Rad \n
    ///  Description : Convertit les degrés en radians
    ///
    ///  @param [in]       A const T &    Les degrés à convertir
    ///
    ///  @return const T La valeur en radians
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline const T Deg2Rad( const T& A )
    { 
        return ( A / T( 180.0 ) ) * T( PI ); 
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Rad2Deg \n
    ///  Description : Convertit les radians en degrés
    ///
    ///  @param [in]       A const T &    Les radians à convertir
    ///
    ///  @return const T La valeur en degrés
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline const T Rad2Deg( const T& A ) 
    { 
        return ( A / T( PI ) ) * T( 180.0 );
    }
}

#endif
