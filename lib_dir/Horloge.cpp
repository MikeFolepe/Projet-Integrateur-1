/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier Horloge.h
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


#include "Horloge.h"
#include "RS232.h"

/// Fonction qui permet de reinitialiser l'horloge.
void resetClock()

{
    PORTD = 1 << PORTD0;      
    _delay_ms(100);   
    PORTD = 0 << PORTD0;   

}

/// Fonction permettant de démarrer la clock en la faisant avancer.
void makeclockOn (ModeTimer mode, Prescaler prescaler, ModeCompare modeC)

{
    PWMMateriel( mode,  prescaler,  modeC);
}

/// Fonction permettant de determiner linéairement la valeur de OCR1A.
uint16_t setvalueOCR1A (double voltage )
{

    uint16_t value = (1302/ voltage) -1;

    return value;
}

/// Fonction permettant de mettre l'horloge à l'heure de départ.
void setHeureDepart(uint16_t heureDepart)
{
    for (uint16_t i = 0 ; i < heureDepart; i++)
    {
        PORTD = 1 << PORTD5;       
        _delay_us(50);   
        PORTD = 0 << PORTD5;       
    }
}


///  Fonction qui permet de definir l'heure de départ. 
//!\ param heureDepart  La valeur de l'heure de depart en minutes.
//!\ param tab          Le tableau contenant les données liées à l'heure et des minutes.
bool setClocktime(uint16_t &heureDepart, uint8_t tab[])
{   

    LectureClavier(tab, FORMAT_HEURE);
    
    if(heureValide(tab))
    {
        heureDepart =  tab[0] * 600 + tab[1] * 60 + tab[2] * 10 + tab[3];
        setHeureDepart(heureDepart);

        return true;

    }

    return  false;          

}


/// Fonction qui permet d'afficher le message d'invite de l'option 1.
void affichageMessageInvite()
{
    char messageInvite [] = "\n\nEntrez l'heure et les minutes de depart de la simulation. HHMM\n\n";
    transmissionMessageUSART (messageInvite, sizeof(messageInvite));
}



/// Fonction qui vérifie si l'heure est valide
//!\ param tab  Le tableau contenant les données liées à l'heure et des minutes.
//!\ return     Un booléen true si l'heure est valide sinon false.
bool heureValide(uint8_t tab[])
{
    if(tab[0] <= 1 && tab[1] <= 9 && tab[2] <= 5 && tab[3] <= 9)
    {
        return true;
    }
    else if(tab[0] > 1 && tab[0] <= 2 && tab[1] <= 3 && tab[2] <= 5 && tab[3] <= 9 )
    {
        return true;
    }
    return false;
}


