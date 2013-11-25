#ifndef __COLOR_H__
#define __COLOR_H__

#include <assert.h>
#include "MathUtils.h"

using namespace Math3D;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
///  CCouleur
///  Cette classe impl�mente une couleur RGB en float dont les valeurs varient
///  entre 0.0 et 1.0
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
class CCouleur
{
    private:
        /// Conversion de ubyte � float
        const static float UBYTE_2_FLOAT;

    public:

        /// Constante de couleur NOIRE
        const static CCouleur NOIR;
        /// Constante de couleur BLANCHE
        const static CCouleur BLANC;

        /// Composantes RGB de la couleur
        float r, g, b;

        /// Constructeurs
        inline CCouleur( void );
        inline CCouleur( const float R, const float G, const float B );
        inline CCouleur( const int R, const int G, const int B );
        inline explicit CCouleur( const float Val );
        inline CCouleur( const CCouleur& Color );

        /// Op�rateurs unitaires
        inline float&    operator [] ( const int i );
        inline CCouleur& operator =  ( const CCouleur& Color );

        inline bool operator ==  ( const CCouleur& Color ) const;
        inline bool operator !=  ( const CCouleur& Color ) const;

        inline CCouleur& operator += ( const CCouleur& Color );
        inline CCouleur& operator -= ( const CCouleur& Color );
        inline CCouleur& operator *= ( const CCouleur& Color );
        inline CCouleur& operator *= ( const REAL Val );

        /// Op�rateurs binaires
        inline friend const CCouleur operator + ( const CCouleur& C1, const CCouleur& C2 );
        inline friend const CCouleur operator - ( const CCouleur& C1, const CCouleur& C2 );
        inline friend const CCouleur operator * ( const CCouleur& C1, const CCouleur& C2 );
        inline friend const CCouleur operator * ( const CCouleur& Color, const REAL Val );
        inline friend const CCouleur operator * ( const REAL Val, const CCouleur& Color );
        
        inline friend ostream& operator << ( ostream& Out, const CCouleur& Color );

        /// D�finir la couleur courante
        inline void Ajuster( const float R, const float G, const float B );
};


    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CCouleur \n
    ///  Description : Constructeur par d�faut
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur::CCouleur()
        : r( 0.0f )
        , g( 0.0f )
        , b( 0.0f )
    {}

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CCouleur \n
    ///  Description : 
    ///
    ///  @param [in]       R const float    Rouge
    ///  @param [in]       G const float    Vert
    ///  @param [in]       B const float    Bleu
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur::CCouleur( const float R, const float G, const float B )
        : r( Borner<float>( R, 0.0f, 1.0f ) )
        , g( Borner<float>( G, 0.0f, 1.0f ) )
        , b( Borner<float>( B, 0.0f, 1.0f ) )
    {}

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CCouleur \n
    ///  Description : 
    ///
    ///  @param [in]       R const int    Rouge
    ///  @param [in]       G const int    Veret
    ///  @param [in]       B const int    Bleu
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur::CCouleur( const int R, const int G, const int B )
        : r( R * UBYTE_2_FLOAT )
        , g( G * UBYTE_2_FLOAT )
        , b( B * UBYTE_2_FLOAT )
    {}

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CCouleur \n
    ///  Description :
    ///
    ///  @param [in]       Val const float   Fixer les composantes aux valeurs fournies
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur::CCouleur( const float Val )
        : r( Borner<float>( Val, 0.0f, 1.0f ) )
        , g( Borner<float>( Val, 0.0f, 1.0f ) )
        , b( Borner<float>( Val, 0.0f, 1.0f ) )
    {}

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded constructor  CCouleur \n
    ///  Description : Constructeur copie
    ///
    ///  @param [in]       Color const CCouleur &    Couleur � copier
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur::CCouleur( const CCouleur& Color )
        : r( Color.r )
        , g( Color.g )
        , b( Color.b )
    {}

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator [] \n
    ///  Description : Op�rateur d'indexation de la couleur (lecteur/�criture)
    ///
    ///  @param [in]       i const int    Index
    ///
    ///  @return float & 
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline float& CCouleur::operator [] ( const int i )
    {
        assert( i > -1 && i < 3 );
        return *( &r + i ); 
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator = \n
    ///  Description : Op�rateur d'�galit�
    ///
    ///  @param [in]       Color const CCouleur &    La couleur � copier
    ///
    ///  @return CCouleur & La couleur courante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008 
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur& CCouleur::operator = ( const CCouleur& Color )
    {
        r = Color.r;
        g = Color.g;
        b = Color.b;

        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public constant  operator == \n
    ///  Description : Op�rateur d'�galit�
    ///
    ///  @param [in]       Color const CCouleur &    La couleur � tester
    ///
    ///  @return bool Vrai si les couleurs sont les m�mes
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline bool CCouleur::operator == ( const CCouleur& Color ) const
    {
        return ( r == Color.r && g == Color.g && b == Color.b );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public constant  operator != \n
    ///  Description : Op�rateur de diff�rence
    ///
    ///  @param [in]       Color const CCouleur &    Couleur � tester
    ///
    ///  @return bool Vrai si les couleurs sont diff�rentes
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline bool CCouleur::operator != ( const CCouleur& Color ) const
    {
        return !( *this == Color );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator += \n
    ///  Description : Op�rateur d'addition
    ///
    ///  @param [in]       Color const CCouleur &    Couleurs � ajouter
    ///
    ///  @return CCouleur & La couleur courante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur& CCouleur::operator += ( const CCouleur& Color )
    {
        r += Color.r;
        g += Color.g;
        b += Color.b;

        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  operator -= \n
    ///  Description : Op�rateur de soustraction
    ///
    ///  @param [in]       Color const CCouleur &    Couleur � soustraire
    ///
    ///  @return CCouleur & La couleur courante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur& CCouleur::operator -= ( const CCouleur& Color )
    {
        r -= Color.r;
        g -= Color.g;
        b -= Color.b;

        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded  operator *= \n
    ///  Description : Op�rateur de modulation de couleur (*)
    ///
    ///  @param [in]       Color const CCouleur &    Couleur � moduler
    ///
    ///  @return CCouleur & La couleur courante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur& CCouleur::operator *= ( const CCouleur& Color )
    {
        r *= Color.r;
        g *= Color.g;
        b *= Color.b;

        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public overloaded  operator *= \n
    ///  Description : Op�rateur de multiplication scalaire
    ///
    ///  @param [in]       Val const Math3D::REAL    Le scalaire par lequel multiplier
    ///
    ///  @return CCouleur & La couleur courante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline CCouleur& CCouleur::operator *= ( const REAL Val )
    {
        r *= static_cast<float>( Val );
        g *= static_cast<float>( Val );
        b *= static_cast<float>( Val );

        return ( *this );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  global inline public  operator + \n
    ///  Description : op�rateur d'addition de couleur
    ///
    ///  @param [in]       C1 const CCouleur &    Couleur 1
    ///  @param [in]       C2 const CCouleur &    Couleur 2
    ///
    ///  @return const CCouleur La couleur r�sultante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CCouleur operator + ( const CCouleur& C1, const CCouleur& C2 )
    {
        return CCouleur( C1.r + C2.r, C1.g + C2.g, C1.b + C2.b );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  global inline public  operator - \n
    ///  Description : Op�rateur de soustraction de 2 couleurs
    ///
    ///  @param [in]       C1 const CCouleur &    Couleur 1
    ///  @param [in]       C2 const CCouleur &    Couleur 2
    ///
    ///  @return const CCouleur La couleur r�sultante 
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CCouleur operator - ( const CCouleur& C1, const CCouleur& C2 )
    {
        return CCouleur( C1.r - C2.r, C1.g - C2.g, C1.b - C2.b );
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  global inline public overloaded  operator * \n
    ///  Description : Op�rateur de modulation de couleur
    ///
    ///  @param [in]       C1 const CCouleur &    Couleur 1
    ///  @param [in]       C2 const CCouleur &    Couleur 2
    ///
    ///  @return const CCouleur La couleur r�sultante de la modulation
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CCouleur operator * ( const CCouleur& C1, const CCouleur& C2 )
    {
        CCouleur Result;

        Result.r = C1.r * C2.r;
        Result.g = C1.g * C2.g;
        Result.b = C1.b * C2.b;

        return Result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  global inline public overloaded  operator * \n
    ///  Description : Op�rateur de multiplication scalaire d'une couleur
    ///
    ///  @param [in]       Color const CCouleur &    Couleur
    ///  @param [in]       Val const Math3D::REAL    Scalaire
    ///
    ///  @return const CCouleur La couleur r�sultante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CCouleur operator * ( const CCouleur& Color, const REAL Val )
    {
        CCouleur Result;

        Result.r = static_cast<float>( Color.r * Val );
        Result.g = static_cast<float>( Color.g * Val );
        Result.b = static_cast<float>( Color.b * Val );

        return Result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  global inline public overloaded  operator * \n
    ///  Description : Op�rateur de multiplication scalaire d'une couleur
    ///
    ///  @param [in]       Val const Math3D::REAL    Scalaire
    ///  @param [in]       Color const CCouleur &    Couleur
    ///
    ///  @return const CCouleur La couleur r�sultante
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline const CCouleur operator * ( const REAL Val, const CCouleur& Color )
    {
        return Color * Val;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  global inline public  operator << \n
    ///  Description : Op�rateur de sortie texte
    ///
    ///  @param [in, out]  Out std::ostream &    Flux de sortie
    ///  @param [in]       Color const CCouleur &    La couleur � afficher
    ///
    ///  @return std::ostream & Le flux de sortie modifi�
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline ostream& operator <<( ostream& Out, const CCouleur& Color )
    {
        Out << setprecision( 3 ) <<"[ " << setw( 3 ) << Color.r << ", " << Color.g << ", " << Color.b << " ]"; 
	    return Out;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///  inline public  Set \n
    ///  Description : Ajuste une couleur aux composantes RGB sp�cifi�es
    ///
    ///  @param [in]       R const float    Rouge
    ///  @param [in]       G const float    Vert
    ///  @param [in]       B const float    Bleu
    ///
    ///  @return None
    ///
    ///  @author Olivier Dionne 
    ///  @date   13/08/2008
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline void CCouleur::Ajuster( const float R, const float G, const float B )
    {
        r = Borner<float>( R, 0.0f, 1.0f );
        g = Borner<float>( G, 0.0f, 1.0f );
        b = Borner<float>( B, 0.0f, 1.0f );
    }

#endif