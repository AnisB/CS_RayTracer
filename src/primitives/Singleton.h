//////////////////////////////////////////////////////////////////////////////
/// @file Singleton.h
/// @author Martin Bisson
/// @date 2007-03-11
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __SINGLETON_H__
#define __SINGLETON_H__


///////////////////////////////////////////////////////////////////////////
/// @class Singleton
/// @brief Cette classe repr�sente une base g�n�rique pour la d�claration
///        de singleton.
///
///        Les singletons qui d�riveront de cette classe g�n�rique et qui
///        utiliseront les macros appropri�es auront d�j� les parties communes
///        � pratiquement tous les singletons, soit la gestion de l'instance
///        unique.
///
/// @author Martin Bisson
/// @date 2007-03-11
///////////////////////////////////////////////////////////////////////////
template <class T>
class Singleton
{
public:
   /// Obtient l'instance unique de la classe.
   static T* ObtenirInstance( void );
   /// Lib�re l'instance unique de la classe.
   static void LibererInstance( void );

protected:
   /// Constructeur vide d�clar� protected.
   Singleton() {}
   /// Destructeur vide d�clar� protected.
   ~Singleton() {}

private:
   /// Instance unique de la classe.
   static T* instance_;

   /// Constructeur par copie d�clar� mais non d�fini.
   Singleton(const Singleton &);
   /// Op�rateur d'assignation d�clar� mais non d�fini.
   Singleton& operator=(const Singleton&);

};

template <typename T> T * Singleton< T >::instance_ = 0;

/// Cette macro doit �tre incluse dans les classes d�riv�es de Singleton.  Elle
/// d�clare les constructeurs et destructeurs priv�s.
#define SINGLETON_DECLARATION_CLASSE(Classe) \
private:                                     \
   Classe () {}                              \
   ~ Classe () {}                            \
   Classe ( const Classe & );                \
   Classe & operator = ( const Classe & );   \
   friend class Singleton< Classe >;         \

/// Cette macro doit �tre incluse dans les classes d�riv�es de Singleton.  Elle
/// d�clare le constructeur copie et l'op�rateur d'assignation priv�, en
/// laissant � la classe d�riv�e le soin de d�finir le constructeur par d�faut
/// et le destructeur afin de faire le traitement souhait�e
#define SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(Classe) \
private:                                                       \
   Classe ( const Classe & );                                  \
   Classe & operator = ( const Classe & );                     \
   friend class Singleton< Classe >;                           \

////////////////////////////////////////////////////////////////////////
///
/// @fn inline T* Singleton<T>::obtenirInstance()
///
/// Cette fonction retourne l'instance unique de la classe. Si l'instance
/// n'existe pas, elle est cr��e. Ainsi, une seule instance sera cr��e.
/// Cette fonction n'est pas "thread-safe".
///
/// @return L'instance unique de la classe.
///
////////////////////////////////////////////////////////////////////////
template <class T>
inline T* Singleton<T>::ObtenirInstance( void )
{
   if( instance_ == 0 )
      instance_ = new T();

   return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Singleton<T>::libererInstance()
///
/// D�truit l'instance unique de la classe.  Cette fonction n'est pas
/// "thread-safe".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
template <class T>
inline void Singleton<T>::LibererInstance( void )
{
   delete instance_;
   instance_ = 0;
}


#endif // __SINGLETON_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
