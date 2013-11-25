#ifndef __CST_H__
#define __CST_H__

#include "singleton.h"

///////////////////////////////////////////////////////////////////////////////
///  CCst
///  Cette classe conserve toutes les constantes globales du programme
///
///  Base class Singleton
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
class CCst : public Singleton<CCst>
{
    SINGLETON_DECLARATION_CLASSE( CCst );

    public:

        /// La position en x de la fenêtre GLUT
        static const int g_FenetreX;
        /// La position en y de la fenêtre GLUT
        static const int g_FenetreY;
};

#endif
