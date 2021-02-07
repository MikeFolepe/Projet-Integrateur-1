#define F_CPU 8000000

#include <stdint.h>
#include <stdio.h>

#include "Horloge.h"

const int SIZE_FORMAT_HEURE = 5;
const int SIZE_ANGLE_SERVO = 3;

const uint8_t TAILLE_ACTION = 6;         // Nombre de caractères pour programmer une action

class Action
{
public:
// CONSTRUCTEUR PAR DÉFAUT

    Action();

// CONSTRUCTEUR PAR PARAMÈTRES 
    Action(uint8_t action[], uint8_t taille);


// CONSTRUCTEUR PAR COPIE
    Action(const Action& action); 
   
// OPERATEUR =
    Action& operator=(Action& action);
   

// GETTERS 
    const uint16_t& getHeure() const;
   
    const uint8_t& getIdDispositif() const;
   
    const uint8_t& getEtat() const;
 

// ATTRIBUTS 
private:

    uint16_t heure_ = 0;
    uint8_t idDispositif_ = 0;
    uint8_t etat_ = 0;
};

bool ajouterAction(Action listeActions[], uint8_t &tailleListe);

void swap(Action* lhs, Action* rhs);

void sortActions(Action listeActions[], uint8_t taille);

bool SupprimerAction(Action listeActions[], uint8_t &taille);

void formatAffichageHeure(char tab[]);

void afficherActions(Action listeActions[], uint8_t taille);

bool entreeValideAction(uint8_t actionTab[], Action action);

