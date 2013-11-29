/* Ce code est du code personnel d'Anis Benyoub
 * ce sont des macros que j'utilise pour debugger
 */ 

#ifndef COMMON_DEFINES
#define COMMON_DEFINES
#include <iostream>
#include <assert.h>


namespace MathTools
{
        static const double PI = 3.14159265359;
        static const double FULL_ANGLE = 360.0;
}


static int USCREEN_X  = 512;
static int USCREEN_Y  = 287;
static double SCREEN_X  = USCREEN_X*1.0;
static double SCREEN_Y  = USCREEN_Y*1.0;
static double RATIO = SCREEN_X/SCREEN_Y;
 

#define DegreeToRadian(Angle) (Angle*MathTools::PI/MathTools::FULL_ANGLE)
#define foreach(IT,X) for ( typeof( X.begin() ) IT = X.begin(); IT != X.end(); ++IT )
#define tryget(IT,LIST, ELEM) typeof( LIST.begin()) IT = LIST.find(ELEM);

#define DEFAULT_COLOR "\033[0m"
#define RED_COLOR "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define ORANGE_COLOR "\033[0;33m"
#define END_PRINT_COLOR DEFAULT_COLOR<<std::endl

#ifdef RELEASE
#define PRINT_GREEN(stuff)
#define PRINT_ORANGE(stuff) 
#else
#define PRINT_GREEN(stuff) std::cout<<GREEN_COLOR<<stuff<<END_PRINT_COLOR
#define PRINT_ORANGE(stuff)  std::cout<<ORANGE_COLOR<<stuff<<END_PRINT_COLOR
#endif

#define PRINT_RED(stuff) std::cout<<RED_COLOR<<stuff<<END_PRINT_COLOR
#define AssertNotValid(stuff)  PRINT_RED(stuff); assert(false);

#endif //COMMON_DEFINES
