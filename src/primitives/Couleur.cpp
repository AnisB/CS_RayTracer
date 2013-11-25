#include "Couleur.h"

/// Conversion d'une couleur float à ubyte
const float  CCouleur::UBYTE_2_FLOAT = 1.0f / 255.0f;
/// Constante de couleur NOIRE
const CCouleur CCouleur::NOIR        = CCouleur( 0.0f );
/// Constante de couleur BLANCHE
const CCouleur CCouleur::BLANC       = CCouleur( 1.0f );