/*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent la génération 
 * d'un signal PWM avec ou sans 
 * l'utilisation des périphériques du microcontroleur ATMega324PA d'Atmel.
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



#ifndef PWM_H
#define PWM_H 


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "BoutonInputOutput.h"
#include "Timer1.h"


///  Méthode qui configure  la durée d'un délai 
//!\ param n  variable double qui représente le délai en ms
void delay_ms(double n);

///  Methode qui configure  la durée d'un délai 
//!\ param frequence  variable double qui représente la fréquence du signal PWM en kHz
double calculPeriode(double frequence);

///  Méthode qui configure la vitesse du moteur (des roues) via un signal PWM logiciel 
//!\ param frequence  double qui représente la fréquence du signal PWM en GHz
//!\ param a          double qui représente le "duty cycle", i.e. la durée (en pourcentage) du "rising edge" du signal PWM
//!\ param delay      double qui représente un délai
//!\ on est contraint d'utiliser le port B pour la sortie du PWN logiciel
void reglageVitesse(double frequence, double a, double delay);

///  Méthode qui configure la vitesse du moteur (des roues) via un signal PWM matériel 
//!\ param mode          volatile qui représente le mode du timer 1
//!\ param prescaler     volatile qui représente le "prescaler", i.e. division d'horloge, pour le PWM
//!\ param modeC         volatile qui ajuste le mode de TCCR1B 
//!\ et nous contraint a utiliser le port B pour la sortie du PWN logiciel
void PWMMateriel(ModeTimer mode, Prescaler prescaler, ModeCompare modeC);


#endif
