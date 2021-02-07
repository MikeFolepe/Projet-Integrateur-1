#include "Projet.h"


void minutesToTimeFormat(double compteurTemps, uint16_t& time)
{
    uint8_t heure = (compteurTemps / 60);
    uint8_t minute = compteurTemps - (heure * 60);
    time = (heure * 100) + minute;
}

void remplirFileAttente(uint16_t time, uint8_t& tailleFileAttente, Action fileAttenteActions[], uint8_t& tailleListe, Action listeActions[])
{
    for(uint8_t i = tailleFileAttente; i < tailleListe; i++)
    {
        if(listeActions[i].getHeure() <= time)
        {
            fileAttenteActions[tailleFileAttente] = listeActions[i];
            tailleFileAttente++;
        }
    }
}

void executerActions(uint8_t& nbActionsExecutees, uint8_t& tailleFileAttente, Action fileAttenteActions[])
{
    for(uint8_t i = nbActionsExecutees; i < tailleFileAttente; i++)
    {
        if(fileAttenteActions[i].getIdDispositif() == 'E')
        {
            pwmTimer2InitForSErvo(PorteServo::E, fileAttenteActions[i].getEtat());
            nbActionsExecutees++;
        }
                    
        else if(fileAttenteActions[i].getIdDispositif() == 'F')
        {
            pwmTimer2InitForSErvo(PorteServo::F, fileAttenteActions[i].getEtat());
            nbActionsExecutees++;
        }
        else
        {
            changerEtatsPorte(fileAttenteActions[i].getIdDispositif(), fileAttenteActions[i].getEtat());
            nbActionsExecutees++;
        }
                 
    }
}

void messageErreur()
{
    char messageInvalide[] = "\n\nInformations invalides\n";
    transmissionMessageUSART(messageInvalide, sizeof(messageInvalide));
}
