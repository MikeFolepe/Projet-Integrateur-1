/*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent 
 * de manipuler à notre guise la DEL avec des couleurs différentes et de déléguer 
 * cela à des ports de notre choix.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique et genie logiciel
 * Cours : inf1900
 *
 * Etienne Chevalier-Tittley, Paul-Marie Akoffodji,
 * Mike-Davy Folepe, Jean-Marc Ndong Ékouaga
 * 
 * Date : 2020-11-03
 *
 * Code qui n'est sous aucune license.
 *
 */



#ifndef DEL_H
#define DEL_H 


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "BoutonInputOutput.h"

enum Couleur    
{
    VERT,
    ROUGE,
    AMBRE,
};

///  Fonction qui permet d'allumer une DEL avec une  couleur verte, rouge
///  ou ambre sur une broche d'un port.
//!\ param port  une catégorie de port.
//!\ param position1 le premier  indice de  broche pour l'écriture.
//!\ param position2 le deuxieme indice de  broche pour l'écriture.
//!\ param couleur  la couleur de DEL désirée.
void allumerDEL(volatile uint8_t& port, uint8_t position1, uint8_t position2, Couleur couleur);

#endif