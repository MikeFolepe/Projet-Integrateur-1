#include "clavier_lib.h"


void LectureClavier(uint8_t tab[], uint8_t nbCaracteres)
{
    //DDRC = (0 << DDC5);
    
    char tabAffichage[10];
    uint8_t caracteresLus = 0;
    uint8_t nbCharAttendus = nbCaracteres;
    bool appuye = false;

    uint8_t numPad[] = {0,   1,   2,   3, 
                        4,   5,   6,   7, 
                        8,   9,  'A', 'B', 
                       'C', 'D', 'E', 'F'};
    
    while(caracteresLus != nbCharAttendus)
    {
        PORTC = (1 << PORTC4);                // Alimente les colonnes

        if((tab[0] == 'E' || tab[0] == 'F') && nbCaracteres == 2)  // A1 ou E000
        {
            nbCharAttendus = nbCaracteres + 2;
        }
        
        if((tab[4] == 'E' || tab[4] == 'F') && nbCaracteres == 6)  // 0000A1 ou 0000E000
        {
            nbCharAttendus = nbCaracteres + 2;
        }
        
        

        for(uint8_t i = 0; i < (NB_COLONNES * NB_RANGEES); i++)
        {
            _delay_ms(10);                    // Delay entre la scrutation de chaque élément du clavier
            if(PINC & (1 << PINC5))
            {
                _delay_ms(10);                // Anti rebond 

                if(PINC & (1 << PINC5))
                {
                    appuye = true;            // Clavier est appuyé
                    while (appuye)            // Tant qu'il n'est pas relaché, on loop infiniment
                    {
                        if (!(PINC & (1 << PINC5)))     // Il est relaché
                        {
                            appuye = false;
                        }
                    }
                    tab[caracteresLus] = numPad[i];
                    caracteresLus++;
                    if(numPad[i] < 'A')
                    {
                        transmissionMessageUSART(uint8ToTabChar(tabAffichage, numPad[i]), 2);  // On affiche le caractère appuyé sur le clavier 
                        transmissionUSART(' ');                                                           // suivi d'une espace.
                    }
                    else
                    {
                        transmissionUSART(numPad[i]);
                        transmissionUSART(' ');
                    }          

                }
            }
            PORTC++;
        }
    }    
}
