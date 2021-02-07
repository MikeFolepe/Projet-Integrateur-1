#include "Tableaux.h"

char* uint8ToTabChar(char tab[], uint8_t value)
{
    sprintf(tab, "%d", value);
    return tab;
}

uint8_t sizeTabChar(char tab[])
{
    uint8_t taille = 0;
    
    while(tab[taille] != 0)
    {
        taille++;
    }
    
    return taille;
}

uint8_t TabToUint8(uint8_t tab[], uint8_t taille)
{
    uint8_t value = 0;
    uint8_t multiplicateur = pow(10, (taille - 1));    

    for(uint8_t i = 0; i < taille; i++)
    {
        value += (tab[i] * multiplicateur);
        multiplicateur /= 10;
    }
    return value;
}
