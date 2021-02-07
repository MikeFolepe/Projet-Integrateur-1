/*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent le controle du
 * du timer1 pour la suite de notre projet. Ces fonctions nous permettront d’ajuster le compteur 
 * pour pouvoir l’utiliser de différentes 
 * façons comme par exemple pour la production des signaux PWM pour le contrôle des moteurs etc. 
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


#ifndef TIMER1_H
#define TIMER1_H


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

enum Prescaler 
{
    CLK8=8,
    CLK64=64,
    CLK256=256,
    CLK1024=1024
}; 

enum ModeTimer
{ 
    CTC,
    PHASECORRECT8,
    FASTPWM8
};

enum ModeCompare
{
    SET,
    CLEAR,
    NUL,
    TOOGLE
};

enum ChannelOCR1X
{
    CA,
    CB,
    CAB     //pour les deux channels 
};



/// Fonction qui permet d'arrềter le compteur
void resetCounter1();

/// Fonction qui permet d'arrềter le compteur
void stopTimer(); 

///  Fonction qui permet d'ajuster le prescaler du timer 1 en utilisant le registre TCCR1B 
//!\ param prescaler  un type enum contenant les différents prescalers qu'on veut pour le timer
void setPrescaler( Prescaler prescaler);


///  Fonction qui permet d'ajuster le mode du timer (WaveFormGeneration Mode)
///  parmi trois modes (CTC, PWM Phase correct 8 bit, Fast PWM 8 bit)
///  en utilisant les registres TTCR1B et TCCR1A
//!\ param mode  un type enum contenant les différentrs mode qu'on veut pour le timer
void ajustementModeTimer1 (ModeTimer mode);

///  Fonction qui permet d'ajuster le mode de sortie (CompareOutputMOde)
///  sur les sorties OC1A et OC1B (set ou clear) des pins D4 et D5 
///  dépendamment du Waveform Generation mode actuel du timer1
//!\ param mode   un type enum contenant les différentrs mode que l'on veut pour le timer
//!\ param modeC  un type enum contenant les différentrs 
//!\ modes que l'on veut pour les sorties OC1A et OC1B
void compareOutputMode(ModeTimer mode, ModeCompare modeC);

///  Fonction qui permet de demarrer la minuterie et d'ajuster
///  la valeur maximale du comptage (OCR1A et OCR1B)
//!\ param time  le temps qu'on veut compter
//!\ param channel , le channel qu'on veut utiliser ,
//!\ A , B ou AB pour les deux.(OCR1A, OCR1B)
void startTimer1Count (uint16_t time, ChannelOCR1X channel);

#endif
