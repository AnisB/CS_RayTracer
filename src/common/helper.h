/* 
 * Auteur Anis Benyoub
 * Petit fichier qui regroupe quelques fonctions d'aide au développment
 *
 */
#ifndef HELPER_COMMON
#define HELPER_COMMON

#include <string>
#include <vector>

// Fonction qui remplace toutes les strings parBase trouvée dans la string parReplace
std::string replaceAll(const std::string& parString, const std::string& parBase, const std::string& parReplace);

// Fonction qui split  la string parString avec parSeparator et renvoi un vector des string resultantes
std::vector<std::string> split(const std::string& parString, char parSeparator);

// Conction qui convertir une string en int
int convertToInt(const std::string& parToConvert);

#endif // HELPER_COMMON
