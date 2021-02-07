#include "Option2.h"
#include "can.h"
#include "Horloge.h"
#include "action_lib.h"

enum Etat
{
    configuration,
    simulation
};


void minutesToTimeFormat(double compteurTemps, uint16_t& time);

void remplirFileAttente(uint16_t time, uint8_t& tailleFileAttente, Action fileAttenteActions[], uint8_t& tailleListe, Action listeActions[]);

void executerActions(uint8_t& nbActionsExecutees, uint8_t& tailleFileAttente, Action fileAttenteActions[]);

void messageErreur();
