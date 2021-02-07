#include "action_lib.h"



// -------------------------------- CONSTRUCTEUR PAR DÉFAUT --------------------------------------------

Action::Action() 
{
}

// -------------------------------- CONSTRUCTEUR PAR PARAMÈTRES ----------------------------------------
Action::Action(uint8_t action[], uint8_t taille)
{
// ID
    idDispositif_ = action[4];

// ÉTAT
    if(idDispositif_ == 'E' || idDispositif_ == 'F')
    {
        uint8_t multiplicateurEtat = 100;
        for(uint8_t i = (taille - SIZE_ANGLE_SERVO); i < taille; i++)
        {
            etat_ += (action[i] * multiplicateurEtat);
            multiplicateurEtat /= 10;
        }
    }
    else
    {
        etat_ = action[5];
    }


// HEURE (UINT8_T)
    int multiplicateurHeure = 1000;                   
    for(uint8_t i = 0; i < SIZE_FORMAT_HEURE; i++)
    {
        heure_ += (action[i] * multiplicateurHeure);   
        multiplicateurHeure /= 10;
    }

}
// -------------------------------- CONSTRUCTEUR PAR COPIE ----------------------------------------
Action::Action(const Action& action) 
{
    heure_ = action.heure_;
    etat_ = action.etat_;
    idDispositif_ = action.idDispositif_;
}

// -------------------------------- OPERATEUR = ----------------------------------------
Action& Action::operator=(Action& action)
{
    heure_     =  action.heure_;
    idDispositif_ =  action.idDispositif_;
    etat_         =  action.etat_;

    return *this;
}

// -------------------------------- GETTERS ----------------------------------------

const uint16_t& Action::getHeure() const
{
    return heure_;
}
const uint8_t& Action::getIdDispositif() const
{
    return idDispositif_;
}
const uint8_t& Action::getEtat() const
{
    return etat_;
}


// -------------------------------- AJOUTER UNE ACTION ----------------------------------------
bool ajouterAction(Action listeActions[], uint8_t &tailleListe)
{
    char m_programmerAction[] = "\n\nVeuillez programmer une action :\n";
    transmissionMessageUSART(m_programmerAction, sizeof(m_programmerAction));

    uint8_t actionAjoutee[8] = {};                                // Initialise un tableau remplie de 0
    LectureClavier(actionAjoutee, TAILLE_ACTION);

    Action actionProgrammee = Action(actionAjoutee, sizeof(actionAjoutee));
    if(!entreeValideAction(actionAjoutee, actionProgrammee))
    {
        return false;
    }

    listeActions[tailleListe] = actionProgrammee;
    tailleListe++;
    sortActions(listeActions, tailleListe);

    return true;
}

// -------------------------------- SWAP 2 ACTIONS ----------------------------------------
void swap(Action* lhs, Action* rhs)
{
    Action temp(*lhs);
    *lhs = *rhs;
    *rhs = temp;
}

// -------------------------------- SORT LES ACTIONS ----------------------------------------
void sortActions(Action listeActions[], uint8_t taille) // Bubble sort (Source : GeeksForGeeks)
{
    bool swapped;
    for(uint8_t i = 0; i < (taille -1); i++)
    {
        swapped = false;
        for(uint8_t j = 0; j < (taille - i - 1); j++)
        {
            if(listeActions[j].getHeure() > listeActions[j+1].getHeure())
            {
                swap(&listeActions[j], &listeActions[j+1]);
                swapped = true;
            }
        }
        if(!swapped)
        {
            break;
        }
    }
}

// -------------------------------- SUPPRIME UNE ACTION ----------------------------------------
bool SupprimerAction(Action listeActions[], uint8_t &taille)   
{

    char m_supprimerAction[] = "\n\nVeuillez entrer le numero de l'action a supprimer\n";
    transmissionMessageUSART(m_supprimerAction, sizeof(m_supprimerAction));

    uint8_t numeroActionDelete[2];
    LectureClavier(numeroActionDelete, sizeof(numeroActionDelete));

    uint8_t numeroAction = TabToUint8(numeroActionDelete, sizeof(numeroActionDelete));

    if(numeroAction < 1 || numeroAction > taille)  // Si le numéro de l'action est plus petit que 1 ou plus grand que le 
    {                                              // nombre d'actions programmées, il y a erreur.     
        return false;
    }

    for(uint8_t i = (numeroAction - 1); i < (taille - 1); i++)
    {
        listeActions[i] = listeActions[i + 1];
    }
    
    Action actionNulle;
    listeActions[taille - 1] = actionNulle;
    taille--;

    return true;
}

void formatAffichageHeure(char tab[])
{
    
    if(tab[1] == '\0') // 1 -> 00:01
    {
        tab[4] = tab[0];
        tab[3] = '0';
        tab[2] = ':';
        tab[1] = '0';
        tab[0] = '0';
    }
    else if(tab[2] == '\0')  // 30 -> 00:30
    {
        tab[4] = tab[1];
        tab[3] = tab[0];
        tab[2] = ':';
        tab[1] = '0';
        tab[0] = '0';
    }
    else if(tab[3] == '\0')  // 845 -> 08:45
    {
        tab[4] = tab[2];
        tab[3] = tab[1];
        tab[2] = ':';
        tab[1] = tab[0];
        tab[0] = '0';
    }
    else                 // 1231 -> 12:31
    {
        tab[4] = tab[3];
        tab[3] = tab[2];
        tab[2] = ':';
        tab[1] = tab[1];
        tab[0] = tab[0];
    }
}

// -------------------------------- AFFICHE LA LISTE DES ACTIONS ----------------------------------------


void afficherActions(Action listeActions[], uint8_t taille)
{
    char tab[10];
    if(taille == 0)
    {
        char erreur[] = "\n\nIl n'y a aucune action programmee\n";
        transmissionMessageUSART(erreur, sizeof(erreur));
    }

    else
    {
        char affichageActions[] = "\n\nListe d'actions programees :\n";
        transmissionMessageUSART(affichageActions, sizeof(affichageActions));

        for(uint8_t numeroAction = 0; numeroAction < taille; numeroAction++)
        {
            
            // NN
            if(numeroAction < 10)
            {
                transmissionMessageUSART(uint8ToTabChar(tab, 0), 1);  // ???????????????????????????????????????????
                
                transmissionMessageUSART(uint8ToTabChar(tab,(numeroAction + 1)), sizeTabChar(tab));
            }
            else
            {
                transmissionMessageUSART(uint8ToTabChar(tab,(numeroAction + 1)), sizeTabChar(tab));
            }
            
            // HH:MM
            char tiret[] = " - ";
            transmissionMessageUSART(tiret, sizeof(tiret));

            sprintf(tab, "%d", listeActions[numeroAction].getHeure()); 
            formatAffichageHeure(tab);
            transmissionMessageUSART(tab, SIZE_FORMAT_HEURE);

            // Action servomoteur
            if(listeActions[numeroAction].getIdDispositif() == 'E' || listeActions[numeroAction].getIdDispositif() == 'F')
            {
                char actionServomoteur[] = " - orienter servomoteur ";
                transmissionMessageUSART(actionServomoteur, sizeof(actionServomoteur));

                transmissionUSART(listeActions[numeroAction].getIdDispositif());

                char a[] = " a ";
                transmissionMessageUSART(a, sizeof(a));

                transmissionMessageUSART(uint8ToTabChar(tab, listeActions[numeroAction].getEtat()), SIZE_ANGLE_SERVO);
                
                char degres[] = " degres\n";
                transmissionMessageUSART(degres, sizeof(degres));

            }
            // Action porte
            else
            {
                if(listeActions[numeroAction].getEtat())
                {
                    char fermer[] = " - fermer porte ";
                    transmissionMessageUSART(fermer, sizeof(fermer));
                }
                else
                {
                    char ouvrir[] = " - ouvrir porte ";
                    transmissionMessageUSART(ouvrir, sizeof(ouvrir));
                }
                transmissionUSART(listeActions[numeroAction].getIdDispositif());
                transmissionUSART('\n');
            }
        }
    }   
}

bool entreeValideAction(uint8_t actionTab[], Action action)
{

    if(heureValide(actionTab))
    {
        if(action.getIdDispositif() >= 'A' && action.getIdDispositif() <= 'D')
        {
            if (action.getEtat() > 1)
            {   
                return false;
            }
            return true;
        }
        else if(action.getIdDispositif() >= 'E' && action.getIdDispositif() <= 'F')
        {
            if (action.getEtat() > 180)
            {
                return false;
            }
            return true;
        }
    }
    return  false;  
}
