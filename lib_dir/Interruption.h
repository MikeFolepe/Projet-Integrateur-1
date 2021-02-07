/*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent 
 * dmanipuler les interruptions liées à des pin spécifiques de l’ATMEGA.
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



#ifndef INTERRUPTION_H
#define INTERRUPTION_H 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum BoutonInterrupt
{
    D2,
    D3,
};


///  Fonction qui permet d'initialiser les registres pour une interruption sur un bouton spécifique
//!\ param bouton , le bouton sur lequel on veut activiter l'interruption (type enum)
void intialisationBoutonInterrupt(BoutonInterrupt bouton);


///  Fonction qui permet d'activer l'interruption sur le timer1
void intialisationTimer1Interrupt();


#endif
