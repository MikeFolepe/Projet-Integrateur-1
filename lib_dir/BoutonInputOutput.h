/*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent le controle du
 * vérifier la validité d’un signal par scrutation avec l’antirebonds et de mettre en mode entrée ou sortie 
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


#ifndef BOUTONINPUTOUTPUT_H
#define BOUTONINPUTOUTPUT_H 



#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

enum LettreRegistre
{
    A,
    B,
    C,
    D,
};

///  Fonction qui permet de verifier la validité d'une entrée par le prindipe d'anti-rebonds
//!\ param pin  une pin de microprocesseur pour la lecture (ex. PIND).
//!\ param position un indice de  broche pour l'écriture (ex. PIND2).
//!\ return un booléen répresentant si  le signal est effectivement valide.
bool readPinDebounce(volatile uint8_t& pin , uint8_t position);


///  Fonction qui permet de verifier la validité d'une entrée et 
///  d'envoyer le signal que lorque la bouton-poussoir est relachée.
//!\ param pin  une pin de microprocesseur pour la lecture (ex. PIND).
//!\ param position un indice de  broche pour l'écriture (ex. PIND2).
//!\ return un booléen répresentant si le signal est effectivement valide.
bool pressNRelease(volatile uint8_t& pin, uint8_t position);


///  Fonction qui permet de mettre un port en mode sortie.
//!\ param lettreRegistre  Une lettre représentant une catégorie de port.
void setRegisterOutput(LettreRegistre lettreRegistre);


///  Fonction qui permet de mettre un port en mode entrée.
//!\ param lettreRegistre  Une lettre représentant une catégorie de port.
void setRegisterInput(LettreRegistre lettreRegistre);


///  Fonction qui permet d'assigner à une broche d'un port une valeur donnée.
//!\ param port  une catégorie de port (ex:PORTA).
//!\ param position un indice de  broche pour l'écriture(ex:PORTA3).
void setSortiePort(volatile uint8_t& port,  uint8_t position); 


#endif
