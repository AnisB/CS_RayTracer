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
/// @brief Cette classe représente une base générique pour la déclaration
///        de singleton.
///
///        Les singletons qui dériveront de cette classe générique et qui
///        utiliseront les macros appropriées auront déjà les parties communes
///        à pratiquement tous les singletons, soit la gestion de l'instance
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
   /// Libère l'instance unique de la classe.
   static void LibererInstance( void );

protected:
   /// Constructeur vide déclaré protected.
   Singleton() {}
   /// Destructeur vide déclaré protected.
   ~Singleton() {}

private:
   /// Instance unique de la classe.
   static T* instance_;

   /// Constructeur par copie déclaré mais non défini.
   Singleton(const Singleton &);
   /// Opérateur d'assignation déclaré mais non défini.
   Singleton& operator=(const Singleton&);

};

template <typename T> T * Singleton< T >::instance_ = 0;

/// Cette macro doit être incluse dans les classes dérivées de Singleton.  Elle
/// déclare les constructeurs et destructeurs privés.
#define SINGLETON_DECLARATION_CLASSE(Classe) \
private:                                     \
   Classe () {}                              \
   ~ Classe () {}                            \
   Classe ( const Classe & );                \
   Classe & operator = ( const Classe & );   \
   friend class Singleton< Classe >;         \

/// Cette macro doit être incluse dans les classes dérivées de Singleton.  Elle
/// déclare le constructeur copie et l'opérateur d'assignation privé, en
/// laissant à la classe dérivée le soin de définir le constructeur par défaut
/// et le destructeur afin de faire le traitement souhaitée
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
/// n'existe pas, elle est créée. Ainsi, une seule instance sera créée.
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
/// Détruit l'instance unique de la classe.  Cette fonction n'est pas
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
