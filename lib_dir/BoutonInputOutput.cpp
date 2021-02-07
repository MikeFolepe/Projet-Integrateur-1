/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier BoutonInputOutput.h
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


#include "BoutonInputOutput.h"

///  Fonction qui permet de verifier la validité d'une entrée par le prindipe d'antirebonds
//!\ param pin  une pin de microprocesseur pour la lecture (ex. PIND).
//!\ param position un indice de  broche pour l'écriture (ex. PIND2).
//!\ return un booléen répresentant si  le signal est effectivement valide.
bool readPinDebounce(volatile uint8_t& pin, uint8_t position)
{
    if (pin & (1 << position))  
    {
        _delay_ms(10);
        return (pin & (1 << position));
    }
    return false;
}


///  Fonction qui permet de verifier la validité d'une entrée et 
///  d'envoyer le signal que lorque le bouton-poussoir est relaché.
//!\ param pin  une pin de microprocesseur pour la lecture (ex. PIND).
//!\ param position un indice de  broche pour l'écriture (ex. PIND2).
//!\ return un booléen répresentant si le signal est effectivement valide.
bool pressNRelease(volatile uint8_t& pin, uint8_t position)
{
    bool pushed = false;
    if (readPinDebounce(pin, position))
    {
        pushed = true;
        while (pushed)
        {
            if (readPinDebounce(pin, position))
            {
                pushed = true;
            }
            else
            {
                pushed = false;
            }
        }
        return true;
    }
    return false;
}


///  Fonction qui permet de mettre un port en mode sortie.
//!\ param lettreRegistre  Une lettre représentant une catégorie de port.
void setRegisterOutput(LettreRegistre lettreRegistre)
{
    switch (lettreRegistre)
    {

        case A: DDRA = 0xFF;
        break;
        case B: DDRB = 0xFF;
        break;
        case C: DDRC = 0xFF;
        break;
        case D: DDRD = 0xFF;
        break;

    }
}



///  Fonction qui permet de mettre un port en mode entrée.
//!\ param lettreRegistre  Une lettre représentant une catégorie de port.
void setRegisterInput(LettreRegistre lettreRegistre)
{
    switch (lettreRegistre)
    {

        case A: DDRA = 0x00;
        break;
        case B: DDRB = 0x00;
        break;
        case C: DDRC = 0x00;
        break;
        case D: DDRD = 0x00;
        break;

    }
}


///  Fonction qui permet d'assigner à une broche d'un port une valeur donnée.
//!\ param port  une catégorie de port (ex:PORTA).
//!\ param position un indice de  broche pour l'écriture(ex:PORTA3).
void setSortiePort(volatile uint8_t& port, uint8_t position)
{

    port= (1<< position);
}

