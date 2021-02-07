#include "barresDEL.h"
#include "ServoMoteur.h"
#include "clavier_lib.h"


///  Fonction qui permet d'identifier les informations entrees au clavier
//!\ param tab          le tableau qui contient les information sur les portes (A-F) et les états(0,1) ou (0-180)
void identificationPortes(uint8_t tab[]);

/// Fonction qui permet de vérfier si les entrée au clavier pour l'option 2 est valide
//!\ param tab          le tableau qui contient les information sur les portes (A-F) et les états(0,1) ou (0-180)
bool entreeValideServoPorte(uint8_t tab[]);

/// Fonction qui permet de faire ce qui est demandé pour l'option 2 
/// elle utilise les fonctions déclarées ci dessus 
/// elle sera directement appelé dans le main du projet
bool configurerOption2();