/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier Moteur.h
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
#include "Moteur.h"

/// PWM logiciel

/// Methode qui configure le sens du mouvement roues afin que le robot avance (avec signal PMW logiciel)
void directionAvant()
{
    PORTB = 1 << PORTB1;
}

///  Methode qui configure le sens du mouvement roues afin que le robot recule (avec signal PMW logiciel)
void directionArriere()
{
    PORTB = 0 << PORTB1;
}

/// PWM avec timer

/// Methode qui configure le sens du mouvement roues afin que le robot avance (avec signal PMW matériel)
void avancer()
{
    PORTD = (0 << PORTD6 | 1<<PORTD3);

}

/// Methode qui configure le sens du mouvement roues afin que le robot recule (avec signal PMW matériel)
void reculer()
{
    PORTD = (1 << PORTD6| 0<<PORTD3);
}
