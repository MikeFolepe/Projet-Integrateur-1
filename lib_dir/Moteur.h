/*
 * Fichier d'en-tête contenant les signatures des fonctions qui permettent le controle du
 * sens du mouvement des moteurs, et des roues du robot, dépendamment de
 * la façon dont le signal PWM est genere (logicielle, ou matériel, i.e
 * avec timer)
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


#ifndef MOTEUR_H
#define MOTEUR_H 



#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


/// PWM logiciel
/// Methode qui configure le sens du mouvement roues afin que le robot avance (avec signal PMW logiciel)
void directionAvant();

///  Methode qui configure le sens du mouvement roues afin que le robot recule (avec signal PMW logiciel)
void directionArriere();


/// PWM avec timer
/// Methode qui configure le sens du mouvement roues afin que le robot avance (avec signal PMW matériel)
void avancer();

/// Methode qui configure le sens du mouvement roues afin que le robot recule (avec signal PMW matériel)
void reculer();

#endif
