#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <assert.h>
#include "MathUtils.h"

using namespace std;

namespace Math3D
{
	///////////////////////////////////////////////////////////////////////////////
	///  CVecteur3
	///  Encapsule un simple vecteur 3D [ x, y, z ]
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008 
	///
	///////////////////////////////////////////////////////////////////////////////
	class CVecteur3
	{
	public:
		/// vecteur nul 
		static const CVecteur3 ZERO;
		/// Vecteur unitaire X
		static const CVecteur3 UNIT_X;
		/// Vecteur unitaire Y
		static const CVecteur3 UNIT_Y;
		/// Vecteur unitaire Z
		static const CVecteur3 UNIT_Z;

		/// Compostantes du vecteur
		REAL x, y, z;

		/// Les constructeurs
		inline CVecteur3( void );
		inline CVecteur3( const REAL X, const REAL Y, const REAL Z );
		inline explicit CVecteur3( const REAL* const Coordonnees );
		inline explicit CVecteur3( const REAL Scalaire );
		inline CVecteur3( const CVecteur3& Vecteur );

		/// Op�rateurs unitaires
		inline REAL&          operator [] ( const int i );
		inline CVecteur3&     operator =  ( const CVecteur3& Vecteur );     

		inline bool           operator == ( const CVecteur3& Vecteur ) const;
		inline bool           operator != ( const CVecteur3& Vecteur ) const;

		inline CVecteur3&     operator += ( const CVecteur3& Vecteur );
		inline CVecteur3&     operator -= ( const CVecteur3& Vecteur );
		inline CVecteur3&     operator *= ( const REAL Scalaire );
		inline CVecteur3&     operator /= ( const REAL Scalaire );

		inline const CVecteur3 operator -  ( void ) const;
		inline const CVecteur3 operator /  ( const REAL Scalaire ) const;

		/// Op�rateurs binaires
		inline friend const CVecteur3 operator + ( const CVecteur3& V1, const CVecteur3& V2 );
		inline friend const CVecteur3 operator - ( const CVecteur3& V1, const CVecteur3& V2 );
		inline friend const CVecteur3 operator * ( const REAL Scalaire, const CVecteur3& Vecteur );
		inline friend const CVecteur3 operator * ( const CVecteur3& Vecteur, const REAL Scalaire );

		inline friend ostream& operator << ( ostream& Out, const CVecteur3& Vecteur );

		/// M�thodes statiques
		inline static const REAL      ProdScal  ( const CVecteur3& V1, const CVecteur3& V2 ); 
		inline static const CVecteur3 ProdVect  ( const CVecteur3& V1, const CVecteur3& V2 );
		inline static const REAL      Norme     ( const CVecteur3& Vecteur );
		inline static const REAL      Distance  ( const CVecteur3& V1, const CVecteur3& V2 );
		inline static const CVecteur3 Normaliser( const CVecteur3& Vecteur );
		inline static const CVecteur3 Reflect   ( const CVecteur3& Vecteur, const CVecteur3& Normal );
		inline static const CVecteur3 Refract   ( const CVecteur3& Vecteur, const CVecteur3& Normal, const REAL IndiceRefractionRatio );
	};

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded constructor  CVecteur3 \n
	///  Description : Constructeur par d�faut
	///
	///  @return None
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3::CVecteur3( void )
		: x( 0 )
		, y( 0 )
		, z( 0 )
	{}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded constructor  CVecteur3 \n
	///  Description : Constructeur de surcharge
	///
	///  @param [in]       X const Math3D::REAL    Vecteur element x
	///  @param [in]       Y const Math3D::REAL    Vecteur element y
	///  @param [in]       Z const Math3D::REAL    Vecteur element z
	///
	///  @return None
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3::CVecteur3( const REAL X, const REAL Y, const REAL Z )
		: x( X )
		, y( Y )
		, z( Z )
	{}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded constructor  CVecteur3 \n
	///  Description : Constructeur de surcharge
	///
	///  @param [in]       Coordonnees const Math3D::REAL *const    pointeur sur tableau
	///
	///  @return None
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3::CVecteur3( const REAL* const Coordonnees )
		: x( Coordonnees[ 0 ] )
		, y( Coordonnees[ 1 ] )
		, z( Coordonnees[ 2 ] )
	{}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded constructor  CVecteur3 \n
	///  Description : Constructeur de surcharge
	///
	///  @param [in]       Scalaire const Math3D::REAL    �l�ments vecteurs comme �tatn des scalaires
	///
	///  @return Aucune
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////        
	inline CVecteur3::CVecteur3( const REAL Scalaire )
		: x( Scalaire )
		, y( Scalaire )
		, z( Scalaire )
	{}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded constructor  CVecteur3 \n
	///  Description : Constructeur par d�faut
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Vecteur � copier
	///
	///  @return None
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3::CVecteur3( const CVecteur3& Vecteur )
		: x( Vecteur.x )
		, y( Vecteur.y )
		, z( Vecteur.z )
	{}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator [] \n
	///  Description : Op�rateur d'indexation du vecteur (lecteur/�criture)
	///
	///  @param [in]       i const int    L'index
	///
	///  @return Math3D::REAL & R�f�rence � la valeur de l'�l�ment
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline REAL& CVecteur3::operator []( const int i )
	{
		assert( i > -1 && i < 3 );
		return *( &x + i );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator = \n
	///  Description : Op�rateur de copie
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Vecteur � copier
	///
	///  @return Math3D::CVecteur3 & Le vecteur courant
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3& CVecteur3::operator =( const CVecteur3& Vecteur )
	{
		x = Vecteur.x;
		y = Vecteur.y;
		z = Vecteur.z;
		return ( *this );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public constant  operator == \n
	///  Description : Op�rateur d'�galit�
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Le vecteur � tester
	///
	///  @return bool Retourne vrai si les vecteurs contiennent les m�mes valeurs, sinon retourn faux
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline bool CVecteur3::operator ==( const CVecteur3& Vecteur ) const
	{
		REAL dx = Abs<REAL>( x - Vecteur.x );
		REAL dy = Abs<REAL>( y - Vecteur.y );
		REAL dz = Abs<REAL>( z - Vecteur.z );

		return ( dx < EPSILON && dy < EPSILON && dz < EPSILON );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public constant  operator != \n
	///  Description : op�rateur de diff�rence
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Le vecteur � tester
	///
	///  @return bool Retourne faux si les vecteurs ont les m�mes valeurs, sinon vrai
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline bool CVecteur3::operator !=( const CVecteur3& Vecteur ) const
	{
		return !( *this == Vecteur );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator +=
	///  Description : op�rateur d'addition
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Le vecteur � ajouter
	///
	///  @return Math3D::CVecteur3 Le vecteur r�sultant
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3& CVecteur3::operator +=( const CVecteur3& Vecteur )
	{
		x += Vecteur.x;
		y += Vecteur.y;
		z += Vecteur.z;
		return ( *this );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator -=
	///  Description : op�rateur de soustraction
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Le vecteur � soustraire
	///
	///  @return Math3D::CVecteur3 Le vecteur r�sultant
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3& CVecteur3::operator -=( const CVecteur3& Vecteur )
	{
		x -= Vecteur.x;
		y -= Vecteur.y;
		z -= Vecteur.z;
		return ( *this );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator *=
	///  Description : op�rateur de multiplication scalaire
	///
	///  @param [in]       Scalaire const Math3D::REAL    Le scalaire � multiplier
	///
	///  @return Math3D::CVecteur3 Le vecteur r�sultant
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3& CVecteur3::operator *=( const REAL Scalaire )
	{
		x *= Scalaire;
		y *= Scalaire;
		z *= Scalaire;
		return ( *this );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator /=
	///  Description : op�rateur de division
	///
	///  @param [in]       Scalaire const Math3D::REAL    Le scalaire � diviser
	///
	///  @return Math3D::CVecteur3 Le vecteur r�sultant
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline CVecteur3& CVecteur3::operator /=( const REAL Scalaire )
	{
		REAL invScalaire = 0;
		assert( Abs( Scalaire ) > EPSILON );
		invScalaire = RENDRE_REEL( 1 ) / Scalaire;
		return ( ( *this ) *= invScalaire );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public constant  operator - \n
	///  Description : op�rateur de n�gation
	///
	///  @return const Math3D::CVecteur3 Le vecteur r�sultant
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 CVecteur3::operator -( ) const
	{
		return CVecteur3( -x, -y, -z );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator /
	///  Description : op�rateur de division scalaire
	///
	///  @param [in]       Scalaire const Math3D::REAL    Le scalaire � diviser
	///
	///  @return Math3D::CVecteur3 Le vecteur r�sultant
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 CVecteur3::operator /( const REAL Scalaire ) const
	{
		REAL invScalaire = 0;
		assert( Abs( Scalaire ) > EPSILON );
		invScalaire = RENDRE_REEL( 1.0 ) / Scalaire;

		return CVecteur3( x * invScalaire, y * invScalaire, z * invScalaire );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded  operator +
	///  Description : op�rateur d'addition vectorielle
	///
	///  @param [in]       V1 const Math3D::CVecteur3 &    V1
	///  @param [in]       V2 const Math3D::CVecteur3 &    V2
	///
	///  @return Math3D::CVecteur3   le r�sultat
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 operator +( const CVecteur3& V1, const CVecteur3& V2 )
	{
		return CVecteur3( V1.x + V2.x, V1.y + V2.y, V1.z + V2.z );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded  operator -
	///  Description : op�rateur de soustraction vectorielle
	///
	///  @param [in]       V1 const Math3D::CVecteur3 &    V1
	///  @param [in]       V2 const Math3D::CVecteur3 &    V2
	///
	///  @return Math3D::CVecteur3   le r�sultat
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 operator -( const CVecteur3& V1, const CVecteur3& V2 )
	{
		return CVecteur3( V1.x - V2.x, V1.y - V2.y, V1.z - V2.z );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded  operator *
	///  Description : op�rateur de multiplication scalaire/vecteur
	///
	///  @param [in]       Scalaire const Math3D::REAL          Scalaire
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Vecteur
	///
	///  @return Math3D::CVecteur3   le r�sultat
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 operator *( const REAL Scalaire, const CVecteur3& Vecteur )
	{
		return CVecteur3( Vecteur.x * Scalaire, Vecteur.y * Scalaire, Vecteur.z * Scalaire );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public overloaded  operator *
	///  Description : op�rateur de multiplication vecteur/scalaire
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Vecteur
	///  @param [in]       Scalaire const Math3D::REAL          Scalaire
	///
	///  @return Math3D::CVecteur3   Le r�sultat
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 operator *( const CVecteur3& Vecteur, const REAL Scalaire )
	{
		return CVecteur3( Vecteur.x * Scalaire, Vecteur.y * Scalaire, Vecteur.z * Scalaire );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public  operator << \n
	///  Description : op�rateur de flux de sortie
	///
	///  @param [in, out]  Out std::ostream &    Le flux de sortie
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Le vecteur � afficher
	///
	///  @return std::ostream & Le flux de sortie modifi�
	///
	///  @author Olivier Dionne 
	///  @date   13/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline ostream& operator <<( ostream& Out, const CVecteur3& Vecteur )
	{
		Out << setprecision( 3 ) << "[ "<< setw( 3 ) 
			<< Vecteur.x << ", " 
			<< Vecteur.y << ", " 
			<< Vecteur.z << " ]" 
			<< setw( 0 ); 
		return Out;
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public ProdScal \n
	///  Description : op�rateur de produit scalaire entre vecteurs
	///
	///  @param [in]       V1 const Math3D::CVecteur3 &    V1
	///  @param [in]       V2 const Math3D::CVecteur3 &    V2
	///
	///  @return Math3D::REAL  le r�sultat du produit scalaire
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const REAL CVecteur3::ProdScal( const CVecteur3& V1, const CVecteur3& V2 )
	{
		return ( V1.x * V2.x + V1.y * V2.y + V1.z * V2.z );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public ProdVect \n
	///  Description : op�rateur de produit vectoriel entre vecteurs
	///
	///  @param [in]       V1 const Math3D::CVecteur3 &    V1
	///  @param [in]       V2 const Math3D::CVecteur3 &    V2
	///
	///  @return Math3D::CVecteur3   le r�sultat du produit vectoriel
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 CVecteur3::ProdVect( const CVecteur3& V1, const CVecteur3& V2 )
	{
		return CVecteur3( V1.y * V2.z - V1.z * V2.y,
			V1.z * V2.x - V1.x * V2.z,
			V1.x * V2.y - V1.y * V2.x );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public Norme \n
	///  Description : retourne la norme d'un vecteur
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Vecteur
	///
	///  @return Math3D::REAL   La norme du vecteur
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const REAL CVecteur3::Norme( const CVecteur3& Vecteur )
	{
		return sqrt( Vecteur.x * Vecteur.x + Vecteur.y * Vecteur.y + Vecteur.z * Vecteur.z );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public Distance \n
	///  Description : retourne la distance entre deux vecteurs
	///
	///  @param [in]       V1 const Math3D::CVecteur3 &    V1
	///  @param [in]       V2 const Math3D::CVecteur3 &    V2
	///
	///  @return Math3D::REAL   la distance
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const REAL CVecteur3::Distance( const CVecteur3& V1, const CVecteur3& V2 )
	{
		return Norme( V1 - V2 );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public Normaliser \n
	///  Description : Normalise un vecteur
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &    Le vecteur � normaliser
	///
	///  @return Math3D::CVecteur3   Le vecteur normalis�
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 CVecteur3::Normaliser( const CVecteur3& Vecteur )
	{
		CVecteur3 Result;
		REAL VecLength = Norme( Vecteur );

		if( VecLength > EPSILON )
		{
			VecLength = RENDRE_REEL( 1.0 ) / VecLength;
			Result = Vecteur * VecLength;
		}

		return Result;
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public Reflect \n
	///  Description : Effectue la r�flexion d'un vecteur selon une normale sp�cifi�e
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &   Le vecteur � r�fl�chir
	///  @param [in]       Normal const Math3D::CVecteur3 &    La normale
	///
	///  @return Math3D::CVecteur3   Le vecteur r�fl�chi
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 CVecteur3::Reflect( const CVecteur3& Vecteur, const CVecteur3& Normal )
	{
		return ( Vecteur - ( RENDRE_REEL( 2.0 ) * ProdScal( Vecteur, Normal ) * Normal ) );
	}

	///////////////////////////////////////////////////////////////////////////////
	///  inline public Refract \n
	///  Description : Effectue la r�fraction d'un vecteur selon une normale sp�cifi�e et un indice de r�fraction
	///
	///  @param [in]       Vecteur const Math3D::CVecteur3 &   Le vecteur � r�fracter
	///  @param [in]       Normal const Math3D::CVecteur3 &    La normale
	///  @param [in]       IndiceRefractionRatio cosnt Math3D::REAL Le ratio des deux indices de r�fractions
	///
	///  @return Math3D::CVecteur3   Le vecteur r�fract�
	///
	///  @author Olivier Dionne @date 11/08/2008
	///
	///////////////////////////////////////////////////////////////////////////////
	inline const CVecteur3 CVecteur3::Refract( const CVecteur3& Vecteur, const CVecteur3& Normal, const REAL IndiceRefractionRatio )
	{
		CVecteur3 Result;
		CVecteur3 Z = IndiceRefractionRatio * (Vecteur - ProdScal(Vecteur,Normal)*Normal);
		REAL normeZ = Norme(Z); // Norme de Z
		REAL A = 1-normeZ*normeZ; // terme sous la racine dans la formule de T
		if ( A < EPSILON ) { // R�flexion totale
			Result = Reflect(Vecteur,Normal);
		}
		else { // R�fraction
			Result = Z - (sqrt(A))*Normal;
		}

		return Result;
	}
}

#endif
