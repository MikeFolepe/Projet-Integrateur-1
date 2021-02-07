 /*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent le controle de 
 * l'horloge, sa reinitialisation ainsi que  vitessse d'avancement.
 * 
 * 
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique et genie logiciel
 * Cours : inf1900
 *
 * Etienne Chevalier-Tittley, Paul-Marie Akoffodji,
 * Mike-Davy Folepe, Jean-Marc Ndong Ékouaga
 * 
 * Date : 2020-12-07
 *
 * Code qui n'est sous aucune license.
 *
 */


#ifndef HORLOGE_H
#define HORLOGE_H 


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "BoutonInputOutput.h"
#include "Timer1.h"
#include "PWM.h"
#include "clavier_lib.h"
#include "RS232.h"

const uint16_t FORMAT_HEURE  = 4;



/// Fonction qui permet de reinitialiser l'horloge. 
void resetClock();


/// Fonction permettant de démarrer la clock en la faisant avancer.
void makeclockOn (ModeTimer mode, Prescaler prescaler, ModeCompare modeC);


/// Fonction permettant de determiner linéairement la valeur de OCR1A.
uint16_t setvalueOCR1A (double voltage);


/// Fonction permettant de mettre l'horloge à l'heure de départ.
void setHeureDepart(uint16_t heureDepart);


///  Fonction qui permet de definir l'heure de départ 
//!\ param heureDepart  La valeur de l'heure de depart en minutes.
//!\ param tab          Le tableau contenant les données liées à l'heure et des minutes.
bool setClocktime (uint16_t &heureDepart, uint8_t tab[]);


/// Fonction qui permet d'afficher le message d'invite de l'option 1
void  affichageMessageInvite();


/// Fonction qui vérifie si l'heure est valide
//!\ param tab  Le tableau contenant les données liées à l'heure et des minutes.
//!\ return     Un booléen true si l'heure est valide sinon false.
bool heureValide(uint8_t tab[]);

#endif
