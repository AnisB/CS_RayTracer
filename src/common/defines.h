/* Ce code est du code personnel d'Anis Benyoub
 * ce sont des macros que j'utilise pour debugger
 */ 

#ifndef COMMON_DEFINES
#define COMMON_DEFINES
#include <iostream>


#define foreach(IT,X) for ( typeof( X.begin() ) IT = X.begin(); IT != X.end(); ++IT )
#define tryget(IT,LIST, ELEM) typeof( LIST.begin()) IT = LIST.find(ELEM);


#define DEFAULT_COLOR "\033[0m"
#define RED_COLOR "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define ORANGE_COLOR "\033[0;33m"

#define PRINT_RED std::cout<<RED_COLOR
#define PRINT_GREEN std::cout<<GREEN_COLOR
#define PRINT_ORANGE std::cout<<ORANGE_COLOR
#define END_PRINT_COLOR DEFAULT_COLOR<<std::endl


namespace MathTools
{
        static const double PI = 3.14159265359;
        static const double FULL_ANGLE = 360.0;
}


#endif //COMMON_DEFINES
