/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier Interruption.h
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



#include"Interruption.h"


///  Fonction qui permet d'initialiser les registres pour une interruption sur un bouton spécifique
//!\ param bouton , le bouton sur lequel on veut activiter l'interruption (type enum)
void intialisationBoutonInterrupt(BoutonInterrupt bouton) 
{

     // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontroleur n'est pas prêt...
    cli();      

    switch(bouton) 
    {
        

        case D2:

             // cette procédure ajuste le registre EIMSK

            // de l’ATmega324PA pour permettre les interruptions externes

            EIMSK |= (1 << INT0);

            // il faut sensibiliser les interruptions externes aux

            // changements de niveau du bouton-poussoir

            // en ajustant le registre EICRA
            EICRA |= (0 << ISC00);
            EICRA |= (1 << ISC01);
            break;
        
        case D3:
            EIMSK |= (1 << INT1);
            EICRA |= (0 << ISC10);
            EICRA |= (1 << ISC11);
            break;




    }

    sei();
}

///  Fonction qui permet d'activer l'interruption sur le timer1
void intialisationTimer1Interrupt()
{

    TIMSK1 = (1 << OCIE1A);
}
