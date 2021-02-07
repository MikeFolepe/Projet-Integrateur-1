/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier PWM.h
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
#include "PWM.h"

///  Méthode qui configure  la durée d'un délai 
//!\ param n  variable double qui représente le délai en ms
void delay_ms(double n)
{
    while (n > 0)
    {
        _delay_ms(1);
        n--;
    }
}

///  Méthode qui configure  la durée d'un délai 
//!\ param frequence  variable double qui représente la fréquence du signal PWM en kHz
double calculPeriode(double frequence)
{
    double r;
    r = ((1 / frequence) * 1000);
    return r;
}

///  Méthode qui configure la vitesse du moteur (des roues) via un signal PWM logiciel 
//!\ param frequence  double qui représente la fréquence du signal PWM en GHz
//!\ param a          double qui représente le "duty cycle", i.e. la durée (en pourcentage) du "rising edge" du signal PWM
//!\ param delay      double qui représente un délai
//!\ on est contraint d'utiliser le port B pour la sortie du PWN logiciel
void reglageVitesse(double frequence, double a, double delay)
{
    double periode = calculPeriode(frequence);
    double rep = delay / periode;

    for (double i = 0; i < rep; i++)
    {
        PORTB = 0 << PORTB0;
        delay_ms(periode * (1 - a));
        PORTB = 1 << PORTB0;
        delay_ms(periode * a);
    }
}

///  Méthode qui configure la vitesse du moteur (des roues) via un signal PWM matériel 
//!\ param mode          volatile qui représente le mode du timer 1
//!\ param prescaler     volatile qui représente le "prescaler", i.e. division d'horloge, pour le PWM
//!\ param modeC         volatile qui ajuste le mode de TCCR1B 
//!\ et nous contraint a utiliser le port B pour la sortie du PWN logiciel
void PWMMateriel(ModeTimer mode, Prescaler prescaler, ModeCompare modeC)
{
    resetCounter1();

    setPrescaler(prescaler);

    ajustementModeTimer1(mode);

    compareOutputMode(mode, modeC);

    TCCR1C = 0;
}
