#include "stringutils.h"

string CStringUtils::TrimRight( const string& Source, const string& T )
{
  string Str = Source;
  return Str.erase( Str.find_last_not_of ( T ) + 1 ) ;
}

string CStringUtils::TrimLeft( const string& Source, const string& T )
{
  string Str = Source;
  return Str.erase( 0 , Source.find_first_not_of ( T ) ) ;
}

string CStringUtils::Trim( const string& Source, const string& T )
{
  string Str = Source;
  return TrimLeft( TrimRight( Str , T ), T );
}

