/**
 * Cette classe est tirée de ma base de code personnelle (Anis)
 * Vous pouvez le retrouver sur mon github https://github.com/AnisB
 **/
 
#ifndef SINGLETON
#define SINGLETON

#include <iostream>

template <typename T>
  class Singleton
  {
  protected:
    Singleton () { }
    ~Singleton () { }

  public:
  // Interface publique
    static T *Instance_Ptr ()
    {
      if (FInstance == NULL)
      {
        FInstance = new T;
      }

      return (static_cast<T*> (FInstance));
    }
    static T &Instance ()
    {
      if (NULL == FInstance)
      {
        FInstance = new T;
      }

      return *(static_cast<T*> (FInstance));
    }

    static void Destroy ()
    {
      if (NULL != FInstance)
      {
        delete FInstance;
        FInstance = NULL;
      }
    }

  private:
  // Unique instance
    static T *FInstance;
  };

template <typename T>
  T *Singleton<T>::FInstance = NULL;

#endif