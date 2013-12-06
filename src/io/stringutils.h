/* 
 * Auteur Florian Korsa
 * Classe qui permet de traiter des string
 * Très inspirée du TP3
 */
#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>
#include <vector>

using namespace std;

class CStringUtils
{
public:
    /// Trim right.
    static string TrimRight( const string& Source, const string& T = " " );

    /// Trim left.
    static string TrimLeft( const string& Source, const string& T = " " );

    /// Trim left and right.
    static string Trim( const string& Source, const string& T = " " );

private:
    CStringUtils( void );
    ~CStringUtils( void );
};

#endif
